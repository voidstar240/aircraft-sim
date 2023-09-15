# Aircraft Sim
This is a homework project for my aerospace C++ class. 
Releases are available on the Releases page.

## Building
To build the project create a `build` directory at the root of the project
and move into it.

    $ mkdir build && cd build

Create the editor project files or Makefile.

    $ cmake ..

### Unix
Run the Makefile.

    $ make

### Windows
Open the solution file `AircraftSim.sln` in Visual Studio.
Build the project from Visual Studio.

## Build Types
There are 4 build types available: `Debug`, `Release`, `RelWithDebInfo` and
`MinSizeRel`. For single-configuration generators (Makefile or ninja), specify
a build type by appending `-DCMAKE_BUILD_TYPE=<build-type>` to your `cmake`
command. When built in any of the release modes `NDEBUG` will be defined.
