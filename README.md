<div align="center">
  
# [University.](https://github.com/BrenoFariasdaSilva/University) <img src="https://github.com/BrenoFariasdaSilva/University/blob/main/.assets/BooksStack.svg"  width="3%" height="3%">

</div>

<div align="center">
  
---

This repo is made with the objective of showing the content learned at my Computer Science university course. \
Here you can find basically all exercises I'm solving during my University journey. This repo will contain lots of folders inside of it, each of one related to one subject, so it won't be limited to one language, but any exercise related to my university course at [UTFPR-CM](https://pt.wikipedia.org/wiki/Universidade_Tecnol%C3%B3gica_Federal_do_Paran%C3%A1). \
You can use this repository as a way to measure your learning to ensure you know all the fundamentals taught in college.
  
---

</div>

<div align="center">

![Build Status](https://github.com/BrenoFariasdaSilva/University-Exercises/actions/workflows/build.yml/badge.svg)
![wakatime](https://wakatime.com/badge/github/BrenoFariasdaSilva/University.svg)
  
</div>

<div align="center">
  
![RepoBeats Statistics](https://repobeats.axiom.co/api/embed/d85626d04b05db948a28d708506a52a384fe0728.svg "Repobeats analytics image")

</div>

<div align="center">

</div>

## Table of Contents
- [University. ](#university-)
  - [Table of Contents](#table-of-contents)
  - [Languages:](#languages)
  - [Installation](#installation)
  - [How to Run](#how-to-run)
  - [Contributing](#contributing)
  - [License](#license)

## Languages:
<div>
  <p align="center">
    <a href="#"><img alt="c" height="36" width="64" src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white"></a>
    &nbsp;
    <a href="#"><img alt="c++" height="36" width="85" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white"></a>
    &nbsp;
    <a href="#"><img alt="Elixir" height="36" width="90" src="https://img.shields.io/badge/elixir-%234B275F.svg?style=for-the-badge&logo=elixir&logoColor=white"></a>
    &nbsp;
    <a href="#"><img alt="java" height="36" width="100" src="https://img.shields.io/badge/java-%23ED8B00.svg?style=for-the-badge&logo=openjdk&logoColor=white"></a>
    &nbsp;
    <a href="#"><img alt="javascript" height="36" width="150" src="https://img.shields.io/badge/javascript-%23323330.svg?style=for-the-badge&logo=javascript&logoColor=%23F7DF1E"></a>
    &nbsp;
    <a href="#"><img alt="python" height="36" width="100" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54"></a>
    &nbsp;
    <a href="#"><img alt="ruby" height="36" width="90" src="https://img.shields.io/badge/ruby-%23CC342D.svg?style=for-the-badge&logo=ruby&logoColor=white"></a>
    &nbsp;
    <a href="#"><img alt="typescript" height="36" width="140" src="https://img.shields.io/badge/typescript-%23007ACC.svg?style=for-the-badge&logo=typescript&logoColor=white"></a>
    &nbsp;
  </p>
</div>

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
