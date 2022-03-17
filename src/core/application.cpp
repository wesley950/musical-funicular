#include "application.hpp"
#include "input.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <cstring>

WrenVM *Application::s_VM = nullptr;

Platform *Application::s_Platform = nullptr;

void Application::init()
{
    // Create and initialize internal resources
    {
        s_Platform = Platform::create_instance();
        Input::init();
    }

    // Initialize Wren
    {
        WrenConfiguration config;
        wrenInitConfiguration(&config);
        config.bindForeignMethodFn = &bind_foreign_method;
        config.loadModuleFn = &load_module;

        config.errorFn = &error;
        config.writeFn = &write;
        s_VM = wrenNewVM(&config);
    }
}

void Application::run()
{
    // Execute the application entry point (written in Wren) by executing
    // the module at data/application.wren
    {
        const char *module = "main";
        const char *script = "import \"data/application\"";

        wrenInterpret(s_VM, module, script);
    }
}

void Application::shutdown()
{
    // Release Wren's resources
    {
        wrenFreeVM(s_VM);
    }

    // Release internal resources
    {
        Platform::destroy_instance();
        s_Platform = nullptr;
    }
}

WrenForeignMethodFn Application::bind_foreign_method(WrenVM *vm, const char *module, const char *class_name, bool is_static, const char *signature)
{
    if (!strcmp(module, "lib/display") || !strcmp(module, "lib/input"))
    {
        return Platform::bind_platform_methods(vm, module, class_name, is_static, signature);
    }

    return NULL;
}

WrenLoadModuleResult Application::load_module(WrenVM *vm, const char *name)
{
    WrenLoadModuleResult result;

    // Read the file into a temp buffer, copy it to a raw buffer and give
    // it to Wren along with a free callback.
    {
        std::string module_full_path = std::string(name) + std::string(".wren");
        std::ifstream module_file(module_full_path);
        if (!module_file.is_open())
            return result; // Return null signaling the file could not be opened or found.

        std::string line;
        std::stringstream buffer;
        while (std::getline(module_file, line))
        {
            buffer << line << "\n";
        }
        module_file.close();

        char *raw_buffer = (char *)malloc(sizeof(char) * buffer.str().length() + 1);
        std::strcpy(raw_buffer, buffer.str().c_str());
        raw_buffer[buffer.str().length()] = 0;

        result.source = raw_buffer;
        result.onComplete = &free_module_raw_buffer;
    }

    return result;
}

void Application::error(WrenVM *vm, WrenErrorType error_type, const char *module, const int line, const char *msg)
{
    switch (error_type)
    {
    case WREN_ERROR_COMPILE:
    {
        std::cout << "[" << module << " line " << line << "] [Error] " << msg << std::endl;
        break;
    }

    case WREN_ERROR_STACK_TRACE:
    {
        std::cout << "[" << module << " line " << line << "] in " << msg << std::endl;
        break;
    }

    case WREN_ERROR_RUNTIME:
    {
        std::cout << "[Runtime Error] " << msg << std::endl;
        break;
    }
    }
}

void Application::write(WrenVM *vm, const char *text)
{
    std::cout << text;
}

void Application::free_module_raw_buffer(WrenVM *vm, const char *name, struct WrenLoadModuleResult result)
{
    free((void *)result.source);
}
