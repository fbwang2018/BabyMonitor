cmake_minimum_required (VERSION 3.0)

project(BabyMonitor)

find_package(OpenCV REQUIRED)

add_compile_options(-std=c++11)

include_directories(
    include
    include/datafetch
    include/training
    ${OpenCV_INCLUDE_DIRS}

)


add_executable(${PROJECT_NAME}
    src/main.cpp
    src/BabyMonitor.cpp
    src/datafetch/RstpDataFetch.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBRARIES}
  vlccore
  vlc
)

