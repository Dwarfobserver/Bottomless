
# Bottomless

This is a personal project for a game.
I use it to test many things.
Ideally, I'd like it to have these properties :

 - cross-platform
 - multi-threaded
 - 2D specific shaders
 - reusable code (eg. serialization)
 - networking (authoritative server architecture)
 - hosted on a raspberry PI, with database on USB
 - arcade platform collision
 - further improvements on lag

### Project organisation

The project is built with cmake.
There is four targets :

 - The common part, created as a static library
 - The client executable
 - The server executable
 - The tests executable

The dependencies folder stores all external code used, apart from the C++ standard library.

To reduce the tests building, static libraries from the client and the server could be created.

### Dependencies

The following libraries are used :

 - asio (boost asio standalone version) for networking
 - spdlog for logging
 - catch2 for tests
 - clara for command line
