#ifndef REAL100BITS_H
#define REAL100BITS_H

#include <string>

class Real100bits
{
public:
	enum Type {Zero, Valid, NaN, Inf};

	Real100bits(const std::string& input);

	friend Real100bits operator+(const Real100bits& r1,const Real100bits& r2);
	friend Real100bits operator-(const Real100bits& r1,const Real100bits& r2);
	friend Real100bits operator*(const Real100bits& r1,const Real100bits& r2);
	friend Real100bits operator/(const Real100bits& r1,const Real100bits& r2);
	friend Real100bits operator^(const Real100bits& r1,const unsigned int n);

	bool operator==(const Real100bits& r);
	bool operator>(const Real100bits& r);
	bool operator<(const Real100bits& r);

	Real100bits& operator+=(const Real100bits& r);
	Real100bits& operator-=(const Real100bits& r);
	Real100bits& operator*=(const Real100bits& r);
	Real100bits& operator/=(const Real100bits& r);
	Real100bits& operator^=(const unsigned int n);

	void printValue() const;
	Type getType() const {return type;}
private:
	void computeSME();

	const static int kd = 4094;//2^(e-1)-1 -1, le deuxième -1 est dû au bit caché !
	const static unsigned int SIZE_E = 13;
	const static unsigned int SIZE_M = 86;

	Type type;
	int S;
	long double M;
	int E;

	bool s;
	bool e[SIZE_E];//LSB bit 0
	bool m[SIZE_M];//LSB bit 0
};

#endif