
#ifndef NM_H_
#define NM_H_

#include <raylib.h>

#define NM_WINDOW_WIDTH 1280
#define NM_WINDOW_HEIGHT 720

#define NM_GRAPH_ZOOM 1.5
#define NM_GRAPH_EDGE 2
#define NM_GRAPH_SIZE 512
#define NM_GRAPH_BIAS 1.0e-6f

typedef double (nm_graph_func)(double x);
typedef struct {
    double x, y;
} vec2d;

void nm_open(const char *title);
void nm_close();

double nm_plot_x(double x);
double nm_plot_y(double y);

vec2d nm_plot(vec2d p);
void nm_open_graph(double x1, double x2, double y1, double y2); /* set domain, render background */
void nm_graph(Color, nm_graph_func *f); /* render graph */

#endif // NM_H_

