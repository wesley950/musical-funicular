#include <cstdio>
#include <cstring>

#include <string>
#include <sstream>
#include <fstream>

#include <unordered_map>

#include "wren.hpp"

static void writeFn(WrenVM *vm, const char *text)
{
    std::printf("%s", text);
}

void errorFn(WrenVM *vm, WrenErrorType errorType, const char *module, const int line, const char *msg)
{
    switch (errorType)
    {
    case WREN_ERROR_COMPILE:
    {
        std::printf("[%s line %d] [Error] %s\n", module, line, msg);
        break;
    }

    case WREN_ERROR_STACK_TRACE:
    {
        std::printf("[%s line %d] in %s\n", module, line, msg);
        break;
    }

    case WREN_ERROR_RUNTIME:
    {
        std::printf("[Runtime Error] %s\n", msg);
    }
    }
}

int main(int argc, char *argv[])
{
    // Parse the program arguments
    std::unordered_map<std::string, std::string> arguments = {
        {"entry_point_path", "data/application.wren"}};

    for (int argi = 1; argi < argc; argi++)
    {
        if (!strcmp(argv[argi], "--path") || !strcmp(argv[argi], "-p"))
        {
            if (argi + 1 < argc)
            {
                arguments["entry_point_path"] = argv[argi + 1];
            }
        }
        else if (!strcmp(argv[argi], "--help") || !strcmp(argv[argi], "-h"))
        {
            printf("Run the application with one of the following arguments:\n");
            printf("--path or -p [path] to override the default path (data/application.wren) to the application entry point.\n");
            printf("--help or -h to show this message.\n");
        }
        else
        {
            printf("Unrecognized argument %s. Run %s --help or %s -h to display available arguments.\n", argv[argi], argv[0], argv[0]);
        }
    }

    // Initialise the VM
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.writeFn = &writeFn;
    config.errorFn = &errorFn;
    WrenVM *vm = wrenNewVM(&config);

    // Read the file with the entry point
    std::ifstream scriptFile(arguments["entry_point_path"]);
    if (!scriptFile.is_open())
    {
        printf("Could not open application entry point.\n");
        exit(EXIT_FAILURE);
    }

    std::string line;
    std::stringstream buffer;
    while (std::getline(scriptFile, line))
    {
        buffer << line << "\n";
    }
    scriptFile.close();

    // Interpret it so the Application class exists in the VM
    WrenInterpretResult result = wrenInterpret(vm, "main", buffer.str().c_str());

    switch (result)
    {
    case WREN_RESULT_COMPILE_ERROR:
    {
        std::printf("Compile Error!\n");
        break;
    }

    case WREN_RESULT_RUNTIME_ERROR:
    {
        std::printf("Runtime Error!\n");
        break;
    }

    case WREN_RESULT_SUCCESS:
    {
        std::printf("Successfully read the application entry point!\n");
        break;
    }
    }

    // Get a handle to the Application class
    wrenEnsureSlots(vm, 1);
    wrenGetVariable(vm, "main", "Application", 0);
    WrenHandle *applicationClass = wrenGetSlotHandle(vm, 0);

    // Get a handle to the run method
    wrenEnsureSlots(vm, 1);
    WrenHandle *method = wrenMakeCallHandle(vm, "run()");

    // Call the run method
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, applicationClass);
    wrenCall(vm, method);

    // Release resources
    wrenReleaseHandle(vm, method);
    wrenFreeVM(vm);

    return 0;
}