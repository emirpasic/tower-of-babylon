#include "tower.h"

Tower::Tower() {}

Tower::Tower(const vector<Block> blocks)
{
    for (unsigned int i = 0; i < blocks.size(); i++)
        this->blocks.push_back(blocks.at(i));
}

unsigned int Tower::getHeight() const
{
    int height = 0;
    for (unsigned int i = 0; i < blocks.size(); i++)
        height += blocks.at(i).getHeight();
    return height;
}

void Tower::print() const
{
    cout << "Tower(" << this << ")";
    cout << "[height:" << getHeight() << "]";
    cout << endl << "  {" << endl;
    for (unsigned int i = 0; i < blocks.size(); i++)
    {
        cout << "    ";
        blocks.at(i).print();
    }
    cout << "  }" << endl;
}

const Block& Tower::getTopBlock() const
{
    if (isEmpty())
        throw "Tower is empty, hence can not get top block";
    return blocks.at(blocks.size() - 1);
}

bool Tower::isEmpty() const
{
    return blocks.size() == 0;
}


bool Tower::canStack(const Block& block)
{
    if (isEmpty())
        return true;
    const Block& topBlock = getTopBlock();
    return topBlock.getWidth() > block.getWidth() && topBlock.getDepth() > block.getDepth();
}

void Tower::stack(const Block& block)
{
    if (!canStack(block))
        throw "Block can not be stacked on the tower";
    blocks.push_back(block);
}

Tower Tower::createChild(Tower& parent1, Tower& parent2)
{
    unsigned int parent1BlockIndex = 0;
    unsigned int parent2BlockIndex = 0;
    unsigned int parent1BlockMaxIndex = parent1.blocks.size();
    unsigned int parent2BlockMaxIndex = parent2.blocks.size();
    Tower tower;

    while (parent1BlockIndex < parent1BlockMaxIndex || parent2BlockIndex < parent2BlockMaxIndex)
    {
        bool selectParent1 = rand() % 2;

        if (selectParent1)
        {
            if (parent1BlockIndex < parent1BlockMaxIndex && tower.canStack(parent1.blocks.at(parent1BlockIndex)))
                tower.stack(parent1.blocks.at(parent1BlockIndex));
            ++parent1BlockIndex;
        }
        else
        {
            if (parent2BlockIndex < parent2BlockMaxIndex && tower.canStack(parent2.blocks.at(parent2BlockIndex)))
                tower.stack(parent2.blocks.at(parent2BlockIndex));
            ++parent2BlockIndex;
        }
    }

    return tower;
}

bool Tower::operator <(const Tower& tower) const
{
	return (getHeight() > tower.getHeight());
}



