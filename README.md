# University Exercises [![Build Status](https://github.com/BrenoFariasdaSilva/University-Exercises/actions/workflows/build.yml/badge.svg)](https://github.com/BrenoFariasdaSilva/University-Exercises/actions/workflows/build.yml)

This repo is made with the objective of showing the content taught at a computer science university.
Here you can find basically all exercises I'm solving during my University journey. This repo will contain lots of folders inside of it, each of one related to one subject. It won't be limited to one language, but any exercise related to coding.
You can use this repository as a way to measure your learning to ensure you know all the fundamentals taught in college.

## Installation

### C

**Linux**: If you are using **linux**, just open the terminal and run the following command: 

```bash
$ sudo apt install build-essential
```

It will require your computer password, as well as a message asking for you to confirm the package installation.

If you are using VisualStudio, install the following extensions and then you are ready to code in C/C++

```bash
C/C++
C/C+ Compile Run
Code Runner
```

**Windows**: If you are using **Windows**, just open [MinGW website](http://mingw-w64.org/doku.php/download) and download the version for your system. MinGW contains all the GCC Package you need.
After installing MinGW, open it and select to install the following packages:
```bash
minggw32-base-bin
minggw32-gcc-g++-bin
```
After, open Windows File Manager, go to MinGW installation folder and open "bin" folder. Copy the folder adress and type "path" on Windows Search Bar. Open it and click on "Environment Variables" then, on System Variables, click on "Path" and then click on "New" and paste the adress of MinGW bin folder. After that, restart your Computer.

### Java
```bash
$ sudo apt install default-jre -y
$ sudo apt install default-jdk -y
```

## How to Run

### C
```bash
$ make
```

### Java
```bash
$ javac ./{ProgramName}.java
$ java {ProgramName without extension}
```


## Contributing
Code improvement recommendations are welcome, but keep in mind that many exercises will be very simple, with a lot of room for improvement, after all here is all the history of my learning progress.

## License
[MIT](https://choosealicense.com/licenses/mit/)
