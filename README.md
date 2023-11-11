# Aircraft Sim

This is homework 2 for AERSP 424. The pre-built Windows binary is available on the [releases](https://github.com/voidstar240/aircraft-sim/releases) page.

## Building

Currently this project is only available on Visual Studio.
Clone this repo. Open HW2_424.sln with Visual Studio.
Ensure that HW2_424 is set as the startup project.
Build the HW2_424 Project. The built executable is located in
the `build\<CONFIG>-<PLATFORM>\bin\` directory. If you want to
move this file ensure to move `SDL2.dll` and `map.bmp` with it.

## Dependencies

SDL2 is the main dependency of this project. This project ships with all the
required SDL2 dependencies for ease of building. Therefore, there is no need
to install SDL2 on your system to build this program.