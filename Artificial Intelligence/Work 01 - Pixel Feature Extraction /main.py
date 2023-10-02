import os # Import the os module for navigating the file system
import pandas as pd # Import the pandas module for data manipulation
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
OUTPUT_PATH = "pixels_count" # The path for the output directory
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# @brief: This function verifies if the output directory exists, if not, it creates the output directory
# @param: output_path: The path for the output directory
# @return: None
def verify_output_directory(output_path):
	if not os.path.exists(output_path): # If the output directory does not exists
		os.mkdir(output_path) # Create the output directory
	
	# Loop through the datasets
	for dataset_name in DATASETS_PATH.keys():
		if not os.path.exists(os.path.join(output_path, f"{dataset_name}")): # If the output directory for the current dataset does not exists
			os.mkdir(os.path.join(output_path, f"{dataset_name}")) # Create the output directory for the current dataset

# @brief: This function verifies if the test and training dataset exists
# @param: None
# @return: True if the dataset exists, False otherwise
def verify_datasets():
	for dataset_name, dataset_path in DATASETS_PATH.items(): # Loop through the datasets
		if not os.path.exists(dataset_path): # If the dataset does not exists
			print(f"{backgroundColors.RED}The {dataset_name} does not exists{Style.RESET_ALL}")
			return False # If the dataset does not exists
	return True # If all of the datasets exists
		
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
	header_string = "GRID, Digit Class, Image Name"

	# Add columns for each grid cell
	for i in range(x_split):
		for j in range(y_split):
			cell_label = f"{i+1}x{j+1}" # Grid cell label
			header_string += f", {cell_label} Black, {cell_label} White"

	# Write the header to the output CSV file
	output_file.write(header_string + "\n")

	return output_file # Return the output file object

# @brief: This function opens each image in the digit class and process each image
# @param: image_path: The path for the image
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: output_file: The output file
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
def process_each_image(image_path, x_grid, y_grid, output_file):
	image = Image.open(image_path) # Open the image

	# Initialize the pixel counter dictionary
	pixels_counter = initialize_pixel_counter(x_grid, y_grid) 
		
	# Count the number of black and white pixels in each split
	pixels_counter = count_pixels(image, x_grid, y_grid, pixels_counter)

	# Write the pixel counters to the output file
	write_pixel_counters(output_file, image_path, pixels_counter, x_grid, y_grid)

# @brief: This function initializes the pixel counter dictionary
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: pixels_counter: A dictionary for storing the number of black and white pixels in each split
def initialize_pixel_counter(x_grid, y_grid):
	pixels_counter = {} # Initialize the pixel counter dictionary
	for i in range(0, x_grid):
		for j in range(0, y_grid):
			# Initialize the pixel counter for the current split
			pixels_counter[f"{i+1}x{j+1}"] = {"black": 0, "white": 0}
	return pixels_counter # Return the initialized pixel counter dictionary 

# @brief: This function counts the number of black and white pixels in each split
# @param: image: The image
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
# @return: pixels_counter: A dictionary for storing the number of black and white pixels in each split
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
# @param: image_path: The path for the image
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: None
def write_pixel_counters(output_file, image_path, pixels_counter, x_grid, y_grid):
	# Get the image and digit class of the current image
	image_name = image_path.split('/')[-1]
	digit_class = image_path.split('/')[-2]

	# Create the line values
	line_values = f"{x_grid}x{y_grid}, {digit_class}, {image_name}"

	# Write the current pixel counters to the output file
	for i in range(x_grid):
		for j in range(y_grid):
			# Get the grid key for this cell
			grid_key = f"{i + 1}x{j + 1}"
			
			# Append the "{i}x{j} Black,{i}x{j} White" to the header string
			line_values += f", {pixels_counter[grid_key]['black']}, {pixels_counter[grid_key]['white']}"

	# Write the line values to the output file
	output_file.write(line_values + "\n")

# @brief: This function normalizes the data using Min-Max scaling
# @param: output_file_path: The path for the output file
# @return: None
def normalize_data(output_file_path):
	# Create a DataFrame from the data
	normalized_data = pd.read_csv(output_file_path)
	# Normalize the data using Min-Max scaling for columns after "Image Name"
	scaler = MinMaxScaler()
	# Normalize the data
	normalized_data.iloc[:, 3:] = scaler.fit_transform(normalized_data.iloc[:, 3:])
	# Create the normalized output file path
	normalized_output_file_path = f"{output_file_path.split('.')[0]}-normalized{OUTPUT_FILE_FORMAT}"
	# Save the normalized data to a CSV file
	normalized_data.to_csv(normalized_output_file_path, index=False)

# @brief: The main function
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the output directory exists
	verify_output_directory(OUTPUT_PATH)

	# Verify if the test and training dataset exists
	if not verify_datasets():
		return # Exit the program

	# Create a progress bar for the splits
	with tqdm(total=len(SPLITS.items()), desc=f"{backgroundColors.GREEN}Splits{Style.RESET_ALL}") as progress_bar:
		# Loop through the splits: 1x1, 2x2, 3x3, 5x5
		for x_grid, y_grid in SPLITS.items():
			# Loop through the datasets
			for dataset_name, dataset_path in DATASETS_PATH.items():
				# Create the output file path
				output_file_path = os.path.join(OUTPUT_PATH, f"{dataset_name}/{x_grid}x{y_grid}-pixel_count{OUTPUT_FILE_FORMAT}")
				# Create the header for the output file
				output_file = create_output_file_header(x_grid, y_grid, output_file_path)
				
				# Open each digit class directory in the current dataset
				for digit_class in sorted(os.listdir(dataset_path)):
					# Get the path for the current digit class
					digit_class_path = os.path.join(dataset_path, digit_class)
					# Open each image in the digit class
					for image_path in os.listdir(digit_class_path):
						# Get the path for the current image
						image_path = os.path.join(digit_class_path, image_path)
						# Verify if the current file is a bmp image
						if image_path.endswith(IMAGE_FILE_FORMAT):
							# Process each image
							process_each_image(image_path, x_grid, y_grid, output_file)

			# Normalize the data stored in the csv
			normalize_data(output_file_path)
			
			# Update the progress bar			
			progress_bar.update(1)

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function