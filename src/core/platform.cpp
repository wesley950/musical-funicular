#include "platform.hpp"
#include "input.hpp"

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
    {
        Input::update(); // Update state before polling the system again
        s_Instance->update();
    }
}

void Platform::display_close(WrenVM *vm)
{
    if (s_Instance)
        s_Instance->close();
}

void Platform::display_destroy(WrenVM *vm)
{
    if (s_Instance)
        s_Instance->destroy();
}

void Platform::input_add_action(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *action_name = wrenGetSlotString(vm, 1);
        Input::add_action(action_name);
    }
}

void Platform::input_action_add_key(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *action_name = wrenGetSlotString(vm, 1);
        int key_code = (int)wrenGetSlotDouble(vm, 2);
        Input::action_add_key(action_name, key_code);
    }
}

void Platform::input_is_action_pressed(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *action_name = wrenGetSlotString(vm, 1);
        wrenSetSlotBool(vm, 0, Input::is_action_pressed(action_name));
    }
}

void Platform::input_is_action_just_pressed(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *action_name = wrenGetSlotString(vm, 1);
        wrenSetSlotBool(vm, 0, Input::is_action_just_pressed(action_name));
    }
}

void Platform::input_get_key_code(WrenVM *vm)
{
    if (s_Instance)
    {
        const char *key_name = wrenGetSlotString(vm, 1);
        wrenSetSlotDouble(vm, 0, Input::get_key_code(key_name));
    }
}

void Platform::platform_time(WrenVM *vm)
{
    if (s_Instance)
    {
        wrenSetSlotDouble(vm, 0, s_Instance->get_time());
    }
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
        if (!strcmp(signature, "close()"))
            return &display_close;
        if (!strcmp(signature, "destroy()"))
            return &display_destroy;
    }
    else if (!strcmp(class_name, "Input") && is_static)
    {
        if (!strcmp(signature, "add_action(_)"))
            return &input_add_action;
        if (!strcmp(signature, "action_add_key(_,_)"))
            return &input_action_add_key;
        if (!strcmp(signature, "is_action_pressed(_)"))
            return &input_is_action_pressed;
        if (!strcmp(signature, "is_action_just_pressed(_)"))
            return &input_is_action_just_pressed;
        if (!strcmp(signature, "get_key_code(_)"))
            return &input_get_key_code;
    }
    else if (!strcmp(class_name, "Platform") && is_static)
    {
        if (!strcmp(signature, "time()"))
            return &platform_time;
    }

    return NULL;
}
