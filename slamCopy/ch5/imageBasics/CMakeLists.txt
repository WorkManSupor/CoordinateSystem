# add C++ 11 
set( CMAKE_XXX_FLAGS "-std=c++11")

# search opencv lib
find_package(OpenCV REQUIRED)

# Add include hpp
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(imageBasics imageBasics.cpp)

# link opencv lib
target_link_libraries(imageBasics ${OpenCV_LIBS})