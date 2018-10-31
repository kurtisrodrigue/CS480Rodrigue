# PA8: Bullet

# Team Members
### Kurtis Rodrigue
### Thomas McCrone
### Jeffrey Williams

# Dependencies, Building, and Running

## Notes:
I didn't finish this, I was able to load everything in, but collisions was another whole beast I did not have time to tackle. I also couldn't find out how to scale the objects..I will be asking for help soon. -Kurtis Rodrigue

## Extra Credit
I managed to load in the board using the triangle mesh method!

## Dependency Instructions
This project uses the following libraries:
- GLM
- Glew
- Bullet

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libbullet-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2 bullet
```



### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. 

```bash
mkdir build
cd build
cmake ..
make
./Bullet
```
