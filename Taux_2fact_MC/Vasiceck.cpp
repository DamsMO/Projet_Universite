#include "Taux.h"
#include<stdio.h>
#include<iostream>
#include<string>

//drt = a(b-rt)dt + vol*dWt
class Vasiceck : public Taux { 
private : //param : 0 = a, 1 = b, 2 = vol
	int type_simu;//Euler 1 - Normal 2

public :
	std::string toString() {
		return "Vasiceck Processus";
	}

	std::string getType() {
		if(type_simu==1) {
			return "Euler Scheme";
		}else{
			return "Analystics Scheme";
		}
	}

	Vasiceck(double init,std::vector<double> param_init,vector<double> ZC_initial,
	vector<double> echeancier) throw(std::string) {
		this->echeancier = echeancier;
		this->ZC_initial = ZC_initial;
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

	Vasiceck(double init,std::vector<double> param_init,int type,vector<double> ZC_initial,
	vector<double> echeancier) throw(std::string) {
		if(type ==1 || type ==2) {
			type_simu = type;
			nb_MB = 1;
			this->echeancier = echeancier;
			this->ZC_initial = ZC_initial;
			if(param_init.size()==3) {
				val_t = init;
				t = 0;
				param_t = param_init;
			}else{
				std::cout << "Problème avec le nombre de parametres" <<std::endl;
				throw("Vasiceck Param Error");
			}
		}else{
			throw("Type non défini");
		}
	}

	Vasiceck(double init,std::vector<double> param_init,std::string fileZCinit) throw(std::string) {
		csvRead file = csvRead(fileZCinit);
		this->echeancier = file.getval()[0];
		this->ZC_initial = file.getval()[1];
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

	Vasiceck(double init,std::vector<double> param_init,int type,std::string fileZCinit) throw(std::string) {
		if(type ==1 || type ==2) {
			type_simu = type;
			nb_MB = 1;
			//Le fichier des ZC doit contenir 2 colonnes
			//1 - avec les echeances et 2 - avec les valeurs des ZC
			csvRead file = csvRead(fileZCinit);
			this->echeancier = file.getval()[0];
			this->ZC_initial = file.getval()[1];
			if(param_init.size()==3) {
				val_t = init;
				t = 0;
				param_t = param_init;
			}else{
				std::cout << "Problème avec le nombre de parametres" <<std::endl;
				throw("Vasiceck Param Error");
			}
		}else{
			throw("Type non défini");
		}
	}

	virtual void Vasiceck::next_simu(double delta,std::vector<double> alea) throw(std::string) {
		if(alea.size()<1) {
			throw("Pas d'alea donnée en entrée (Vasiceck Simu)");
		}else{
			t= t +delta;
			//drt = a*(b-rt)dt + sigdWt
			//Les parametres restent constants
			switch(type_simu) {
			case 1://Euler
				val_t = val_t + param_t[0]*(param_t[1]-val_t)*delta + param_t[2]*sqrt(delta)*alea[0];
				break;
			case 2:
				//drift
				val_t = val_t*exp(-param_t[0]*delta) + param_t[1]*(1-exp(-param_t[0]*delta));
				//alea
				val_t +=  alea[0]*(1-exp(-2*param_t[0]*delta))*param_t[2]/sqrt(2*param_t[0]);
				break;
			}
			//return new Vasiceck(*this);
		}
	}

	double getZC(double T) {
		return 0;
	}
	double getCap(double T,double DeltaT) {
		return 0;
	}
	double getSwaption(double T1,double T2,double DeltaT) {
		return 0;
	}

};
