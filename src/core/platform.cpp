#include "platform.hpp"

#include <cstring>

Platform *Platform::s_Instance = nullptr;

void Platform::display_set_title(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *new_title = wrenGetSlotString(vm, 1);
        s_Instance->set_title(new_title);
    }
}

void Platform::display_set_size(WrenVM *vm)
{
    if (s_Instance)
    {
        int new_width = (int)wrenGetSlotDouble(vm, 1);
        int new_height = (int)wrenGetSlotDouble(vm, 2);
        s_Instance->set_size(new_width, new_height);
    }
}

void Platform::display_create(WrenVM *vm)
{
    if (s_Instance)
    {
        s_Instance->create();
    }
}

void Platform::display_is_close_requested(WrenVM *vm)
{
    if (s_Instance)
    {
        wrenSetSlotBool(vm, 0, s_Instance->is_close_requested());
        return;
    }

    wrenSetSlotBool(vm, 0, false);
}

void Platform::display_update(WrenVM *vm)
{
    if (s_Instance)
        s_Instance->update();
}

void Platform::display_destroy(WrenVM *vm)
{
    if (s_Instance)
        s_Instance->destroy();
}

WrenForeignMethodFn Platform::bind_platform_methods(WrenVM *vm, const char *module, const char *class_name, bool is_static, const char *signature)
{
    if (!strcmp(class_name, "Display") && is_static)
    {
        if (!strcmp(signature, "setTitle(_)"))
            return &display_set_title;
        if (!strcmp(signature, "setSize(_,_)"))
            return &display_set_size;
        if (!strcmp(signature, "create()"))
            return &display_create;
        if (!strcmp(signature, "isCloseRequested()"))
            return &display_is_close_requested;
        if (!strcmp(signature, "update()"))
            return &display_update;
        if (!strcmp(signature, "destroy()"))
            return &display_destroy;
    }

    return NULL;
}
