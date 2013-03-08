#ifndef CSVREAD_H_
#define CSVREAD_H_

#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <cstring>
#include <vector>
class csvRead
{
public:
  csvRead(const std::string &file); //argument du constructeur= chemin vers le fichier csv à lire
	int getnrow() {return nrow;}
	int getncol() {return ncol;}
	double getval(int i, int j); //renvoie la valeur de la ième ligne (sans compter la ligne header) et jème colonne
	std::string getheader(int k); //renvoie le kème header
private:
	std::vector<std::vector<double>> val;
	std::vector<std::string> headers;
	int nrow;
	int ncol;
};
#endif
