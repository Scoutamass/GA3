#include "Genome.h"   
#include <iostream>   
using namespace std;  

genome::genome()
{
	genes = NULL;
	nGenes = 0;
	mRate = 0;
}

genome::~genome()
{
	deallocate();
}

void genome::deallocate()
{
	if(nGenes!= 0) return;
	delete genes;
	nGenes = 0;
}

void genome::allocate(int numGenes)
{
	if(numGenes <= 0) return;
	deallocate();
	nGenes = numGenes;
	genes = new Pixel[numGenes];
}

void genome::randomize()
{
	for(int i = 0; i < nGenes; i++)
	{
		genes[i].red = rand() * 256.0/RAND_MAX;
		genes[i].green = rand() * 256.0/RAND_MAX;
		genes[i].blue = rand() * 256.0/RAND_MAX;
	}
}

void genome::set_red(int index, int value)
{
	if(index < 0 || index > nGenes) return;
	genes[index].red = value;
}

int genome::get_red(int index)
{
	if(index < 0 || index > nGenes) return -1;
	return genes[index].red;
}

void genome::set_green( int index, int value)
{
	if(index < 0 || index > nGenes) return;
	genes[index].green = value;
}

int genome::get_green(int index)
{
	if(index < 0 || index > nGenes) return -1;
	return genes[index].green;
}

void genome::set_blue( int index, int value)
{
	if(index < 0 || index > nGenes) return;
	genes[index].blue = value;
}

int genome::get_blue(int index)
{
	if(index < 0 || index > nGenes) return -1;
	return genes[index].blue;
}

void genome::print()
{
	for(int i = 0; i < nGenes; i++)
	{
		cout << genes[i].red << "\t" << genes[i].green << "\t" << genes[i].blue << "\n";
	}
	cout << "\n";
}

void genome::set_mRate(double rate)
{
	mRate = rate;
}

double genome::get_mRate()
{
	return mRate;
}

void genome::mutate_gene(int i)
{
	if(i > nGenes) return;
	if(rand() * 1.0/RAND_MAX < mRate) genes[i].red = rand() * 1.0/RAND_MAX*256;
	if(rand() * 1.0/RAND_MAX < mRate) genes[i].green = rand() * 1.0/RAND_MAX*256;
	if(rand() * 1.0/RAND_MAX < mRate) genes[i].blue = rand() * 1.0/RAND_MAX*256;
}

void genome::mutate()
{
	for(int i = 0; i < nGenes; i++) mutate_gene(i);
}

double genome::calculate_gene_fitness(int i, Pixel target)
{
	return (genes[i].red + genes[i].green + genes[i].blue - target.red - target.green - target.blue)/3.0/256;
}

double genome::calculate_overall_fitness(Pixel* target, int pixels)
{
	if(pixels != nGenes) return -1;
	double error = 0;
	for(int i = 0; i < nGenes; i++) error += abs(calculate_gene_fitness(i, target[i]));
	error/=nGenes;
	return error;
}

void genome::set_pixel(int i, Pixel p)
{
	genes[i] = p;
}

Pixel genome::get_pixel(int i)
{
	return genes[i];
}