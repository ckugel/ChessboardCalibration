cmake_minimum_required(VERSION 3.0.0)
project(dispmap VERSION 0.1.0)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include(CTest)
enable_testing()

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(dispmap src/main.cpp src/Settings.cpp src/Settings.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

TARGET_LINK_LIBRARIES(dispmap ${OpenCV_LIBS})
