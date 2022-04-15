#include "ellipse.h"

void getApisides(struct Ellipse e, struct Apisides* a)
{
    a->min = e.a * (1.0 - e.e);
    a->max = e.a * (1.0 + e.e);
}

double getSemiMinorAxis(struct Ellipse e)
{
    return e.a * sqrt(1.0 - e.e * e.e);
}

void getPosition(struct Ellipse e, double t, vec2 p)
{
    double b = getSemiMinorAxis(e);

    double x = e.a * cos(t);
    double y = b * sin(t);

    vec2 pos = {x,y};
    glm_vec2_copy(pos, p);
}

double getFocusDistance(struct Ellipse e)
{
    double a = e.a;
    double b = getSemiMinorAxis(e);
    return sqrt(a * a - b * b);
}
