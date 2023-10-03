# @TODO: FIX -> Eucledian distance is not working properly.
# @TODO: FEAT -> Write the results to a csv file.
# @TODO: FEAT -> Cross Validation.

import os # Import the os module for navigating the file system
import pandas as pd # Import the pandas module for data manipulation
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
OUTPUT_DIRECTORY = "output" # The path for the output file
TRAINING_DATASET_SIZE = [0.25, 0.5, 1] # The size of the training dataset
NEIGHBOURS_VALUES = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19] # The K values for the KNN algorithm
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
DATASET_FILES_FORMAT = ".csv" # The dataset files format
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
				results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Accuracy"] = 0.00 # Initialize the accuracy to 0
	return results # Return the results dictionary

# @brief: This function process the datasets
# @param: results: The results dictionary
# @return: None
def process_datasets(results):
	# Create the progress bar
	with tqdm(total=len(NEIGHBOURS_VALUES)*len(SPLITS)*len(TRAINING_DATASET_SIZE)) as progress_bar:
		for neighbours_value in NEIGHBOURS_VALUES: # Loop through the neighbours values: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
			for x_split, y_split in SPLITS.items(): # Loop through the splits: 1x1, 2x2, 3x3 and 5x5.
				for training_dataset_size in TRAINING_DATASET_SIZE: # Loop through the training dataset sizes
					training_dataset, test_dataset = read_datasets(x_split, y_split, training_dataset_size) # Read the datasets
					results = process_test_dataset(training_dataset, test_dataset, neighbours_value, x_split, y_split, training_dataset_size, results) # Process each test dataset row

		# Update the progress bar
		progress_bar.update(1)

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
	# Pick a random sample from the training dataset
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
	# For every line in the test dataset
	for index, test_dataset_row in test_dataset.iterrows():
		for index, training_dataset_row in training_dataset.iterrows():
			euclidean_distance = 0 # The euclidean distances
			# Calculate the euclidean distance between the test dataset row and the training dataset
			for i in range(3, len(test_dataset_row)):
				euclidean_distance += (test_dataset_row.values[i] - training_dataset_row.values[i])**2
			distances[f"{training_dataset_row}->{test_dataset_row}"] = euclidean_distance # Add the euclidean distance to the distances dictionary
			# Sort the distances dictionary
			distances = dict(sorted(distances.items(), key=lambda item: item[1]))
			# Get the K nearest neighbours
			nearest_neighbours = list(distances.keys())[:neighbours_value]
			# Get the most frequent label from the K nearest neighbours list
			most_frequent_label = max(set(nearest_neighbours), key = nearest_neighbours.count)
			
			# Validate the results
			validate_results(results, neighbours_value, x_split, y_split, training_dataset_size, test_dataset_row, most_frequent_label)
			
	# Return the results dictionary
	return results

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
	if most_frequent_label == test_dataset_row["Digit Class"]:
		# Add 1 to the correct predictions column
		results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Correct Predictions"] += 1
	# Add 1 to the total predictions column
	results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Total Predictions"] += 1
	# Calculate the accuracy
	results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Accuracy"] = results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Correct Predictions"] / results[neighbours_value][f"{x_split}x{y_split}"][training_dataset_size]["Total Predictions"]

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
	process_datasets(results)

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function