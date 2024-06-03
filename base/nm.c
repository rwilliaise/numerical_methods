
#include <math.h>
#include <nm.h>
#include <raylib.h>
#include <stdio.h>

const int GRAPH_X = (NM_WINDOW_WIDTH - NM_GRAPH_SIZE) / 2;
const int GRAPH_Y = (NM_WINDOW_HEIGHT - NM_GRAPH_SIZE) / 2;

struct {
    int init;
    double x1, x2;
    double y1, y2;
    float dx;
} graph_state = {};

void nm_open(const char *title) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(NM_WINDOW_WIDTH, NM_WINDOW_HEIGHT, title);
}

void nm_close() {
    CloseWindow();
}

double nm_plot_x(double x) {
    double domain = graph_state.x2 - graph_state.x1;
    return (x - graph_state.x1) * NM_GRAPH_SIZE / domain + GRAPH_X;
}

double nm_plot_y(double y) {
    double range = graph_state.y2 - graph_state.y1;
    return (graph_state.y2 - y) * NM_GRAPH_SIZE / range + GRAPH_Y;
}

vec2d nm_plot(vec2d p) {
    return (vec2d) {
        nm_plot_x(p.x),
        nm_plot_y(p.y),
    };
}

/* this is where roundoff errors in rendering are introduced. NOWHERE ELSE!! */
static Vector2 nm_quantize(vec2d p) {
    return (Vector2) {
        p.x,
        p.y,
    };
}

void nm_open_graph(double x1, double x2, double y1, double y2) {
    if (!graph_state.init) {
        graph_state.init = 1;
        graph_state.x1 = x1;
        graph_state.y1 = y1;
        graph_state.x2 = x2;
        graph_state.y2 = y2;
        graph_state.dx = (x2 - x1) / 1000.0f;
    }

    float mouseWheelMovement = GetMouseWheelMove();
    if (mouseWheelMovement > 0) {
        graph_state.x1 *= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.y1 *= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.x2 *= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.y2 *= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.dx = (x2 - x1) / 1000.0f;
    }
    if (mouseWheelMovement < 0) {
        mouseWheelMovement = fabsf(mouseWheelMovement);
        graph_state.x1 /= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.y1 /= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.x2 /= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.y2 /= NM_GRAPH_ZOOM * mouseWheelMovement;
        graph_state.dx = (x2 - x1) / 1000.0f;
    }

    // drawing gridmarks at integer values
    {
        double x = ceilf(graph_state.x1);
        while (x < graph_state.x2) {
            Color c = x == 0 ? BLACK : LIGHTGRAY;
            double render_x = nm_plot_x(x);
            DrawLine(render_x, GRAPH_Y, render_x, GRAPH_Y + NM_GRAPH_SIZE, c);
            x++;
        }
    }

    {
        double y = ceilf(graph_state.y1);
        while (y < graph_state.y2) {
            Color c = y == 0 ? BLACK : LIGHTGRAY;
            double render_y = nm_plot_y(y);
            DrawLine(GRAPH_X, render_y, GRAPH_X + NM_GRAPH_SIZE, render_y, c);
            y++;
        }
    }

    Rectangle graph_rect = (Rectangle) {
        .width = NM_GRAPH_SIZE,
        .height = NM_GRAPH_SIZE,
        .x = GRAPH_X,
        .y = GRAPH_Y,
    };
    DrawRectangleLinesEx(graph_rect, NM_GRAPH_EDGE, GRAY);
}

void nm_graph(Color c, nm_graph_func *f) {
    if (graph_state.x1 > graph_state.x2) return;
    if (graph_state.y1 > graph_state.y2) return;
    double x = graph_state.x1;

    // DrawRectangleLinesEx draws insetted borders, which is annoying
    // anyway...
    BeginScissorMode(GRAPH_X + NM_GRAPH_EDGE, GRAPH_Y + NM_GRAPH_EDGE, NM_GRAPH_SIZE - 2 * NM_GRAPH_EDGE, NM_GRAPH_SIZE - 2 * NM_GRAPH_EDGE);

    // roundoff error bias
    while (x + graph_state.dx - NM_GRAPH_BIAS <= graph_state.x2) {
        double last_x = x;
        x += graph_state.dx;

        vec2d p1 = (vec2d) { last_x, f(last_x) };
        vec2d p2 = (vec2d) { x, f(x) };
        DrawLineEx(
            nm_quantize(nm_plot(p1)),
            nm_quantize(nm_plot(p2)),
            1.5f,
            c
        );
    }

    EndScissorMode();
}

