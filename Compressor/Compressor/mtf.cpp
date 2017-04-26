#include <algorithm>

#include "mtf.h"
#include "tree.h"

void printDict(const mtf::dict_type &orig)
{
    for (auto it = orig.cbegin(); it != orig.cend(); ++it)
    {
        std::cout << (it - orig.cbegin()) << " = " << *it << std::endl;
    }
}

void mtf::encode(std::istream & is, std::ostream & os, mtf::dict_type & dict)
{
    using std::cout;
    using std::endl;

    auto data = readAll(is);

    for (auto sym : data)
    {
        cout << "\ninput " << sym << endl;
        printDict(dict);
        
        //index-based solution
        //find & output index
        decltype(dict.size()) k = 0;
        for (; k != dict.size(); ++k)
        {
            if (dict.at(k) == sym)
            {
                break;
            }
        }
        if (k == dict.size())
        {
            dict.push_back(sym);
        }
        //formatted output for clarity in debug
        os << k << std::ends;
        //writeBinary(os, k);
        cout << "output " << k << endl;

        //modify the dictionary
        if (k != 0)
        {
            dict.push_front(dict.at(k));
            dict.erase(dict.cbegin() + k + 1);
        }
        
        /*
        //iterator-based solution
        //find & output index
        auto it = std::find(dict.cbegin(), dict.cend(), sym);
        if (it == dict.cend())
        {
            dict.push_back(sym);
            it = dict.cend()-1;
            //since the container has changed, iterator is no longer available,
            //although if it is index-based, it is still usable.
        }
        auto diff = it - dict.cbegin();
        //formatted output for clarity in debug
        os << diff << std::ends;
        //writeBinary(os, diff);
        cout << "output " << diff << endl;

        //modify the dictionary
        if (diff != 0)
        {
            auto temp = *it;
            dict.erase(it);
            dict.push_front(temp);
        }
        */
    }
}

void mtf::decode(std::istream & is, std::ostream & os, mtf::dict_type & dict)
{
}