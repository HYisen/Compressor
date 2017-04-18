#pragma once

#include <memory>
#include <utility>
#include <iostream>

class Symbol
{
	friend std::ostream &operator<<(std::ostream &os, const Symbol &orig);
	friend std::istream &operator>>(std::istream &is, Symbol &orig);
	friend bool operator<(const Symbol &lhs, const Symbol &rhs);
public:
	Symbol(unsigned char c) : content(c) {};
private:
	//Actually, I prefere std::byte.
	unsigned char content;
};
std::ostream &operator<<(std::ostream &os, const Symbol &orig);
std::istream &operator>>(std::istream &is,Symbol &orig);
bool operator<(const Symbol &lhs, const Symbol &rhs);

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

class Tree
{
public:
	Tree();
private:

	std::shared_ptr<Node> root;
};