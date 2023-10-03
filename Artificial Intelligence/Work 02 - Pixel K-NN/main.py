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

# @brief: This is the main function
# @param: None
# @return: None
def main():
	# Verify if the test and training dataset exists
	if not verify_datasets():
		return # If the datasets does not exists, exit the program
	
	# Verify if the output directory exists, if not, it creates the output directory
	verify_output_directory(OUTPUT_DIRECTORY)
	
	for neighbours_value in NEIGHBOURS_VALUES: # Loop through the neighbours values: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
		for x_split, y_split in SPLITS.items(): # Loop through the splits: 1x1, 2x2, 3x3 and 5x5.
			for training_dataset_size in TRAINING_DATASET_SIZE: # Loop through the training dataset sizes
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

				# For every line in the test dataset
				for index, test_dataset_row in tqdm(test_dataset.iterrows(), desc=f"KNN: {neighbours_value} - {x_split}x{y_split} - {training_dataset_size}"):
					# Calculate the euclidean distance between the test dataset row and the training dataset
					euclidean_distances = ((training_dataset.iloc[:, 2:] - test_dataset_row[2:]) ** 2).sum(axis=1) ** 0.5
					# Create a new column with the euclidean distances
					training_dataset["euclidean_distance"] = euclidean_distances
					# Sort the training dataset by the euclidean distance
					training_dataset = training_dataset.sort_values(by=["euclidean_distance"])
					# Get the first K rows from the training dataset
					k_nearest_neighbours = training_dataset.head(neighbours_value)
					# Get the most frequent label from the K nearest neighbours
					most_frequent_label = k_nearest_neighbours["Digit Class"].mode()[0]
					# Add the most frequent label to the test dataset
					test_dataset.loc[index, "KNN"] = most_frequent_label
					# Verify if the most frequent label is equal to the actual label (Digit Class) column
					if most_frequent_label == test_dataset_row["Digit Class"]:
						# Add 1 to the correct predictions column
						test_dataset.loc[index, "Correct Predictions"] = 1
					else:
						# Add 0 to the correct predictions column
						test_dataset.loc[index, "Correct Predictions"] = 0

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function