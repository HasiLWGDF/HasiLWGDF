# HasiLWGDF
A lightweight, open-source, 2D and 3D game engine/framework written in C++. HasiLWGDF provides support for lightweight and easy game development, using multiple graphics backends (both for 2D and 3D) and much more. HasiLWGDF is mostly inspired by Godot and Unity.
This repository contains the core of the HasiLWGDF project, providing an easy-to-use framework for developing simple games and prototypes, with support for input handling, graphics rendering, physics management and audio handling behind the scenes.

As said earlier, HasiLWGDF supports multiple graphics backend. Such as OpenGL (3.2+), Vulkan (1-1.3), Direct3D/DirectX (9, 11, 12), Metal, OpenGL ES (Currently only 2.0 is supported) and Software.

The core of the engine is designed to be lightweight and fast, with minimal overhead and efficient resource management. It supports a variety of platforms, and can be easily integrated with other libraries and frameworks.

## Supported Platforms
| OS | Renderers | Versions/Variants | Architectures | Compilers |
|-|-|-|-|-|
| Android | OpenGL ES, Software, Vulkan | 6+ | arm, arm64, amd64, i386 | Clang, GCC |
| Android TV | OpenGL ES, Software, Vulkan | 9+ | arm, arm64, i386, amd64 | Clang, GCC |
| FreeBSD | OpenGL, Software, Vulkan | Any | amd64, i386 | Clang, GCC |
| iOS | Metal, OpenGL ES, Software, Vulkan | 9+ | arm, arm64, amd64 | Apple Clang |
| Linux | OpenGL, Software, Vulkan | Any | amd64, arm64, i386 | Clang, GCC |
| macOS | Metal, OpenGL, Software, Vulkan | 11+ | amd64, arm64 | Apple Clang, GCC |
| OpenBSD | OpenGL, Software, Vulkan | Any | amd64, i386 | Clang, GCC |
| Switch | Software, Vulkan | Any | Any | Clang, GCC |
| tvOS | Metal, Software, Vulkan | Any | arm64, amd64 | Apple Clang |
| UWP | Direct3D/DirectX, Software | Any | Any | MSVC |
| watchOS | Metal, Software, Vulkan | Any | arm, arm64, amd64 | Apple Clang |
| Windows | Direct3D/DirectX, OpenGL, Software, Vulkan | 7+ | amd64, i386 | MinGW, MSYS, MSVC |
| Xbox | Direct3D/DirectX, Software | 360, One, series s/x | Any | MSVC |
| HTML5/Javascript | WebGL, WebGPU | Any | Any | None |
| Node.JS | WebGL, WebGPU | v14+ | Any | None |

Currently, there is no official support for using build tools other than CMake for using HasiLWGDF. Though you can try it yourself to see if it works (Note: IT IS NOT RECOMMENDED SINCE MOST OF THE DEPENDENCIES REQUIRE CMAKE AND MAY NOT WORK AS INTENDED).

Note that HasiLWGDF project also contains [HasiLWGDF-GS](https://github.com/Hasibix/HasiLWGDF-GS) (Game Server Library, inspired by Unity's NetCode for GameObjects), which is released under the AGPLv3 license, and [HasiLWGDF-Editor](https://github.com/Hasibix/HasiLWGDF-Editor) (Editor interface to make game development even more easier), which is released under the GPLv3 license. 

In future, we might make language bindings for Java, Javascript (Rewrite supporting only WebGL and WebGPU, because Emscripten might not work well since we have multiple graphics APIs and stuff), Node.JS (Rewrite like Javascript, but as a Node.JS package), C#, Haxe, Lua, Rust, Ruby, Go, Python etc.

All kind of contributions and feedback are welcome!

This project is **COMPLETELY** free to use. Anyone can make use of this project for any kind of open source use, so long as said use is also under the LGPLv3 license. For more info, consult [LICENSE.md](https://github.com/Hasibix/HasiLWGDF/blob/master/LICENSE.md).

Credits:

Coming soon!

---------------------------------------------------

<big><pre>
-----BEGIN LICENSE BLOCK-----
Copyright (c) 2023 Hasibix Hasib. All Rights Reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see https://www.gnu.org/licenses/.
-----END LICENSE BLOCK-----
</pre></big>
