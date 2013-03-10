#include "Processus.h"

std::vector<double> Processus::getParam() {
	return param_t;
}

double Processus::getVal() {
	return val_t;
}

double Processus::getTime() {
	return t;
}
int Processus::getNbMB() {
	return nb_MB;
}
void Processus::setParam(std::vector<double> new_param) {
	param_t = new_param;
}


	

