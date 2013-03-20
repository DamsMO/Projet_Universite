#include <vector>
#include<time.h>
#include<math.h>
#include<time.h>
#include<cmath>
#include "csvRead.h"
#include "Outils.h"

using namespace std;
//Type inverse : 1-Box Muller, 2-Moro/Baesley
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
		double pi = 3.1416;
		vector<double> res = vector<double>(2);
		res[0] = sqrt(uni1)*cos(2*pi*uni2);
		res[1] = sqrt(uni1)*sin(2*pi*uni2);
		return res;
	}

public :
	static vector<vector<vector<double>>> Alea_Sobol_QMC(int nb_var,int nb_pas_de_temps,int nb_simu) {
		clock_t deb,fin;
		deb=clock();
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
		 fin = clock();
		 cout << "Tps de lecture du fichier sobol : " << (fin-deb)/(1.0*CLOCKS_PER_SEC) << endl;
		 return tmp;
	//	return stockage(alea,nb_var,nb_pas_de_temps,nb_simu);
		
	}

	static vector<vector<vector<double>>> Alea_C(int nb_var,int nb_pas_de_temps,int nb_simu,int type) {
		clock_t deb,fin;
		deb = clock();
		//Creation de l'alea
		int nbAlea = nb_var*nb_pas_de_temps*nb_simu;
		vector<double> alea = vector<double>(nbAlea);
		srand(time(NULL));
		for(int i=0;i<nbAlea;i=i+2) {
			if (type==1) {
				vector<double> tmp = BoxMuller(rand()/(double)(RAND_MAX),rand()/(double)(RAND_MAX));
				alea[i] = tmp[0];
				alea[i+1] = tmp[1];
			}else{
				alea[i] = Outils::InverseRepartitionNormal(rand()/(double)(RAND_MAX));
				alea[i+1] = Outils::InverseRepartitionNormal(rand()/(double)(RAND_MAX));
			}
		}
		fin = clock();
		 cout << "Tps de creation de ml'alea via le compilateur : " << (fin-deb)/(1.0*CLOCKS_PER_SEC) << endl;
		 cout << "Max de l'alea : " << Outils::max(alea) << " et Min : " << Outils::min(alea) <<endl;

		return stockage(alea,nb_var,nb_pas_de_temps,nb_simu);
		
	}

static vector<vector<vector<double>>> Alea_Congruentiel(int graine,int nb_var,int nb_pas_de_temps,int nb_simu,int type) {
		clock_t deb,fin;
		deb = clock();
		//Creation de l'alea
		vector<double> uni = vector<double>(nb_simu/2.0);
		for(int i=0;i<nb_simu/2.0;i++) {
			uni[i] = (i+1)/(1.0*(nb_simu+1));
		}
		for(int i=0;i<((nb_simu)/2)-1;i=i+2) {
			if(type==1) {
				vector<double> tmp = BoxMuller(uni[i],uni[i+1]);
				uni[i] = tmp[0];
				uni[i+1] = tmp[1];
			}else{
				uni[i] = Outils::InverseRepartitionNormal(uni[i]);
				uni[i+1] = Outils::InverseRepartitionNormal(uni[i+1]);
			}
		}
		double stock = 0;
		for(int i=0;i<nb_simu/2;i++) {
			stock = stock + (uni[i]*uni[i]);
		}
		stock = sqrt(2*stock/(1.0*(nb_simu-1)));

		vector<double> norm = vector<double>(nb_simu);
		for(int i=0;i<nb_simu/2;i++) {
			norm[i] = uni[i]/stock;
			norm[i+nb_simu/2] = -norm[i];
		}
		//Mélange
		//cout << "Debut Melane COngruentiel" << endl;
		int nb = nb_var*nb_pas_de_temps;
		vector<vector<double>> rang = vector<vector<double>>(nb_simu);
		vector<vector<double>> y = vector<vector<double>>(nb_simu);
		vector<vector<double>> z = vector<vector<double>>(nb_simu);

		//Initialisation
		for(int i=0;i<nb_simu;i++) {
			rang[i] = vector<double>(nb);
			y[i] = vector<double>(nb);
			z[i] = vector<double>(nb);
		}
		rang[0][0] = (nb_simu/2)-1;
		y[0][0] = norm[nb_simu/2];
		z[0][0] = y[0][0];
		//Melange
		for(int j=1;j<nb;j++) {
			rang[0][j] = 21*rang[0][j-1] + graine - nb_simu*int((21*rang[0][j-1] + graine)/nb_simu);
			//cout << rang[0][j]<<endl;
			y[0][j] = norm[rang[0][j]];
			z[0][j] = y[0][j];
		}
		//cout <<"TEst"<<endl;
		for(int j=0;j<nb;j++) {
			for(int i=1;i<nb_simu;i++) {
				rang[i][j] = 21*rang[i-1][j] + 13 - nb_simu*int((21*rang[i-1][j] + 13)/nb_simu);
				//cout << rang[i][j] << endl;
				y[i][j] = norm[rang[i][j]];
				z[i][j] = y[i][j];
			}
		}
		cout << "Normalisation" <<endl;
		//Normalisation du vecteur
		vector<double> rho = vector<double>(nb);
		double std1;
		double std2;
		for(int j=1;j<nb;j++) {
			for(int k=0;k<j-1;k++) {
				rho[k] = 0;
				std1 = 0;
				std2 = 0;
				for(int i=0;i<nb_simu;i++) {
					rho[k] = rho[k] + y[i][j]*z[i][k];
					std1 = std1 + y[i][j]*y[i][j];
					std2 = std2 + z[i][k]*z[i][k];
				}
				rho[k] = rho[k]/sqrt(std1*std2);
				for(int i=0;i<nb_simu;i++) {
					z[i][j] = z[i][j] -rho[k]*z[i][k];
				}
			}
			std1 = 0;
			for(int i=0;i<nb_simu;i++) {
				std1 = std1 + z[i][j]*z[i][j];
			}
			std1 = sqrt(std1/(nb_simu-1));
			for(int i=0;i<nb_simu;i++) {
				z[i][j] = z[i][j]/std1;
			}
		}
		//STockage
		//cout << "stockage" <<endl;
		vector<vector<vector<double>>> alea = vector<vector<vector<double>>>(nb_simu);
		for(int i=0;i<nb_simu;i++) {
			alea[i] = vector<vector<double>>(nb_pas_de_temps);
			for(int j=0;j<nb_pas_de_temps;j++) {
				alea[i][j] = vector<double>(nb_var);
				for(int k=0;k<nb_var;k++) {
					alea[i][j][k] = z[i][j*nb_var+k];
					//cout << alea[i][j][k] << " - ";
				}
				//cout << " _____ ";
			}
			//cout<<endl<<endl;
		}
		fin = clock();
		 cout << "Tps de creation alea via Gen Congruentiel : " << (fin-deb)/(1.0*CLOCKS_PER_SEC) << endl;
		return alea;
	}

};
