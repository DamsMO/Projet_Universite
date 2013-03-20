#include "Processus.h"
#include "csvRead.h"
#include <vector>

using namespace std;

class Taux : public Processus {
protected :
	//La courbe de taux initiale déjà interpolé
	//A interpolé suivant les calculs de ZC(t,T), Caps et Swaption voulus
	vector<double> ZC_initial;
	vector<double> echeancier;
public :
	vector<double> getZC_init();
	vector<double> getEcheancier();
	//Ces prix sont suivant des formules analytiques
	virtual double getZC(double T);
	virtual double getCap(double T,double DeltaT,double K);
	virtual double getSwaption(double T1,double T2,double DeltaT);
};


