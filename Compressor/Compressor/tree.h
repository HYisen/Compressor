#pragma once

#include <memory>
#include <utility>
#include <iostream>
#include <vector>

//I declear friend func even if the class is plain,
//to ease the trouble when refactor to private data.

class Symbol
{
	friend std::ostream &operator<<(std::ostream &os, const Symbol &orig);
	friend std::istream &operator>>(std::istream &is, Symbol &orig);
	friend bool operator<(const Symbol &lhs, const Symbol &rhs);
    friend bool operator==(const Symbol &lhs, const Symbol &rhs);
    friend bool operator!=(const Symbol &lhs, const Symbol &rhs);
public:
	Symbol(unsigned char c) : content(c) {};
    Symbol(const Symbol &orig) :content(orig.content) {};
    Symbol() = default;
    Symbol &operator= (const Symbol &orig);

    //the EOF signal used for BWT
    static Symbol signal();
private:
	//Actually, I prefere std::byte.
	unsigned char content;
};
std::ostream &operator<<(std::ostream &os, const Symbol &orig);
std::istream &operator>>(std::istream &is,Symbol &orig);
bool operator<(const Symbol &lhs, const Symbol &rhs);
bool operator==(const Symbol &lhs, const Symbol &rhs);
bool operator!=(const Symbol &lhs, const Symbol &rhs);
std::vector<Symbol> readAll(std::istream &is);

class Item
{
	friend std::ostream &operator<<(std::ostream &os, const Item &orig);
public:
	Item(const int wgt, const Symbol &sym) :isFinal(true), symbol(sym), weight(wgt) {};
	Item(const int wgt) :isFinal(false), weight(wgt) {};
	
	const bool isFinal;//isFinal stands whether its symbol is compositive&meaningless or not.
	const Symbol symbol = Symbol{'&'};
	const int weight;//Let's reserve the minus region for potential usages.
};
std::ostream &operator<<(std::ostream &os, const Item &orig);

class Node
{
public:
	Node(Item &&i) :item(std::move(i)) {} ;
	~Node()=default;

	Item item;
	std::unique_ptr<Node> l = nullptr;
	std::unique_ptr<Node> r = nullptr;
};

//Cell is used to store tree structure in array.
class Cell
{
    friend std::ostream & writeBinary(std::ostream &os, const Cell &orig);
    friend std::istream & readBinary(std::istream &is, Cell &orig);
    friend size_t install(const std::unique_ptr<Node> &node, std::vector<Cell> &container);
    friend std::unique_ptr<Node> construct(const Cell &orig, const std::vector<Cell> &container);
public:
    //using size_t = unsigned char;
    //Warning, it's of vital importance to determine the type of size_t,
    //a too large type would be a waste of space,
    //while a too small type would destroy the data.

    Symbol sym;
    size_t l;
    size_t r;
    //l or r ==0 stands nullptr;
};
std::ostream & writeBinary(std::ostream &os, const Cell &orig);
std::istream & readBinary(std::istream &is, Cell &orig);

//Install a Node as Cell together with its leaves, return where it located.
size_t install(const std::unique_ptr<Node> &node, std::vector<Cell> &container);
std::unique_ptr<Node> construct(const Cell &orig, const std::vector<Cell> &container);

template<typename T>
std::ostream & writeBinary(std::ostream & os, const T &orig);

template<typename T>
std::istream & readBinary(std::istream & is,T &orig);

template<typename T>
inline std::ostream & writeBinary(std::ostream & os, const T &orig)
{
    os.write(reinterpret_cast<const char*>(&orig), sizeof(T));
    return os;
}

template<typename T>
inline std::istream & readBinary(std::istream & is, T & orig)
{
    is.read(reinterpret_cast<char*>(&orig), sizeof(T));
    return is;
}
