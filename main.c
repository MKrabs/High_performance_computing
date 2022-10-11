#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
#include <stdio.h>

int width = 1000;
int height = 1000;
int board[100][100];
int size = 20;
bool debug = false;


void setup() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            int randint = rand() % 100;
            board[i][j] = randint < 10 ? randint : 0;
        }
    }
}

void init(int argc, char **argv) {
    glutInit(&argc, argv);                       // Initialisierung der GLUT Bibliothek
    glutInitDisplayMode(GLUT_SINGLE);       // Initialisierung des Single Buffer Modes
    glutInitWindowSize(width, height);                 // Fenstergröße in Pixel (Breite, Hoehe)
    glutInitWindowPosition(20, 20);            // Fensterposition in Pixel, ausgehend vom Ursprung des Window Systems
    glutCreateWindow("Game of life");              // Erstellen des Fensters
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void calculate() {
    int new_board[100][100];

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (board[i][j] > 0)
                printf("%d", board[i][j]);

            // TODO
        }
        printf("\n");
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (board[i][j] == 0)
                glColor3f(0.0, 0.0, 0.0);
            else
                glColor3f(board[i][j] / 10.0, 0.71, 0.27);

            glBegin(GL_POLYGON);
            glVertex3f(i * size, j * size, 0.0);
            glVertex3f(i * size + size, j * size, 0.0);
            glVertex3f(i * size + size, j * size + size, 0.0);
            glVertex3f(i * size, j * size + size, 0.0);
            glEnd();

            if (!debug)
                continue;
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(i * size, j * size);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + board[i][j]);

        }
    }
    glFlush();
}

void render(void) {
    calculate();
    display();
}


int main(int argc, char **argv) {
    srand(time(NULL));
    setup();
    init(argc, argv);
    glutDisplayFunc(render);                // Callback-Funktion für das Fenster
    glutMainLoop();                            // Abgabe der Kontrolle an GLUT-Bibliothek
    return 0;
}


