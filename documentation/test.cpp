#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fichier("fichier.data");

    if (fichier)
    {
        //L'ouverture s'est bien passée, on peut donc lire

        string ligne; //Une variable pour stocker les lignes lues
        fichier.seekg(9, ios::beg);
        fichier >> ligne;
        cout << ligne;
        // while (getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        // {
        //     cout << ligne << endl;

        //     //Et on l'affiche dans la console
        //     //Ou alors on fait quelque chose avec cette ligne
        //     //À vous de voir
        // }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    return 0;
}