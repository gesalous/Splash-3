# Build and run instructions

Assuming <HOME> is the root folder of the project

cd ges_lock/build

 - For spin lock
cmake -DCMAKE_INSTALL_PREFIX=../../deps ../ -DSPIN_LOCK=TRUE; make; make install

- For ticket lock
cmake -DCMAKE_INSTALL_PREFIX=../../deps ../ -DTICKET_LOCK=TRUE; make; make install

- For mcs lock
cmake -DCMAKE_INSTALL_PREFIX=../../deps ../  make; make install


Then, cd ../../ (back to root folder)

