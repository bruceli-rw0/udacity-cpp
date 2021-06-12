# Neural Network from Scratch

This is the capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Neural network has been a recent trend in the area of Machine Learning. It has the ability to learn nonlinear decision boundaries from the complex structures underlying the data. In this project, a simple feedforward neural network has been implemented and deployed on the Fashion-MNIST dataset. I trained a 3-layer feedforward neural network with ReLU as the activation function and softmax loss as the loss function, using stochastic gradient descent as the optimization strategy. The model achieves 82% test accuracy in 20 epochs.

### Program Schematic
```
|- include
    |- Datasets.h
    |- Layers.h
    |- FeedForward.h
    |- NeuralNetworks.h
|- src
    |- Datasets.cpp		
    |- Layers.cpp		
    |- FeedForward.cpp		
    |- NeuralNetworks.cpp
    |- mnist.cpp
    |- xor.cpp
|- fashion-mnist // the dataset  
```

* `src/mnist.cpp` trained a 3-layer feedforward neural network on the Fashion-MNIST dataset.
  - `mnist.out` is a sample output from `mnist.cpp` reporting the training processing.
* `src/xor.cpp` trained a 2-layer feedforward neural network with 4 XOR examples.

#### Note
The implementation is not yet efficient. It may takes more than 50 minutes for a 3-layer network to complete 1 epoch of training on the Fashion-MNIST dataset.

### Build Instruction
1. run `make` to build the project
2. run `cd build` to direct to the `build` directory
3. run either `./mnist_nn` or `./xor_nn` to run the program

### Criteria Met
1. Loops, Functions, I/O
    - The project demonstrates an understanding of C++ functions and control structures.
    - The project reads data from a file and process the data.
2. Object Oriented Programming
    - The project uses Object Oriented Programming techniques.
    - Classes use appropriate access specifiers for class members.
    - Class constructors utilize member initialization lists.
    - Classes abstract implementation details from their interfaces.
    - Classes encapsulate behavior.
    - Classes follow an appropriate inheritance hierarchy.
    - Derived class functions override virtual base class functions.
3. Memory Management
    - The project makes use of references in function declarations.
    - The project uses smart pointers instead of raw pointers.

### Dataset
http://yann.lecun.com/exdb/mnist/
