struct Pixel
{
	int red;
	int green;
	int blue;
};

class genome {
	public:
	genome(); // constructor
	~genome(); // destructor
	void allocate( int nGenes );
	void deallocate();
	void randomize();
	void set_red( int index, int value);
	int get_red( int index);
	void set_green( int index, int value);
	int get_green( int index);
	void set_blue( int index, int value);
	int get_blue( int index);
	void print();

	void set_mRate(double);
	double get_mRate();
	void mutate_gene(int);
	void mutate();
	double calculate_gene_fitness(int, Pixel);
	double calculate_overall_fitness(Pixel*, int);
	void set_pixel(int, Pixel);
	Pixel get_pixel(int);

	private:
	Pixel* genes;
	int nGenes;
	double mRate;
};
