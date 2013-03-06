#include <vector>
using namespace std;

static class Generateur {

	static vector<vector<double>> genereNormalCongruentiel(int nb_var,int nb_simu);
	static vector<vector<double>> genereNormalSobol(int nb_var,int nb_simu);
}