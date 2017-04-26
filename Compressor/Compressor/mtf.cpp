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

inline void moveToFront(mtf::dict_type::size_type index, mtf::dict_type & container)
{
    if (index != 0)
    {
        container.push_front(container.at(index));
        container.erase(container.cbegin() + index + 1);
    }
}

void mtf::encode(std::istream & is, std::ostream & os, mtf::dict_type & dict)
{
    using std::cout;
    using std::endl;

    auto data = readAll(is);

    for (auto sym : data)
    {
        //cout << "\ninput " << sym << endl;
        //printDict(dict);
        
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
        writeBinary(os, k);
        //cout << "output " << k << endl;

        //modify the dictionary
        moveToFront(k, dict);
        
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
    using std::cout;
    using std::endl;

    using input_type = size_t;
    std::vector<input_type> data;
    input_type input;
    while (readBinary(is, input))
    {
        data.push_back(input);
    }

    std::sort(dict.begin(), dict.end());

    for (auto index : data)
    {
        //cout << "\ninput " << index << endl;
        //printDict(dict);
        os << dict.at(index);
        //cout << "output " << dict.at(index) << endl;
        moveToFront(index, dict);
    }

    //cout << "\nfinal dict " << endl;
    //printDict(dict);
}