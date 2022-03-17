#pragma once

#include <string>

#include "wren.hpp"

class Platform
{
public:
    Platform() = default;
    virtual ~Platform() = default;

    virtual void set_title(const std::string &new_title) = 0;
    virtual void set_size(int new_width, int new_height) = 0;
    virtual void create() = 0;
    virtual bool is_close_requested() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;

    static Platform *create_instance();
    static void destroy_instance();

    static void display_set_title(WrenVM *vm);
    static void display_set_size(WrenVM *vm);
    static void display_create(WrenVM *vm);
    static void display_is_close_requested(WrenVM *vm);
    static void display_update(WrenVM *vm);
    static void display_destroy(WrenVM *vm);
    static WrenForeignMethodFn bind_platform_methods(WrenVM *vm, const char *module, const char *class_name, bool is_static, const char *signature);

protected:
    static Platform *s_Instance;

    std::string m_Title;
    int m_Width = 0;
    int m_Height = 0;
};
