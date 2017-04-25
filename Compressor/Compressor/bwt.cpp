#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "bwt.h"
#include "tree.h"

void printMatrix(std::vector<std::vector<Symbol>> orig)
{
    for (auto str : orig)
    {
        for (auto ch : str)
        {
            if (ch == Symbol::signal())
            {
                //ch is pass by ref, doesn't really change the value.
                ch = Symbol{ '|' };
            }
            std::cout << ch << std::ends;
        }
        std::cout << std::endl;
    }
}

void bwt::encode(std::istream & is, std::ostream & os)
{
    using std::vector;
    using std::cout;
    using std::ends;
    using std::endl;

    vector<Symbol> data=readAll(is);
    data.push_back(Symbol::signal());

    vector<vector<Symbol>> matrix;
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
        //cout << "it = " << *it << endl;
        decltype(matrix)::value_type rotated(data.size());
        std::rotate_copy(data.cbegin(), it, data.cend(), rotated.begin());
        matrix.push_back(std::move(rotated));
    }

    cout << "\nrotated matrix" << endl;
    printMatrix(matrix);

    std::sort(matrix.begin(), matrix.end(),
        [](const decltype(matrix)::value_type &lhs, const decltype(matrix)::value_type &rhs)
    {return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()); });

    cout << "\nsorted matrix" << endl;
    printMatrix(matrix);

    for (auto str : matrix)
    {
        os << str.back();
    }

    //A poor simulation, further optimizaion based on ptr rather than matrix should be applied later.
}

void bwt::decode(std::istream & is, std::ostream & os)
{
    auto data = readAll(is);
    using std::vector;
    using std::cout;
    using std::endl;

    vector<vector<Symbol>> matrix;
    std::generate_n(std::back_inserter(matrix), data.size(),
        [size = data.size()](){return std::move(vector<Symbol>(size)); });
    auto i = data.size();
    do
    {
        --i;
        //insert column
        for (decltype(data.size()) j = 0; j != data.size(); ++j)
        {
            matrix.at(j).at(i) = data.at(j);
        }

        cout << "\ncountdown " << i << " matrix" << endl;
        printMatrix(matrix);

        //sort row
        std::sort(matrix.begin(), matrix.end(),
            [](const decltype(matrix)::value_type &lhs, const decltype(matrix)::value_type &rhs)
        {return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()); });
    } while (i != 0);

    cout << "\nfinal matrix" << endl;
    printMatrix(matrix);

    auto rtn= *(std::find_if(matrix.cbegin(), matrix.cend(),
        [](const decltype(matrix)::value_type &str) {return str.back() == Symbol::signal(); }));
    rtn.pop_back();//remove the EOF signal added in encode()
    for (auto sym : rtn)
    {
        os << sym;
    }
}
