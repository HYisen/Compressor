#include <string>
#include <vector>
#include <algorithm>

#include "bwt.h"
#include "tree.h"

void bwt::encode(std::istream & is, std::ostream & os)
{
    using std::vector;
    using std::cout;
    using std::ends;
    using std::endl;

    vector<Symbol> data;
    Symbol input{ 0 };
    while (is >> input)
    {
        data.push_back(input);
    }
    //Waring, the previous code is copied from huffman.cpp,
    //because of the slightly modification, the method hasn't been abstracted yet,
    //it should be under consideration if the code is used one more time.
    for (auto ch : data)
    {
        cout << ch << ends;
    }
    cout << endl;
    vector<vector<Symbol>> matrix;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
        cout << "it = " << *it << endl;
        vector<Symbol> rotated(data.size());
        std::rotate_copy(data.cbegin(), it, data.cend(), rotated.begin());
        matrix.push_back(std::move(rotated));
    }
    cout << "\nrotated matrix" << endl;
    for (auto str : matrix)
    {
        for (auto ch : str)
        {
            cout << ch << ends;
        }
        cout << endl;
    }
    std::sort(matrix.begin(), matrix.end(),
        [](const vector<Symbol> &lhs, const vector<Symbol> &rhs)
    {return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()); });
    cout << "\nsorted matrix" << endl;
    for (auto str : matrix)
    {
        for (auto ch : str)
        {
            cout << ch << ends;
        }
        cout << endl;
    }
    for (auto str : matrix)
    {
        os << str.back();
    }
    //A poor simulation, further optimizaion based on ptr rather than matrix should be applied later.
}

void bwt::decode(std::istream & is, std::ostream & os)
{
}
