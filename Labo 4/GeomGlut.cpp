#include "GeomGlut.h"
#include "functions.h"

GeomGlut graphWin;
long double (*f)(long double);

GeomGlut::GeomGlut( void )
{
    minWin.x = 0;
    minWin.y = 0;
    maxWin.x = 0;
    maxWin.y = 0;
    winFuncPixels.x = 0;
    winFuncPixels.y = 0;
    winPixels.x = 0;
    winPixels.y = 0;
}

GeomGlut::~GeomGlut( void )
{

}

long double GeomGlut::findSmartStepX( void )
{
  long double ratio = 1.0/static_cast<long double>(winFuncPixels.x);
  return( ratio );
}

long double GeomGlut::findSmartStepX( long double workingMinX, long double workingMaxX )
{
  long double ratio = (xMax()-xMin())/((workingMaxX-workingMinX)*static_cast<long double>(winFuncPixels.x));
  return( ratio );
}

void GeomGlut::initGraphicsWin( unsigned int pixelWinX, double _xMin, double _xMax, double _yMin, double _yMax ,long double (*func)(long double))
{
  f = func;
  if(_xMax-_xMin<=0)
        return;

  winFuncPixels.x = pixelWinX;
  winFuncPixels.y = static_cast<unsigned int>((_yMax-_yMin) * static_cast<double>(winFuncPixels.x)/(_xMax-_xMin));

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(0, 0);

  glutInitWindowSize(winFuncPixels.x, winFuncPixels.y);

  // at the begining, the function win pixel and the actual win pixel are identical:
  graphWin.setWinPixels( winFuncPixels.x, winFuncPixels.y );

  minWin.x = _xMin;
  minWin.y = _yMin;
  maxWin.x = _xMax;
  maxWin.y = _yMax;

  glutCreateWindow("Algorithmes numériques: labo#2");

  // Initialiser la couleur du fond (blanc)
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

  glutReshapeFunc( Reshape );
  glutDisplayFunc( Display );
  glutMainLoop();
}

void GeomGlut::drawAxes()
{
  // Draw the white background:
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // red
    glVertex3d(minWin.x, minWin.y, -1.0);
    glVertex3d(maxWin.x, minWin.y, -1.0);
    glVertex3d(maxWin.x, maxWin.y, -1.0);
    glVertex3d(minWin.x, maxWin.y, -1.0);
  glEnd();

  // Draw the axes :
  glLineWidth( 3.0 );
  glBegin(GL_LINES);
  {
    glColor3f(1.0f, 0.0f, 0.0f); // red
    // Axe X
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0-ARROW, -ARROW, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0-ARROW, ARROW, 0.0);

    // Axe Y
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(ARROW, 1.0-ARROW, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(-ARROW, 1.0-ARROW, 0.0);
  }
  glEnd();

  glLineWidth( 1.0 );
  glBegin(GL_LINES);
  {
    glColor3f(0.0f, 0.0f, 1.0f); // blue
    // Axe X
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(maxWin.x, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(minWin.x, 0.0, 0.0);

    // Axe Y
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, maxWin.y, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, minWin.y, 0.0);
  }
  glEnd();
}

void GeomGlut::plot( bool presetColorAndGLVertex, GLfloat x, GLfloat y )
{
  if( presetColorAndGLVertex )
    glVertex2d(x, y);
  else
    plot( x, y, DEFAULT_SIZE_POINT );
}

void GeomGlut::setColorForPlotWithoutColor( GLfloat r, GLfloat g, GLfloat b )
{
    glColor3f( r, g, b );
}

void GeomGlut::plot( GLfloat x, GLfloat y )
{
    plot(x, y, DEFAULT_SIZE_POINT);
}

void GeomGlut::plot( GLfloat x, GLfloat y, GLfloat sizePoint )
{
  if( (x<minWin.x) || (x>maxWin.x) || (y<minWin.y) || (y>maxWin.y) )
    glColor3f(0.7f, 0.7f, 0.7f);
  else
    glColor3f(0.0f, 0.0f, 0.0f);

  glPointSize( sizePoint );
  glBegin( GL_POINTS );
    glVertex3d(x, y, 0.0);
  glEnd();
}

void GeomGlut::plot( GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b )
{
  if( (x<minWin.x) || (x>maxWin.x) || (y<minWin.y) || (y>maxWin.y) )
    glColor3f(0.5+r/2., 0.5+g/2., 0.5+b/2.);
  else
    glColor3f(r, g, b);

  glBegin( GL_POINTS );
    glVertex2d(x, y);
  glEnd();
}

void GeomGlut::segment( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 )
{
  if( (x1<minWin.x) || (x1>maxWin.x) || (y1<minWin.y) || (y1>maxWin.y) ||
      (x2<minWin.x) || (x2>maxWin.x) || (y2<minWin.y) || (y2>maxWin.y) )
    glColor3f(0.7f, 0.7f, 0.7f);
  else
    glColor3f(0.0f, 0.0f, 0.0f);

  glBegin( GL_LINES );
    glVertex3d(x1, y1, 0.0);
    glVertex3d(x2, y2, 0.0);
  glEnd();
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void Display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  graphWin.drawAxes();
  drawFunctions();
  glFlush();
}

void Reshape(int w, int h)
{
  if (h == 0) h = 1;
  if (w == 0) w = 1;
  glViewport(0, 0, w, h);

  graphWin.setWinPixels( w, h );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float xRatio = static_cast<float>(w)/static_cast<float>(graphWin.xWinFunc());
  float yRatio = static_cast<float>(h)/static_cast<float>(graphWin.yWinFunc());

  // Volume de clipping : (left, right, bottom, top, near, far)
  glOrtho(graphWin.xMin()*xRatio, graphWin.xMax()*xRatio, graphWin.yMin()*yRatio, graphWin.yMax()*yRatio, -2.0f, 2.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

