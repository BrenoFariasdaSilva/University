import os # Import the os module for navigating the file system
import numpy as np # Import the numpy module for data manipulation
import threading # Import the threading module for creating threads
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
DATASETS_PATH = {"training":"dataset/digits/training", "test":"dataset/digits/test",} # The path for the training and test datasets
OUTPUT_PATH = "pixels_count/digits" # The path for the output directory
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILES_FORMAT_HEADER = {".csv": True, ".txt": False} # The output file format
OUTPUT_INFORMATION = {".csv": "detailed", ".txt": "simplified"} # The output file type

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

# @brief:This function process each split, creating a thread for each split
# @param: None
# @return: None
def process_each_split():
	with tqdm(total=len(SPLITS.items()), desc=f"{backgroundColors.GREEN}Splits{Style.RESET_ALL}") as progress_bar:
		# Create threads for each split
		threads = []
		for x_grid, y_grid in SPLITS.items():
			thread = threading.Thread(target=process_split, args=(x_grid, y_grid, progress_bar))
			threads.append(thread)
			thread.start()

		# Wait for all threads to finish
		for thread in threads:
			thread.join()

# @brief:This function process each split, creating a thread for each split
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: progress_bar: The progress bar for the splits
# @return: None
def process_split(x_grid, y_grid, progress_bar):
	for dataset_name, dataset_path in DATASETS_PATH.items():
		digit_class_pixel_counters = {}  # Initialize the digit class pixel counters dictionary
		# Open each digit class directory that is inside the current dataset
		for digit_class in sorted(os.listdir(dataset_path)):
			# Initialize the pixel counter for the current digit class
			digit_class_pixel_counters[digit_class] = {}
			# Get the path for the current digit class
			digit_class_folder_path = os.path.join(dataset_path, digit_class)
			# Open each image that is inside the current digit class directory
			for image_name in os.listdir(digit_class_folder_path):
				# Process each image
				digit_class_pixel_counters = process_each_image(
					digit_class_pixel_counters, digit_class, image_name, digit_class_folder_path, x_grid, y_grid)
		# Write results to the output file
		write_results_to_output_files(digit_class_pixel_counters, dataset_name, x_grid, y_grid)
		# Update the progress bar
		progress_bar.update(1)

# @brief: This function processes each image, counting the number of black and white pixels in each split
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: digit_class: The current digit class
# @param: image_name: The current image name
# @return: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def process_each_image(digit_class_pixel_counters, digit_class, image_name, digit_class_folder_path, x_grid, y_grid):
	# Initialize the pixel counter for the current image
	digit_class_pixel_counters[digit_class][image_name] = {}
	# Initialize the pixel counter for the current image
	digit_class_pixel_counters = initialize_pixel_counter(digit_class_pixel_counters, digit_class, image_name, x_grid, y_grid)
	if image_name.endswith(IMAGE_FILE_FORMAT): # Verify if the current file is a bmp image
		# Get the path for the current image
		image_path = os.path.join(digit_class_folder_path, image_name)
		# Process each image
		digit_class_pixel_counters = count_pixels(image_path, x_grid, y_grid, digit_class_pixel_counters, digit_class, image_name)
	else: # If the current file is not a bmp image
		print(f"{backgroundColors.RED}The current file is not a bmp image{Style.RESET_ALL}")
	return digit_class_pixel_counters # Return the digit_class_pixel_counters dictionary
	
# @brief: This function initializes the pixel counter dictionary
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: digit_class: The current digit class
# @param: image_name: The current image name
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: pixels_counter: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def initialize_pixel_counter(digit_class_pixel_counters, digit_class, image_name, x_grid, y_grid):
	# Loop through the number of splits for the current grid in the current digit class and image name
	for i in range(0, x_grid * y_grid):
		digit_class_pixel_counters[digit_class][image_name][i] = {} # Initialize the pixel counter for the current image
		digit_class_pixel_counters[digit_class][image_name][i]["black"] = 0 # Initialize the black pixel counter for the current image
		digit_class_pixel_counters[digit_class][image_name][i]["white"] = 0 # Initialize the white pixel counter for the current image
	return digit_class_pixel_counters # Return the initialized pixel counter dictionary 

# @brief: This function counts the number of black and white pixels in each split
# @param: image_path: The image path
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: digit_class: The current digit class
# @param: image_name: The current image name
# @return: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def count_pixels(image_path, x_grid, y_grid, digit_class_pixel_counters, digit_class, image_name):
	image = Image.open(image_path) # Open the image
	image_pixels = image.load() # Load the image pixels
	image_width, image_height = image.size # Get the image width and height
	split_number = 0 # Initialize the split number
	# Loop through the number of splits in the x axis
	for x_split_number in range(0, x_grid):
		# Loop through the number of splits in the y axis
		for y_split_number in range(0, y_grid):
			pixel_colors = [0, 0] # Initialize the pixel colors counter that stores the number of black and white pixels
			# Loop inside the pixels range for the current x_split_number
			for i in range(0, image_width // x_grid):
				# Loop inside the pixels range for the current y_split_number
				for j in range(0, image_height // y_grid):
					# Get the pixel color
					pixel_color = image_pixels[i + (x_split_number * (image_width // x_grid)), j + (y_split_number * (image_height // y_grid))]
					if pixel_color == BLACK: # If the pixel color is black
						pixel_colors[0] += 1 # Update the black pixel counter
					elif pixel_color == WHITE: # If the pixel color is white
						pixel_colors[1] += 1 # Update the white pixel counter
					else: # If the pixel color is not black or white
						print(f"{backgroundColors.RED}The pixel color is not black or white{Style.RESET_ALL}")

			# Update the black and white pixel counter dictionary
			digit_class_pixel_counters[digit_class][image_name][split_number]["black"] += pixel_colors[0]
			digit_class_pixel_counters[digit_class][image_name][split_number]["white"] += pixel_colors[1]
			split_number += 1 # Update the split number

	image.close() # Close the image
	return digit_class_pixel_counters # Return the pixel counter dictionary

# @brief: This function writes the results to the output file
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: dataset_name: The current dataset name
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: dataset_path: The path for the current dataset
# @return: None
def write_results_to_output_files(digit_class_pixel_counters, dataset_name, x_grid, y_grid):
	for output_file_format in OUTPUT_FILES_FORMAT_HEADER.keys():
		# Create the output file path
		raw_output_file_path = os.path.join(OUTPUT_PATH, f"{dataset_name}/{x_grid}x{y_grid}-pixel_count{output_file_format}")
		if OUTPUT_INFORMATION[output_file_format] == "detailed": # If the output file is detailed
			# Write the pixel counters to the output file
			write_detailed_pixel_counters(raw_output_file_path, digit_class_pixel_counters, x_grid, y_grid)
		else:
			# Write the pixel counters to the output file
			write_simplified_pixel_counters(raw_output_file_path, digit_class_pixel_counters, x_grid, y_grid)
		# Create the output file path
		norm_output_file_path = os.path.join(OUTPUT_PATH, f"{dataset_name}/{x_grid}x{y_grid}-normalized-pixel_count{output_file_format}")
		# Normalize the data stored in the csv
		normalized_digit_class_pixel_counters = normalize_data(digit_class_pixel_counters, x_grid, y_grid)
		# Write the digit_class_pixel_counters to the output file
		if OUTPUT_INFORMATION[output_file_format] == "detailed": # If the output file is detailed
			write_detailed_pixel_counters(norm_output_file_path, normalized_digit_class_pixel_counters, x_grid, y_grid)
		else:
			write_simplified_pixel_counters(norm_output_file_path, normalized_digit_class_pixel_counters, x_grid, y_grid)
		# Delete the non normalized pixel counters files
		os.remove(raw_output_file_path)

# @brief: This function writes the pixel counters to the output file
# @param: output_file: The output file
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: None
def write_detailed_pixel_counters(output_file_path, digit_class_pixel_counters, x_grid, y_grid):
	output_file = create_output_file(output_file_path) # Create the output file
	# Get the file format (dot included)
	file_format = os.path.splitext(output_file_path)[1]
	if OUTPUT_FILES_FORMAT_HEADER[file_format]: # If this file format requires a header
		# Create the header for the output file
		output_file = create_detailed_output_file_header(output_file, x_grid, y_grid)
	# Loop through the digit classes
	for digit_class, digit_class_data in digit_class_pixel_counters.items():
		# Loop through the images in the current digit class
		for image_name in digit_class_data.keys():
			output_string = f"{x_grid}x{y_grid},{digit_class},{image_name}" # Initialize the output string
			# Loop through the splits for the current image in the current digit class
			for i in range(0, x_grid * y_grid):
				output_string += f",{digit_class_pixel_counters[digit_class][image_name][i]['black']},{digit_class_pixel_counters[digit_class][image_name][i]['white']}"
			output_file.write(output_string + "\n")

# @brief: This function writes the pixel counters to the output file
# @param: output_file: The output file
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: None
def write_simplified_pixel_counters(output_file_path, digit_class_pixel_counters, x_grid, y_grid):
	output_file = create_output_file(output_file_path) # Create the output file
	# Get the file format (dot included)
	file_format = os.path.splitext(output_file_path)[1]
	if OUTPUT_FILES_FORMAT_HEADER[file_format]: # If this file format requires a header
		# Create the header for the output file
		output_file = create_simplified_output_file_header(output_file, x_grid, y_grid)
	# Loop through the digit classes
	for digit_class, digit_class_data in digit_class_pixel_counters.items():
		# Loop through the images in the current digit class
		for image_name in digit_class_data.keys():
			output_string = f"{digit_class}" # Initialize the output string
			# Loop through the splits for the current image in the current digit class
			for i in range(0, x_grid * y_grid):
				output_string += f" {digit_class_pixel_counters[digit_class][image_name][i]['black']} {digit_class_pixel_counters[digit_class][image_name][i]['white']}"
			output_file.write(output_string + "\n")

# @brief: This function create and return the output file object
# @param: output_file_path: The path for the output file
# @return: output_file: The output file object
def create_output_file(output_file_path):
	# Create and open the output CSV file
	output_file = open(output_file_path, "a")
	# Clear the output file (truncate its contents)
	output_file.truncate(0)
	return output_file # Return the output file object

# @brief: This function create the detailed header for the output file
# @param: output_file: The output file object
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @return: output_file: The output file object
def create_detailed_output_file_header(output_file, x_split, y_split):
	# Create the header string
	header_string = "GRID,Digit Class,Image Name"

	# Add columns for each grid cell
	for i in range(x_split):
		for j in range(y_split):
			cell_label = f"{i}x{j}" # Grid cell label
			header_string += f",{cell_label} Black,{cell_label} White"

	# Write the header to the output CSV file
	output_file.write(header_string + "\n")

	return output_file # Return the output file object

# @brief: This function create the simplified header for the output file
# @param: output_file: The output file object
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @return: output_file: The output file object
def create_simplified_output_file_header(output_file, x_split, y_split):
	# Create the header string
	header_string = "Digit Class"

	# Add columns for each grid cell
	for i in range(x_split):
		for j in range(y_split):
			cell_label = f"{i}x{j}" # Grid cell label
			header_string += f",{cell_label} Black,{cell_label} White"

	# Write the header to the output CSV file
	output_file.write(header_string + "\n")

	return output_file # Return the output file object

# @brief: This function normalizes the data stored in the digit_class_pixel_counters dictionary using Min-Max scaling
# @param: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @return: digit_class_pixel_counters: A dictionary for storing the number of black and white pixels for the current image in the current digit class
def normalize_data(digit_class_pixel_counters, x_grid, y_grid):
	all_images_data = [] # Initialize a list to store pixel data for all images
	# Loop through the digit classes
	for digit_class_data in digit_class_pixel_counters.values():
		# Loop through the images in the current digit class
		for splits_data in digit_class_data.values():
			image_data = [] # Initialize a list to store the black and white pixel data for the current image
			# Loop through the splits for the current image in the current digit class
			for i in range(x_grid * y_grid):
				# Append the pixel data to the image_data list
				image_data.extend([splits_data[i]["black"], splits_data[i]["white"]])
			# Append the image_data list to all_images_data
			all_images_data.append(image_data)

	# Convert all_images_data to a NumPy array
	image_pixels = np.array(all_images_data, dtype=np.float64)
	scaler = MinMaxScaler() # Initialize the MinMaxScaler
	image_pixels = scaler.fit_transform(image_pixels) # Normalize the data using Min-Max scaling

	# Re-assign the normalized data to the digit_class_pixel_counters dictionary
	image_index = 0 # Initialize the image index
	# Loop through the digit classes
	for digit_class_data in digit_class_pixel_counters.values():
		# Loop through the images in the current digit class
		for splits_data in digit_class_data.values():
			# Loop through the splits for the current image in the current digit class
			for i in range(x_grid * y_grid):
				# Update the dictionary with the normalized values
				splits_data[i]["black"] = image_pixels[image_index][2 * i]
				splits_data[i]["white"] = image_pixels[image_index][2 * i + 1]
			image_index += 1 # Update the image index

	return digit_class_pixel_counters # Return the digit_class_pixel_counters dictionary

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

	# Process each split
	process_each_split()

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function