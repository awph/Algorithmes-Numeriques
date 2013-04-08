#include "include/squarematrix.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	SquareMatrix<3,double> m(2);
	SquareMatrix<3,double> m2(m);
	cout << m;
	cout << m2;
	cout << m*m2;
	cout << m.determinant();
    //Test GenericMatrix
	/*GenericMatrix<3,3,double> a(2.333333);
	cout << a+a;
	cout << a-a;
	cout << a*a;
	//Constructors
	{
		//Not supposed to work
		// GenericMatrix<0,0,int> a(0); //OK
		//GenericMatrix<-1,-1,double> a(0.05); //OK
		cout << "Constructor with default value" << endl;
		GenericMatrix<3,3,double> a(2.5);
		cout << a;
		GenericMatrix<3,3,double> c(a);
		cout << c;
		c.fill(2);
		cout << a << endl << c;

		cout << "Constructor with an array 2D" << endl;
		int tab[4][4] = {{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}};
		GenericMatrix<4,4,int> b(tab);
		cout << b;

		GenericMatrix<4,4,int*> d(new int(25));
		d.~GenericMatrix();
		cin.get();
		cout << string(100,'\n');
	}

	//Functions
	{
		{
			int tab[4][4] = {{1,2,3,4},
			{5,6,7,8},
			{9,10,11,12},
			{13,14,15,16}};
			GenericMatrix<4,4,int> b;
			cout << "B with tab" << endl;
			b.init(tab);
			cout << b;

			cout << "B with -5 " << endl;
			b.fill(-5);
			cout << b;
		}
		{
			cout << "Transpose" << endl;
			GenericMatrix<3,2,double> b(1);
			b(0,0) = 2;
			b(0,1) = 34;
			b(1,0) = 6;
			b(1,1) = -1;
			cout << "B:" << endl << b << endl;
			cout << "Bt:" << endl;
			cout << b.transpose();
			cin.get();
			cout << string(100,'\n');
		}
	}

	//Get
	{
		cout << "GET" << endl;
		GenericMatrix<3,2,float> a(-1);
		cout << "A:" << endl << a << endl;

		cout << "Rows : " << a.rows() << endl
			 << "Cols : " << a.cols() << endl;
		cin.get();
		cout << string(100,'\n');
	}

	//Operator
	{
		{
			cout << "OPERATORS" << endl;
			cout << "A+=B" << endl;

			GenericMatrix<3,4,int> a(1);
			int tab[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
			GenericMatrix<3,4,int> b(tab);

			cout << "A:" << endl;
			cout << a;
			cout << "B:" << endl;
			cout << b;
			cout << "---------------------------" << endl;

			a+=b;
			cout << a;
			cin.get();
			cout << string(100,'\n');
		}

		{
			cout << "OPERATORS" << endl;
			cout << "A-=B" << endl;

			GenericMatrix<3,4,int> a(1);
			int tab[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
			GenericMatrix<3,4,int> b(tab);

			cout << "A:" << endl;
			cout << a;
			cout << "B:" << endl;
			cout << b;
			cout << "---------------------------" << endl;

			a-=b;
			cout << a;
			cin.get();
			cout << string(100,'\n');
		}

		{
			cout << "OPERATORS" << endl;
			cout << "A*=t" << endl;

			GenericMatrix<3,4,int> a(1);
			int t = 8;

			cout << "A:" << endl;
			cout << a;
			cout << "t=" << t << endl;

			a*=t;
			cout << a;
			cin.get();
			cout << string(100,'\n');
		}

		{
			cout << "OPERATORS" << endl;
			cout << "A/=t" << endl;

			GenericMatrix<3,4,double> a(1);
			double t = 8;

			cout << "A:" << endl;
			cout << a;
			cout << "t=" << t << endl;

			a/=t;
			cout << a;
			cin.get();
			cout << string(100,'\n');
		}

		{
			cout << "OPERATORS" << endl;
			cout << "A==B" << endl;
			cout << "A==A" << endl;
			GenericMatrix<3,3,double> a(2.5);

			double tab[3][3] = {{1,2.5,3},
			{5,6.5,7},
			{9,10.5,3.14}};
			GenericMatrix<3,3,double> b(tab);

			cout << "A:" << endl << a << endl;
			cout << "B:" << endl << b << endl;
			bool etat;
			etat = a==a;
			cout << "A==A : " << boolalpha << etat << endl;
			etat = a==b;
			cout << "A==B : " << boolalpha << etat << endl;
			etat = a!=a;
			cout << "A!=A : " << boolalpha << etat << endl;
			etat = a!=b;
			cout << "A!=B : " << boolalpha << etat << endl;
			etat = b==b;
			cout << "B==B : " << boolalpha << etat << endl;

			cin.get();
			cout << string(100,'\n');

			GenericMatrix<3,3,double> c(tab);
			GenericMatrix<3,3,double> d(tab);
			c(2,2)=12.421341234152452545243*2;
			d(2,2)=12.421341234152452545243*2+0.00000000000000000000001;
			cout << "C:" << c << endl << "D:" << d << endl;
			etat = c==d;
			cout << "C==D : " << boolalpha << etat << endl;
			etat = d==c;
			cout << "C==D : " << boolalpha << etat << endl;

			cin.get();
			cout << string(100,'\n');
		}

		{
			cout << "OPERATORS" << endl;
			cout << "A(1,2)" << endl;

			double tab[3][3] = {{1,2,3},
			{5,6,7},
			{9,10,11}};
			GenericMatrix<3,3,double> a(tab);
			cout << "A:" << endl << a << endl;

			cout << "A(1,2) : " << a(1,2) << endl;
			cout << "A(1,2) = 8" << endl;
			cout << "A:" << endl;
			a(1,2) = 8;
			cout << a << endl;
			cin.get();
			cout << string(100,'\n');
		}
		{
			{
				cout << "OPERATORS" << endl;
				cout << "A+B" << endl;
				cout << "A-B" << endl;
				cout << "A*B" << endl;
				cout << "-A" << endl;
				cout << "t*A" << endl;
				cout << "A*t" << endl;
				cout << "A/t" << endl;

				GenericMatrix<2,3,double> a(2);
				GenericMatrix<2,3,double> b(3);
				double t = 2.5;

				cout << "A:" << endl << a << endl;
				cout << "B:" << endl << b << endl;
				cout << "t:" << endl << t << endl;
				cout << "A+B" << endl;
				cout << a+b << endl;
				cout << "A-B" << endl;
				cout << a-b << endl;
				cout << "-A" << endl;
				cout << -a << endl;
				cout << "t*A" << endl;
				cout << t*a << endl;
				cout << "A*t" << endl;
				cout << a*t << endl;
				cout << "A/t" << endl;
				cout << a/t << endl;
				cin.get();
				cout << string(100,'\n');
			}

			{
				GenericMatrix<2,3,double> a(2);
				GenericMatrix<3,5,double> b(3);

				cout << "A:" << endl << a << endl;
				cout << "B:" << endl << b << endl;
				cout << "A*B" << endl;
				cout << a*b << endl;
				cin.get();
				cout << string(100,'\n');
			}
		}
	}*/

	return 0;
}
