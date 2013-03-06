
#include<vector>
using namespace std;

class Processus {
private :
	int nb_param ;
	template <class T> vector<T> param;
	double first;

public :
	int get_nb_param();
	template <class T> vector<T> get_param();
	double get_first();
	Processus(int nb,vector<double> p,double x0); 
	virtual double getNext(double delta_t);
	virtual double simul(double delta_t,double T);
}
