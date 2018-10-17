# PA5: Assimp Model Loading

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
Reverse spin direction: A

Reverse orbit direction: S

Camera

Reset to Sun - r
Move to next planet - n

## To Change The Model
To change the model, type in the name of the obj file you would like to load.
Example: "dragon.obj"


### Makefile Instructions 
Using CMake. 

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```
