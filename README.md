# Music visualizer

> Program allows you to play audio files with wav format and show simple audio wave "visualisation".
___

### Dependencies for Running Locally
* cmake >= 3.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
  * For Windows you will need download SDL2 manually and put it under `extern/SDL2`, [Click to get SDL2](https://www.libsdl.org/download-2.0.php)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Windows: recommend using [MinGW](http://www.mingw.org/)

### Basic Build Instructions

1. Clone this repo.
2. Compile: `cd build && cmake .. && make`.
3. Run it `./MusicVisualizer -f test.wav`.

### Developet and tested under this platforms
> Windows 10 x64

> Debian GNU/Linux 10 (buster)

## Next to develop
```
- Fix issue with fast play for some wav files
- Add UI components to control player (Stop/play, volume, next, prev buttons etc)
- Update visualisation to be more relevant to audio wave, channel and frequency
```
