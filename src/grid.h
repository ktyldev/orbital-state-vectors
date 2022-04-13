#pragma once

#include "gfx.h"

struct Grid
{
    GLfloat* vertices;
    int vertCount;
    GLuint vbo;
    GLuint vao;
};

// generate a grid with side length n. n refers to the vertices per side, not tiles.
//
// generate static data to do with the grid, so all the vertex data, vertex attributes, vbo and vao.
// none of this data should change while the application is running.
//
//          0 2 4
//      
//      6   x x x   7
//      8   x x x   9
//      10  x x x   11
//
//          1 3 5
//
// Grid*        g   generated grid data stored in a struct
// dimension    n   side length of a square grid i.e 1->1 points, 2->4 points, 3->9 ...
void generateGrid(struct Grid* g, int n);
void drawGrid(struct Grid g, GLuint shaderProgram);
