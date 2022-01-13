#include<vector>

class UpAndInOption{
public:

	//constructor
	UpAndInOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double barrier_
		);

	//destructor
	~UpAndInOption(){};

	//methods
	void generatePath();
	void printPath();
	double getUpAndInCallPrice(int nReps);
	double getUpAndInPutPrice(int nReps);
	double operator()(char optionType, int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;
};
