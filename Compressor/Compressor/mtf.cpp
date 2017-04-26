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

void mtf::encode(std::istream & is, std::ostream & os,const mtf::dict_type & dictionary)
{
    using std::cout;
    using std::endl;

    mtf::dict_type dict(dictionary.cbegin(), dictionary.cend());

    Symbol sym;
    while (readBinary(is,sym))
    {
        //cout << "\ninput " << sym << endl;
        //printDict(dict);
        
        //index-based solution
        //find & output index
        decltype(dict.size()) index = 0;
        for (;; ++index)
        {
            if (dict.at(index) == sym)
            {
                break;
            }
            //An index should always be found in the dictionary,
            //otherwise I would rather crash the program.
            //dict.at(index) will throw an exception if the dict doesn't contain the sym,
            //therefore a busy loop would never happen, unless dict.size()==SIZE_MAX,
            //such a rare coincidence that I would never image to come ture.
        }
        writeBinary(os, index);
        //cout << "output " << index << endl;

        //modify the dictionary
        moveToFront(index, dict);
        
        //iterator-based solution is also possible, but removed,
        //as the result of my lazyness to update code not in use.
    }
}

void mtf::decode(std::istream & is, std::ostream & os, const mtf::dict_type & dictionary)
{
    using std::cout;
    using std::endl;

    mtf::dict_type dict(dictionary.cbegin(), dictionary.cend());

    mtf::dict_type::size_type index;
    while (readBinary(is, index))
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