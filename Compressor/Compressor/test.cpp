#include "tree.h"

#include "huffman.h"
#include "bwt.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

void testHuffman()
{
    using std::cout;
    using std::endl;
    using std::string;

    unsigned char ch = 'B';
    Item ci{ 10,'D' }, ni{ 1,ch };
    cout << ci << endl << ni << endl;

    Node node{ { 50 } };
    cout << node.item << endl;

    const string text0{ "this is an example of a huffman tree" };
    const string text1{ "abacab" };
    const string &temp = text0;
    ;
    std::ostringstream oss{};

    cout << "sizeof(Cell) = " << sizeof(Cell) << endl;
    cout << "sizeof(Symbol) = " << sizeof(Symbol) << endl;

    Coder coder[2];
    cout << "\nencode" << endl;
    cout << temp << endl;
    const string textName{ "sample" };
    //std::istringstream{ temp }
    coder[0].sample(std::ifstream(textName));
    const string encrName{ "out" };
    coder[0].encode(std::ifstream(textName), std::ofstream(encrName, std::ios::binary));
    const string dictName{ "dict" };
    coder[0].save(std::ofstream(dictName, std::ios::binary));
    coder[1].load(std::ifstream(dictName, std::ios::binary));
    coder[1].decode(std::ifstream(encrName, std::ios::binary), oss);
    cout << "\ndecode" << endl;
    cout << oss.str() << endl;
}

void testBwt()
{
    using std::cout;
    using std::endl;
    using std::string;

    std::ostringstream oss{};
    bwt::encode(std::istringstream{ "^BANANA|" }, oss);
    cout << "\ndecode" << endl;
    cout << oss.str() << endl;
}

int main()
{
    //testHuffman();
    testBwt();
    system("pause");
}
