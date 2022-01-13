#include<iostream>
#include<cmath>
#include<algorithm>
#include"getOneGaussianByBoxMueller.h"
#include"EuropeanOption.h"


//definition of constructor
EuropeanOption::EuropeanOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		generatePath();
}

//method definition
void EuropeanOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
void EuropeanOption::printPath(){
	for(int i = 0;  i < nInt; i++){
		std::cout << thisPath[i] << "\n";
	}
}

//method definition
double EuropeanOption::getCallPrice(int nReps){

	double rollingSum = 0.0;
	for(int i = 0; i < nReps; i++){
		generatePath();
		if (thisPath.back() > strike){
			rollingSum += (thisPath.back() - strike);
		}
	}
	return exp(-r*expiry)*rollingSum/double(nReps);
}

//method definition
double EuropeanOption::getPutPrice(int nReps){

	double rollingSum = 0.0;
	for(int i = 0; i < nReps; i++){
		generatePath();
		if (thisPath.back() < strike){
			rollingSum += (strike - thisPath.back());
		}
	}
	return exp(-r*expiry)*rollingSum/double(nReps);
}


//overloaded operator ();
double EuropeanOption::operator()(char optionType, int nReps){
	if (optionType =='C') return getCallPrice(nReps);
	else if (optionType =='P' )return getPutPrice(nReps);
	else return -99;
}
