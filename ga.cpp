#include <algorithm>
#include "ga.h"

inline unsigned int random(unsigned int min, unsigned int max)
{
    return min + (rand() % (unsigned int)(max - min + 1));
}

GA::GA(vector<Block> blocks)
{
    for (unsigned int i = 0; i < blocks.size(); i++)
        this->blocks.push_back(blocks.at(i));
}

unsigned int GA::getPopulationSize() const
{
    return populationSize;
}

void GA::setPopulationSize(unsigned int populationSize)
{
    this->populationSize = populationSize;
}

float GA::getMutationRate() const
{
    return mutationRate;
}

void GA::setMutationRate(float mutationRate)
{
    this->mutationRate = mutationRate;
}

unsigned int GA::getMaxEpochs() const
{
    return maxEpochs;
}

void GA::setMaxEpochs(unsigned int maxEpochs)
{
    this->maxEpochs = maxEpochs;
}

void GA::run()
{
    rotateBlocks();
    createInitialPopulation();
    unsigned int epoch = 0;
    unsigned int lastBestHeight = 0;
    unsigned int lastBestHeightRepetition = 0;
    while (epoch++ < maxEpochs)
    {
        unsigned int bestHeight = getBestHeight();

        if (lastBestHeight == bestHeight)
            ++lastBestHeightRepetition;
        if (lastBestHeightRepetition > MAX_BEST_HEIGHT_REPETITIONS)
            break;
		lastBestHeight = bestHeight;

        cout << "Best height: " << bestHeight << " Epoch: " << epoch << endl;

        // create offspring
        vector<Tower> offspring;
        for (unsigned int i = 0; i < populationSize; i++)
            offspring.push_back(createSingleOffspring());

        // select most fit from parents and offspring
        towers.insert(towers.end(), offspring.begin(), offspring.end());
        sort(towers.begin(), towers.end());
        towers.resize(populationSize);

        // TODO mutations;

    }
    cout << endl << "Final best height: " << getBestHeight() << endl << endl;
	printBestHeight();
}

Tower GA::createSingleOffspring() const
{
    Tower& parent1 = getRandomParent();
    Tower& parent2 = getRandomParent();
    Tower child = Tower::createChild(parent1, parent2);
    return child;
}

Tower GA::getRandomParent() const
{
    /* Roulette wheel selection */
    unsigned int heightSum = 0;
    for (unsigned int i = 0; i < towers.size(); i++)
        heightSum += towers.at(i).getHeight();

    unsigned int towerIndex = 0;
	unsigned int towerIndexSafe = 0;
    double sum = ((double)towers.at(towerIndex).getHeight() / (double)heightSum);
    double epsilon = ((double)rand() / (double)RAND_MAX); // (0,1]
    while (sum < epsilon)
    {
        ++towerIndex;
		towerIndexSafe = towerIndex % towers.size();
		sum += ((double)towers.at(towerIndexSafe).getHeight() / (double)heightSum);
    }
    return towers.at(towerIndexSafe);
}

unsigned int GA::getBestHeight() const
{
    max(1.0, 2.0);
    unsigned int maxHeight = 0;
    for (unsigned int i = 0; i < towers.size(); i++)
        maxHeight = max(maxHeight, towers.at(i).getHeight());
    return maxHeight;
}

void GA::createInitialPopulation()
{
    for (unsigned int n = 0; n < populationSize; n++)
        towers.push_back(createRandomTower());
}

void GA::rotateBlocks()
{
    unsigned int blocksSizeBeforeRotation = blocks.size();
    for (unsigned int i = 0; i < blocksSizeBeforeRotation; i++)
    {
        Block block = blocks.at(i);
        this->blocks.push_back(Block(block.getWidth(), block.getHeight(), block.getDepth()));
        this->blocks.push_back(Block(block.getDepth(), block.getWidth(), block.getHeight()));
        this->blocks.push_back(Block(block.getDepth(), block.getHeight(), block.getWidth()));
        this->blocks.push_back(Block(block.getHeight(), block.getWidth(), block.getDepth()));
        this->blocks.push_back(Block(block.getHeight(), block.getDepth(), block.getWidth()));
    }
}

Tower GA::createRandomTower() const
{
    unsigned int blockMaxIndex = blocks.size() - 1;
    unsigned int maxRandomMisses = blocks.size() * 100; //TODO calculate through distribution of probabilities to have less than 1% of missing a block in maxRandomMisses tries
    Tower tower;
    while (true)
    {
        unsigned int randomBlockIndex = random(0, blockMaxIndex);
        unsigned int randomMisses = 0;
        Block randomBlock = blocks.at(randomBlockIndex);
        while (!tower.canStack(randomBlock) && randomMisses < maxRandomMisses)
        {
            randomBlockIndex = random(0, blockMaxIndex);
            randomBlock = blocks.at(randomBlockIndex);
            ++randomMisses;
        }
        if (tower.canStack(randomBlock))
            tower.stack(randomBlock);
        else
            break;
    }
    return tower;
}

void GA::printBestHeight() const {
	unsigned int bestHeight = getBestHeight();
	 for (unsigned int i = 0; i < towers.size(); i++)
		 if(towers.at(i).getHeight() == bestHeight) {
			 towers.at(i).print();
			 return;
		 }
}



