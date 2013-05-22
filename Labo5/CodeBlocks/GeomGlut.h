// Fichier Geoglut.h

#ifndef GeomGlut_H
#define GeomGlut_H

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>                // Librairie GLUT
#endif

using namespace std;

const GLfloat ARROW = 0.2;
const GLfloat DEFAULT_SIZE_POINT = 2.0;

typedef struct
{
    double x;
    double y;
} coord2D;

typedef struct
{
    unsigned int x;
    unsigned int y;
} coord2D_UInt;

class GeomGlut
{
  public:

    //--- Constructor ---
    GeomGlut( void );
    //--- Destructor ---
    ~GeomGlut( void );


    //--- Public members ---
    // <none>

    //--- Public methods ---
    void initGraphicsWin( unsigned int pixelWinX, unsigned int pixelWinY, double xMin, double xMax, double yMin, double yMax);

    void drawAxes();
    void plot( GLfloat x, GLfloat y );
    void plot( GLfloat x, GLfloat y, GLfloat sizePoint );
    void plotRetangle(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2,GLfloat x3, GLfloat y3,GLfloat x4, GLfloat y4);

    //--- to find an « good » delta_x
    long double findSmartStepX( void );  // if working in the full defined area (from winMinX to winMaxX)
    long double findSmartStepX( long double workingMinX, long double workingMaxX );  // if working in a restricted area defined between workingMinX and workingMaxX

    void print(float x, float y, const char* text, float r = 0.0f, float g = 0.0f, float b=0.0f, LPVOID font = GLUT_BITMAP_HELVETICA_18);

    //--- improving plottings ---
    void plot( GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b ); // dessine un point de couleur {r,g,b} si dans la zone de travail et de taille DEFAULT_SIZE_POINT
    void setColorForPlotWithoutColor( GLfloat r, GLfloat g, GLfloat b ); // to assign color, but must use the following function
    void plot( bool presetColorAndGLVertex, GLfloat x, GLfloat y ); // dessine un point sans changer la couleur ni préciser l’appel à GL_POINT2D si le drapeau presetColorAndGLVertex est vrai (c’est bcp mieux pour OpenGL)

    void segment( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,GLfloat w = 1.0f, GLfloat r=0.0f, GLfloat g=0.0f, GLfloat b=0.0f);

    double xMin( void ) { return( minWin.x); }
    double yMin( void ) { return( minWin.y); }
    double xMax( void ) { return( maxWin.x); }
    double yMax( void ) { return( maxWin.y); }

    void setWinPixels( unsigned int x, unsigned int y ) { winPixels.x = x; winPixels.y = y; }

    unsigned int xWinFunc( void ) { return( winFuncPixels.x ); }
    unsigned int yWinFunc( void ) { return( winFuncPixels.y ); }

  private:
    //--- Private members ---
    coord2D minWin;
    coord2D maxWin;
    coord2D_UInt winFuncPixels;
    coord2D_UInt winPixels;

    //--- Private methods ---
    coord2D getMinWin( void ) { return( minWin ); }
    coord2D getMaxWin( void ) { return( maxWin ); }
    coord2D_UInt getFuncWinPixel( void ) { return( winFuncPixels ); }

  protected:
    // <none>

};

// openGL functions
void Display();
void Reshape(int, int);

#endif // GeomGlut_H
