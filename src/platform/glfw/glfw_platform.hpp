#pragma once

#include "core/platform.hpp"

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GLFWPlatform : public Platform
{
public:
    GLFWPlatform() = default;
    ~GLFWPlatform() = default;

    void set_title(const std::string& new_title) override;
    void set_size(int new_width, int new_height) override;
    void create() override;
    bool is_close_requested() override;
    void update() override;
    void close() override;
    void destroy() override;

    double get_time() override;

private:
    GLFWwindow* m_Window = nullptr;

};