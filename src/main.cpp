#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"EuropeanOption.h"
#include"UpAndIn.h"

using namespace Rcpp;
using std::vector;

// [[Rcpp::export]]
double getUpAndInPrice(
    int nInt,
    double strike,
    double spot,
    double vol,
    double r,
    double expiry,
    double barrier,
    int nReps,
    char optionType){

  // set the seed
  srand( time(NULL) );

  //create a new instance of class
  UpAndInOption myUpInOption(nInt, strike, spot, vol, r, expiry, barrier);

  //return Monte Carlo to obtain theoretical price of Up-and-In options
  double price = 0.0;
  if (optionType == 'C'){
    price = myUpInOption.getUpAndInCallPrice(nReps);
  }
  else if (optionType == 'P'){
    price = myUpInOption.getUpAndInPutPrice(nReps);
  }
  else {
    std::printf("\n Option type must be 'C' (for call) or 'P' (for put)");
  };

  return price;
}

// [[Rcpp::export]]
double getEuropeanPrice(
    int nInt,
    double strike,
    double spot,
    double vol,
    double r,
    double expiry,
    int nReps,
    char optionType
    ){

  // set the seed
  srand( time(NULL) );

  // create a new instance of a class
  EuropeanOption myEuropean(nInt, strike, spot, vol, r, expiry);

  // call the method to get option price
  double price = 0.0;
  if (optionType == 'C'){
    price = myEuropean.getCallPrice(nReps);
  }
  else if (optionType == 'P'){
    price = myEuropean.getPutPrice(nReps);
  }
  else {
    std::printf("\n Option type must be 'C' (for call) or 'P' (for put)");
  };
  // return option price
  return price;
}
