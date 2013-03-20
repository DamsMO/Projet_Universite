
#include "Outils.h"

const double sur_racine2Pi = 0.398942280401433;

double Outils::factoriel(int n) {
	int res =1;
	for(int i=n;i>1;i++) {
		res *=i;
	}
	return res;
}

std::vector<std::vector<double>> Outils::cholesky(std::vector<std::vector<double>> CorrMatrix )
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
		sum1=0.0;
		for(int k=0;k<=i-1;k++)
			sum1=sum1+A[i][k]*A[i][k];
		//sum1=sum1+A[i][i-1]*A[i][i-1];
		A[i][i]=sqrt(CorrMatrix[i][i]-sum1);
		for(int j=i+1;j<d;j++)
		{
			sum2=0.0;
			for(int k=0;k<=i-1;k++)
				sum2=sum2+A[i][k]*A[j][k];
			A[j][i]=(CorrMatrix[i][j]-sum2)/(A[i][i]);
			A[i][j]=0.0;
		}
	}
	return A;
}

std::vector<double> Outils::MatrixvectorProduct(std::vector<std::vector<double>> A, std::vector<double> x)
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

double Outils::MeanEstimate(std::vector<double> a)
{
	double n=a.size();
	double sum=0.0;
	for(int i=0;i<n;i++)
		sum=sum+a[i];
	return sum/n;
}

double Outils::CorrelationEstimate(std::vector<double> a, std::vector<double> b)
{
	double n=a.size();
	std::vector<double> c;
	for(int i=0;i<n;i++)
	{
		c.push_back(a[i]*b[i]);
	}
	return (MeanEstimate(c)-MeanEstimate(a)*MeanEstimate(b))/sqrt(VarianceEstimate(a)*VarianceEstimate(b));
}

double Outils::VarianceEstimate(std::vector<double> a)
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

std::vector<std::vector<double>> Outils::transpose(std::vector<std::vector<double>> A)
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


double Outils::K_MomentEstimate(std::vector<double> a,int k) {
	double estimate = 0;
	double prod;
	for(int i=0;i<a.size();i++) {
		prod = 1;
		for(int j=0;j<k;j++) {
			prod = prod*a[i];
		}
		estimate += prod;
	}
	return estimate/(1.0*a.size());
}

double Outils::NormalDensite(double x)
{
    return sur_racine2Pi*exp(-x*x/2);
}

// Fction Repartition loi normale via the Beasley-Springer ou Moro approximation
double Outils::InverseRepartitionNormal(double u)
{

    static double x[4]={ 2.50662823884,
                        -18.61500062529,
                         41.39119773534,
                        -25.44106049637};

    static double y[4]={-8.47351093090,
                        23.08336743743,
                       -21.06224101826,
                         3.13082909833};

    static double z[9]={0.3374754822726147,
                        0.9761690190917186,
                        0.1607979714918209,
                        0.0276438810333863,
                        0.0038405729373609,
                        0.0003951896511919,
                        0.0000321767881768,
                        0.0000002888167364,
                        0.0000003960315187};

    
    double a=u-0.5;
    double r;

    if (fabs(a)<0.42) // Beasley-Springer
    {
        double b=a*a;
        
        r=a*(((x[3]*b+x[2])*b+x[1])*b+x[0])/
                ((((y[3]*b+y[2])*b+y[1])*b+y[0])*b+1.0);
               
    }
    else // Moro
    {
    
        r=u;
    
        if (a>0.0) 
            r=1.0-u;
        r=-log(r);
		r=log(r);
        
        r=z[0]+r*(z[1]+r*(z[2]+r*(z[3]+r*(z[4]+r*(z[5]+r*(z[6]+
                r*(z[7]+r*z[8])))))));
        
        if (a<0.0) 
            r=-r;
    
    }
	/*if(r>DBL_MAX) {
		std::cout << "BUG dans l'inversion" <<std::endl;
		return 0;
	}else if(r<DBL_MIN) {
		std::cout << "BUG dans l'inversion" <<std::endl;
		return 0;
	}else{*/
	    return r;
	//}
}


// standard normal cumulative distribution function
double Outils::RepartitionNormal(double u)
{
    static double x[5] = { 0.319381530,
                          -0.356563782,
                           1.781477937,
                          -1.821255978,
                           1.330274429};

    double result;
    
    if (u<-7.0)
        result = NormalDensite(u)/sqrt(1.+u*u);
    
    else 
    {
        if (u>7.0)
            result = 1.0 - RepartitionNormal(-u);
        else
        {
            double tmp = 1.0/(1.0+0.2316419*fabs(u));

            result=1-NormalDensite(u)*
                     (tmp*(x[0]+tmp*(x[1]+tmp*(x[2]+tmp*(x[3]+tmp*x[4])))));

            if (u<=0.0) 
                result=1.0-result;

        }
    }

    return result;
}

double Outils::max(std::vector<double> v) {
	double max = INT_MIN;
	for(int i=0;i<v.size();i++) {
		if(v[i]>max) {
			max = v[i];
		}
	}
	return max;
}

double Outils::min(std::vector<double> v) {
	double min = INT_MAX;
	for(int i=0;i<v.size();i++) {
		if(v[i]<min) {
			min = v[i];
		}
	}
	return min;
}

std::string Outils::toString(double x) {
        std::ostringstream oss;
        oss << x;
        return oss.str();
 }
