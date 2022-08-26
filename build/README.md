# Build Instructions
Make sure you have the Pico C/C++ SDK installed and working on your machine. [Getting started with Raspberry Pi Pico is
the best place to start.](https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf)

You need to have PICO_SDK_PATH defined, e.g. `export PICO_SDK_PATH=/home/pi/pico/pico-sdk/`

- Clone the code from the repository.
- Change directory into `build`
- Run `cmake -DCMAKE_BUILD_TYPE=Debug ..` (for a debug build) or `cmake ..` (for a release build).
- Run `make`

The resulting file `piccolo_os_demo.elf` can be flashed on your Pico in the normal way.
