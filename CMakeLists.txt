cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(hello_library VERSION 1.0.0 LANGUAGES CXX)
add_library(process_monitor SHARED process_monitor.cpp process_monitor.def)

set_target_properties(process_monitor PROPERTIES
    PUBLIC_HEADER process_monitor.hpp
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "process_monitor"
)