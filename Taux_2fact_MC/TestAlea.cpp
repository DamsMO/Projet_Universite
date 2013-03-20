#include "Generateur.cpp"
#include "Outils.h"

class TestAlea {

public:
	vector<vector<double>> res;

	vector<double> verif(vector<vector<vector<double>>> alea) throw(string) {
		double tmp;
		int nb_simu = alea.size();
		int nb_pas = alea[0].size();
		int nb_var = alea[0][0].size();
		vector<double> res = vector<double>(4);//Moy,Var,4-Moment,Correl
		//Construction d'une matrice pour chaque var (Test Moy et Var)
		vector<vector<double>> var = vector<vector<double>>(nb_pas);
		double testM = 0;
		double testV = 0;
		double testK = 0;
		for(int k=0;k<nb_var;k++) {
			testM = 0;
			testV = 0;
			testK = 0;
			for(int j=0;j<nb_pas;j++) {
				var[j] = vector<double>(nb_simu);
				for(int i=0;i<nb_simu;i++) {
					var[j][i] = alea[i][j][k];
				}
				tmp = Outils::MeanEstimate(var[j]);
				testM = testM + tmp ;
				//cout << "Le min de la var " << k << " est " << Outils::min(var[j]) << endl;
				tmp = Outils::VarianceEstimate(var[j]);
				//cout << "Le max de la var " << k << " est " << Outils::max(var[j]) << endl;
				testV = testV + tmp;
				testK = testK + Outils::K_MomentEstimate(var[j],4);
			}
			testM =testM/(nb_pas*1.0);
			testV =testV/(nb_pas*1.0);
			testK =testK/(nb_pas*1.0);
			cout << "La moyenne Moy de la var " << k << " est " << testM << endl;
			cout << "La variance Moy de la var " << k << " est " << testV << endl;
			cout << "Le 4eme moment Moy de la var " << k << " est " << testK << endl;
			res[0] += testM/nb_var;
			res[1] += testV/nb_var;
			res[2] += testK/nb_var;
		}

		//Construction Matrice (Test Correlation)
		vector<vector<double>> var1 = vector<vector<double>>(nb_pas);
		vector<vector<double>> var2 = vector<vector<double>>(nb_pas);
		double testC =0;
		for(int k=0;k<nb_var-1;k++) {
			for(int u=k+1;u<nb_var;u++) {
				testC = 0;
				for(int j=0;j<nb_pas;j++) {
					var1[j] = vector<double>(nb_simu);
					var2[j] = vector<double>(nb_simu);
					for(int i=0;i<nb_simu;i++) {
						var1[j][i] = alea[i][j][k];
						var2[j][i] = alea[i][j][u];
					}
					tmp = Outils::CorrelationEstimate(var1[j],var2[j]);
					//cout << "La correl de la var " << k << " avec la var " << u << " est " << tmp << endl;
					testC = testC + tmp;
				}
				testC =testC/(nb_pas*1.0);
				res[3] += testC/Outils::factoriel(nb_var-1);
				cout << "La correl Moy de la var " << k << " avec la var " << k+1 << " est " << testC << endl;
			}
		}

		return res;
	}

	TestAlea(int nb_simu,int nb_var,int nb_pas,int type_generateur) {
		res = vector<vector<double>>();
		cout << "nb_simu="<<nb_simu<<" nb_var ="<<nb_var<<" nb pas="<<nb_pas<<endl;
		switch(type_generateur) {
			case 1:
				cout << "Test de l'alea du compilateur avec Box-Muller :" <<endl;
				verif(Generateur::Alea_C(nb_var,nb_pas,nb_simu,1));
				cout << "Test de l'alea du compilateur avec Moro/Baesley :" <<endl;
				verif(Generateur::Alea_C(nb_var,nb_pas,nb_simu,2));
				cout <<endl;
				break;
			case 2:
				cout<<"Test de l'alea COngruentiel avec Box-Muller"<<endl;
				verif(Generateur::Alea_Congruentiel(13,nb_var,nb_pas,nb_simu,1));
				cout<<"Test de l'alea COngruentiel avec Moro/Baesley"<<endl;
				verif(Generateur::Alea_Congruentiel(13,nb_var,nb_pas,nb_simu,2));
				cout<<endl;
				break;
			case 3:
				cout<<"Test de l'alea SOBOL avec Quantlib"<<endl;
				verif(Generateur::Alea_Sobol_QMC(nb_var,nb_pas,nb_simu));
				cout<<endl;
				break;
			default:
				cout <<"Bienvenur dans le test de l'alea, c'est a vous de faire les test avec la fonction verif"<<endl;
		}
	}


	void TestMonteCarlo(int nb_simu,int nb_var,int nb_pas,int type_generateur,int type_inverse) {
		cout << "nb_simu="<<nb_simu<<" nb_var ="<<nb_var<<" nb pas="<<nb_pas<<endl;
		res.resize(10);
		for(int i=0;i<10;i++) {
			res[i].resize(4);
			switch(type_generateur) {
				case 1:
					cout << "Test de l'alea du compilateur" <<endl;
					res[i] = verif(Generateur::Alea_C(nb_var,nb_pas,nb_simu+i*nb_simu,type_inverse));
					cout <<endl;
					break;
				case 2:
					cout<<"Test de l'alea COngruentiel "<<endl;
					res[i] = verif(Generateur::Alea_Congruentiel(13,nb_var,nb_pas,nb_simu+i*nb_simu,type_inverse));
					cout<<endl;
					break;
				case 3:
					cout<<"Test de l'alea SOBOL avec Quantlib"<<endl;
					res[i] = verif(Generateur::Alea_Sobol_QMC(nb_var,nb_pas,nb_simu+i*nb_simu));
					cout<<endl;
					break;
			}
		}
		for(int j=0;j<4;j++) {
			for(int i=0;i<10;i++) {
				cout << i<<" "<<j <<res[i][j] <<endl ;
			}
			cout << endl;
		}


	}

};	//C71732D7FDAE1CC66135F4F5CFCC7F