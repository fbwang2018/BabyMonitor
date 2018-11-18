cmake_minimum_required (VERSION 3.0)

#project name
PROJECT(BabyMonitor)

#head file path
INCLUDE_DIRECTORIES(
include
)
#source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)


#add executable file
ADD_EXECUTABLE(BabyMonitor ${DIR_SRCS})
