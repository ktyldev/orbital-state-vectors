#include "kepler.h"

double getEllipticalMeanAnomaly(double t, double P)
{
    double progress = fmod(t, P) / P;   // calc progress around orbit in range 0..1
    return progress * PI * 2.0;         // map 0..1 -> 0..2PI
}

// uses a binary search.
// algorithm from Jean H. Meeus - Astronomical Algorithms p. 206
double getEccentricAnomaly(double e, double M)
{
    double E = e;
    double E0;      // estimate for eccentric anomaly
    double D;

    const int iterations = 33;

    // 110 F = SGN(M) : M = ABS(M)/(2*PI)
    double F = (double)signbit(M);
    M = fabs(M) / (2.0 * PI);
    // 120 M = (M-INT(M))*2*PI*F 
    M = (M - (int) M) * 2.0 * PI* F;
    // 130 IF M < 0 THEN M = M+2*PI
    if (M < 0)
    {
        M = M + 2.0 * PI;
    }

    // 140 F = 1
    F = 1.0;
    // 150 IF M > PI THEN F = -1 
    // 160 IF M > PI THEN M = 2*PI - M
    if (M > PI)
    {
        F = -1.0;
        M = 2.0 * PI - M;
    }

    // 170 E0 = PI/2 : D = PI/4
    E0 = PI * 0.5;
    D = PI * 0.25;
    // 180 FOR J = 1 TO 33
    for (int J = 0; J < iterations; J++)
    {
        // 190 M1 = E0 - E*SIN(E0)
        double M1 = E0 - E * sin(E0);
        // 200 E0 = E0 + D*SGN(M-M1) : D = D/2
        E0 = E0 + D * signbit(M - M1);
        D *= 0.5;
    }

    // 220 E0 = E0*F
    E0 *= F;

    return E0;
}
