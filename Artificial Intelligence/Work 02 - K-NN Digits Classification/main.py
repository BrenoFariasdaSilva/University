# @TODO: FEAT -> Cross Validation.

import atexit # For playing a sound when the program finishes
import os # Import the os module for navigating the file system
import math # Import the math module for the square root function
import pandas as pd # Import the pandas module for data manipulation
import platform # For getting the operating system name
from colorama import Style # For coloring the terminal
from tqdm import tqdm # For Generating the Progress Bars

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# Dataset Constants:
DATASETS_PATH = {"training":"dataset/digits/training", "test":"dataset/digits/test"} # The path for the training dataset

# KNN Constants:
TRAINING_DATASET_SIZE = [0.25, 0.5, 1] # The training dataset sizes
NEIGHBOURS_VALUES = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19] # The K values for the KNN algorithm
SPLITS = {"1":1, "2":2, "3":3, "5":5} # The x and y splits for the feature extractor

# File Constants:
OUTPUT_DIRECTORY = "output" # The path for the output file
DATASET_FILES_FORMAT = ".csv" # The dataset files format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# Sound Constants:
SOUND_COMMANDS = {"Darwin": "afplay", "Linux": "aplay", "Windows": "start"} # The sound commands for each operating system
SOUND_FILE = "../../.assets/NotificationSound.wav" # The path to the sound file

# @brief: This function verifies if the test and training dataset exists
# @param: None
# @return: True if the dataset exists, False otherwise
def verify_datasets():
	for dataset_name, dataset_path in DATASETS_PATH.items(): # Loop through the datasets
		if not os.path.exists(dataset_path): # If the dataset does not exists
			print(f"{backgroundColors.RED}The {dataset_name} does not exists{Style.RESET_ALL}")
			return False # If the dataset does not exists
	return True # If all of the datasets exists

# @brief: This function verifies if the output directory exists, if not, it creates the output directory
# @param: output_path: The path for the output directory
# @return: None
def verify_output_directory(output_path):
	if not os.path.exists(output_path): # If the output directory does not exists
		os.mkdir(output_path) # Create the output directory

# @brief: This function initialize the results dictionary
# @param: none
# @return: results: The results dictionary
def initialize_results():
	results = {} # The results dictionary
	for neighbours_value in NEIGHBOURS_VALUES: # Loop through the neighbours values: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
		results[neighbours_value] = {} # Create a new dictionary for the current neighbours value
		for x_split, y_split in SPLITS.items(): # Loop through the splits: 1x1, 2x2, 3x3 and 5x5.
			results[neighbours_value][f"{x_split}x{y_split}"] = {} # Create a new dictionary for the current split
			for training_dataset_size in TRAINING_DATASET_SIZE: # Loop through the training dataset sizes
				results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size] = {} # Create a new dictionary for the current training dataset size
				results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Correct Predictions"] = 0 # Initialize the correct predictions to 0
				results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Total Predictions"] = 0 # Initialize the total predictions to 0
				results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Accuracy"] = 0.00 # Initialize the accuracy to 0.00
	return results # Return the results dictionary

# @brief: This function process the datasets
# @param: results: The results dictionary
# @return: results: The results dictionary
def process_datasets(results):
	# Create the progress bar
	with tqdm(total=len(NEIGHBOURS_VALUES) * len(SPLITS) * len(TRAINING_DATASET_SIZE), desc=f"{backgroundColors.GREEN}Processing Datasets{Style.RESET_ALL}") as progress_bar:
		for neighbours_value in NEIGHBOURS_VALUES: # Loop through the neighbours values: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
			for x_split, y_split in SPLITS.items(): # Loop through the splits: 1x1, 2x2, 3x3 and 5x5.
				for training_dataset_size in TRAINING_DATASET_SIZE: # Loop through the training dataset sizes
					training_dataset, test_dataset = read_datasets(x_split, y_split, training_dataset_size) # Read the datasets
					# Create a new dictionary for the current neighbours value, split and training dataset size that will save the correct predictions, total predictions and accuracy
					results = process_test_dataset(training_dataset, test_dataset, neighbours_value, x_split, y_split, training_dataset_size, results) # Process each test dataset row
					# Update the progress bar
					progress_bar.update(1)
	return results # Return the results dictionary

# @brief: This function reads the datasets
# @param: x_split: The x split for the feature extractor
# @param: y_split: The y split for the feature extractor
# @param: training_dataset_size: The size of the training dataset
# @return: training_dataset: The training dataset
# @return: test_dataset: The test dataset
def read_datasets(x_split, y_split, training_dataset_size):
	# The path for the training dataset file
	training_file_path = f"{DATASETS_PATH['training']}/{x_split}x{y_split}-normalized-pixel_count{DATASET_FILES_FORMAT}"
	# Load the training dataset
	training_dataset = pd.read_csv(training_file_path)
	# Pick a random sample from the training dataset based on the training dataset size
	training_dataset = training_dataset.sample(frac=training_dataset_size)
	# The path for the test dataset file
	test_file_path = f"{DATASETS_PATH['test']}/{x_split}x{y_split}-normalized-pixel_count{DATASET_FILES_FORMAT}"
	# Load the test dataset
	test_dataset = pd.read_csv(test_file_path)
	# Return the training and test datasets
	return training_dataset, test_dataset

# @brief: This function process each test dataset row, calculating the euclidean distance between the test dataset row and the training dataset
# @param: training_dataset: The training dataset
# @param: test_dataset: The test dataset
# @param: neighbours_value: The K value for the KNN algorithm
# @param: x_split: The x split for the feature extractor
# @param: y_split: The y split for the feature extractor
# @param: training_dataset_size: The size of the training dataset
# @param: results: The results dictionary
# @return: results: The results dictionary
def process_test_dataset(training_dataset, test_dataset, neighbours_value, x_split, y_split, training_dataset_size, results):
	distances = {} # The euclidean distances dictionary
	with tqdm(total=len(test_dataset), desc=f"{backgroundColors.GREEN}GRID: {backgroundColors.CYAN}{x_split}x{y_split}{backgroundColors.GREEN}, Training Dataset Size: {backgroundColors.CYAN}{training_dataset_size}{backgroundColors.GREEN}, K: {backgroundColors.CYAN}{neighbours_value}{Style.RESET_ALL}") as progress_bar:
		# For every line in the test dataset
		for test_dataset_row in test_dataset.itertuples():
			# For every line in the training dataset
			for training_dataset_row in training_dataset.itertuples():
				squared_difference = 0 # Initialize the squared difference to 0
				# loop through from the fourth column to the last column
				for i in range(4, len(training_dataset_row)):
					squared_difference += (test_dataset_row[i] - training_dataset_row[i]) ** 2 # Calculate the squared difference
				distances[f"{math.sqrt(squared_difference)}"] = training_dataset_row[2] # Add the squared difference to the distances dictionary

			# Sort the distances dictionary by its keys
			sorted_distances = dict(sorted(distances.items()))
			# Get the first K values from the sorted distances dictionary
			nearest_neighbours = list(sorted_distances.values())[:neighbours_value]
			# Find the element with the maximum count
			most_common_neighbour = most_common_element(nearest_neighbours)
			# Validate the results
			validate_results(results, neighbours_value, x_split, y_split, training_dataset_size, test_dataset_row, most_common_neighbour)
			# Update the progress bar
			progress_bar.update(1)

	# Calculate the accuracy
	results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Accuracy"] = results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Correct Predictions"] / results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Total Predictions"]
	print(f"{backgroundColors.GREEN}Accuracy for {backgroundColors.CYAN}{x_split}x{y_split}{backgroundColors.GREEN} with {backgroundColors.CYAN}{training_dataset_size}{backgroundColors.GREEN} of the training dataset and {backgroundColors.CYAN}{neighbours_value}{backgroundColors.GREEN} neighbours: {backgroundColors.CYAN}{results[neighbours_value][f'{x_split}x{y_split}'][training_dataset_size]['Accuracy']}{Style.RESET_ALL}")
			
	# Return the results dictionary
	return results

# @brief: This function finds the most common element in a list
# @param: lst: The list
# @return: most_common_value: The most common element in the list
def most_common_element(nearest_neighbours):
	# Verify if the list is empty
	if not nearest_neighbours:
		return None # Return None for an empty list
	
	most_common_value = None # Initialize most_common_value to None
	max_count = 0 # Initialize max_count to 0
	
	# Loop through the nearest neighbours list
	for item in nearest_neighbours:
		count = nearest_neighbours.count(item) # Count occurrences of the current item
		# Verify if the current count is greater than the max_count
		if count > max_count:
			max_count = count # Update max_count
			most_common_value = item # Update most_common_value

	# Verify if there is a tie, return the first value that appears the most
	if max_count == 1:
		most_common_value = nearest_neighbours[0] # If there is a tie, it will return the first value that appears the most.

	return most_common_value # Return most_common_value

# @brief: This function validates the results
# @param: results: The results dictionary
# @param: neighbours_value: The K value for the KNN algorithm
# @param: x_split: The x split for the feature extractor
# @param: y_split: The y split for the feature extractor
# @param: training_dataset_size: The size of the training dataset
# @param: test_dataset_row: The current test dataset row
# @param: most_frequent_label: The most frequent label from the K nearest neighbours
# @return: results: The results dictionary
def validate_results(results, neighbours_value, x_split, y_split, training_dataset_size, test_dataset_row, most_frequent_label):
	# Verify if the most frequent label is equal to the actual label (Digit Class) column
	if most_frequent_label == test_dataset_row[2]:
		# Add 1 to the correct predictions column
		results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Correct Predictions"] += 1
	# Add 1 to the total predictions column
	results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Total Predictions"] += 1

# @brief: This function loops through the results dictionary and call the write_results_to_csv function
# @param: results: The results dictionary
# @return: output_file_path: The path for the output file
def write_results(results):
	output_file_path = initialize_output_file() # Initialize the output file
	for neighbours_value in NEIGHBOURS_VALUES: # Loop through the neighbours values: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
		for x_split, y_split in SPLITS.items(): # Loop through the splits: 1x1, 2x2, 3x3 and 5x5.
			for training_dataset_size in TRAINING_DATASET_SIZE: # Loop through the training dataset sizes
				write_results_to_csv(results, neighbours_value, x_split, y_split, training_dataset_size, output_file_path) # Write the results to a csv file

	# return the output file path
	return output_file_path

# @brief: This function initializes the output file (creates the output file and writes the headers)
# @param: None
# @return: output_file_path: The path for the output file
def initialize_output_file():
	# The path for the output file
	output_file_path = f"{OUTPUT_DIRECTORY}/K-NN{OUTPUT_FILE_FORMAT}"

	# Create the output file
	with open(output_file_path, "w") as output_file: 
		# Write the headers to the output file
		output_file.write(f"Grid,Training Dataset %,K Value,Correct Predictions,Total Predictions,Accuracy\n")

	return output_file_path # Return the output file path

# @brief: This function appends the results to a csv file
# @param: results: The results dictionary
# @param: neighbours_value: The K value for the KNN algorithm
# @param: x_split: The x split for the feature extractor
# @param: y_split: The y split for the feature extractor
# @param: training_dataset_size: The size of the training dataset
# @param: output_file_path: The path for the output file
# @return: None
def write_results_to_csv(results, neighbours_value, x_split, y_split, training_dataset_size, output_file_path):
	# Append the results to the output file
	with open(output_file_path, "a") as output_file:
		# Write the results to the output file
		output_file.write(f"{x_split}x{y_split},{training_dataset_size},{neighbours_value},{results[neighbours_value][f'{x_split}x{y_split}'][training_dataset_size]['Correct Predictions']},{results[neighbours_value][f'{x_split}x{y_split}'][training_dataset_size]['Total Predictions']},{results[neighbours_value][f'{x_split}x{y_split}'][training_dataset_size]['Accuracy']}\n")

# @brief: This function sorts the output file by the accuracy column
# @param: output_file_path: The path for the output file
# @return: None
def sort_output_file(output_file_path):
	# Read the output file
	output_file = pd.read_csv(output_file_path)
	# Sort the output file by the accuracy column
	output_file = output_file.sort_values(by=["Accuracy"], ascending=False)
	# Save the output file
	output_file.to_csv(output_file_path, index=False)

# @brief: This function defines the command to play a sound when the program finishes
# @param: None
# @return: None
def play_sound():
	if os.path.exists(SOUND_FILE):
		if platform.system() in SOUND_COMMANDS: # if the platform.system() is in the SOUND_COMMANDS dictionary
			os.system(f"{SOUND_COMMANDS[platform.system()]} {SOUND_FILE}")
		else: # if the platform.system() is not in the SOUND_COMMANDS dictionary
			print(f"{backgroundColors.RED}The {backgroundColors.CYAN}platform.system(){backgroundColors.RED} is not in the {backgroundColors.CYAN}SOUND_COMMANDS dictionary{backgroundColors.RED}. Please add it!{Style.RESET_ALL}")
	else: # if the sound file does not exist
		print(f"{backgroundColors.RED}Sound file {backgroundColors.CYAN}{SOUND_FILE}{backgroundColors.RED} not found. Make sure the file exists.{Style.RESET_ALL}")

# Register the function to play a sound when the program finishes
atexit.register(play_sound)

# @brief: This is the main function
# @param: None
# @return: None
def main():
	# Verify if the test and training dataset exists
	if not verify_datasets():
		return # If the datasets does not exists, exit the program
	
	# Verify if the output directory exists, if not, it creates the output directory
	verify_output_directory(OUTPUT_DIRECTORY)

	results = initialize_results() # Initialize the results dictionary

	# Process the datasets
	results = process_datasets(results)

	# Write the results to a csv file
	output_file_path = write_results(results)

	# Sort the output file by the accuracy column
	sort_output_file(output_file_path)

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function