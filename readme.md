# OrbitsGL

An OpenGL application demonstrate the construction and manipulation of an elliptical Keplerian orbit by the use of Keplerian orbits or orbital state vectors.

# Dependencies

* gcc
* glew
* sdl2
* cglm

# Compiling

Run `make` to compile a binary to `bin/orbitsgl`.

# Running

Run `make run` to compile and run application.
Otherwise it can be run with `./bin/orbitsgl` or `./launch`.
The `./launch` script detects the presence of `prime-run` in order to use [PRIME](https://wiki.archlinux.org/title/PRIME) to force the use of a second GPU.
