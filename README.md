# graphics-math
A small, fully `constexpr`, header-only C++17 mathematics library for graphics. `graphics-math` was originally part of [Traced](https://github.com/jvmnielsen/traced). 

## Features
* Vectors: `Vec2`, `Vec3`
* Points: `Point2`, `Point3`
* Normals: `Normal3`
* Matrices: `Matrix4x4`
* Transformations: `Transform`, `ONB`
* Miscellaneous utility: `Color3`, *constants*

## Dependencies
* [gcem](https://github.com/kthohr/gcem)

I recommend installing dependencies via a package manager such as [vcpkg](https://github.com/Microsoft/vcpkg), and then invoking CMake with `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`, pointing it to the relevant toolcahin file. 

## Using the Library
The library is header-only and can be added to a project by simply copying the `include` folder and then including `graphics-math.hpp`. 

Alternatively, the library exports the `graphics-math` CMake target. 

The library uses the namespace `gm`. 