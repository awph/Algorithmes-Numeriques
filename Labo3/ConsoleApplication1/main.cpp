#include "src/linalg.h"

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

int main () 
{
	srand(time(NULL));

	int n = 500;
	int min = 0,max = 10;

	string matrix = "[";
	for(int i = 0;i < n;++i)
	{
		matrix += "[";
		for(int j = 0;j < n;++j)
		{
			ostringstream oss;
			oss << (rand() % max + min);
			matrix += oss.str();
			matrix += ",";
		}
		matrix[matrix.size()-1] = ']';
		matrix += ",";
	}
	matrix[matrix.size()-1] = ']';
	//cout << matrix;
	system("PAUSE");
	alglib::real_2d_array b = matrix.c_str();
	cout << rmatrixdet(b) << endl;

	system("PAUSE");
}
