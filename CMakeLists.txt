cmake_minimum_required(VERSION 3.16)


project(wren_lib)
file(GLOB WREN_SOURCE 
            "thirdparty/wren/src/vm/*.c" 
            "thirdparty/wren/src/vm/*.h" 

            "thirdparty/wren/src/optional/*.c" 
            "thirdparty/wren/src/optional/*.h" 

            "thirdparty/wren/src/include/*.h")
add_library(wren_lib ${WREN_SOURCE})
target_include_directories(wren_lib PUBLIC
                                "thirdparty/wren/src/vm"
                                "thirdparty/wren/src/include"
                                "thirdparty/wren/src/optional")


project(musical_funicular)
file(GLOB CORE_SOURCE "src/core/*.hpp" "src/core/*.cpp")
file(GLOB PLATFORM_GLFW_SOURCE "src/platform/glfw/*.hpp" "src/platform/glfw/*.cpp")
add_executable(musical_funicular 

                src/main.cpp

                ${CORE_SOURCE}

                ${PLATFORM_GLFW_SOURCE})
target_include_directories(musical_funicular PUBLIC

                            ${PROJECT_SOURCE_DIR}/src

                            "thirdparty/wren/src/vm"
                            "thirdparty/wren/src/include"
                            "thirdparty/wren/src/optional"
                            )
target_link_libraries(musical_funicular wren_lib)
                                
                                
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)
target_link_libraries(musical_funicular glfw)
