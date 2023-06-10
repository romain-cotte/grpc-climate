#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES src/main.cpp src/netcdf_tools.cpp src/tmax_service.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_executable(server ${SOURCES})
target_link_libraries(server PRIVATE myproto netcdf-cxx4)
