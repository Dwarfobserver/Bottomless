
[![Build Status](https://travis-ci.org/Dwarfobserver/Bottomless.svg?branch=master)](https://travis-ci.org/Dwarfobserver/Bottomless)

# Bottomless

This is a personal project for a game.
I use it to test many things.
Ideally, I'd like it to have these properties :

 - cross-platform (linux and windows)
 - multi-threaded
 - 2D specific shaders
 - reusable code (eg. serialization)
 - networking (authoritative server architecture)
 - hosted on a raspberry PI, with database on USB
 - arcade platform collision
 - further improvements on lag

### Build the project

```
cd build
cmake ../..
cmake --build .
ctest
```

### Project organisation

The project is built with cmake and msvc, gcc or clang.
There is three main parts :

 - The common code
 - The client
 - The server

Each part has a static library and a test executable associated.
The client and the server also generate their executables.

The dependencies folder stores all external code used, apart from the C++ standard library.

To reduce the tests building, static libraries from the client and the server could be created.

### Dependencies

The following libraries are used :

 - asio (boost asio standalone version) for networking
 - spdlog for logging
 - catch2 for tests
 - clara for command line
