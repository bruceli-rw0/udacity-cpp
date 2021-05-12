# System Monitor

### Contribution
* `src/linux_parser.cpp`
* `src/system.cpp`
* `src/process.cpp`
* `src/processor.cpp`
* `src/format.cpp`		

### My Sample Output
![img](./images/my_sample_output.png)

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions
1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`
2. Build the project: `make build`
3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)
4. Follow along with the lesson.
5. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.
6. Submit!

### Suggestions to Make Your Project Stand Out!
* [x] Calculate CPU utilization dynamically, based on recent utilization
* [x] Sort processes based on CPU or memory utilization
* [ ] Make the display interactive
* [ ] Restructure the program to use abstract classes (interfaces) and pure virtual functions
* [ ] Port the program to another operating system