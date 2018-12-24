cmake_minimum_required(VERSION 3.0)

project(circles)
find_package(Boost 1.44.0)
include_directories( ${Boost_INCLUDE_DIR} )
find_package (Threads)
add_executable(circles main.cpp cgridgenerator.cpp)
target_link_libraries (circles  X11 ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
install(TARGETS circles RUNTIME DESTINATION bin)
