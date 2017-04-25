#pragma once

#include <iostream>

namespace bwt
{
    void encode(std::istream &is, std::ostream &os);
    void decode(std::istream &is, std::ostream &os);
}