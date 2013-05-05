#include "functions.h"
#include "GeomGlut.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

extern GeomGlut graphWin;

using namespace std;

void clear()
{
	cout << string(50, '\n' );
}

void printHeader()
{
    cout << "|===========================================|" << endl
         << "|Program realized by :                      |" << endl
         << "|                        - Diego Antognini  |" << endl
         << "|                        - Alexandre Perez  |" << endl
         << "|                        - Sebastien Vaucher|" << endl
         << "|===========================================|" << endl;
}

bool sortSinglePair(std::pair<std::string, long double> a, std::pair<std::string, long double> b)
{
    return a.second < b.second;
}

bool sortDoublePair(std::pair<std::string, std::pair<std::string, long double> > a, std::pair<std::string, std::pair<std::string, long double> > b)
{
    return sortSinglePair(a.second,b.second);
}

vector<pair<string, long double> > computeBestMomentToBuyGoldForOneYear(int iStart)
{
    /*For each day, we'll compute the delta of the inflation and we'll save the
    biggest delta
    There is each year, in average over the 34 years of the database, 260,912 days per year, so
    we round it to 261 days per year*/

    vector<pair<string, long double> > bestMoments;
    const vector<pair<string, long double> > goldInflations = graphWin.getGoldInflations();
    const int maxLimit = goldInflations.size()-GeomGlut::numberOfDaysInbrokerYear+1;
    string date = "";

    for(; iStart < maxLimit; ++iStart)
        bestMoments.push_back(pair<string, long double>(goldInflations[iStart].first,
                                                        goldInflations[iStart+GeomGlut::numberOfDaysInbrokerYear].second-goldInflations[iStart].second));

    sort(bestMoments.begin(),bestMoments.end(),sortSinglePair);
    return bestMoments;
}

vector<pair<string, pair<string, long double> > > computeBestMomentToBuyGoldForAnyTime(int iStart)
{
    /*For each day, we'll keep the maximum delta until the last know gold inflation.
    Afterwards, we'll keep the 5 best*/

    vector<pair<string, pair<string, long double> > > bestMoments;
    const vector<pair<string, long double> > goldInflations = graphWin.getGoldInflations();

    const int maxLimit = goldInflations.size();
    string date = "";

    for(int i = iStart; i < maxLimit; ++i)
        bestMoments.push_back(pair<string, pair<string, long double> >(goldInflations[iStart].first,
                                                                       pair<string, long double>(goldInflations[i].first,
                                                                                                   goldInflations[i].second-goldInflations[iStart].second)));
    sort(bestMoments.begin(),bestMoments.end(),sortDoublePair);
    return bestMoments;
}

int findIndexGoldValues(const string& date)
{
    const vector<pair<string, long double> > goldValues = graphWin.getGoldValues();
    unsigned int i = 0;
    for(;i < goldValues.size() && date != goldValues[i].first;++i){}
    return i;
}

//Source : http://www.cplusplus.com/forum/articles/9645/
long double stringToLongDouble(const string& str)
{
	stringstream ss(str);
	long double out;
	ss >> out;
	return out;
}

//Source : http://www.cplusplus.com/forum/articles/9645/
string longDoubleToString(long double a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}

void drawBestTimeToBuyDuringOneYear(float r, float g, float b, int iStart)
{
    int height = graphWin.yMax()/2.5d;
    if(iStart >= 10)//To have a better display
        height = graphWin.yMax()/6;

    const vector<pair<string, long double> > bestMomentsAll = computeBestMomentToBuyGoldForOneYear(iStart);
    const int nbMaxNumberOfBenefitsToDisplay = GeomGlut::nbMaxNumberOfBenefitsToDisplay;
    const int numberOfDaysInbrokerYear = GeomGlut::numberOfDaysInbrokerYear;
    for(vector<pair<string, long double> >::const_iterator it = bestMomentsAll.end()-1; it >= bestMomentsAll.end()-nbMaxNumberOfBenefitsToDisplay; --it)
    {
        int x = findIndexGoldValues(it->first);
        graphWin.segment(x,
                        height,
                        x+numberOfDaysInbrokerYear,
                        height, r, g, b);

        string delta = "+";
        delta += longDoubleToString(it->second);
        delta += "%";
        graphWin.print(x, height+20, delta.c_str(), r, g, b);
        height += graphWin.yMax()/15;
        cout << " From " << it->first << " to " << graphWin.getGoldInflations()[x+numberOfDaysInbrokerYear].first <<  " -> benefit of " << delta << endl;
    }
}

void drawBestTimeToBuyDuringAnyTime(float r, float g, float b, int iStart)
{
    int height = graphWin.yMax()*8.0d/10.0d;
    if(iStart >= 10)//To have a better display
        height = graphWin.yMax()*6.0d/10.0d;

    const vector<pair<string, pair<string, long double> > > bestMomentsAll = computeBestMomentToBuyGoldForAnyTime(iStart);
    const int nbMaxNumberOfBenefitsToDisplay = GeomGlut::nbMaxNumberOfBenefitsToDisplay;
    for(vector<pair<string, pair<string, long double> > >::const_iterator it = bestMomentsAll.end()-1; it >= bestMomentsAll.end()-nbMaxNumberOfBenefitsToDisplay; --it)
    {
        int x1 = findIndexGoldValues(it->first);
        int x2 = findIndexGoldValues(it->second.first);
        graphWin.segment(x1,
                        height,
                        x2,
                        height, r, g, b);

        string delta = "+";
        delta += longDoubleToString(it->second.second);
        delta += "%";
        graphWin.print(x1+(x2-x1)/2.0d, height+20, delta.c_str(), r, g, b);
        height += graphWin.yMax()/15;
        cout << " From " << it->first << " to " << it->second.first << " -> benefit of " << delta << endl;
    }
}

void drawFunctions()
{
    clear();
    printHeader();

    const vector<pair<string, long double> > goldValues = graphWin.getGoldValues();
    const vector<pair<string, long double> > goldInflations = graphWin.getGoldInflations();

    cout << "x axe starts in " << goldValues[0].first << " and finish in the during the year " << goldValues[goldValues.size()-1].first << "." << endl << "Each unity represents a broker day" << endl << endl;
    cout << "y axe represents the value of the gold, in CHF or in %, depending the graphic" << endl << endl;
    cout << "Graphical Informations : " << endl
              << "- Gold value in Swiss franc [CHF], in blue" << endl
              << "- Inflation in percent [%] with a factor 2 (to have a better display), in green" << endl
              << "- Best period to buy gold during one year, since 1979, in light red" << endl
              << "- Best period to buy gold to have the biggest benefits, since 1993, in dark red" << endl
              << "- Best period to buy gold during one year, since 1993, in light rose" << endl
              << "- Best period to buy gold to have the biggest benefits, since 1979, in dark rose" << endl;

    glPointSize(2.0f);

    //Draw gold values
    string oldYear="";
    vector<pair<string,long double> >::const_iterator it = goldValues.begin();
    int middle = goldValues.size()/2;
    for(float x=graphWin.xMin(); it != goldValues.end() && x < graphWin.xMax(); ++it, ++x)
    {
        graphWin.plot(x, it->second, 0.0f,0.0f,1.0f);
        string date = it->first;
        string currentYear = date.substr(date.length()-4,4);
        if(currentYear != oldYear)
        {
            graphWin.print(x+20, graphWin.yMax()-70, currentYear.c_str());
            graphWin.segment(x,graphWin.yMin(),x,graphWin.yMax());
            oldYear = currentYear;
        }
        if(x == middle)
            graphWin.print(x+20, it->second+100, "Gold Values [CHF]", 0.0f,0.0f,1.0f,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    //Draw inflations
    it = goldInflations.begin()+1;
    for(float x=graphWin.xMin(); it != goldInflations.end() && x < graphWin.xMax(); ++it, ++x)
    {
        graphWin.plot(x, 2*it->second, 0.0f,1.0f,0.0f);
        if(x == middle)
            graphWin.print(x+20, it->second+100, "Inflation Values [%]", 0.0f,1.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    //From the beginning
    cout << endl <<GeomGlut::nbMaxNumberOfBenefitsToDisplay << " best dates (since 1979) to invest money in gold for a period of 1 year" << endl;
    drawBestTimeToBuyDuringOneYear(1.0f,0.0f,0.0f);

    //From the last 20 years
    cout << endl <<GeomGlut::nbMaxNumberOfBenefitsToDisplay << " best dates (since 1993) to invest money in gold for a period of 1 year" << endl;
    drawBestTimeToBuyDuringOneYear(1.0f,0.5f,1.0f,goldValues.size()-20*GeomGlut::numberOfDaysInbrokerYear);

    //From the beginning
    cout << endl <<GeomGlut::nbMaxNumberOfBenefitsToDisplay << " best dates (since 1979) to invest money in gold to have a maximum of benefits" << endl;
    drawBestTimeToBuyDuringAnyTime(245.0f/255.0f,0.0f,0.0f);

    //From the last 20 years
    cout << endl <<GeomGlut::nbMaxNumberOfBenefitsToDisplay << " best dates (since 1993) to invest money in gold to have a maximum of benefits" << endl;
    drawBestTimeToBuyDuringAnyTime(1.0f,0.0f,1.0f,goldValues.size()-20*GeomGlut::numberOfDaysInbrokerYear);
}
