#include "Processus.h"
#include<stdio.h>
#include<iostream>
#include<string>

//drt = a(b-rt)dt + vol*dWt
class Vasiceck : public Processus { 
private : //param : 0 = a, 1 = b, 2 = vol
	int type_simu;//Euler 1 - Normal 2

public :
	std::string getType() {
		if(type_simu==1) {
			return "Euler Scheme";
		}else{
			return "Analystics Scheme";
		}
	}

	Vasiceck(double init,std::vector<double> param_init) throw(std::string) {
		type_simu = 1;
		nb_MB = 1;
		if(param_init.size()==3) {
			val_t = init;
			t = 0;
			param_t = param_init;
		}else{
			std::cout << "Problème avec le nombre de parametres" <<std::endl;
			throw("Vasiceck Param Error");
		}
	}

	Vasiceck(double init,std::vector<double> param_init,int type) throw(std::string) {
		if(type ==1 || type ==2) {
			type_simu = type;
			Vasiceck(init,param_init);
		}else{
			throw("Type non défini");
		}
	}


	virtual double Vasiceck::next_simu(double delta,std::vector<double> alea,double prev) throw(std::string) {
		if(alea.size()<1) {
			throw("Pas d'alea donnée en entrée (Vasiceck Simu)");
		}else{
			t= t +delta;
			double val=0;
			//drt = a*(b-rt)dt + sigdWt
			//Les parametres restent constants
			switch(type_simu) {
			case 1://Euler
				val = prev + param_t[0]*(param_t[1]-val_t)*delta + param_t[2]*sqrt(delta)*alea[0];
				break;
			case 2:
				//drift
				val = prev*exp(-param_t[0]*delta) + param_t[1]*(1-exp(-param_t[0]*delta));
				//alea
				val +=  alea[0]*(1-exp(-2*param_t[0]*delta))*param_t[2]/sqrt(2*param_t[0]);
				break;
			}
			return val;
		}
	}
};
