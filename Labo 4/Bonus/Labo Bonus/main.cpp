#include <iostream>
#include <clocale>
#include <sstream>
#include <cmath>

#include "GeomGlut.h"
#include "functions.h"

extern GeomGlut graphWin;

using namespace std;

double readDouble()
{
    double output = 0;
    bool isOk = false;
    do
    {
        string input = "";
        output = 0;
        cin >> input;

        stringstream stream(input);
        if(stream >> output)
            isOk = true;
    }while(!isOk);

    return output;
}

int main()
{
	setlocale(LC_ALL, "frs");

    printHeader();
    cout << "Please enter the speed to go straight in the lake: ";
    double speedStraight = fabs(readDouble());
    cout << "Please enter the speed to go along the lake : ";
    double speedAlong = fabs(readDouble());

    double radius = 2.0d;//Change nothing in the graph, the curves have the same behavior
    double y_max = radius+radius/5.0d;

    graphWin.initGraphicsWin( 1000, -y_max,y_max,-y_max,y_max, radius, speedStraight, speedAlong);

    return( 0 );
}
