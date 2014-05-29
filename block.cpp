#include "block.h"

Block::Block(unsigned int width, unsigned int depth, unsigned int height)
    : width(width),
      depth(depth),
      height(height) {}

Block::Block(const Block& block)
{
    assignDimensions(block);
}

Block& Block::operator=(const Block& block)
{
    assignDimensions(block);
    return *this;
}

void Block::assignDimensions(const Block& block)
{
    width = block.getWidth();
    depth = block.getDepth();
    height = block.getHeight();
}

unsigned int Block::getWidth() const
{
    return width;
}

unsigned int Block::getDepth() const
{
    return depth;
}

unsigned int Block::getHeight() const
{
    return height;
}

void Block::print() const
{
    cout << "Block(" << this << ")";
    cout << "[" << "width:" << width << ", depth:" << depth << ", height:" << height << "]";
    cout << endl;
}


