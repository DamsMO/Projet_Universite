#include <vector>
#include<time.h>
#include<math.h>
#include<cmath>
#include "csvRead.h"

using namespace std;

class Generateur {
private :
	
	static vector<vector<vector<double>>> stockage(vector<double> alea,int nb_var,int nb_pas_de_temps,int nb_simu) {
		int nb = 0;
		//Stockage de l'alea
		vector<vector<vector<double>>> simu = vector<vector<vector<double>>>(nb_simu);
		for(int i=0;i<nb_simu;i++) {
			vector<vector<double>> temps = vector<vector<double>>(nb_pas_de_temps);
			for(int j=0;j<nb_pas_de_temps;j++) {
				vector<double> var = vector<double>(nb_var);
				for(int k=0;k<nb_var;k++) {
					var[k] = alea[nb];
					nb++;
				}
				temps[j] = var;
			}
			simu[i] = temps;
		}

		return simu;
	}
	
	static vector<double> BoxMuller(double uni1,double uni2) {
		double pi = 3.14;
		vector<double> res = vector<double>(2);
		res[0] = sqrt(uni1)*cos(2*pi*uni2);
		res[1] = sqrt(uni1)*sin(2*pi*uni2);
		return res;
	}

public :
	static vector<vector<vector<double>>> Alea_Sobol_QMC(int nb_var,int nb_pas_de_temps,int nb_simu) {
	
		//Creation de l'alea
		int nbAlea = nb_var*nb_pas_de_temps*nb_simu;
		csvRead csvAlea = csvRead("Sobol_600__10000.csv");//Sobol_600__10000.csv
		vector<vector<double>> alea = csvAlea.getval();
		for(int i=0;i<nb_var;i++) {
			for(int j=0;j<nb_pas_de_temps;j++) {
				cout << alea[i][j] ;
			}
			cout <<endl;
		}
		 vector<vector<vector<double>>> tmp;
		 return tmp;
	//	return stockage(alea,nb_var,nb_pas_de_temps,nb_simu);
		
	}

	static vector<vector<vector<double>>> Alea_C(int nb_var,int nb_pas_de_temps,int nb_simu) {
	
		//Creation de l'alea
		int nbAlea = nb_var*nb_pas_de_temps*nb_simu;
		vector<double> alea = vector<double>(nbAlea);
		srand(time(NULL));
		for(int i=0;i<nbAlea;i=i+2) {
			vector<double> tmp = BoxMuller(rand(),rand());
			alea[i] = tmp[0];
			alea[i+1] = tmp[1];
		}

		return stockage(alea,nb_var,nb_pas_de_temps,nb_simu);
		
	}

static vector<vector<vector<double>>> Alea_Congruentiel(int nb_var,int nb_pas_de_temps,int nb_simu) {
	
		//Creation de l'alea
		vector<double> uni = vector<double>(nb_simu/2);
		for(int i=0;i<nb_simu/2;i++) {
			uni[i] = (i+1)*2/nb_simu;
		}
		for(int i=0;i<(nb_simu)/2;i=i+2) {
			vector<double> tmp = BoxMuller(uni[i],uni[i+1]);
			uni[i] = tmp[0];
			uni[i+1] = tmp[1];
		}
		//Mélange

		int nbAlea = nb_var*nb_pas_de_temps*nb_simu;
		vector<double> alea = vector<double>(nbAlea);
		srand(time(NULL));
		for(int i=0;i<nbAlea;i=i+2) {
			vector<double> tmp = BoxMuller(rand(),rand());
			alea[i] = tmp[0];
			alea[i+1] = tmp[1];
		}

		return stockage(alea,nb_var,nb_pas_de_temps,nb_simu);
		
	}
};
