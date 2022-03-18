#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow*, int key_code, int scan_code, int action, int mods);
void framebuffer_size_callback(GLFWwindow*, int width, int height);
