cmake_minimum_required(VERSION 4.1)
project(Audio_Signal_Filtering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Audio_Signal_Filtering
        src/main.cpp
        src/SineLookup.cpp
        src/Filter.cpp
        src/LowPassFilter.cpp
        src/HighPassFilter.cpp
        src/BandPassFilter.cpp
        src/WavWriter.cpp
)

target_include_directories(Audio_Signal_Filtering
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external/CLI11/include
)
