#pragma once

#include <vector>
#include <map>

#include "tree.h"

class Coder
{
public:
    void sample(std::istream &is);
    void encode(std::istream &is, std::ostream &os);
    void decode(std::istream &is, std::ostream &os);
private:
    std::unique_ptr<Node> tree;

    //I can also use the codebook as a return rather than log,
    //which would add a enormous cost to merge books,
    //but would also make it possible to parallelize the job.
    //If it's in Java, a ConcurrentHashMap might be the best choice.
    void record(const std::unique_ptr<Node> &node, std::vector<bool> &trace, std::map<Symbol, std::vector<bool>> &codebook);

    Symbol next(const std::unique_ptr<Node> &node, std::vector<bool> &trace);
};