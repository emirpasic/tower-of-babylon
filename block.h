#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
using namespace std;

class Block
{
public:
    Block(unsigned int width = 0, unsigned int depth = 0, unsigned int height = 0);
    Block(const Block& block);
    Block& operator=(const Block& block);
    void assignDimensions(const Block& block);
    unsigned int getWidth() const;
    unsigned int getDepth() const;
    unsigned int getHeight() const;
    void print() const;
private:
    unsigned int width;
    unsigned int depth;
    unsigned int height;
};

#endif
