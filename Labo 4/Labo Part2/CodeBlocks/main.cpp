#include <iostream>
#include <clocale>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include "GeomGlut.h"
#include "functions.h"

extern GeomGlut graphWin;

using namespace std;

long double StringToLongDouble(const string& str)
{
	stringstream ss(str);
	long double out;
	ss >> out;
	return out;
}

vector<pair<string,long double> > createMapGold()
{
    vector<pair<string,long double> > goldValues;
    ifstream file;
    file.open ("datas/prix_or.csv");

    if(file.is_open())
    {
        string line;
        while(file.good())
        {
            getline(file,line);
            istringstream ins(line);

            int i = 1;
            string key;
            long double value;
            while(ins.good())
            {
                getline(ins, line, ';');
                if(!line.empty())
                {
                    if(i++%2 == 0)
                        value = StringToLongDouble(line);
                    else
                        key = line;
                }
            }
            goldValues.push_back(pair<string,long double>(key,value));
        }
        file.close();
        return goldValues;
    }
    else
    {
        cerr << "Error during the reading process !";
        exit (EXIT_FAILURE);
    }
}

vector<pair<string,long double> > createInflationChart(const vector<pair<string,long double> >& goldValues)
{
    vector<pair<string,long double> > inflation;
    inflation.push_back(pair<string,long double>(goldValues[0].first,0));

    for(vector<pair<string,long double> >::const_iterator it = goldValues.begin()+1; it != goldValues.end(); ++it)
        inflation.push_back(pair<string,long double>(it->first,(it->second-(it-1)->second)*100.0f/(it-1)->second));

    return inflation;
}

int main()
{
	setlocale(LC_ALL, "frs");
    vector<pair<string,long double> > goldValues = createMapGold();
    vector<pair<string,long double> > goldInflations = createInflationChart(goldValues);
    graphWin.initGraphicsWin( 1400, 0, goldValues.size(), -100, 2000, goldValues, goldInflations);
    return( 0 );
}
