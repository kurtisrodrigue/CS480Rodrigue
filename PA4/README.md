# PA1: Spinning Cube

# Dependencies, Building, and Running

## Controls
Reverse spin direction: A

Reverse orbit direction: S

## To Change The Model
To change the model obj file, go to line 5 of object.cpp and change the string literal (assigned to obj_file) to the desired file directory. Currently it is set to ../src/board.obj and to switch to dragon it should be ../src/dragon.obj

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```
