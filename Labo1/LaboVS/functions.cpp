#include "functions.h"
#include "real100bits.h"
#include <sstream>

/// Fonctionne pour des tableaux avec des int € [0;9]
/// Attention cas spécial, si le tableau contient que des zéros, renvoi 1 !
/// Gere le cas ou le tableau est de taille 1 et avec un 0
std::string convert10to2(int tabValues[],const int length,const int prec)
{
	if(onlyZero(tabValues, length)) 
		return "0";

	int d = prec;
	char c;
	std::string result;

	do 
	{
		if(tabValues[length-1] % 2 == 0)
			c = '0';
		else
		{
			c = '1';
			tabValues[length-1]--;
		}

		int next = 0;
		int templength = length;

		for(int i = 0; i < length; ++i)
		{
			int tempNext = 0;
			if(tabValues[i] % 2 != 0)
				tempNext = 5;
			tabValues[i] /= 2;
			tabValues[i] += next;
			next = tempNext;
			if(tabValues[i] == 0)
				templength--;
		}

		if(templength <= 0)
		{
			result = "1" + result;
			break;
		}
		else
			result = c + result;
	} while(d-- > 0);

	return result;
}

const std::string convertDecimale10to2(int tabValues[],const int length,const int prec)
{
	if(onlyZero(tabValues, length)) 
		return "0"; 

	int d = prec;

	char c = 0;
	std::string result("");

	do 
	{
		if(tabValues[0] * 2 >= 10)
			c = '1';
		else
			c = '0';

		int next = 0;
		int templength = length;

		for(int i = length - 1; i >= 0; --i)
		{
			int tempNext = 0;
			tabValues[i] *= 2;

			if(tabValues[i] >= 10)
			{
				tempNext = 1;
				tabValues[i] -= 10;
			}

			tabValues[i] += next;
			next = tempNext;

			if(tabValues[i] == 0)
				templength--;
		}

		if(templength <= 0)
		{
			result += "1";
			break;
		}
		else
			result += c;
	} while(d-- > 0);

	return result;
}

bool onlyZero(const int tabValues[], const int length)
{
	bool hasOnlyZero  = true;
	for(int i = 0; i < length; ++i)
	{
		if(tabValues[i] != 0)
		{
			hasOnlyZero = false;
			break;
		}
	}
	return hasOnlyZero;
}

int convert2to10(const std::string& input)
{
	int output = 0;
	int mul = 1;

	for(int j = input.length()-1;j >= 0;--j,mul *= 2)
		if(input[j] == '1')
			output += mul;

	return output;
}

int* convertStringToTabInt(const std::string& intput)
{
	int* output = new int[intput.length()];

	for(unsigned int i = 0;i < intput.length();++i)
		output[i] = intput[i]%48;//Convertit en char, donc il faut faire %48

	return output;
}

bool tabPlusOne(bool tab[], int length)
{
	for(int i = 0; i < length; i++)
	{
		if(tab[i] == false)
		{
			tab[i] = true;
			return true;
		}
		else
			tab[i] = false;
	}
	// Overflow !!
	return false;
}

bool tabMinusOne(bool tab[], int length)
{
	bool* one = new bool[length];
	std::fill_n(one, length, false);
	one[0] = true;
	bool* res = sous(tab, one, length);

	for(int i = 0; i < length; i++)
		tab[i] = res[i];

	delete[] one;
	delete[] res;

	return true;
}

bool shiftLeft(bool tab[], int length, bool padding)
{
	bool out = tab[0]; // To return
	for(int i = 0; i < length -1; i++)
		tab[i] = tab[i+1];
	
	tab[length-1] = padding;
	return out;
}

bool shiftRight(bool tab[], int length, bool padding)
{
	bool out = tab[length -1]; // To return
	for(int i = length -1; i > 0; i--)
		tab[i] = tab[i-1];
	
	tab[0] = padding;
	return out;
}

bool* sum(const bool b1[], const bool b2[], const int length)
{
	bool* result = new bool[length+1]; // +1 pour le cas où le MSB des deux tableaux sont true.
	bool retenu = false;

	for (int i = 0; i < length; ++i)
	{
		result[i] = false;

		int sum = (retenu) ? 1 : 0;
		sum += (b1[i]) ? 1 : 0;
		sum += (b2[i]) ? 1 : 0;

		if(sum == 1)
		{
			result[i] = true;
			retenu = false;
		}
		else if(sum == 2)
			retenu = true;
		else if(sum == 3)
		{
			result[i] = true;
			retenu = true;
		}
	}

	result[length] = retenu;

	return result;
}

bool* sous(const bool b1[], const bool b2[], const int length)
{
	bool* b2Inv = new bool[length];
	for(int i = 0; i < length; ++i)
		b2Inv[i] = !b2[i];

	bool* btemp = new bool[length];
	std::fill_n(btemp, length, false);
	btemp[0] = true;

	bool* b2Compl2 = sum(b2Inv, btemp, length);

	bool* output = sum(b1, b2Compl2, length);

	delete[] btemp;
	delete[] b2Inv;
	delete[] b2Compl2;

	return output;
}

bool* product(const bool b1[], const bool b2[], const int length)
{
	bool* result = new bool[2*length];
	std::fill_n(result,length*2,false);

	for (int i = 0; i < length; ++i)
	{
		if(b1[i])
		{
			bool* temp = new bool[length + i];
			std::fill_n(temp,length + i,false);

			for(int j = 0; j < length; ++j)
				temp[j+i] = b2[j];

			bool* tempResult = sum(result,temp,length+i);

			for(int j = 0; j < length + i + 1; ++j)
				result[j] = tempResult[j];

			delete[] tempResult;
			delete[] temp;
		}
	}

	return result;
}

bool* div(const bool b1[], const bool b2[], const int length)
{
	// http://www.csgnetwork.com/binmultdivcalc.html
	// 100b2 / 101b2	==		shiftLeft(1000b2 / 101b2)
	//*
	bool* result = new bool[2*length+1];	
	bool* b1Temp = new bool[2*length+1];
	bool* b2Temp = new bool[2*length+1];
	std::fill_n(result,2*length+1,false);
	std::fill_n(b1Temp,2*length+1,false);
	std::fill_n(b2Temp,2*length+1,false);
	
	for (int i = length; i < 2*length; ++i)
	{
		b1Temp[i] = b1[i-length];
		b2Temp[i] = b2[i-length];
	}

	for (int i = 2*length; i >= 0; --i)
	{
		// Si le diviseur est plus grand que le divisé, alors on shift le divisé pour qu'il soit plus grand
		if(isBigger(b2Temp,b1Temp, 2*length+1))
			shiftRight(b1Temp, 2*length+2);
		else 
		{
			b1Temp = sous(b1Temp, b2Temp,2*length+1);
			result[i] = true;
			shiftLeft(b2Temp,2*length+1);
		}
	}

	return result;
}

bool isBigger(const bool b1[], const bool b2[], const int length)
{
	for(int i = length-1; i >= 0; --i)
		if(b1[i] != b2[i])
			return b1[i];
	return true;
}

Real100bits approximationPI(const int n)
{	
	Real100bits output("1");//initialiser

	Real100bits numerateur1("4");
	Real100bits numerateur2("-2");
	Real100bits numerateur3("-1");
	Real100bits numerateur4("-1");

	Real100bits diviseurCoeffP1("8");

	Real100bits diviseur1P2("1");
	Real100bits diviseur2P2("4");
	Real100bits diviseur3P2("5");
	Real100bits diviseur4P2("6");

	Real100bits multiplicateur("0.0625");

	for(int i = 0;i <= n;++i)
	{
		Real100bits puissance(multiplicateur);
		puissance ^= i;

		std::stringstream ss;
		ss << i;
		std::string number = ss.str();
		
		Real100bits diviseurP1(diviseurCoeffP1*number);

		Real100bits p1(numerateur1/(diviseurP1+diviseur1P2));
		Real100bits p2(numerateur2/(diviseurP1+diviseur2P2));
		Real100bits p3(numerateur3/(diviseurP1+diviseur3P2));
		Real100bits p4(numerateur4/(diviseurP1+diviseur4P2));

		Real100bits res((p1+p2+p3+p4)*puissance);
		output = (i==0) ? res : output + res;
	}

	return output;
}