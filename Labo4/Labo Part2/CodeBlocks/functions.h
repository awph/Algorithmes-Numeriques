#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>
#include <vector>
#include <string>

void clear();
void printHeader();

long double stringToLongDouble(const std::string& str);
std::string longDoubleToString(long double a);

void plotBestTimeToBuyDuringOneYear(float r, float g, float b, int iStart = 0);
void plotBestTimeToBuyDuringAnyTime(float r, float g, float b, int iStart = 0);

/*Function used to sort*/
bool sortSinglePair(std::pair<std::string, long double> a, std::pair<std::string, long double> b);
bool sortDoublePair(std::pair<std::string, std::pair<std::string, long double> > a, std::pair<std::string, std::pair<std::string, long double> > b);

std::vector<std::pair<std::string, long double> > computeBestMomentToBuyGoldForOneYear(int iStart = 0);
std::vector<std::pair<std::string, std::pair<std::string, long double> > > computeBestMomentToBuyGoldForAnyTime(int iStart = 0);

int findIndexGoldValues(const std::string& date);
void drawFunctions();

#endif // FUNCTIONS_H

