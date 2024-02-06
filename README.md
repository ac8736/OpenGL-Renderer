# OpenGL-Renderer

## Purpose
To learn graphics with OpenGL by building an OpenGL Graphics Engine in C++. The goal is to create a graphics renderer capable of 2D/3D graphics rendering.

## Run
Currently, this project is built in Visual Studio 2022. Make sure to run the GenerateProjectFiles.bat file to create the project files.

## Technologies
- GLFW
- Glad
- OpenGL
- stb_image
- ImGui

## Dev Log (migrating to a website very soon)
### Version: Apricot
#### Renderer
The graphics engine is currently capable of rendering various shapes composed of simple triangles. For instance, in the screenshot below, I've created two cubes, which are conposed of 6 faces, each face being composed of two triangles. 
#### Camera
I have implemented two types of cameras: orthographic and perspective. The orthographic camera is used for 2D renders, while the perspective camera will be used for 3D renders. The screenshot below is a 3D render, and as such I am using my perspective camera implementation.
#### Shaders, Textures, Lighting
I have implemented a shaders class which is responsible for compiling shaders in GLSL and uploading various uniforms. Not every uniform has been implemented as I have not reached a use case for them yet, but they will implemented in the future. A Texture class is responsible for reading in and binding textures during rendering. For lighting, much of the code lies within the GLSL files.

#### Current Goals
- Switch to CMake. Since all external libraries use CMake and it is industry standard, I will be learning CMake and most likely switch from Visual Studio to Visual Studio Code for future development.
- Code refactor for better code structure. Currently, it is more messy than intended as my primary goal was learning the OpenGL basics.
- Fully integrate Assimp. The ability to import 3D models is a primary goal that I intend to implement once the CMake conversion and refactoring is done.
- Better GUI and implement ability to update the scene with GUI controls. I only plan on working on this once Assimp is integrated and stable.
- Note: I may be taking a small leave on this graphics engine development since there are a number of game development projects I'm involved in. I'm also revisiting and polishing old website projects I've made in the past. 

![renderer](https://github.com/ac8736/OpenGL-Renderer/assets/87680132/54921676-8b35-4d76-a5c6-8db7aea654ed)
