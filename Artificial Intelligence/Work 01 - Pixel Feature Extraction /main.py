import os # Import the os module for navigating the file system
from colorama import Style # For coloring the terminal
from PIL import Image # Import the PIL module for image manipulation
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
DATASETS_PATH = {"test":"dataset/digits/test", "trainning":"dataset/digits/trainning"} # The path for the trainning dataset
OUTPUT_PATH = "pixels_count" # The path for the output directory
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# @brief: This function verifies if the output directory exists, if not, it creates the output directory
# @param: output_path: The path for the output directory
def verify_output_directory(output_path):
	if not os.path.exists(output_path): # If the output directory does not exists
		os.mkdir(output_path) # Create the output directory

# @brief: This function verifies if the test and trainning dataset exists
# @param: None
# @return: True if the dataset exists, False otherwise
def verify_datasets():
	for dataset_name, dataset_path in DATASETS_PATH.items(): # Loop through the datasets
		if not os.path.exists(dataset_path): # If the dataset does not exists
			print(f"{backgroundColors.RED}The {dataset_name} does not exists{Style.RESET_ALL}")
			return False
		
# @brief: This function create the header for the output file
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @param: output_file_path: The path for the output file
# @return: output_file: The output file object
def create_header(x_split, y_split, output_file_path):
	# Create the output file
	with open (os.path.join(OUTPUT_PATH, f"{output_file_path}"), "w") as output_file:
		header_string = "Digit Class,Filename," # The header string
		for i in range(0, x_split):
			for j in range(0, y_split):
				# Append the header string
				header_string += f"{i}x{j} Black Pixels,{i}x{j} White Pixels,"
		# Write the header to the output file
		output_file.write(f"{header_string}\n")
	return output_file

# @brief: This function opens each image in the digit class and process each image
# @param: image_path: The path for the image
# @param: number_of_digit_classes: The number of digit classes
# @param: x_grid: The number of splits in the x axis
# @param: y_grid: The number of splits in the y axis
# @param: output_file_path: The path for the output file
# @param: output_file: The output file
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
def process_each_image(image_path, number_of_digit_classes, x_grid, y_grid, output_file, pixels_counter):
	image = Image.open(image_path) # Open the image

	# If the current split is not in the pixel counter dictionary
	if f"{x_grid}x{y_grid}" not in pixels_counter:
		pixels_counter[f"{x_grid}x{y_grid}"] = {} # Initialize the pixel counter dictionary for this split

	# Verfies if the current digit class is not in the pixel counter dictionary
	for digit_class in range(number_of_digit_classes):
		if f"{digit_class}" not in pixels_counter[f"{x_grid}x{y_grid}"]:
			pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"] = {}
		
		if f"{image_path.split('/')[-1]}" not in pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"]:
			pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"][f"{image_path.split('/')[-1]}"] = {"black": 0, "white": 0}
		
		# Count the number of black and white pixels in each split
		pixels_counter = count_pixels(image, x_grid, y_grid, output_file, pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"][f"{image_path.split('/')[-1]}"])
		# Write the pixel counters to the output file
		write_pixel_counters(output_file, x_grid, y_grid, pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"][f"{image_path.split('/')[-1]}"])

# @brief: This function counts the number of black and white pixels in each split
# @param: image: The image
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
# @return: pixels_counter: A dictionary for storing the number of black and white pixels in each split
def count_pixels(image, x_split, y_split, pixels_counter):
	# Load the image pixels
	image_pixels = image.load()
	# Get the image width and height
	image_width, image_height = image.size

	# Loop through the image pixels
	for x_split_iterator in range(0, x_split):
		for y_split_iterator in range(0, y_split):
			for i in range(0, image_width // x_split):
				for j in range(0, image_height // y_split):
					pixel_color = image_pixels[i + (x_split_iterator * (image_width // x_split)), j + (y_split_iterator * (image_height // y_split))]
					
					if pixel_color == BLACK:
						pixels_counter["black"] += 1
					elif pixel_color == WHITE:
						pixels_counter["white"] += 1
					else:
						print(f"{backgroundColors.RED}The pixel color is not black or white{Style.RESET_ALL}")

	return pixels_counter

# @brief: This function writes the pixel counters to the output file
# @param: output_file: The output file
# @param: x_split: The number of splits in the x axis
# @param: y_split: The number of splits in the y axis
# @param: pixels_counter: A dictionary for storing the number of black and white pixels in each split
def write_pixel_counters(output_file, x_split, y_split, pixels_counter):
	# Write the current pixel counters to the output file
	for x_split_iterator in range(0, x_split):
		for y_split_iterator in range(0, y_split):
			output_file.write(f"{pixels_counter[f'{x_split_iterator}x{y_split_iterator}']['black']},{pixels_counter[f'{x_split_iterator}x{y_split_iterator}']['white']},")
	output_file.write("\n")

# @brief: The main function
# @param: None
# @return: None
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the output directory exists
	verify_output_directory(OUTPUT_PATH)

	# Verify if the test and trainning dataset exists
	if not verify_datasets():
		return # Exit the program

	pixels_counter = {} # A dictionary for storing the number of black and white pixels in each split

	# Create a progress bar for the splits
	with tqdm(total=len(SPLITS.items())) as progress_bar:
		# Loop through the splits: 1x1, 2x2, 3x3, 5x5
		for x_grid, y_grid in SPLITS.items():
			# Loop through the datasets
			for dataset_name, dataset_path in DATASETS_PATH.items():
				# Create the output file path
				output_file_path = os.path.join(OUTPUT_PATH, f"{dataset_name}-{x_grid}x{y_grid}-pixel_count{OUTPUT_FILE_FORMAT}")
				# Create the header for the output file
				output_file = create_header(x_grid, y_grid, output_file_path)
				
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
							process_each_image(digit_class_path, len(os.listdir(dataset_path)), x_grid, y_grid, output_file, pixels_counter)

			# Update the progress bar			
			progress_bar.update(1)

# @brief: The entry point of the program
# @param: None
# @return: None
if __name__ == '__main__':
	main() # Call the main function