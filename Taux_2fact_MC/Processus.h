#include<vector>

class Processus {
protected :
	std::vector<double> param_t;
	double t;
	double val_t;
	int nb_MB;

public :
	double getVal();
	double getTime();
	std::vector<double> getParam();
	void setParam(std::vector<double> new_param);
	virtual double next_simu(double delta,std::vector<double> alea,double prev) =0;
	int getNbMB();
};
