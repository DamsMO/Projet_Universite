#include "Taux.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include "Outils.h"

//drt = a(b-rt)dt + vol*dWt
class Vasiceck : public Taux { 
private : //param : 0 = a, 1 = b, 2 = vol
	int type_simu;//Euler 1 - Normal 2

public :
	std::string toString() {
		std::string res;
		res += "Vasiceck Processus";
		res+= "type de simu : " + getType() +"\n";
		res+="Temps de la simu : " + Outils::toString(getTime())+"\n";
		res+= "Val actuel du process : " + Outils::toString(getVal()) +"\n";
		res+="Ce process nécessite " + Outils::toString(getNbMB()) + " mouvements Browniens"+"\n";
	}

	std::string getType() {
		if(type_simu==1) {
			return "Euler Scheme";
		}else{
			return "Analystics Scheme";
		}
	}

	Vasiceck(double init,double delta,double nb_simu,std::vector<double> param_init,vector<double> ZC_initial,
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

	Vasiceck(double init,double delta,double nb_simu,std::vector<double> param_init,int type,vector<double> ZC_initial,
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

	Vasiceck(double init,double delta,double nb_simu,std::vector<double> param_init,std::string fileZCinit) throw(std::string) {
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

	Vasiceck(double init,double delta,double nb_simu,std::vector<double> param_init,int type,std::string fileZCinit) throw(std::string) {
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

	void Vasiceck::next_simu(std::vector<double> alea) throw(std::string) {
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
		double AtT;
		double BtT;
		BtT = (1-exp(-param_t[0]*(T-t)))/param_t[0];
		AtT = exp((param_t[1] -param_t[2]*param_t[2]/(2*param_t[0]*param_t[0]))*(BtT - T -t) - param_t[2]*param_t[2]*BtT*BtT/(4*param_t[0]));
		return AtT*exp(-BtT*val_t);
	}

	double getBondOptionE(double T,double S,double K,int type) {//1 - Call, 2- Put
		if (S>T && ZC_initial.size() < S/delta +1) {
			int w;
			if (type==1) {
				w=1;
			}else{
				w=-1;
			}
			double vol = param_t[2]*sqrt((1-exp(-2*param_t[0]*(T-t)))/param_t[0])*(1-exp(-param_t[0]*(S-T)))/param_t[0];
			double h = log(ZC_initial[T/delta]/(ZC_initial[S/delta]*K))/vol + vol/2;
			return w*(ZC_initial[S/delta]*Outils::RepartitionNormal(w*h) - K*ZC_initial[T/delta]*Outils::RepartitionNormal(w*(h-vol))); 
		}else{
			return -1;
		}
	}

	 double getCap(double T,double deltaT,double K) {
		double somme_caplet = 0;
		int n = T/deltaT;
		for(int i=0;i<n;i++) {
			double caplet = (1+K*deltaT)*getBondOptionE(i*deltaT,(i+1)*deltaT,1/(1+K*deltaT),2);
			if(caplet = -1) {
				cout <<"problème dans l'échéancier" <<endl;
			}
			somme_caplet += caplet;	
		}
		return somme_caplet;
	}

	 double getSwaption(double T1,double T2,double DeltaT) {
		return 0;
	}

};
