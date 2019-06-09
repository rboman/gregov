# MATH 0471: Multiphysics integrated computational project 

[![Build Status](https://travis-ci.com/math0471/dg_shallow.svg?branch=romain)](https://travis-ci.com/math0471/dg_shallow)

## Goal
Development of the [Discontinuous Galerkin method](https://en.wikipedia.org/wiki/Discontinuous_Galerkin_method) (DG) applied to 2D [shallow water equations](https://en.wikipedia.org/wiki/Shallow_water_equations).  
[Link](http://www.montefiore.ulg.ac.be/~geuzaine/MATH0471/enonce2019.pdf) of the problem statement.

## Useful reminders
[Link](https://github.com/tgregov/Multiphysics/wiki) to the wiki.

## Assumptions
### On the mesh
* The elements edges are straight (constant normal vector over it)

## Compilation procedure
### On NIC4/VEGA
Connect to NIC4/VEGA (using SSH for instance). Then, build the code (`<cluster>` is either `vega` or `nic4`):
```bash
. ./build_cluster.sh <cluster>
```
Submit a batch file for one of the simulations
```bash
cd ../simulations
sbatch runObstacleSquare.sh
```


# Romain's notes


```
gmsh -2 ./geometry/young/young.geo
export OMP_NUM_THREADS=12
./build/bin/main ./geometry/young/young.msh ./params/young.dat pipo.msh
```
