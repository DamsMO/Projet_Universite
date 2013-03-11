#include "Processus.h"
#include "csvRead.h"
#include <vector>

using namespace std;

class Taux : protected Processus {
protected :
	//La courbe de taux initiale déjà interpolé
	//A interpolé suivant les calculs de ZC(t,T), Caps et Swaption voulus
	vector<double> ZC_initial;
	vector<double> echeancier;
public :
	vector<double> getZC_init();
	vector<double> getEcheancier();
	//Ces prix sont suivant des formules analytiques
	virtual double getZC(double T) = 0;
	virtual double getCap(double T,double DeltaT) = 0;
	virtual double getSwaption(double T1,double T2,double DeltaT) = 0;
};


