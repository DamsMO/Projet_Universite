#include <cmath>
#include <vector>
#include <iostream>
#include "Outils.h"

std::vector<std::vector<double>> cholesky(std::vector<std::vector<double>> CorrMatrix)
{
  //Fais la décomposition de cholesky de la matrice de corrélation
	int d=CorrMatrix.size();
	std::vector<std::vector<double>> A;
	double sum1=0.0;
	double sum2=0.0;
	A.resize(d);
	A[0].resize(d);
	A[0][0]=sqrt(CorrMatrix[0][0]);
	for(int i=1;i<d;i++)
	{
		A[i].resize(d);
		A[i][0]=CorrMatrix[0][i]/A[0][0];
	}
	for(int i=1;i<d;i++)
	{
		sum1=sum1+A[i][i-1]*A[i][i-1];
		A[i][i]=sqrt(CorrMatrix[i][i]-sum1);
		for(int j=i+1;j<d;j++)
		{
			sum2=sum2+A[i][i-1]*A[j][i-1];
			A[j][i]=(CorrMatrix[i][j]-sum2)/(A[i][i]);
			A[i][j]=0.0;
		}
	}
	return A;
}

std::vector<double> MatrixvectorProduct(std::vector<std::vector<double>> A, std::vector<double> x)
{
	std::vector<double> b;
	int n=A.size();
	int m=A[0].size();
	double sumtemp=0;
	if(m!=x.size())
	{
		std::cout<<"Problème de dimensions"<<std::endl;
		b.resize(1);
		b[0]=0.0;
	}
	else
	{
		b.resize(n);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				sumtemp=sumtemp+A[i][j]*x[j];
			b[i]=sumtemp;
			sumtemp=0.0;
		}
	}
	return b;
}

double MeanEstimate(std::vector<double> a)
{
	double n=a.size();
	double sum=0.0;
	for(int i=0;i<n;i++)
		sum=sum+a[i];
	return sum/n;
}

double CorrelationEstimate(std::vector<double> a, std::vector<double> b)
{
	double n=a.size();
	std::vector<double> c;
	for(int i=0;i<n;i++)
	{
		c.push_back(a[i]*b[i]);
	}
	return (MeanEstimate(c)-MeanEstimate(a)*MeanEstimate(b))/sqrt(VarianceEstimate(a)*VarianceEstimate(b));
}

double VarianceEstimate(std::vector<double> a)
{
	double n=a.size();
	double sum=0.0;
	double mean=MeanEstimate(a);
	for(int i=0;i<n;i++)
	{
		sum=sum+(a[i]-mean)*(a[i]-mean);
	}
	return sum/(n-1);
}

std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A)
{
	int n=A.size();
	int m=A[0].size();
	std::vector<std::vector<double>> At;
	At.resize(m);
	for(int i;i<m;i++)
	{
		At[i].resize(n);
		At[i][i]=A[i][i];
		for(int j=1;j<n;j++)
		{
			At[i][j]=A[j][i];
		}
	}
	return At;
}
