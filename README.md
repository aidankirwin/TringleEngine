# Tringle Engine
Tringle Engine is a multi-purpose engine for rendering and simulation. Version 1.0 is currently in progress.

## 1.0 Features in Development
- Model loading
- 2D and 3D rigid body physics
- Ambient and diffuse lighting

## Application Goals
The Tringle Engine is currently being developed to support the following applications:
- Port of [Voxel Renderer](https://github.com/aidankirwin/voxel_renderer)
- DICOM Viewer

## Build (Windows)

### Install Mingw64 Compiler
Note that the pre-compiled GLFW binaries are for the mingw64 compiler only. If you want to use a different C++ compiler you will need to compile your own GLFW binaries.
1. Go to https://www.msys2.org/
2. Install the MSYS2 shell
3. Launch the MSYS2 shell and type the following commands:
- ```pacman -Syu```
- ```pacman -S --needed base-devel mingw-w64-x86_64-toolchain```
- ```pacman -S gcc```
4. Ensure ```C:\msys64\mingw64\bin``` is in your PATH

### Install CMake
Go to https://cmake.org/download/ and install the latest version

### Build and Compile
1. Clone the repository
2. Build with CMake