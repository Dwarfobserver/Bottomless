
#include <catch.hpp>
#include <GL/glew.h>
#include <glfw3.h>
#include <utility.hpp>


TEST_CASE("glew & glfw test", "[opengl]") {

    REQUIRE(glfwInit());
    
    auto const terminateGlfw = defer([] { glfwTerminate(); });

    glfwWindowHint(GLFW_SAMPLES, 4);
    auto window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

    REQUIRE(window != nullptr);

    auto const destroyWindow = defer([&] { glfwDestroyWindow(window); });

    glfwMakeContextCurrent(window);
    glClear(GL_COLOR_BUFFER_BIT);
}
