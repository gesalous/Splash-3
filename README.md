# Lock implementation
The folder ges_locks contains the code for a) spin locks, b) ticket locks, c) mcs locks, and d) a centralized barrier.

# Build instructions
Assuming HOME is the root folder of the project


`cd ges_locks`

`mkdir build`

`cd build`

`cmake -DCMAKE_INSTALL_PREFIX=../../deps -DSPIN_LOCK=TRUE for spin locks` or

`cmake -DCMAKE_INSTALL_PREFIX=../../deps for mcs locks`


`make; make install`

`cd ../../codes`

`make -C kernels/lu/contiguous_blocks`

`make -C apps/water-nsquared`


`cd kernels/lu/contiguous_blocks`

`./LU -n <matrix dimensions> -p <number of processes>`

for all LU runs we use dimensions = 6000

and for the water-nsquared

`cd apps/water-nsquared`

`./WATER-SQUARED < inputs/parsec_gesalous`


# RESULTS
In the <HOME>/results are the runs for lu and water-nsquared for mcs and spin locks.
<HOME>/results/water_nsquared_speedup.pdf
<HOME>/results/lu_speedup.pdf

