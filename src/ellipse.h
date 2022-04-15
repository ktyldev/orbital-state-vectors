#pragma once

#include <cglm/vec2.h>

struct Ellipse
{
    double a;   // semi-major axis
    double e;   // eccentricity
};

// apisides are the min and max radii of an ellipse
struct Apisides
{
    double min;
    double max;
};

// get the apisides of an ellipse
//
// e - the ellipse
// a - destination apisides
void getApisides(struct Ellipse e, struct Apisides* a);

// get the semi-minor axis (b) of an ellipse
//
// e - the ellipse
double getSemiMinorAxis(struct Ellipse e);

// get a position on the edge of an ellipse
//
// e - the ellipse
// t - angle around the centre of ellipse
void getPosition(struct Ellipse e, double t, vec2 position);

// get the distance between a focus and the origin of an ellipse
//
// e - the ellipse
double getFocusDistance(struct Ellipse e);
