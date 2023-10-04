import os # Import the os module for navigating the file system
import pandas as pd # Import the pandas module for data manipulation
import numpy as np # Import the numpy module for data manipulation
from colorama import Style # For coloring the terminal
from PIL import Image # Import the PIL module for image manipulation
from sklearn.preprocessing import MinMaxScaler # Import the MinMaxScaler for normalizing the data
from tqdm import tqdm # For Generating the Progress Bars

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# Colors:
BLACK = 0 # Black Pixel Color 
WHITE = 255 # White Pixel Color

# Constants:
DATASETS_PATH = {"test":"dataset/digits/test", "training":"dataset/digits/training"} # The path for the training dataset
OUTPUT_PATH = "pixels_count/digits" # The path for the output directory
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

# @brief: This function verifies if the output directory exists, if not, it creates the output directory
# @param: output_path: The path for the output directory
# @return: None
def verify_output_directory(output_path):
	if not os.path.exists(output_path): # If the output directory does not exists
		os.makedirs(output_path) # Create the output directory
	
	# Loop through the datasets
	for dataset_name in DATASETS_PATH.keys():
		if not os.path.exists(os.path.join(output_path, f"{dataset_name}")): # If the output directory for the current dataset does not exists
			os.makedirs(os.path.join(output_path, f"{dataset_name}")) # Create the output directory for the current dataset

# @brief: This function initializes the pixel counter dictionary
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def initialize_pixel_counter(x_grid, y_grid):
	pixels_counter = {} # Initialize the pixel counter dictionary
	for i in range(0, x_grid):
		for j in range(0, y_grid):
			# Initialize the pixel counter for the current split
			pixels_counter[f"{i+1}x{j+1}"] = {"black":0, "white":0} # Initialize the pixel counter for the current split
	return pixels_counter # Return the initialized pixel counter dictionary 

# @brief: This function opens each image in the digit class and process each image
# @param: image_path: The path for the current image
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @return: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def process_each_image(image_path, x_grid, y_grid, pixels_counter):
	image = Image.open(image_path) # Open the image

	# Count the number of black and white pixels in each split
	pixels_counter = count_pixels(image, x_grid, y_grid, pixels_counter)

	image.close() # Close the image

	return pixels_counter # Return the pixel counter dictionary

# @brief: This function counts the number of black and white pixels in each split
# @param: image: The image
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @return: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def count_pixels(image, x_grid, y_grid, pixels_counter):
	# Load the image pixels
	image_pixels = image.load()
	# Get the image width and height
	image_width, image_height = image.size

	# Loop through the image pixels
	for x_split_iterator in range(0, x_grid):
		for y_split_iterator in range(0, y_grid):
			for i in range(0, image_width // x_grid):
				for j in range(0, image_height // y_grid):
					# Get the pixel color
					pixel_color = image_pixels[i + (x_split_iterator * (image_width // x_grid)), j + (y_split_iterator * (image_height // y_grid))]
					
					if pixel_color == BLACK:
						pixels_counter[f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["black"] += 1
					elif pixel_color == WHITE:
						pixels_counter[f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["white"] += 1
					else:
						print(f"{backgroundColors.RED}The pixel color is not black or white{Style.RESET_ALL}")

	# Return the pixel counter dictionary
	return pixels_counter

# @brief: This function writes the pixel counters to the output file
# @param: output_file: The output file
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: None
def write_pixel_counters(output_file_path, digit_class_pixel_counters, x_grid, y_grid):
	# Create the output file header
	output_file = create_output_file_header(x_grid, y_grid, output_file_path)

	# Loop through the digit classes
	for digit_class in digit_class_pixel_counters.keys():
		# Loop through the images
		for image_name in digit_class_pixel_counters[digit_class].keys():
			# Get the pixel counter for the current image in the current digit class
			pixels_counter = digit_class_pixel_counters[digit_class][image_name]
			# Create the output string
			output_string = f"{x_grid}x{y_grid},{digit_class},{image_name}"
			# Add the number of black and white pixels for each grid cell
			for i in range(x_grid):
				for j in range(y_grid):
					cell_label = f"{i+1}x{j+1}" # Grid cell label
					output_string += f",{pixels_counter[cell_label]['black']},{pixels_counter[cell_label]['white']}"
			# Write the output string to the output file
			output_file.write(output_string + "\n")

	# Close the output file
	output_file.close()

# @brief: This function normalizes the data stored in the digit_class_pixel_counters dictionary using Min-Max scaling
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def normalize_data(digit_class_pixel_counters, x_grid, y_grid):
	# Create a 2D array for storing the data
	pixels_counter = np.zeros((len(digit_class_pixel_counters.keys()) + 1, len(digit_class_pixel_counters[digit_class_pixel_counters.keys().__iter__().__next__()].keys()) * x_grid * y_grid))
	# Loop through the digit classes
	for i, digit_class in enumerate(digit_class_pixel_counters.keys()):
		for j, image_name in enumerate(digit_class_pixel_counters[digit_class].keys()):
			for x_split_iterator in range(0, x_grid):
				for y_split_iterator in range(0, y_grid):
					# Get the number of black and white pixels for the current split
					black_pixels = digit_class_pixel_counters[digit_class][image_name][f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["black"]
					white_pixels = digit_class_pixel_counters[digit_class][image_name][f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["white"]
					# Add the number of black and white pixels to the pixels_counter array
					pixels_counter[i + 1][j + (x_split_iterator * y_grid) + y_split_iterator] = black_pixels
					pixels_counter[i + 1][j + (x_split_iterator * y_grid) + y_split_iterator] = white_pixels

	# Now normalize the data using Min-Max scaling
	scaler = MinMaxScaler()
	scaler.fit(pixels_counter)
	pixels_counter = scaler.transform(pixels_counter)

	# Now update the digit_class_pixel_counters dictionary
	for i, digit_class in enumerate(digit_class_pixel_counters.keys()):
		for j, image_name in enumerate(digit_class_pixel_counters[digit_class].keys()):
			for x_split_iterator in range(0, x_grid):
				for y_split_iterator in range(0, y_grid):
					# Get the number of black and white pixels for the current split
					black_pixels = pixels_counter[i + 1][j + (x_split_iterator * y_grid) + y_split_iterator]
					white_pixels = pixels_counter[i + 1][j + (x_split_iterator * y_grid) + y_split_iterator]
					# Update the digit_class_pixel_counters dictionary
					digit_class_pixel_counters[digit_class][image_name][f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["black"] = black_pixels
					digit_class_pixel_counters[digit_class][image_name][f"{x_split_iterator + 1}x{y_split_iterator + 1}"]["white"] = white_pixels

	return digit_class_pixel_counters # Return the digit_class_pixel_counters dictionary

# @brief: This function create the header for the output file
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @param: output_file_path: The path for the output file
# @return: output_file: The output file object
def create_output_file_header(x_split, y_split, output_file_path):
	# Create and open the output CSV file
	output_file = open(output_file_path, "w")
	
	# Clear the output file (truncate its contents)
	output_file.truncate(0)
	
	# Create the header string
	header_string = "GRID,Digit Class,Image Name"

	# Add columns for each grid cell
	for i in range(x_split):
		for j in range(y_split):
			cell_label = f"{i+1}x{j+1}" # Grid cell label
			header_string += f",{cell_label} Black,{cell_label} White"

	# Write the header to the output CSV file
	output_file.write(header_string + "\n")

	return output_file # Return the output file object

# @brief: The main function
# @param: None
# @return: None
def main():
	# Print the welcome message
	print(f"{backgroundColors.GREEN}Welcome to the {backgroundColors.CYAN}Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the test and training dataset exists
	if not verify_datasets():
		return # Exit the program
	
	# Verify if the output directory exists
	verify_output_directory(OUTPUT_PATH)

	# Create a progress bar for the splits
	with tqdm(total=len(SPLITS.items()), desc=f"{backgroundColors.GREEN}Splits{Style.RESET_ALL}") as progress_bar:
		# Loop through the splits: 1x1, 2x2, 3x3, 5x5
		for x_grid, y_grid in SPLITS.items():
			# Loop through the datasets
			for dataset_name, dataset_path in DATASETS_PATH.items():
				# Initialize the digit class pixel counters dictionary
				digit_class_pixel_counters = {}
				# Open each digit class directory that is inside the current dataset
				for digit_class in sorted(os.listdir(dataset_path)):
					# Initialize the pixel counter for the current digit class
					digit_class_pixel_counters[digit_class] = {}
					# Get the path for the current digit class
					digit_class_folder_path = os.path.join(dataset_path, digit_class)
					# Open each image that is inside the current digit class directory
					for image_name in os.listdir(digit_class_folder_path):
						# Initialize the digit class pixel counters for the current image in the current digit class
						digit_class_pixel_counters[digit_class][image_name] = {}
						# Initialize the pixel counter for the current image
						pixel_counter = initialize_pixel_counter(x_grid, y_grid)
						# Verify if the current file is a bmp image
						if image_name.endswith(IMAGE_FILE_FORMAT):
							# Get the path for the current image
							image_path = os.path.join(digit_class_folder_path, image_name)
							# Process each image
							digit_class_pixel_counters[digit_class][image_name] = process_each_image(image_path, x_grid, y_grid, pixel_counter)
						else:
							print(f"{backgroundColors.RED}The current file is not a bmp image{Style.RESET_ALL}")

				# Create the output file path
				output_file_path = os.path.join(OUTPUT_PATH, f"{dataset_name}/{x_grid}x{y_grid}-normalized-pixel_count{OUTPUT_FILE_FORMAT}")
				# Normalize the data stored in the csv
				digit_class_pixel_counters = normalize_data(digit_class_pixel_counters, x_grid, y_grid)
				# Write the digit_class_pixel_counters to the output file
				write_pixel_counters(output_file_path, digit_class_pixel_counters, x_grid, y_grid)
			
			# Update the progress bar			
			progress_bar.update(1)

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function