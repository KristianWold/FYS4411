cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)
project(project_1_FYS4411)

# Add directories containing header-files
include_directories(
    src
    src/InitialStates
    src/Hamiltonian
    src/WaveFunction
)

# Add sources from all directories
file(
    GLOB SOURCES "main.cpp"
    GLOB SOURCES "src/*.cpp"
    GLOB SOURCES "src/InitialStates/*.cpp"
    GLOB SOURCES "src/Hamiltonians/*.cpp"
    GLOB SOURCES "src/WaveFunctions/*.cpp"
)

# Create executable called "vmc"
add_executable(vmc ${SOURCES})


# Testing
#add_subdirectory(./googletest)

# Add sources from all directories
#file(
#    GLOB TESTSOURCES "test.cpp"
#    GLOB TESTSOURCES "src/*.cpp"
#    GLOB TESTSOURCES "src/InitialStates/*.cpp"
#    GLOB TESTSOURCES "src/Hamiltonians/*.cpp"
#    GLOB TESTSOURCES "src/WaveFunctions/*.cpp"

#)

#add_executable(runUnitTests ${TESTSOURCES})

#target_link_libraries(runUnitTests gtest gtest_main)
