#include<vector>

class EuropeanOption{
public:

	//constructor
	EuropeanOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_
		);

	//destructor
	~EuropeanOption(){};

	//methods
	void generatePath();
	void printPath();
	double getCallPrice(int nReps);
	double getPutPrice(int nReps);
	double operator()(char optionType, int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
};
