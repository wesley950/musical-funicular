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
add_executable(musical_funicular src/main.cpp)
target_include_directories(musical_funicular PUBLIC
                                "thirdparty/wren/src/vm"
                                "thirdparty/wren/src/include"
                                "thirdparty/wren/src/optional")
target_link_libraries(musical_funicular wren_lib)