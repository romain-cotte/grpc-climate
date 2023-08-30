#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES src/main.cpp src/netcdf_tools.cpp src/tmax_service.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

message(SOURCES="${SOURCES}")

#
# Targets
#
add_executable(server ${SOURCES})
target_link_libraries(server PRIVATE myproto netcdf-cxx4)

add_executable(test_netcdf_tools src/netcdf_tools.cpp tests/test_netcdf_tools.cpp)
target_link_libraries(test_netcdf_tools PRIVATE netcdf-cxx4)

#
# Tests
#
add_test(NAME test_netcdf_tools COMMAND test_netcdf_tools)
