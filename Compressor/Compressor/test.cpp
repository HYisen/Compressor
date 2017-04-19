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

    std::string text0{ "this is an example of a huffman tree" };
    std::string text1{ "abacab" };
    std::istringstream is{ "abacab" };
    std::ofstream os("out");

    Coder coder{};
    coder.sample(std::istringstream{ text1 });
	coder.encode(std::istringstream{ text1 }, os);
    os.close();
	system("pause");
}
