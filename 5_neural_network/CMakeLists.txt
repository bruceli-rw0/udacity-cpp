cmake_minimum_required(VERSION 3.11.3)

project(neural_network)
set(CMAKE_CXX_STANDARD 14)

# header files
include_directories(src)
include_directories(include)

# Find all executables
file(GLOB project_SRCS 
    src/Layers.cpp
    src/Datasets.cpp
    src/NeuralNetworks.cpp
    src/FeedForward.cpp
) #src/*.h

# Add project executable
add_executable(mnist_nn src/mnist.cpp ${project_SRCS})
add_executable(xor_nn src/xor.cpp ${project_SRCS})
# add_executable(read_data src/read_data.cpp ${project_SRCS})
