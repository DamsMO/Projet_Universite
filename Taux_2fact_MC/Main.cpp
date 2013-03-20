#include<iostream>
#include "TestAlea.cpp"
#include "Vasiceck.cpp"

using namespace std;

int main() {

	cout << "Bienvenue dans le simulateur de proc sto" <<endl;

	cout << "Test des Alea !" <<endl;
	TestAlea test = TestAlea(1,1,1,8);//C
	test.TestMonteCarlo(5000,2,10,2,1);

	//test = TestAlea(1000,4,100,3);

	//test = TestAlea(10000,3,100,2);
	int stop;

	//Generateur::Alea_Sobol_QMC(10,10,10);
	cin >> stop;
	return 0;

}
