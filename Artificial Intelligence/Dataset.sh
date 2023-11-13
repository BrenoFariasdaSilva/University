#!/bin/bash

# Run:
# chmod +x ./Dataset.sh
# ./Dataset.sh

# Search for and rename "data" or "dados" directory to "dataset"
if [ -d "data" ]; then
  mv "data" "dataset"
  echo "Renamed 'data' directory to 'dataset'."
elif [ -d "dados" ]; then
  mv "dados" "dataset"
  echo "Renamed 'dados' directory to 'dataset'."
else
  echo "No 'data' or 'dados' directory found."
fi

# Change to the "dataset" directory
cd "dataset" || exit

# Rename "teste.txt" to "test.txt" if it exists
if [ -f "teste.txt" ]; then
  mv "teste.txt" "test.txt"
  echo "Renamed 'teste.txt' to 'test.txt'."
fi

# Rename "treinamento.txt" or "trainning.txt" to "train.txt" if it exists
if [ -f "treinamento.txt" ]; then
  mv "treinamento.txt" "train.txt"
  echo "Renamed 'treinamento.txt' to 'train.txt'."
elif [ -f "trainning.txt" ]; then
  mv "trainning.txt" "train.txt"
  echo "Renamed 'trainning.txt' to 'train.txt'."
fi

echo "Script execution completed."
