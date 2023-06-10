cmake_minimum_required(VERSION 3.13)
project(example-grpc LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

set(ENV{CPATH} /usr/include/hdf5/serial/)

set(DEP_ROOT_DIR ${CMAKE_SOURCE_DIR}/external-${CMAKE_SYSTEM_NAME})

if(NOT EXISTS ${DEP_ROOT_DIR})
  file(MAKE_DIRECTORY ${DEP_ROOT_DIR})
endif()

include(cmake/netcdf.cmake)
find_package(CURL REQUIRED)



link_directories(${DEP_ROOT_DIR}/install/lib/libnetcdf-cxx4.so)
include_directories(${DEP_ROOT_DIR}/${NETCDF_NAME}/cxx4)


link_directories(${DEP_ROOT_DIR}/install/lib)


# add_executable(netcdf_reader src/main.cpp)
# target_link_libraries(netcdf_reader netcdf-cxx4)


add_subdirectory(server)
add_subdirectory(proto)
