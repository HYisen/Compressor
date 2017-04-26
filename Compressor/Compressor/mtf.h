//Move To Front transform
#pragma once

#include "tree.h"

#include <iostream>
#include <deque>

namespace mtf
{
    //As the dict_type, both vector and list are candidates,
    //vector is inefficient to rearrange the order but efficient to get the index,
    //while list is on the contrast. It's hard to decide as the two methods are usually invoked together.
    using dict_type = std::deque<Symbol>;

    void encode(std::istream &is, std::ostream &os, dict_type &dict);
    //I didn't claim that dict is const, which means it will be ruined in the func.
    void decode(std::istream &is, std::ostream &os, dict_type &dict);
}