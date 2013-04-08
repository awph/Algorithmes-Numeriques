#include "real100bits.h"
#include "functions.h"

#include <cctype> //isdigit
#include <cmath> //pow
#include <iostream>
#include <sstream>
#include <algorithm>//fill_n
#include <iomanip> //setPrecision

using namespace std;

Real100bits::Real100bits(const string& completeValueb10):type(Valid),S(1),M(0L),E(0),s(false)
{
	//Initilialise les tableaux
	fill_n(m,SIZE_M,false);
	fill_n(e,SIZE_E,false);

	s = (completeValueb10[0] == '-');

	if((s && completeValueb10.length() == 1) || completeValueb10.length() == 0)
		type = NaN;
	else if(completeValueb10.find_first_of(',') != completeValueb10.find_last_of(',') || completeValueb10.find_first_of('.') != completeValueb10.find_last_of('.'))//Si pas présent, doit être égal à str::npos
		type = NaN;
	else
	{
		for(unsigned int i = (s) ? 1 : 0;completeValueb10[i] != ',' && completeValueb10[i] != '.' && i < completeValueb10.length() && type == Valid;++i)
			if(!isdigit(completeValueb10[i]))
				type = NaN;

		if(type != Valid)
			return;

		string integer("");
		
		//Vérifie la présence de 0 seul afin de gérer le cas +-0
		bool isZero = true;
		for(unsigned int i = (s) ? 1 : 0;i < completeValueb10.length() && isZero;++i)
			if(completeValueb10[i] != '0' && completeValueb10[i] != ',' && completeValueb10[i] != '.')
				isZero = false;

		if(isZero)
			type = Zero;
		else
		{
			unsigned int i = (s) ? 1 : 0;

			for(;completeValueb10[i] != ',' && completeValueb10[i] != '.' && i < completeValueb10.length();++i)
				integer += completeValueb10[i];
	
			string decimals("");
			if(i != completeValueb10.length())
				for(++i/*du au '.'*/; i < completeValueb10.length();++i)
					decimals += completeValueb10[i];

			int* tabValues = convertStringToTabInt(integer);
			integer = convert10to2(tabValues,static_cast<int>(integer.length()),kd);
			delete[] tabValues;

			if(decimals.length() != 0)
			{
				tabValues = convertStringToTabInt(decimals);
				decimals = convertDecimale10to2(tabValues,static_cast<int>(decimals.length()),kd);
				delete[] tabValues;
			}

			string completeValueb2 = integer + ',' + decimals;

			//On cherche le décalage pour déplacer la virgule vers le premier 1
			for(i = 0; completeValueb2[i] != '1' && i < completeValueb2.length();++i);

			//Calcule le décalage selon la position de la virgule
			int decalage = static_cast<int>(completeValueb2.find_first_of(',') - i);
			if(decalage > 0)//Un pas de trop
				decalage--;

			string exposant("");

			ostringstream convert;
			convert << (decalage+kd+1);
			exposant = convert.str();

			tabValues = convertStringToTabInt(exposant);
			string e_val = convert10to2(tabValues,static_cast<int>(exposant.length()),kd);
			delete[] tabValues;

			//Remplit e
			for(i = 0;i < SIZE_E && i < e_val.length();i++)
				e[i] = (e_val[e_val.length() - 1 - i] == '1');

			completeValueb2 = integer + decimals;
			decimals = "";
			//On cherche depuis où commence la partie décimale (après le premier 1)
			for(i = 0;completeValueb2[i] != '1' && i < completeValueb2.length();++i);

			for(++i;i < completeValueb2.length();++i)
				decimals += completeValueb2[i];

			unsigned int j = 0;
		
			//On remplit m
			for(int k = SIZE_M-1;j < decimals.length() && k >= 0;--k,++j)
				m[k] = (decimals[j] == '1');
			computeSME();
		}
	}
}

void Real100bits::computeSME()
{
	S = (s) ? -1 : 1;

	string exposant("");
	for(int i = SIZE_E-1;i >=0;--i)
		exposant += (e[i] ? '1' : '0');

	string mantisse("");
	for(int i = SIZE_M-1;i >= 0;--i)
		mantisse += (m[i] ? '1' : '0');

	if(type == Valid)
	{
		/*
		 Source : IEEE Std 754-1985 Reaffirmed revision of 1990
		NaN :  if E = 2^SIZE_E-1 and M != 0
		+-Inf : if E = 2^SIZE_E-1 and M ==0
		 */
		bool isNaNExp = true;
		bool isNaNMan = false;

		for(unsigned int i = 0;i < exposant.length() && isNaNExp;++i)
			if(exposant[i] == '0')
				isNaNExp = false;

		for(unsigned int i = 0;i < mantisse.length() && !isNaNMan;++i)
			if(mantisse[i] == '1')
				isNaNMan = true;

		if(isNaNExp && isNaNMan)
			type = NaN;
		else if(isNaNExp && !isNaNMan)
			type = Inf;


		if(type == Valid)
		{
			E = convert2to10(exposant) - kd;
			M = 0;

			for(unsigned int i = 0;i < SIZE_M;++i)
				if(m[i])
					M += pow(2,i);

			M += pow(2,SIZE_M);
			M /= pow(2,SIZE_M+1);
		}
	}
}

void Real100bits::printValue() const
{
	string output("");
	output += (s) ? '-' : '+';

	if(type == Inf)
		output += "infinity";
	else if(type == NaN)
		output = "NaN";
	else if(type == Zero)
		output  = '0';
	
	if(type == Valid)
	{
		cout << "S : " << ((s) ? 1 : 0) << " -> " << S;
		cout << endl;

		cout << "E (lsb a droite) : ";
		for(int i = SIZE_E-1;i >= 0;--i)
			cout << (e[i] ? 1 : 0);
		cout << endl;

		cout << "M (lsb a droite) : [1]";
		for(int i = SIZE_M-1;i >= 0;--i)
			cout << (m[i] ? 1 : 0);
		cout << endl;

		cout << "Formule : " << output << setprecision(16) << M << "*2^" << E << endl
			 << "Resultat (long double) ~= " << S*M*pow(2,E);
	}
	else
		cout << "Valeur : " << output;
	cout << endl << endl;
}

Real100bits& Real100bits::operator+=(const Real100bits& r)
{
	// Special treatments
	if(type == Zero)
	{
		*this = r;
		return *this;
	}
	else if(r.type == Zero || type != Valid)
		return *this;
	else if(r.type != Valid)
	{
		*this = r;
		return *this;
	}

	if(s != r.s)
	{
		bool ls = s;
		Real100bits r2(r);
		//On adapte le signe en conséquence, on fait toujours A-B dans la sous, A>B
		s = false;
		r2.s = false;

		r2 = *this;
		*this = r;
		s = false;
		*this-=r2;
		s = false;

		if(*this > r2)//Inverse à cause du swap précédent
		{
			if(!ls)
				s = true;
		}
		else
			if(ls)
				s = true;

		computeSME();

		return *this;
	}
	else
	{
		// The number with the smaller exponent will reside in b
		Real100bits a("1");
		Real100bits b("1");
		if(r.E > this->E)
		{
			a = Real100bits(r);
			b = Real100bits(*this);
		}
		else
		{
			a = Real100bits(*this);
			b = Real100bits(r);
		}
		// Hidden bits
		bool hbA = true, hbB = true;

		// Align mantissas (the exponents will then be the same)
		while(a.E != b.E)
		{
			// Shift b to the right (left array shift)
			shiftLeft(b.m, SIZE_M, hbB);
			hbB = false;
			if(!tabPlusOne(b.e, SIZE_E))
			{
				// Overflow !
				this->type = NaN;
				return *this;
			}
			b.computeSME();
		}

		// SIZE_M + 2 because of the hidden bits
		bool mRes[SIZE_M + 2];

		// Addition of the mantissas
		bool carry = false;
		for(unsigned int i = 0; i < SIZE_M; i++)
		{
			if(a.m[i] && b.m[i])
			{
				mRes[i] = carry;
				carry = true;
			}
			else if(a.m[i] || b.m[i])
				mRes[i] = !carry;
			else
			{
				mRes[i] = carry;
				carry = false;
			}
		}

		// Addition of the hidden bits
		if(hbA && hbB)
		{
			mRes[SIZE_M] = carry;
			carry = true;
		}
		else if(!hbA && ! hbB)
		{
			mRes[SIZE_M] = carry;
			carry = false;
		}
		else
			mRes[SIZE_M] = !carry;

		mRes[SIZE_M +1] = carry;

		// Normalization
		while(mRes[SIZE_M+1] != true)
		{
			shiftRight(mRes, SIZE_M +2);
			tabMinusOne(b.e, SIZE_E);
		}

		// Copy the exponent in this
		for(unsigned int i = 0; i < SIZE_E; i++)
			e[i] = b.e[i];

		tabPlusOne(this->e, SIZE_E);

		// Copy the mantissas in this
		for(unsigned int i = 1; i <= SIZE_M; i++)
			m[i-1] = mRes[i];

		// Rounding
		if(mRes[0] && mRes[1])
			tabPlusOne(this->m, SIZE_M);

		// Update the integer values
		computeSME();
		return *this;
	}
}

Real100bits& Real100bits::operator-=(const Real100bits& r)
{
	// Special treatments
	if(type == Zero)
	{
		*this = r;
		s = !s;
		S *= -1;
		return *this;
	}
	else if(r.type == Zero || type != Valid)
		return *this;
	else if(r.type != Valid)
	{
		*this = r;
		return *this;
	}

	if(s != r.s)
	{
		Real100bits r2(r);
		r2.s = !r2.s;
		r2.S *= -1;
		*this+=r2;
		return *this;
	}
	else
	{
		// The number with the smaller exponent will reside in b
		Real100bits a("1");
		Real100bits b("1");
		if(r.E == this->E)
		{
			if(*this > r)
			{
				a = Real100bits(*this);
				b = Real100bits(r);
				b.s = true;
			}
			else
			{
				a = Real100bits(r);
				a.s = true;
				b = Real100bits(*this);
			}

		}
		else if(r.E > this->E)
		{
			a = Real100bits(r);
			a.s = true;
			b = Real100bits(*this);
		}
		else
		{
			a = Real100bits(*this);
			b = Real100bits(r);
			b.s = true;
		}

		bool sa = a.s;
		bool sb= b.s;

		a.s = b.s;

		if(a == b)
		{
			type = Zero;
			return *this;
		}

		this->s = (*this < r);

		a.s = sa;
		b.s = sb;				

		int decalage = a.E-b.E;

		shiftLeft(b.m,SIZE_M,true);
		shiftLeft(a.m,SIZE_M,true);

		for(int i = 0;i<decalage;++i)
			shiftLeft(b.m,SIZE_M,false);

		bool* mantisse = sous(a.m,b.m,SIZE_M);

		int decalage2 = 0;
		for(int i = SIZE_M-1;!mantisse[i] && i >= 0;--i)
			decalage2 = SIZE_M-i;

		for(int i = SIZE_M -1 - (decalage2+1), j = SIZE_M-1;i >= 0 && j > 0;--j,--i)
			m[j] = mantisse[i];
		delete[] mantisse;

		stringstream ss;
		ss << (a.E+kd-decalage2);

		string exp = ss.str();

		int* tabValue = convertStringToTabInt(exp);
		exp = convert10to2(tabValue,static_cast<int>(exp.length()),SIZE_E);
		delete[] tabValue;

		fill_n(e,SIZE_E,false);

		for(unsigned int i = 0;i < SIZE_E && i < exp.length();++i)
			e[i] = (exp[exp.length() -1 - i] == '1');

		this->computeSME();
		return *this;
	}
}

Real100bits& Real100bits::operator*=(const Real100bits& r)
{
	///////////////////////////////////////////////////////////////////////////
	/// http://pages.cs.wisc.edu/~smoler/x86text/lect.notes/arith.flpt.html ///
	///////////////////////////////////////////////////////////////////////////

	// Special treatment
	if(type != Valid)
		return *this;
	else if(r.type != Valid)
	{
		*this = r;
		return *this;
	}

	bool d2Compl[] = {false,true,true,true,true,true,true,true,true,true,true,true,false};

	// Calcul de l'exposant
	bool *e3, *sumExposant;

	sumExposant = sum(this->e, r.e, SIZE_E);
	e3 = sous(sumExposant, d2Compl, SIZE_E);

	//  1.0100
	//x 1.1100
	bool* m1 = new bool[SIZE_M+1];
	bool* m2 = new bool[SIZE_M+1];

	for(unsigned int i = 0; i < SIZE_M; ++i)
	{
		m1[i] = this->m[i];
		m2[i] = r.m[i];
	}
	m1[SIZE_M] = true;
	m2[SIZE_M] = true;

	// Calcul de la mantisse
	bool* m3 = product(m1,m2,SIZE_M+1);

	bool one[] = {true,false,false,false,false,false,false,false,false,false,false,false,false};
	while(!m3[2*(SIZE_M+1)-1])
	{
		e3 = sous(e3, one, SIZE_E);

		for (unsigned int i = 2*(SIZE_M+1)-2; i >= SIZE_M+1; --i)
			m3[i+1] = m3[i];
		
		e3[SIZE_E-1] = e3[SIZE_E-1] && (this->e[SIZE_E-1] || r.e[SIZE_E-1]);
	}
	
	for (int i = SIZE_E-1; i >= 0; --i)
		this->e[i] = e3[i];

	for (unsigned int i = 2*(SIZE_M+1)-2; i >= SIZE_M+1; --i)
		this->m[i-SIZE_M-1] = m3[i];

	this->s = this->s ^ r.s;
	this->computeSME();

	delete[] e3;
	delete[] sumExposant;
	delete[] m1;
	delete[] m2;
	delete[] m3;

	return *this;
}

Real100bits& Real100bits::operator/=(const Real100bits& r)
{
	// Special treatment
	if((type == Zero && r.type == Zero) || (type == Inf && r.type == Inf) || type == NaN || r.type == NaN)
	{
		type = NaN;
		return *this;
	}
	else if(r.type == Zero)
	{
		type = Inf;
		return *this;
	}
	else if(type == Zero)
		return *this;

	// Pour la division du type a/b, on fait a*(1/b)

	Real100bits r1("1");

	if(*this == r)
	{
		*this = r1;
		return *this;
	}

	bool d2Compl[] = {false,true,true,true,true,true,true,true,true,true,true,true,false};

	//e
	bool *e3, *sousExposant;
	sousExposant = sous(r1.e, r.e, Real100bits::SIZE_E);
	e3 = sum(sousExposant, d2Compl, Real100bits::SIZE_E);

	bool* m1 = new bool[Real100bits::SIZE_M+1];
	bool* m2 = new bool[Real100bits::SIZE_M+1];

	for(unsigned int i = 0; i < Real100bits::SIZE_M; ++i)
	{
		m1[i] = r1.m[i];
		m2[i] = r.m[i];
	}
	m1[Real100bits::SIZE_M] = true;
	m2[Real100bits::SIZE_M] = true;

	bool* m3 = div(m1,m2,Real100bits::SIZE_M+1);

	int j = 86;
	do 
	{
		shiftLeft(m3,2*(Real100bits::SIZE_M+1));
	} while (--j > 0);

	while(!m3[2*(Real100bits::SIZE_M+1)-1])
		shiftRight(m3,2*(Real100bits::SIZE_M+1)+1);

	for (unsigned int i = 2*(Real100bits::SIZE_M+1)-2; i >= Real100bits::SIZE_M; --i)
		r1.m[i-Real100bits::SIZE_M-1] = m3[i];
	for (int i = Real100bits::SIZE_E-1; i >= 0; --i)
		r1.e[i] = e3[i];

	*this *= r1;

	this->s = this->s ^ r.s;
	computeSME();

	delete[] e3;
	delete[] sousExposant;
	delete[] m1;
	delete[] m2;
	delete[] m3;

	return *this;
}

Real100bits& Real100bits::operator^=(const unsigned int n)
{
	if(n == 0)
	{
		Real100bits output("1");
		*this = output;
		return *this;
	}
	else
	{
		Real100bits factor(*this);
		for(unsigned int i = 1;i<n;++i)
			(*this)*=factor;
		return *this;
	}
}

bool Real100bits::operator==(const Real100bits& r)
{
	if(s!=r.s)
		return false;

	for(unsigned int i = 0;i < SIZE_E;++i)
		if(e[i] != r.e[i])
			return false;

	for(unsigned int i = 0;i < SIZE_M;++i)
		if(m[i] != r.m[i])
			return false;

	return true;
}

bool Real100bits::operator>(const Real100bits& r)
{
	if(!s && r.s)
		return true;
	else if(s && !r.s)
		return false;

	for(int i = SIZE_E-1;i >= 0;--i)
		if(e[i] != r.e[i])
			return (s) ? !e[i] : e[i];

	for(int i = SIZE_M-1;i >= 0;--i)
		if(m[i] != r.m[i])
			return m[i];

	return false;
}

bool Real100bits::operator<(const Real100bits& r)
{
	return !(*this>r);
}
Real100bits operator+(const Real100bits& r1,const Real100bits& r2)
{
	Real100bits output(r1);
	output += r2;
	return output;
}

Real100bits operator-(const Real100bits& r1,const Real100bits& r2)
{
	Real100bits output(r1);
	output -= r2;
	return output;
}

Real100bits operator*(const Real100bits& r1,const Real100bits& r2)
{
	Real100bits output(r1);
	output *= r2;
	return output;
}

Real100bits operator/(const Real100bits& r1,const Real100bits& r2)
{
	Real100bits output(r1);
	output /= r2;
	return output;
}

Real100bits operator^(const Real100bits& r1,const unsigned int n)
{
	Real100bits output(r1);
	output ^= n;
	return output;
}