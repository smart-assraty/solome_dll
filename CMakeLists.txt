cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(process_monitor VERSION 1.0.0 LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(process_monitor SHARED process_monitor.cpp process_monitor.def process_monitor.hpp)

target_link_libraries(process_monitor Boost::filesystem)

set_target_properties(process_monitor PROPERTIES
    PUBLIC_HEADER process_monitor.hpp
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "process_monitor"
)