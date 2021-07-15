#!/bin/bash

# Exists on error
set -e

# Function to build each individual .c files into a given directory (except FullList.c) using gcc
# or by means of a Makefile (if existing).
# $1 - source directory path
build(){
   SOURCE_DIR="$1"

   # If there is a Makefile, use it to build
   if [ -f "$SOURCE_DIR/Makefile" ]; then
      echo "# Building from Makefile in $SOURCE_DIR"
      # make into the given dir
      make -C "$SOURCE_DIR" 
      return 0
   fi

   echo "# Build individual .c files from $SOURCE_DIR"
   ## List only files in the given dir
   for FILE in `find $SOURCE_DIR -maxdepth 1 -not -name 'FullList.c' -name "*.c"`; do
      OUTPUT=`basename $FILE` 
      OUTPUT="/tmp/${OUTPUT%.*}"
      echo "## Building $FILE to $OUTPUT"
      #-lm (load math) is required when math.h is used on Linux
      gcc "$FILE" -o "OUTPUT" -lm
   done
}

# Function to list directories and build .c files (excluding .git/ dir)
list_and_build(){
   for DIR in `find . -type d -not -path './.git*'`; do
      build "$DIR"
   done
}

#----main-----

list_and_build
