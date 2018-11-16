# PA10: Pinball (???)

# Team Members
### Kurtis Rodrigue
### Thomas McCrone
### Jeffrey Williams

# Dependencies, Building, and Running

## Notes:
Bullet is hard. We were unable to get things working properly in order to start on game mechanics. So we have a board loaded in with partially working physics. Lighting is done, however I didn't get the spotlight or multiple lights working.

## Dependency Instructions
This project uses the following libraries:
- GLM
- Glew
- Bullet
- Assimp
- ImageMagick

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libbullet-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2 bullet assimp imagemagick
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
