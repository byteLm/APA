

include_directories("includes/") 
add_library(BruteForceLib "src/BruteForce.cpp")
target_include_directories(BruteForceLib PUBLIC "includes/") 

target_include_directories(BruteForceLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(BruteForceLib PUBLIC cxx_std_17)

add_subdirectory("tests/")