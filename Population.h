#include "Genome.h"

class Population
{
	public:
	Population();
	~Population();
	void generate_population(int, int);
	void set_target(Pixel*, int);
	void select_parents();
	void set_nCrossover(int);
	int get_Crossovers();
	void set_mutation(double);
	void generate_new_population();
	double calculate_overall_fitness();
	void print_parents();
	void print_population();
	bool contains(int*, int, int);

	private:
	genome *individuals;
	int nIndividuals;
	genome best;
	genome runnerUp;
	int crossovers;
	Pixel *image;
	int imageSize;
	double mRate;
	bool parentsSet;
};