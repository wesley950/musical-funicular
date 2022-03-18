#include "glfw_platform.hpp"
#include "glfw_callbacks.hpp"

#include <glad/glad.h>

void GLFWPlatform::set_title(const std::string &new_title)
{
    m_Title = new_title;
    if (m_Window)
    {
        glfwSetWindowTitle(m_Window, new_title.c_str());
    }
}

void GLFWPlatform::set_size(int new_width, int new_height)
{
    m_Width = new_width;
    m_Height = new_height;
    if (m_Window)
    {
        glfwSetWindowSize(m_Window, new_width, new_height);
    }
}

void GLFWPlatform::create()
{
    if (!m_Window)
    {
        glfwInit();
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(0);

        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        
        glfwSetTime(0.0);
    }
}

bool GLFWPlatform::is_close_requested()
{
    if (m_Window)
    {
        return glfwWindowShouldClose(m_Window);
    }
    return false;
}

void GLFWPlatform::update()
{
    if (m_Window)
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}

void GLFWPlatform::destroy()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}

void GLFWPlatform::close()
{
    if (m_Window)
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }
}

double GLFWPlatform::get_time()
{
    // Note to future: apparently glfwSwapBuffers makes "System.clock" on Wren's
    // side return "strange" values. For some reason implementing a foreign time 
    // function does seem to solve the problem and I'm too lazy to use Xorg so...
    return glfwGetTime();
}

Platform *Platform::create_instance()
{
    s_Instance = new GLFWPlatform();
    return s_Instance;
}

void Platform::destroy_instance()
{
    delete s_Instance;
    s_Instance = nullptr;
}
