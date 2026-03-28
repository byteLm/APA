

include_directories("includes/") 
add_library(GreedyLib "src/Greedy.cpp")
target_include_directories(GreedyLib PUBLIC "includes/") 

target_include_directories(GreedyLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(GreedyLib PUBLIC cxx_std_17)

add_subdirectory("tests/")