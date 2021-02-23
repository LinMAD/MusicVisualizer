Music visualizer
========

> Program allows you to play audio file with wav format and show simple audio wave "visualisation".
___

## Example of application window

![Demo](doc/app_window.PNG)

## Getting Started

### Requirements

! `Your machine must have access to audio device` !

Docker containers or virtual machines without audio will lead to application termination.

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

### Build and Run
1. Compile: `cd build && cmake .. && make`.
2. Run it `./MusicVisualizer -f test.wav`.

* `test.wav` contains audio of coffe machine but you can use own sounds.

## Project structure
```
src
├── main.cpp    // Entry point
├── Audio       // Contains audio related implementation
│   └── SDL
├── Exception   // Application exceptions
└── Graphic     // Graphic related implementation
    └── SDL
```
* Project based on SDL library so concreet implementation (wrappers) must be stored inside SDL folders, for example `Graphic/SDL`.

## Next to develop
```
- Fix issue with fast play for some wav files
- Add UI components to control player (Stop/play, volume, next, prev buttons etc)
- Update visualisation to be more relevant to audio wave, channel and frequency
```

#### Developet and tested under this platforms
- Windows 10 x64
- Debian GNU/Linux 10 (buster)

## License
This project is licensed with the `MIT license`.
___

# Udacity Capstone Project Requirements – Rubric Points Addressed

Below is the description of how Udacity project requirements are fulfilled.

### 1. README (All Rubric Points REQUIRED)

* A README with instructions is included with the project
  * Yes - you are reading this README

* The README indicates which project is chosen
  * Yes - after title

* The README includes information about each rubric point addressed
  * Yes

### 2. Compiling and Testing (All Rubric Points REQUIRED)

* The submission must compile and run
  * Yes

### 3. Loops, Functions, I/O

* The project demonstrates an understanding of C++ functions and control structures
  * Yes.

* The project reads data from a file and process the data, or the program writes data to a file
  * Yes, WAV file will be loaded. Check `AudioWrapper.cpp:17` called `SDL_LoadWAV`

* The project accepts user input and processes the input
  * Yes, by flag `-f` you can load any wav file. Check `main.cpp` and function `GetCmdOption`

### 4. Object Oriented Programming

* The project uses Object Oriented Programming techniques
  * Yes, birght example `Graphic/Renderer.h` and `Graphic/SDL/RendererWrapper.h`

* Classes use appropriate access specifiers for class members
  * Yes.

* Class constructors utilize member initialization lists
  * Yes, following constructors: `AudioWrapper`, `RendererWrapper`

* Classes abstract implementation details from their interfaces
  * Yes, `RendererWrapper` implements abstract `Renderer` with isolated SDL calls.

* Classes encapsulate behavior
  * Yes, `RendererWrapper` controlls SDL functions, other code will only use `Renderer`. Same with `AudioData`.

* Classes follow an appropriate inheritance hierarchy
  * Yes, `Renderer` and `RendererWrapper`

* Overloaded functions allow the same function to operate on different parameters
  * No, nothing designed like that.

* Derived class functions override virtual base class functions
  * Yes, take a look virtual methods overloads `RendererWrapper` overloads protected methods of `Renderer`.

* Templates generalize functions in the project
  * No, not implmeneted.

### 5. Memory Management

* The project makes use of references in function declarations
  * Yes, I used it to passing values like `const std::string&`

* The project uses destructors appropriately
  * Yes, for example: `RendererWrapper::~RendererWrapper()`

* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
  * Yes, for example `AudioWrapper` has `std::shared_ptr<AudioData> m_AudioData;` and `std::unique_ptr<Renderer> s_RendererImpl` in `Renderer`

* The project follows the Rule of 5
  * No, I used mostly smart pointers.

* The project uses move semantics to move data, instead of copying it, where possible
  * No, I using refrences and mutex to access audio data.

* The project uses smart pointers instead of raw pointers
  * Yes & No: mostly I used smart pointers when code must be used else where. Raw pointers was used only for class owners.

### 6. Concurrency

* The project uses multithreading
  * Yes, the log messages are in `launch::async` check method `Log::Write` and SDL uses it as well.
* A promise and future is used in the project
  * No, no need for that. Could be updated when playlist of audio will be loaded.
* A mutex or lock is used in the project
  * Yes, when searching audio file and writing it to vector, check `Player` for more details.
* A condition variable is used in the project
  * No.
