#include <map>
#include <list>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>

#include "huffman.h"


void Coder::sample(std::istream & is)
{
    using std::cout;
    using std::endl;
    using std::setw;
    using std::unique_ptr;
    using std::make_unique;

    static auto pNodeComp = [](const unique_ptr<Node> &lhs, const  unique_ptr<Node> &rhs)
    {return lhs->item.weight < rhs->item.weight; };

    std::map<Symbol, int> stats;
    std::vector<Symbol> data;
    Symbol input{ 0 };
    while (is >> input)
    {
        ++(stats[input]);
        data.push_back(input);
    }
    /*
    cout << "\nstatictics" << endl;
    for (auto one : stats)
    {
    cout << setw(4) << one.second << " [" << one.first << "]" << endl;
    }
    */
    std::list<unique_ptr<Node>> stack;
    for (auto one : stats)
    {
        stack.push_back(make_unique<Node>(Item{ one.second, one.first }));
    }
    stack.sort(pNodeComp);

    unique_ptr<Node> l, r, p;
    while (stack.size()>1)
    {
        /*
        cout << "\ncurrent stack" << endl;
        for (auto &one : stack)
        {
        cout << (*one).item << endl;
        }
        */
        //It would be quite difficult to combine the pop procedure because of rvalue.
        l = std::move(stack.front());
        stack.pop_front();

        r = std::move(stack.front());
        stack.pop_front();

        p = make_unique<Node>(Item{ l->item.weight + r->item.weight });
        p->l = std::move(l);
        p->r = std::move(r);
        /*
        cout
        << "\tinsert " << p->item
        << "\n\t l  =  " << p->l->item
        << "\n\t r  =  " << p->r->item
        << endl;
        */
        //Searching from lowest or highest, which would be faster, that's a question.
        auto it = std::lower_bound(stack.cbegin(), stack.cend(), p, pNodeComp);
        stack.insert(it, std::move(p));
    }

    assert(stack.size() == 1);
    tree = std::move(stack.back());
}

void Coder::encode(std::istream & is, std::ostream & os)
{
    using std::cout;
    using std::endl;
    using std::setw;
    using std::unique_ptr;
    using std::make_unique;
    using std::flush;

    std::map<Symbol, std::vector<bool>> codebook;
    record(tree, std::vector<bool>(), codebook);

    cout << "\ncodebook" << endl;
    for (auto one : codebook)
    {
        cout << one.first << " = ";
        for (bool bit : one.second)
        {
            cout << static_cast<int>(bit);
        }
        cout << endl;
    }

    //Maybe I should use sth else to store a 8-bit struct.
    unsigned char byte{};
    constexpr int SIZE = sizeof(byte) * 8;
    int cnt = SIZE;
    cout << "count = " << cnt << endl;
    Symbol input{ 0 };
    while (is >> input)
    {
        //If the input is not in the tree, an Exception shall be throwed.
        for (auto bit : codebook.at(input))
        {
            byte <<= 1;
            byte += bit;
            if ((--cnt) == 0)
            {
                cnt = SIZE;
                os << byte;
                cout << " put " << std::hex << static_cast<int>(byte) << endl;;
            }
        }
    }
    if (cnt != SIZE)
    {
        byte <<= cnt;
        os << byte;
        cout << " put " << std::hex << static_cast<int>(byte) << endl;;
    }
}

void Coder::decode(std::istream & is, std::ostream & os)
{
}

void Coder::record(const std::unique_ptr<Node>& node, std::vector<bool>& trace, std::map<Symbol, std::vector<bool>>& codebook)
{
    if (node->item.isFinal)
    {
        codebook.emplace(node->item.symbol, trace);
    }
    else
    {
        auto traceCopy = std::vector<bool>(trace);
        traceCopy.push_back(false);
        record(node->l, traceCopy, codebook);
        trace.push_back(true);
        record(node->r, trace, codebook);
    }
}
