# PA7: Solar System

# Team Members:

Thomas McCrone

Kurtis Rodrigue

Jeffrey Williams

# Dependencies, Building, and Running

### Assimp:

Enter the following commands into terminal to install.

Mac: 
```bash
brew install assimp
```

Linux: 
```bash
sudo apt-get install assimp
```

### ImageMagick:

Enter the following commands into terminal to install.

Mac: 
```bash
brew install imagemagick
```

Linux: 
```bash
sudo apt-get install imagemagick
```


## Controls
### Planets
Reverse spin direction: A

Reverse orbit direction: S

Change simulation speed: UP/DOWN arrow keys

Toggle System Scale: M

### Camera

Reset to Sun: R

Move to next planet: N


### Makefile Instructions 
Using CMake. 

```bash
mkdir build
cd build
cmake ..
make
./SolarSystem
```
