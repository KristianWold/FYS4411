cmake_minimum_required(VERSION 3.10)
project(project_1_FYS4411)

# Add directories containing header-files
include_directories(
    src
    src/Hamiltonian
    src/WaveFunction
)

# Add sources from all directories
file(
    GLOB SOURCES "*.cpp"
    GLOB SOURCES "src/*.cpp"
    GLOB SOURCES "src/Hamiltonians/*.cpp"
    GLOB SOURCES "src/WaveFunctions/*.cpp"
)

# Create executable called "vmc"
add_executable(vmc ${SOURCES})
