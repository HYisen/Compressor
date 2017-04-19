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
    using std::string;

	unsigned char ch = 'B';
	Item ci{ 10,'D' }, ni{ 1,ch };
	cout << ci << endl << ni << endl;

	Node node{ {50} };
	cout << node.item << endl;

    string text0{ "this is an example of a huffman tree" };
    string text1{ "abacab" };
    string &temp = text0;
    std::ofstream ofs("out");
    std::ostringstream oss{};

    Coder coder{};
    cout << "\nencode" << endl;
    cout << temp << endl;
    coder.sample(std::istringstream{ temp });
	coder.encode(std::istringstream{ temp }, ofs);
    ofs.close();
    coder.decode(std::ifstream("out"), oss);
    cout << "\ndecode" << endl;
    cout << oss.str() << endl;
	system("pause");
}
