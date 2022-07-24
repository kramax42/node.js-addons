## Building Node-API Addons Using CMake.js

## Tutorial:
- [build with cmake.js](https://napi.inspiredware.com/build-tools/cmake-js.html)

### Examples

The objective of these examples is to demonstrate how to build Node-API addons using [CMake.js](https://github.com/cmake-js/cmake-js#readme).

### NAPI_VERSION

When building Node-API addons, it's important to specify to the build system the Node-API version your code is designed to work with. With CMake.js, this information is specified in the `CMakeLists.txt` file:  

```
add_definitions(-DNAPI_VERSION=3)
```

Since Node-API is ABI-stable, your Node-API addon will work, without recompilation, with the Node-API version you specify in `NAPI_VERSION` and all subsequent Node-API versions. 

In the absence of a need for features available only in a specific Node-API version, version 3 is a good choice as it is the version of Node-API that was active when Node-API left experimental status. 