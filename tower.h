#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include "block.h"

class Tower
{
public:
    Tower();
    Tower(const vector<Block> blocks);
    void print() const;
    unsigned int getHeight() const;
	bool canStack(const Block& block);
	const Block& getTopBlock() const; 
	bool isEmpty() const;
	void stack(const Block& block);
	static Tower createChild(Tower& parent1, Tower& parent2);
	bool operator <(const Tower& tower) const;
private:
    vector<Block> blocks;
};

#endif
