#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma clang diagnostic push

#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

const int window_width = 1000;
const int window_height = 1000;
const int size = 10;
const int speed_milliseconds = 100;
const bool debug = false;
const bool gospel = false;
const bool simkin = false;

int board[102][102] = {0};
int generation = 0;
int windowID;


void setup() {
    if (gospel) {
        int Gosper_glider_gun[9][36] = {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        for (int r = 0; r < 9; ++r) {
            for (int w = 0; w < 36; ++w) {
                board[r + 20][w + 20] = Gosper_glider_gun[r][w];
            }
        }
        return;
    }

    if (simkin) {
        int Gosper_glider_gun[21][33] = {
                {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };


        for (int r = 0; r < 21; ++r) {
            for (int w = 0; w < 33; ++w) {
                board[r + 40][w + 40] = Gosper_glider_gun[r][w];
            }
        }
        return;
    }


    for (int i = 1; i < 101; i++) {
        for (int j = 1; j < 101; j++) {
            if (rand() % 10 < 1) // NOLINT(cert-msc30-c, cert-msc50-cpp)
                board[i][j] = 1;
        }
    }

}

void init(int argc, char **argv) {
    glutInit(&argc, argv);                      // Initialisierung der GLUT Bibliothek
    glutInitDisplayMode(GLUT_SINGLE);      // Initialisierung des Single Buffer Modes
    glutInitWindowSize(window_width, window_height);                // Fenstergröße in Pixel (Breite, Hoehe)
    glutInitWindowPosition(20, 20);             // Fensterposition in Pixel, ausgehend vom Ursprung des Window Systems
    windowID = glutCreateWindow("Game of life - Game broke");            // Erstellen des Fensters
    glutSetWindow(windowID);
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);
    glMatrixMode(GL_MODELVIEW);
}

int countNeighbours(int x, int y) {
    int count = 0;

    if (board[x - 1][y - 1] > 0) count++;
    if (board[x - 1][y] > 0) count++;
    if (board[x - 1][y + 1] > 0) count++;
    if (board[x][y - 1] > 0) count++;
    if (board[x][y + 1] > 0) count++;
    if (board[x + 1][y - 1] > 0) count++;
    if (board[x + 1][y] > 0) count++;
    if (board[x + 1][y + 1] > 0) count++;

    return count;
}

int cellsurvival(int x, int y) {
    int neighbours = countNeighbours(x, y);
    int age = board[x][y];

    if (age < 1)
        return (neighbours == 3) ? ++age : 0;

    if (neighbours < 2 || neighbours > 3)
        return 0;

    return ++age;
}

void calculate() {
    int max_x = sizeof(board) / sizeof(board[0]);
    int max_y = sizeof(board[0]) / sizeof(board[0][0]);

    int new_board[max_x][max_y];

    for (int i = 1; i < 101; i++) {
        for (int j = 1; j < 101; j++) {
            new_board[i][j] = MIN(cellsurvival(i, j), 100);
            if (debug)
                printf(" %d ", new_board[i][j]);
        }
        if (debug)
            printf("\n");
    }


    for (int i = 1; i < 101; i++) {
        for (int j = 1; j < 101; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 1; i < 101; ++i) {
        for (int j = 1; j < 101; ++j) {
            int age = board[i][j];
            if (age == 0)
                glColor3f(0.0f, 0.0f, 0.0f);
            else
                glColor3f((float) (age / 100.0), 0.71f, 0.27f);

            glBegin(GL_POLYGON);
            glVertex3f((float) ((i - 1) * size), (float) ((j - 1) * size), 0.0f);
            glVertex3f((float) (i * size), (float) ((j - 1) * size), 0.0f);
            glVertex3f((float) (i * size), (float) (j * size), 0.0f);
            glVertex3f((float) ((i - 1) * size), (float) (j * size), 0.0f);
            glEnd();

            if (debug) {
                glColor3f(1.0f, 1.0f, 1.0f);
                glRasterPos2i(i * size, j * size);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + board[i][j]);
            }
        }
    }
    glFlush();

    char title[32];
    sprintf(title, "Game of life - Gen %d", generation++);
    glutSetWindow(windowID);
    glutSetWindowTitle(title);
}

void *timedThread() {
    while (true) {
        usleep(speed_milliseconds * 1000);

        calculate();
    }
}

void on_timer() {
    glutPostRedisplay();
    glutTimerFunc(speed_milliseconds, on_timer, 0);
}

int main(int argc, char **argv) {
    pthread_t tid;
    pthread_create(&tid, NULL, &timedThread, NULL);

    srand(time(NULL)); // NOLINT(cert-msc51-cpp)
    setup();
    init(argc, argv);
    glutDisplayFunc(display);                // Callback-Funktion für das Fenster
    glutTimerFunc(speed_milliseconds, on_timer, 0);
    glutMainLoop();                            // Abgabe der Kontrolle an GLUT-Bibliothek
    return 0;
}