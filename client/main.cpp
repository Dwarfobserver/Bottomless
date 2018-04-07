
#include <iostream>
#include <utility.hpp>
#include <GL/glew.h>
#include <glfw3.h>

int main()
{
    std::cout << "Bottomless -- client v" << build::version_string
              << " (" << build::mode_string << ")\n";

    glfwSetErrorCallback([] (int error, const char* description)
    {
        std::cout << description;
    });

    if (!glfwInit()) return 1;

    auto const terminateGlfw = defer([] { glfwTerminate(); });

    glfwWindowHint(GLFW_SAMPLES, 4);
    auto window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window) return 1;

    auto const destroyWindow = defer([&] { glfwDestroyWindow(window); });

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
