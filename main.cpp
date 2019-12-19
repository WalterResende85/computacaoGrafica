// Trabalho de computação grafica de Walter Resende e Davi Souza
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <cmath>
#pragma comment (lib, "glut32.lib")

GLuint texture;
double angulo = 0;
typedef struct
{
    int a;
    int b;
    int c;
    double d;
    double e;
   
}VERTICES;

GLuint LoadTextureRAW( const char * filename );
const double PI = 3.1415926535897;
const int espaco = 10;
const int contagemDeVertices = (90 / espaco) * (360 / espaco) * 4;
VERTICES VERTEX[contagemDeVertices];
void criarEsfera (double raio, double H, double K, double Z) {
    double a;
    double b;
    int n=0;
    
for( b = 0; b <= 90 - espaco; b+=espaco){

    for( a = 0; a <= 360 - espaco; a+=espaco)
    {
        VERTEX[n].a = raio * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].b = raio * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].c = raio * cos((b) / 180 * PI) - Z;
        VERTEX[n].e = (2 * b) / 360;
        VERTEX[n].d = (a) / 360;
        n++;
        VERTEX[n].a = raio * sin((a) / 180 * PI) * sin((b + espaco) / 180 * PI) - H;
        VERTEX[n].b = raio * cos((a) / 180 * PI) * sin((b + espaco) / 180 * PI) + K;
        VERTEX[n].c = raio * cos((b + espaco) / 180 * PI) - Z;
        VERTEX[n].e = (2 * (b + espaco)) / 360;
        VERTEX[n].d = (a) / 360;
        n++;
        VERTEX[n].a = raio * sin((a + espaco) / 180 * PI) * sin((b) / 180 * PI) - H;
        VERTEX[n].b = raio * cos((a + espaco) / 180 * PI) * sin((b) / 180 * PI) + K;
        VERTEX[n].c = raio * cos((b) / 180 * PI) - Z;
        VERTEX[n].e = (2 * b) / 360;
        VERTEX[n].d = (a + espaco) / 360;
        n++;
        VERTEX[n].a = raio * sin((a + espaco) / 180 * PI) * sin((b + espaco) /180 * PI) - H;
        VERTEX[n].b = raio * cos((a + espaco) / 180 * PI) * sin((b + espaco) /180 * PI) + K;
        VERTEX[n].c = raio * cos((b + espaco) / 180 * PI) - Z;
        VERTEX[n].e = (2 * (b + espaco)) / 360;
        VERTEX[n].d = (a + espaco) / 360;
        n++;
    }

}
}

void mostrarEsfera (double raio, GLuint texture)
{
  //terra girando em torno dela mesma  
  glTranslatef(0,0,0);
  
  
  //caso queira a terra girando em torno dela e movimento do sistema solar descomente o codigo abaixo
  //glTranslatef(4,0,0);
    
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int b;
    glScalef (0.0300 * raio, 0.0300 * raio, 0.0300 * raio);
    glRotatef (-90, 1, 0, 0);
    glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);
    for (b = 0; b <contagemDeVertices; b++)
    {
        glTexCoord2f (VERTEX[b].d, VERTEX[b].e);
        glVertex3f (VERTEX[b].a, VERTEX[b].b, -VERTEX[b].c);
    }



for ( int i = 0; i <contagemDeVertices; i++)
{
    glVertex3f (VERTEX[i].a, VERTEX[i].b, VERTEX[i].c);
    glTexCoord2f (VERTEX[i].d, -VERTEX[i].e);
}
    glEnd();
}




void display (void) {
    glClearDepth(1);
    glClearColor (0.0,0.0,0.1,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-7);
    glRotatef(angulo,0,1,0);
    mostrarEsfera(4, texture);
    glutSwapBuffers();
    angulo ++;
}

void init (int distance) {
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );
    glDepthFunc(GL_LEQUAL);

    texture= LoadTextureRAW( "terra.bmp" );
    criarEsfera(distance,0,0,0);
      
}

void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (50, (GLfloat)w / (GLfloat)h, 0.1, 110.0);
    glMatrixMode (GL_MODELVIEW);
}


GLuint LoadTextureRAW( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );

  fread( data, width * height * 3, 1, file );
  fclose( file );

for(int i = 0; i < width * height ; ++i)
{
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];
    data[index] = R;
    data[index+2] = B;
}
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data );
    
return texture;
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (1500, 600);
    glutInitWindowPosition (0, 0);

    glutCreateWindow ("Planeta Terra OpenGL");
     
    init(10);

    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    
    return 0;
}