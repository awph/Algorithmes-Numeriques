#include "real100bits.h"
#include "functions.h"

#include <iostream>

using namespace std;

void pause()
{
	cin.sync();
	cout << "Appuyez sur [Entree] pour continuer.";
	cin.ignore();
}

void clear()
{
	cout << string(50, '\n' );
}
int main()
{
	clear();
	int choix = 0;

	do 
	{
		cout << "|===========================================|" << endl
			 << "|Programme realise par :                    |" << endl
			 << "|                        - Diego Antognini  |" << endl
			 << "|                        - Alexandre Perez  |" << endl
			 << "|                        - Sebastien Vaucher|" << endl
			 << "|===========================================|" << endl;
		do 
		{
			cout << "Menu : " << endl
				<< "1) Convertir un nombre donne" << endl
				<< "2) Effectuer des operations" << endl 
				<< "3) Approximer Pi" << endl
				<< "4) Quitter" << endl << endl
				<< "Choix : ";
			cin >> choix;
			clear();
		}while(choix < 1 || choix > 4);
	
		if(choix == 1)
		{
			string input("");
			cout << "Entrez votre nombre : ";
			cin >> input;
			cout << endl << input << " est interprete : " << endl << endl;
			Real100bits output(input);
			output.printValue();
			pause();
		}
		else if(choix == 2)
		{
			string input1("");
			string input2("");
			cout << "Entrez votre premier nombre (a): ";
			cin >> input1;
			cout << "Entrez votre deuxieme nombre (b): ";
			cin >> input2;

			cout << endl << endl;
			choix = 0;
			do 
			{
			cout << "Operation :" << endl
				 << "1) a + b" << endl
				 << "2) a - b" << endl
				 << "3) a * b" << endl
				 << "4) a / b" << endl;
			cout << "Choix : ";
			cin >> choix;
			}while(choix < 1 || choix > 4);

			Real100bits r1(input1);
			Real100bits r2(input2);
			Real100bits r3("1");

			if(choix == 1)
				r3 = r1+r2;
			else if(choix == 2)
				r3 = r1-r2;
			else if(choix == 3)
				r3 = r1*r2;
			else if(choix == 4)
				r3 = r1/r2;

			cout << input1 << ":" << endl;
			r1.printValue();
			cout << endl << input2 << ":" << endl;
			r2.printValue();
			cout << endl << "Resultat : " << endl;
			r3.printValue();
			choix = 0;
			pause();
		}
		else if(choix == 3)
		{
			int n = 0;
			cout << "Entrez la valeur pour n : ";
			cin >> n;
			cout << "Pi vaut : " << endl;
			Real100bits r(approximationPI(n));
			r.printValue();
			cout << endl << "REMARQUE : A cause des doubles, on a l'impression que le nombre est le meme, mais les bits ont bien change, donc pi est mieux approxime !" << endl;
			pause();
		}
		clear();
	}while(choix != 4);	
}