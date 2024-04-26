#include "Population.h"
#include <iostream>

using namespace std;

Population::Population()
{
	individuals = nullptr;
	nIndividuals = 0;
	crossovers = 0;
	srand(time(0));
	parentsSet = false;
}

Population::~Population()
{
	delete individuals;
	individuals = nullptr;
	nIndividuals = 0;
}

void Population::generate_population(int popSize, int genes)
{
	//for(int i = 0; i < nIndividuals; i++) delete individuals[i];
	individuals = new genome[popSize];
	nIndividuals = popSize;
	for(int i = 0; i < popSize; i++) individuals[i] = genome();
	for(int i = 0; i < popSize; i++) individuals[i].allocate(genes);
}

void Population::set_target(Pixel* target, int targetSize)
{
	image = target;
	imageSize = targetSize;
}

void Population::select_parents()
{
	double bestScore = 0;
	int bestIndex = 0;
	for(int i = 0; i < nIndividuals; i++) if(individuals[i].calculate_overall_fitness(image, imageSize) > individuals[bestIndex].calculate_overall_fitness(image, imageSize))
	{
		best = individuals[i];
		bestScore = individuals[i].calculate_overall_fitness(image, imageSize);
		bestIndex = i;
	}

	double runnerUpScore = 0;
	int runnerUpIndex = 0;
	for(int i = 0; i < nIndividuals; i++) if(individuals[i].calculate_overall_fitness(image, imageSize) > individuals[bestIndex].calculate_overall_fitness(image, imageSize) && i != bestIndex)
	{
		runnerUp = individuals[i];
		runnerUpScore = individuals[i].calculate_overall_fitness(image, imageSize);
		runnerUpIndex = i;
	}
	parentsSet = true;
}

void Population::set_nCrossover(int nCrossover)
{
	crossovers = nCrossover;
}

int Population::get_Crossovers()
{
	return crossovers;
}

void Population::set_mutation(double rate)
{
	mRate = rate;
	for(int i = 0; i < nIndividuals; i++) individuals[i].set_mRate(rate);
}

void Population::generate_new_population()
{
	genome* newPop = new genome[nIndividuals];
	for(int i = 0; i < nIndividuals; i++)
	{
		newPop[i] = genome();
		newPop[i].allocate(imageSize);
		newPop[i].set_mRate(mRate);
		genome p1 = best;
		genome p2 = runnerUp;
		int* crossover = new int[crossovers];
		for(int j = 0; j < crossovers; j++)
		{
			int cross = rand()%imageSize;
			while(!contains(crossover, crossovers, cross)) cross = rand()%imageSize;
			crossover[j] = cross;
		}
		bool firstParent = rand() % 2 == 0;
		for(int j = 0; j < imageSize; j++)
		{
			if(contains(crossover, crossovers, j)) firstParent = !firstParent;
			if(firstParent) individuals[i].set_pixel(j, p1.get_pixel(j));
			else individuals[i].set_pixel(j, p2.get_pixel(j));
		}
	}
	for(int i = 0; i < nIndividuals; i++)
	{
		individuals[i].deallocate();
		individuals[i] = newPop[i];
	}
}

double Population::calculate_overall_fitness()
{
	double fitness = 0;
	for(int i = 0; i < nIndividuals; i++) fitness += individuals[i].calculate_overall_fitness(image, imageSize);
	fitness/=nIndividuals;
	return fitness;
}

void Population::print_parents()
{
	if(!parentsSet) cout << "no parents set yet\n";
	else
	{
		best.print();
		runnerUp.print();
	}
}

void Population::print_population()
{
	std::cout << crossovers << "\t" << mRate;
	for(int i = 0; i < nIndividuals; i++)
	{
		individuals[i].print();
	}
}

bool Population::contains(int* array, int size, int num)
{
	for(int i = 0; i < size; i++) if(array[i] == num) return true;
	return false;
}