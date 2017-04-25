#include "tree.h"

std::ostream & operator<<(std::ostream & os, const Symbol & orig)
{
    os << static_cast<char>(orig.content);
    return os;
}

std::istream & operator>>(std::istream & is, Symbol & orig)
{
    is >> std::noskipws >> orig.content;
    //std::cout << "read " << orig.content<<" = "<<static_cast<int>(orig.content)<< std::endl;
    //unchecked if the input is successful
    return is;
}

bool operator<(const Symbol & lhs, const Symbol & rhs)
{
    return lhs.content < rhs.content;
}

bool operator==(const Symbol & lhs, const Symbol & rhs)
{
    return lhs.content==rhs.content;
}

std::vector<Symbol> readAll(std::istream & is)
{
    std::vector<Symbol> rtn;
    Symbol input{ 0 };
    //It's formated input rather than the binary one, should it?
    while (is >> input)
    {
        rtn.push_back(input);
    }
    return rtn;
}

std::ostream & operator<<(std::ostream & os, const Item &orig)
{
    os << "{\"isFinal\":" << orig.isFinal <<
        ",\"symbol\":\"" << orig.symbol <<
        "\",\"weight\":" << orig.weight << "}";//JSON
    return os;
}

std::ostream & writeBinary(std::ostream & os, const Cell & orig)
{
    writeBinary(os, orig.sym);
    writeBinary(os, orig.l);
    writeBinary(os, orig.r);
    //std::cout << "save " << orig.sym << " l=" << orig.l << " r=" << orig.r << std::endl;
    return os;
}

std::istream & readBinary(std::istream & is, Cell & orig)
{
    readBinary(is, orig.sym);
    readBinary(is, orig.l);
    readBinary(is, orig.r);
    //std::cout << "load " << orig.sym<<" l="<<orig.l<<" r="<<orig.r<<std::endl;
    return is;
}

size_t install(const std::unique_ptr<Node>& node, std::vector<Cell>& container)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        size_t index = container.size();
        container.push_back(Cell{ node->item.symbol, index, index });
        container.at(index).l = install(node->l, container);
        container.at(index).r = install(node->r, container);
        return index;
    }
}


std::unique_ptr<Node> construct(const Cell & orig, const std::vector<Cell>& container)
{
    //std::cout << "alpha construct " << orig.sym << std::endl;
    if (orig.l == 0 && orig.r == 0)//which means isFinal == true;
    {
        //std::cout << "omega construct " << orig.sym << std::endl;
        return std::make_unique<Node>(Item{ -1,orig.sym });
    }
    else
    {
        auto rtn = std::make_unique<Node>(Item{ -1 });
        if (orig.l != 0)
        {
            (rtn->l) = construct(container.at(orig.l), container);
        }
        if (orig.r != 0)
        {
            (rtn->r) = construct(container.at(orig.r), container);
        }

        //I give up to simplfy the two similar procedure
        //through use index rather than const & to stands orig
        //and validate the index at the very beginning of the function

        //std::cout << "omega construct " << orig.sym << std::endl;
        return std::move(rtn);
    }
}

Symbol &Symbol::operator=(const Symbol &orig)
{
    content = orig.content;
    return *this;
}

Symbol Symbol::signal()
{
    return Symbol{'\003'};
}

