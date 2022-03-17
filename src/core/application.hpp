#pragma once

#include "platform.hpp"

#include "wren.hpp"

class Application
{
public:
    static void init();
    static void run();
    static void shutdown();

    static WrenForeignMethodFn bind_foreign_method(WrenVM *vm, const char *module, const char *class_name, bool is_static, const char *signature);
    static WrenLoadModuleResult load_module(WrenVM *vm, const char *name);
    static void error(WrenVM* vm, WrenErrorType error_type, const char* module, const int line, const char* msg);
    static void write(WrenVM *vm, const char *text);

    static void free_module_raw_buffer(WrenVM* vm, const char *name, struct WrenLoadModuleResult result);

private:
    static WrenVM *s_VM;

    static Platform *s_Platform;
};
