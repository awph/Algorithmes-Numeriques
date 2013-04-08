#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
class Real100bits;

std::string convert10to2(int tabValues[],const int length,const int prec);
const std::string convertDecimale10to2(int tabValues[],const int length, const int prec);
int convert2to10(const std::string& str);
int* convertStringToTabInt(const std::string& intput);
bool onlyZero(const int tabValues[], const int length);
bool tabPlusOne(bool tab[], int length);
bool tabMinusOne(bool tab[], int length);
bool shiftLeft(bool tab[], int length, bool padding = false);
bool shiftRight(bool tab[], int length, bool padding = false);
bool* sum(const bool b1[], const bool b2[], const int length);
bool* sous(const bool b1[], const bool b2[], const int length);
bool* product(const bool b1[], const bool b2[], const int length);
bool* div(const bool b1[], const bool b2[], const int length);
bool isBigger(const bool b1[], const bool b2[], const int length);
Real100bits approximationPI(const int n);
#endif