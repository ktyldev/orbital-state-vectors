#include "scene.h"

const int GRID_COLUMNS = 19;
const int TRAJECTORY_POINTS = 100;
const float ORIGIN_RADIUS = 0.02;

void createScene(struct Scene* s)
{
    // generate scene objects
    createCamera(&(s->camera));
    generateGrid(&(s->grid), GRID_COLUMNS + 1);
    generateTrajectory(&(s->trajectory), TRAJECTORY_POINTS);
    generateCircle(&(s->origin), ORIGIN_RADIUS);
}
