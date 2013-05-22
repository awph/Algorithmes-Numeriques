#include <clocale>
#include "GeomGlut.h"

extern GeomGlut graphWin;

using namespace std;

int main()
{
	setlocale(LC_ALL, "frs");

    graphWin.initGraphicsWin( 1400, 800, -10, 10, -0.2, 6);

    return(0);
}
