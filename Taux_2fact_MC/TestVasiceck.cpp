#include "Vasiceck.cpp"


class TestVasiceck {
public :

	TestVasiceck() {
		int r0= 0.01;
		int nb_simu= 1000;
		double delta = 3.0/12.0;
		vector<double> param = vector<double>(3);
		param[0] = 0.5;
		param[1] = 0.03;
		param[2] = 0.1;
		vector<double> ZC_init = vector<double>(100);
		vector<double> echeance = vector<double>(100);
		for(int i=0;i<100;i++) {
			ZC_init[i] = exp(-(i+1)*delta*0.02);
			echeance[i] = (i+1)*delta;
		}
		//Creation de tous les constructeurs
		Vasiceck v = Vasiceck(r0,delta,nb_simu,param,ZC_init,echeance);
		cout << v.toString() << endl;
		
	//	string file = "
		//v =Vasiceck(r0,delta,nb_simu,param,file);



	}


};