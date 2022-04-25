#include "grid.h"
#include "trajectory.h"
#include "cam.h"

struct Scene
{
    struct Camera camera;
    struct Grid grid;
    struct Trajectory trajectory;
};

void createScene(struct Scene* s);
