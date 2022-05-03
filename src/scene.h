#include "grid.h"
#include "trajectory.h"
#include "cam.h"
#include "circle.h"

struct Scene
{
    struct Camera camera;
    struct Grid grid;
    struct Trajectory trajectory;
    struct Circle origin;
};

void createScene(struct Scene* s);
