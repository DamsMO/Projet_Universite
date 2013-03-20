#ifndef OUTIL_H_
#define OUTIL_H_
#include <cmath>
#include <vector>
#include <iostream>
#include<math.h>
#include <string>
#include <cmath>
#include <sstream>

class Outils {
public :
static std::vector<std::vector<double>> cholesky(std::vector<std::vector<double>> CorrMatrix);
static std::vector<double> MatrixvectorProduct(std::vector<std::vector<double>> A, std::vector<double> x);
static double MeanEstimate(std::vector<double>);
static double CorrelationEstimate(std::vector<double> a, std::vector<double> b);
static double VarianceEstimate(std::vector<double> a);
static std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A);
static double K_MomentEstimate(std::vector<double> a,int k);
static double NormalDensite(double x);
static double InverseRepartitionNormal(double u);
static double RepartitionNormal(double u);
static double max(std::vector<double> v);
static double min(std::vector<double> v);
static double factoriel(int n);
static std::string toString(double x);
};

#endif
