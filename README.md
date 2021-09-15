# pbase
Base library for 3D stuff, like pointc, visu, ...

## Getting started
Should work on Unix (Ubuntu) and msys2/mingw (Windows).
```sh
# in the pbase dir:
mkdir build && cd build
cmake ..
make
make install # or sudo make install
```
On Unix, the library will be installed in /usr/local/
On Windows, it will be installed in C:/Libraries/
If using Windows, add C:/Libraries/lib to your PATH, so cmake can find libpbase.so

If you want to install the python bindings as well, set the env variable:
`PYTHON_LIB_INSTALL_DIR`
to the destination, in which the bindings should be installed


## Visu
My library [Visu](https://github.com/renehorstmann/Visu) uses pbase as its base library.
Visu uses OpenGL to render point clouds, meshes, etc.
SVisu is a simple version to quickly show a point cloud in code for debugging.


## types
Base classes for 3D stuff
 - `pCloud` point cloud (list of `vec4`)
 - `pIndices` indices (list of `int`)
 - `pIndicesList` list of `pIndices`
 - `pMeshIndices` list of triangles (list of `ivec3`)
 - `pMatrix` matrix of floats
 - `pVector` vector of floats

## error
Error management is based on rhc
`p_error` returns a string with the error code, or NULL if no error occured
`p_error_set` sets and returns an error
Functions can set an error and should return invalid data (e. g. `p_cloud_new_invalid`) or return `p_error`

## io
 - load and save stl files (Mesh)
 - load and save ply files (PointClouds (with normals and or colors), Meshs (with normals and or colors))
 - load and save csv files (Indices, IndicesList, Matrix, Vector)

## meshprimitives
Generates meshs:
 - plane
 - box
 - sphere
 - half_sphere
 - cylinder
 - cone
 - arrow

## RHC
based on my [rhc](https://github.com/renehorstmann/rhc) library.
Contains some useful stuff for C programming
 - allocators
 - error
 - log
 - dynarray
 - ...
All globals are renamed from `rhc_*` to `p_rhc_*`

## Mathc
based on my [Mathc](https://github.com/renehorstmann/Mathc) library.
Linear algebra types and functions in a glsl style
 - vec3
 - vec4
 - mat4
 - ...


## Todo
- visu
  - README.md
- pointc
  - uses flann
  - does not use pcl
    - normals
    - sac
    - icp
    - mesh
- collisionc?
  - capsule
  - mesh - cloud?
- robotc?
  - fk
  - ik
  - some robots
  - cell?
  - abb connection

## Author

René Horstmann

## Licence

This project is licensed under the MIT License - see the LICENSE file for details

