#include<vector>
#include "Generateur.cpp"
#include "Processus.h";

class Simulateur {
private :
	std::vector<std::vector<std::vector<double>>> alea; //nb simu, nb pas de temps, cas ou il y a plusieurs MB
	int type_generateur;//1 - C++, 2-Congruentiel, 3-Sobol
	int nb_simu;
	int nb_pas;
	int pas;
	int nb_MB;
	std::vector<Processus*> tab_process;
	
public :
	Simulateur(int type,std::vector<Processus*> init,int nb_simu,double T,int delta) {
		pas = delta;
		type_generateur = type;
		tab_process = init;
		int nb_pas = T/delta +1;
		nb_MB=0;
		for(int i=0;i<init.size();i++) {
			nb_MB += init[i]->getNbMB();
		}

		switch (type_generateur) {
		case 1:
			alea = Generateur::Alea_C(nb_MB,nb_pas,nb_simu);
			break;
		case 2:
			alea = Generateur::Alea_Congruentiel(nb_MB,nb_pas,nb_simu);
			break;
		case 3:
			alea = Generateur::Alea_Sobol_QMC(nb_MB,nb_pas,nb_simu);
			break;
		}
	}

	std::vector<std::vector<std::vector<double>>> simulation() throw(string) {
		
		std::vector<std::vector<std::vector<double>>> res_simu = std::vector<std::vector<std::vector<double>>>(alea.size());

		for(int i=0;i<alea.size();i++) { //Pour chaque simu
			std::vector<std::vector<double>> tmp_pas_proc = std::vector<std::vector<double>>(alea[i].size());
			for(int j=0;j<alea[i].size();j++) { //Pour chaque pas de temps
				std::vector<double> tmp_proc = std::vector<double>(alea[i][j].size());
				int nb=0;
				for(int k=0;k<alea[i][j].size();k++) { //Pour chaque process
					//Gestion du nb de MB par process
					Processus *p = tab_process[k];
					std::vector<double> tmp_MB = std::vector<double>(p->getNbMB());
					for(int u=0;u<tmp_MB.size();u++) {
						tmp_MB[u] = alea[i][j][nb+u]; 
					}
					nb += p->getNbMB();

					//init if j=0
					if(j=0) {
						res_simu[i][j][k] = p->next_simu(pas,tmp_MB,p->getVal());
					}else{
						res_simu[i][j][k] = p->next_simu(pas,tmp_MB,res_simu[i][j-1][k]);
					}
				}
			}
		}
	}

};
