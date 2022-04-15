#pragma once

#include <math.h>

#include "geom.h"
#include "ellipse.h"
#include "gfx.h"

struct KeplerElements
{
    struct Ellipse ellipse;
};

// get the mean anomaly of an elliptical orbit at time t with period P
//
// t - time
// P - period
double getEllipticalMeanAnomaly(double t, double P);

// get the eccentric anomaly of an elliptical orbit from the mean anomaly
//
// e - eccentricity of the orbit
// M - mean anomaly
double getEllipticalEccentricAnomaly(double e, double M);
