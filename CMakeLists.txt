cmake_minimum_required(VERSION 3.15)
project(graphicsEngineClion C)

set(CMAKE_C_STANDARD 11)

include_directories(build/test/cache)
include_directories(build/test/mocks)
include_directories(build/test/preprocess/files)
include_directories(build/test/preprocess/includes)
include_directories(src)
include_directories(vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src)
include_directories(vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder)
include_directories(vendor/ceedling/plugins/fake_function_framework/src)
include_directories(vendor/ceedling/vendor/c_exception/lib)
include_directories(vendor/ceedling/vendor/cmock/src)
include_directories(vendor/ceedling/vendor/unity/src)

add_executable(graphicsEngineClion
        src/gpio.c
        src/gpio.h
        src/player.c
        src/player.h
        main.c)
