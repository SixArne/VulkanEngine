# Summary

This is a personal project of mine, the goal here is to make a 3D Engine that has the following features.

- ECS system (either custom written or ETTS)
- 3D Rendering (OpenGL, Vulkan, Directx12 and Directx11)
- 3D Sound system (FMOD is used for this)
- Physics Engine (Nvidia PhysX)
- An Editor window (ImGui)
- The ability to load and save levels in files.

Everything should be set up CROSS platform.

To ensure this I have used CMAKE as a build system and Visual Studio Code as my editor.

# Setup

## Install VLD

This is for windows only, comment out the VLD include in main.cpp if you are
using a different system

- https://kinddragon.github.io/vld/

## Install extensions

Install the extensions in the `.vscode` folder, it only contains the important ones for debugging and hot reloading cmake configurations.

## Configure the project

>Ctrl Shift P

>Tasks: Run Build Task

>Configure

Choose either Debug or Release

## Build the project

>Ctrl Shift P

>Tasks: Run Build Task

Choose either Debug or Release

## Debugging

Go to the debug pannel and run the debugger. Make sure that the CMAKE project was configured for the
configuration you are debugging.

## Output

You can find the output of the Engine under `build/Engine/Debug|Release`.
Note: If you don't see fmod.dll or a resource folder then you have not configured cmake correctly.
