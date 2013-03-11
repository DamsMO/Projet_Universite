#include "csvRead.h"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
csvRead::csvRead(const string &file)
{
cout << "ON va lire le fichier : " << file << endl;
  nrow=0;
	ncol=1;
	ifstream fichier(file, ios::in);
	if(fichier)
	{
			string contenu;
			// calcul du nombre de lignes et de colonnes
			while(getline(fichier,contenu))
				nrow++;
			nrow--; // On retire la ligne correspondant aux entêtes
			fichier.clear();
			fichier.seekg(0, ios::beg); //on se remet au début du fichier
			char caract;
			fichier.get(caract);
			while(caract!='\n')
			{
				if(caract==';')
					ncol++;
				fichier.get(caract);
			}
			//

			fichier.clear();
			fichier.seekg(0, ios::beg); //on se remet au début du fichier

			//On récupère les hearers
			headers.resize(ncol);
			for(int j=0;j<ncol-1;j++)
				{
					getline(fichier,contenu,';');//lit l'entrée dans une colonne
					headers[j]=contenu;
				}
			getline(fichier,contenu);//lit l'entrée dans la dernière colonne
			headers[ncol-1]=contenu;
			//

			//On récupère les données chiffrées
			vector<vector<string>> tab2;
			tab2.resize(nrow);
			for(int i=0;i<nrow;i++)
				tab2[i].resize(ncol);
			for(int i=0;i<nrow;i++)
			{
				for(int j=0;j<ncol-1;j++)
				{
					getline(fichier,contenu,';');//lit l'entrée dans une colonne
					tab2[i][j]=contenu;
				}
				getline(fichier,contenu);//lit l'entrée dans la dernière colonne
				tab2[i][ncol-1]=contenu;
			}
			val.resize(nrow); 
			for(int i=0;i<nrow;i++)
			{
				val[i].resize(ncol);
			}
			for(int i=0;i<nrow;i++) // conversion string->double
			{
				for(int j=0;j<ncol;j++)
				{
					string old_string=tab2[i][j];
					char *new_string=new char[old_string.length()+1];
					strcpy(new_string, old_string.c_str());
					val[i][j]=atof(new_string);
					delete[] new_string;
				}
			}
                fichier.close();  // on ferme le fichier
				cout << "FIN de la lecture" <<endl;
	}
        else 
                cout<< "impossible d'ouvrir le fichier !" << endl;
}

std::vector<std::vector<double>> csvRead::getval() {
	return val;
}

double csvRead::getval(int i, int j)
{
	if(i<nrow && j<ncol)
	{
		return val[i][j];
	}
	else
		cout<<"Problème de dimension"<<endl;
}

string csvRead::getheader(int k)
{
	return headers[k];
}
