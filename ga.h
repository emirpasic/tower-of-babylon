#ifndef GA_H
#define GA_H

#include "tower.h"

class GA
{
public:
    GA(const vector<Block> blocks);
    unsigned int getPopulationSize() const;
    void setPopulationSize(unsigned int populationSize);
    float getMutationRate() const;
    void setMutationRate(float mutationRate);
	unsigned int getMaxEpochs() const;
	void setMaxEpochs(unsigned int maxEpochs);
	void run();
	unsigned int getBestHeight() const;
	void printBestHeight() const;
private:
	static const unsigned int MAX_BEST_HEIGHT_REPETITIONS = 10;
    unsigned int populationSize;
	unsigned int maxEpochs;
    float mutationRate;
    vector<Block> blocks;
    vector<Tower> towers;
	void rotateBlocks();
	void createInitialPopulation();
	Tower createRandomTower() const;
	Tower createSingleOffspring() const;
	Tower getRandomParent() const;
};

#endif GA_H
