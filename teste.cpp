//
//  main.cpp
//
//  Created by Sandro Fernandes.
//  Copyright © 2016 Sandro Fernandes. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

// Tamanho e posição inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// Tamanho do incremento nas direções x e y
// (número de pixels para se mover a cada
// intervalo de tempo)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;


// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Especifica que a cor corrente é vermelha
    //         R     G     B
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // Desenha um quadrado preenchido com a cor corrente
    // x1 - y1 - rsize: Tamanho e posição inicial do quadrado
    // x1 = 100.0f;
    // y1 = 150.0f;
    // rsize = 50;
    
    glBegin(GL_QUADS);
        glVertex2i(x1, y1+rsize);
        glVertex2i(x1, y1);
        // Especifica que a cor corrente é azul
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(x1+rsize, y1);
        glVertex2i(x1+rsize, y1+rsize);
    glEnd();
    
    glFlush();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void Timer(int value)
{
    // Muda a direção quando chega na borda esquerda ou direita
    if(x1 > windowWidth-rsize || x1 < 0)
        xstep = -xstep;
    
    // Muda a direção quando chega na borda superior ou inferior
    if(y1 > windowHeight-rsize || y1 < 0)
        ystep = -ystep;
    
    // Verifica as bordas.  Se a window for menor e o
    // quadrado sair do volume de visualização
    if(x1 > windowWidth-rsize)
        x1 = windowWidth-rsize-1;
    
    if(y1 > windowHeight-rsize)
        y1 = windowHeight-rsize-1;
    
    // Move o quadrado
    x1 += xstep;
    y1 += ystep;
    
    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0){
        h = 1;
    }
    
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)  {
        windowHeight = 250.0f * h/w;
        windowWidth = 250.0f;
    }
    else  {
        windowWidth = 250.0f * w/h;
        windowHeight = 250.0f;
    }
    
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
    /*
    glutInitWindowSize define o tamanho da janela.
    
    gluOrtho2D especifica as coordenadas a serem usadas com a viewport que é padrão para o tamanho da janela.
    
    Use glViewport para especificar a região da janela nas coordenadas da janela a serem desenhadas.
    
    Então, se você quiser criar uma janela de 400 x 400 e apenas desejar desenhar para o retângulo (50, 50, 350, 350) dentro da janela, use glViewport (50, 50, 300, 300). Você usaria então gluOrtho2D para configurar suas coordenadas GL na janela de exibição. Então, se você usou gluOrtho2D (-1.0, 1.0, 0.0, 1.0), as coordenadas GL visíveis variariam de -1.0 a 1.0 na direção x, de 0.0 a 1.0 na direção y. E, se você usou o gluOrtho2D como mostrou em sua postagem, as coordenadas visíveis variariam de 100 a 300 na direção x e de 100 a 300 na direção y.
    
    Ao mesmo tempo, se você desenhasse um quadrado com coordenadas {(-0.25,0.25), (0.25,0.25), (0.25,0.75), (- 0.25,0.75)} apareceria na tela como um retângulo com altura duas vezes a largura porque a relação de aspecto do comando gluOrtho2D é 2 a 1 em relação a x e y. Normalmente, os índices de aspecto são mantidos para ambos, de modo que as imagens não aparecem distorcidas.
     
    */
}

// Programa Principal
int main(int argc, char **argv)
{
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Anima");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    
    glutTimerFunc(33, Timer, 1);
    Inicializa();
    glutMainLoop();
}
