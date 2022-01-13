#include<iostream>
#include<cmath>
#include<algorithm>
#include"getOneGaussianByBoxMueller.h"
#include"UpAndIn.h"


//definition of constructor
UpAndInOption::UpAndInOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		barrier = barrier_;
		generatePath();
}

//method definition
void UpAndInOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
void UpAndInOption::printPath(){
	for(int i = 0;  i < nInt; i++){
		std::cout << thisPath[i] << "\n";
	}
}

//method definition
double UpAndInOption::getUpAndInCallPrice(int nReps){

	double rollingSum = 0.0;
	for(int i = 0; i < nReps; i++){
		generatePath();
		double thisMax = *max_element(thisPath.begin(), thisPath.end());
		if ((thisMax >= barrier) & (thisPath.back() > strike)){
			rollingSum += (thisPath.back() - strike);
		}
	}
	return exp(-r*expiry)*rollingSum/double(nReps);
}

//method definition
double UpAndInOption::getUpAndInPutPrice(int nReps){

	double rollingSum = 0.0;
	for(int i = 0; i < nReps; i++){
		generatePath();
		double thisMax = *max_element(thisPath.begin(), thisPath.end());
		if ((thisMax >= barrier) & (thisPath.back() < strike)){
			rollingSum += (strike - thisPath.back());
		}
	}
	return exp(-r*expiry)*rollingSum/double(nReps);
}


//overloaded operator ();
double UpAndInOption::operator()(char optionType, int nReps){
	if (optionType =='C') return getUpAndInCallPrice(nReps);
	else if (optionType =='P' )return getUpAndInPutPrice(nReps);
	else return -99;
}
