/*
 * Chapter 2, Exercise 6.
 *
 * "Write a program that receives as input a number x and a parameter n and
 * returns x rounded to n decimal digits."
 */

#include <nm.h>
#include <raylib.h>
#include <math.h>

double f(double x) {
    return ceil(x);
}

double ex6_round(double x, double n) {
    double big = pow(10, n);
    return round(x * big) / big;
}

double ex6_round1(double x) {
    return ex6_round(x, 1);
}

double ex6_round2(double x) {
    return ex6_round(x, 2);
}

int main(void) {
    nm_open("Chapter 2, Exercise 6");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);

            nm_open_graph(-0.15, 0.15, -0.15, 0.15);
            nm_graph(RED, &ex6_round1);
            nm_graph(BLUE, &ex6_round2);
        EndDrawing();
    }

    nm_close();
}
