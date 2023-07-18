<div align="center">
  
# [University Exercises.](https://github.com/BrenoFariasdaSilva/University) 

</div>
(https://github.com/BrenoFariasdaSilva/University-Exercises/actions/workflows/build.yml)
[![Build Status](https://github.com/BrenoFariasdaSilva/University-Exercises/actions/workflows/build.yml/badge.svg)]
[![wakatime](https://wakatime.com/badge/github/BrenoFariasdaSilva/University.svg)](https://wakatime.com/badge/github/BrenoFariasdaSilva/University)

## Languages:
<img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg"  width="3%" height="3%"> <img src="https://github.com/devicons/devicon/blob/master/icons/cplusplus/cplusplus-original.svg"  width="3%" height="3%"> <img src="https://github.com/devicons/devicon/blob/master/icons/python/python-original.svg"  width="3%" height="3%"> <img src="https://github.com/devicons/devicon/blob/master/icons/java/java-original.svg"  width="3%" height="3%">

This repo is made with the objective of showing the content taught at a computer science university. \
Here you can find basically all exercises I'm solving during my University journey. This repo will contain lots of folders inside of it, each of one related to one subject, so it won't be limited to one language, but any exercise related to my university course at UTFPR-CM (Universidade Tecnológica Federal do Paraná campus Campo Mourão). \
You can use this repository as a way to measure your learning to ensure you know all the fundamentals taught in college.

## Installation

* C:
  ```bash
  # C:
  sudo apt install build-essential -y
  sudo apt-get install manpages-dev -y
  ```

* C++:
  ```bash
  # C++:
  sudo apt install clang-12 -y
  ```

* Python:
  ```bash
  # Python:
  sudo apt-get install python3 python3-venv python3-pip -y
  ```

* Zip and Unzip Tools: Zip and Unzip might be some necessary tools to install SDKMAN
  ```bash
  # Unzip:
  sudo apt-get install unzip -y

  # Zip:
  sudo apt-get install zip -y
  ```

* SDKMAN Tool: SDKMAN is a tool for managing parallel versions of multiple Software Development Kits on most Unix based systems. \
It provides a convenient Command Line Interface (CLI) and API for installing, switching, removing and listing Candidates.

  ```bash
  # SDKMAN:
  curl -s "https://get.sdkman.io" | bash
  source "$HOME/.sdkman/bin/sdkman-init.sh"
  sdk version
  ```
* Java Language via SDKMAN:
  ```bash
  # Java:
  sdk install java
  java -version
  ```

## How to Run

* If there is a file in the folder called Makefile:
  ```bash
  make
  ```

* If there isn't a file in the folder called Makefile:

  * C: \
  C is a general-purpose computer programming language. 
    ```bash
    # if there is external file to link
    gcc -c linkedLibrary.c  # Linked files here
    gcc main.c linkedLibrary.o -o main
    ./main
    
    # if there isn't external file to link
    gcc {ProgramName}.c -o {OutProgramName}
    # Example: gcc main.c -o main
    ./{ProgramName}
    #Example: ./main
    ```

  * C++: \
  C++ is a high-level, general-purpose programming language.
    ```bash
    g++ -o {OutputProgramName} {ProgramName}.cpp
    # Example: g++ -o main main.cpp
    ./{ProgramName}
    #Example: ./main
    ```

  * Python: \
  Python is a high-level, general-purpose programming language.
    ```bash
    python3 ./{ProgramName}.py
    # Example: python3 ./main.py 
    ```

  * Java: \
  Java is a high-level, class-based, object-oriented programming language.
    ```bash
    # Compile the application using the Java compiler (JVM):
    javac ./{ProgramName}.java
    # Example: javac ./main.java 

    # Run the application.
    java ./{ProgramName without extension}
    # Example: javac ./main
    ```

## Contributing
Code improvement recommendations are very welcome, but keep in mind that many exercises will be very simple, with a lot of room for improvement, after all here is all the history of my learning progress.

## License
[MIT](https://choosealicense.com/licenses/mit/)
