#ifndef OUTIL_H_
#define OUTIL_H_
#include <cmath>
#include <vector>
#include <iostream>
std::vector<std::vector<double>> cholesky(std::vector<std::vector<double>> CorrMatrix);
std::vector<double> MatrixvectorProduct(std::vector<std::vector<double>> A, std::vector<double> x);
double MeanEstimate(std::vector<double>);
double CorrelationEstimate(std::vector<double> a, std::vector<double> b);
double VarianceEstimate(std::vector<double> a);
std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A);
#endif
