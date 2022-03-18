#include "glfw_callbacks.hpp"
#include "core/input.hpp"

#include <glad/glad.h>

static int32_t glfw_to_internal_key_code(int32_t key_code)
{
    switch (key_code)
    {
    case GLFW_KEY_ESCAPE:
        return Input::KEY_ESCAPE;

    case GLFW_KEY_F1:
        return Input::KEY_F1;
    case GLFW_KEY_F2:
        return Input::KEY_F2;
    case GLFW_KEY_F3:
        return Input::KEY_F3;
    case GLFW_KEY_F4:
        return Input::KEY_F4;
    case GLFW_KEY_F5:
        return Input::KEY_F5;
    case GLFW_KEY_F6:
        return Input::KEY_F6;
    case GLFW_KEY_F7:
        return Input::KEY_F7;
    case GLFW_KEY_F8:
        return Input::KEY_F8;
    case GLFW_KEY_F9:
        return Input::KEY_F9;
    case GLFW_KEY_F10:
        return Input::KEY_F10;
    case GLFW_KEY_F11:
        return Input::KEY_F11;
    case GLFW_KEY_F12:
        return Input::KEY_F12;

    case GLFW_KEY_1:
        return Input::KEY_1;
    case GLFW_KEY_2:
        return Input::KEY_2;
    case GLFW_KEY_3:
        return Input::KEY_3;
    case GLFW_KEY_4:
        return Input::KEY_4;
    case GLFW_KEY_5:
        return Input::KEY_5;
    case GLFW_KEY_6:
        return Input::KEY_6;
    case GLFW_KEY_7:
        return Input::KEY_7;
    case GLFW_KEY_8:
        return Input::KEY_8;
    case GLFW_KEY_9:
        return Input::KEY_9;
    case GLFW_KEY_0:
        return Input::KEY_0;

    case GLFW_KEY_LEFT_SHIFT:
    case GLFW_KEY_RIGHT_SHIFT:
        return Input::KEY_SHIFT;
    case GLFW_KEY_LEFT_CONTROL:
    case GLFW_KEY_RIGHT_CONTROL:
        return Input::KEY_CONTROL;
    case GLFW_KEY_LEFT_SUPER:
    case GLFW_KEY_RIGHT_SUPER:
        return Input::KEY_SUPER;
    case GLFW_KEY_LEFT_ALT:
    case GLFW_KEY_RIGHT_ALT:
        return Input::KEY_ALT;
    case GLFW_KEY_ENTER:
    case GLFW_KEY_KP_ENTER:
        return Input::KEY_ENTER;
    case GLFW_KEY_BACKSPACE:
        return Input::KEY_BACKSPACE;
    case GLFW_KEY_DELETE:
        return Input::KEY_DELETE;
    case GLFW_KEY_INSERT:
        return Input::KEY_INSERT;
    case GLFW_KEY_PAGE_UP:
        return Input::KEY_PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:
        return Input::KEY_PAGE_DOWN;
    case GLFW_KEY_HOME:
        return Input::KEY_HOME;
    case GLFW_KEY_END:
        return Input::KEY_END;

    case GLFW_KEY_UP:
        return Input::KEY_UP;
    case GLFW_KEY_DOWN:
        return Input::KEY_DOWN;
    case GLFW_KEY_LEFT:
        return Input::KEY_LEFT;
    case GLFW_KEY_RIGHT:
        return Input::KEY_RIGHT;

    case GLFW_KEY_SPACE:
        return Input::KEY_SPACE;

    default:
        if (key_code >= GLFW_KEY_A && key_code <= GLFW_KEY_Z)
        {
            return Input::KEY_Z - (GLFW_KEY_Z - key_code);
        }
    }

    return -1;
}

void key_callback(GLFWwindow *, int key_code, int scan_code, int action, int mods)
{
    key_code = glfw_to_internal_key_code(key_code);
    if (key_code == -1)
        return;

    if (action == GLFW_PRESS)
        Input::set_key_pressed(key_code, true);
    else if (action == GLFW_RELEASE)
        Input::set_key_pressed(key_code, false);
}


void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}
