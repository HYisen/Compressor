#include "tree.h"

std::ostream & operator<<(std::ostream & os, const Symbol & orig)
{
	os << static_cast<char>(orig.content);
	return os;
}

std::istream & operator>>(std::istream & is,Symbol & orig)
{
	is >> std::noskipws >> orig.content;
	//std::cout << "read " << orig.content<<" = "<<static_cast<int>(orig.content)<< std::endl;
	//unchecked if the input is successful
	return is;
}

bool operator<(const Symbol & lhs, const Symbol & rhs)
{
	return lhs.content<rhs.content;
}

std::ostream & operator<<(std::ostream & os, const Item &orig)
{
	os << "{\"isFinal\":" << orig.isFinal <<
		",\"symbol\":\"" << orig.symbol <<
		"\",\"weight\":" << orig.weight << "}";//JSON
	return os;
}
