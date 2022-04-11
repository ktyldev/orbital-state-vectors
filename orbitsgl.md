# Requirements

## Primitives

### Line

Orbits are drawn from polylines.
Lines are one pixel thick, regardless of their distance to the camera.

### Circles

The focus of the orbit and the satellite are circles.
The circles may be a fixed width.

## Orbit

I can view an orbit in 3D space.
The orbit is one pixel thick.
The orbit may by elliptical, hyberbolic or parabolic.

## Satellite

I can see a satellite following the orbit as per Kepler's laws of planetary motion.
The orbital state vectors of the orbiting object are visible.

## Grid

There is a reference grid on the horizontal plane centred on the orbit's focus.
The reference grid has labelled axes in all 3 dimensions.

## Camera

The camera rotates around the focus of the orbit.
The camera may use perpective or orthgraphic projection.

## Controls

### Time

I can pause the orbit animation by pressing space.
Pressing space again unpauses the animation.

### Impulse

While the paused I can use HN, JL, IK to apply impulse to the orbiter, as in KSP.

# Not in scope

I do not need to be able to see nested orbits.
