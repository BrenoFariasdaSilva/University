import os # Import the os module for navigating the file system
import pandas as pd # Import the pandas module for data manipulation
import random # Import the random module for generating random numbers
from colorama import Style # For coloring the terminal
from tqdm import tqdm # For Generating the Progress Bars

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# Constants:
DATASETS_PATH = {"test":"dataset/digits/test", "training":"dataset/digits/training"} # The path for the training dataset
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# @brief: This function verifies if the test and training dataset exists
# @param: None
# @return: True if the dataset exists, False otherwise
def verify_datasets():
	for dataset_name, dataset_path in DATASETS_PATH.items(): # Loop through the datasets
		if not os.path.exists(dataset_path): # If the dataset does not exists
			print(f"{backgroundColors.RED}The {dataset_name} does not exists{Style.RESET_ALL}")
			return False # If the dataset does not exists
	return True # If all of the datasets exists

# @brief: This is the main function
# @param: None
# @return: None
def main():
	# Verify if the test and training dataset exists
	if not verify_datasets():
		return # If the datasets does not exists, exit the program
	
# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function