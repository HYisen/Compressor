#include "tree.h"

#include "huffman.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


void writeString(std::ostream &os, const std::string s)
{
	os << s << std::endl;
}


int main()
{
	using std::cout;
	using std::endl;

	unsigned char ch = 'B';
	Item ci{ 10,'D' }, ni{ 1,ch };
	cout << ci << endl << ni << endl;

	Node node{ {50} };
	cout << node.item << endl;

	std::string text{ "this is an example of a huffman tree" };
    std::istringstream is{ "abacab" };
    std::ofstream os("out");
	encode(is, os);
    os.close();
	system("pause");
}
