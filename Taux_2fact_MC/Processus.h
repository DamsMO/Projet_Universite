#include<vector>
#include<string>


class Processus {
protected :
	std::vector<double> param_t; //Les param du process à instant donné
	double t; //instant du process
	double val_t; //val du process en t
	int nb_MB; //nb de MB necessaire à la simulation

public :
	double getVal();
	double getTime();
	std::vector<double> getParam();
	void setParam(std::vector<double> new_param);
	//Calcule la valeur suivante du processus, suivant un alea et un pas de temps
	//Change les attributs t,val_t et param_t(si nécessaire)
	virtual void next_simu(double delta,std::vector<double> alea) =0;
	int getNbMB();
	virtual std::string toString() =0;
};
