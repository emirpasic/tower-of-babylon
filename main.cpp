#include <iostream>
#include <vector>
#include <time.h>
#include "ga.h"

using namespace std;

int main()
{
	srand ( time(0) );

    vector<Block> blocks;
    blocks.push_back(Block(31, 41, 59));
    blocks.push_back(Block(26, 53, 58));
    blocks.push_back(Block(97, 93, 23));
    blocks.push_back(Block(84, 62, 64));
    blocks.push_back(Block(33, 83, 27));


	GA ga(blocks);
	ga.setPopulationSize(200);
	ga.setMaxEpochs(1000);
	ga.setMutationRate(0.01f);
	ga.run();

    char c;
    cin >> c;
}
