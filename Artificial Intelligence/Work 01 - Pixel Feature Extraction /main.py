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
OUTPUT_PATH = "output" # The path for the output directory
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# Define a main() 
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the output directory exists
	if not os.path.exists(OUTPUT_PATH):
		# Create the output directory
		os.mkdir(OUTPUT_PATH)

	# Verify if the test and trainning dataset exists
	for dataset_name, dataset_path in DATASETS_PATH.items():
		if not os.path.exists(dataset_path):
			print(f"{backgroundColors.RED}The {dataset_path} does not exists{Style.RESET_ALL}")
			return
		else:
			with open(os.path.join(OUTPUT_PATH, f"{dataset_name}_pixel_count{OUTPUT_FILE_FORMAT}"), "w") as output_file:
				output_file.write("Split,Digit Class,Filename, Black Counter, White Counter\n")

	pixels_counter = {} # A dictionary for storing the number of black and white pixels in each split

	for dataset_name, dataset_path in DATASETS_PATH.items():
		# Open each digit class directory in the trainning dataset
		for digit_class in sorted(os.listdir(dataset_path)):
			# Get the path for the current digit class
			digit_class_path = os.path.join(dataset_path, digit_class)
			# Open each image in the digit class
			for image_path in os.listdir(digit_class_path):
				# Get the path for the current image
				image_path = os.path.join(digit_class_path, image_path)

				# Verify if the current file is a bmp image
				if not image_path.endswith(IMAGE_FILE_FORMAT):
					continue # Skip the current file

				# Open the image
				image = Image.open(image_path)
				# Load the image pixels
				image_pixels = image.load()
				# Get the image width and height
				image_width, image_height = image.size

				# Loop through image pixels and update the counters
				for x_grid, y_grid in SPLITS.items():
					pixels_counter[f"{x_grid}x{y_grid}"] = {}  # Initialize the pixel counter dictionary for this split
					for digit_class in range(10):  # Assuming you have 10 digit classes
						pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"] = {"black": 0, "white": 0}
					
					for x_split_iterator in range(0, x_grid):  # Iterate over the number of splits in the x axis
						for y_split_iterator in range(0, y_grid):  # Iterate over the number of splits in the y axis
								for i in range(0, image_width // x_grid):  # Iterate over the number of pixels in the x axis
									for j in range(0, image_height // y_grid):  # Iterate over the number of pixels in the y axis
										# Get the pixel color
										pixel_color = image_pixels[i + (x_split_iterator * (image_width // x_grid)), j + (y_split_iterator * (image_height // y_grid))]
										
										if pixel_color == BLACK:  # Verify if the pixel is black
												# Increment the number of black pixels
												pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"]["black"] += 1
										elif pixel_color == WHITE:  # Verify if the pixel is white
												# Increment the number of white pixels
												pixels_counter[f"{x_grid}x{y_grid}"][f"{digit_class}"]["white"] += 1
										else:  # The pixel color is not black or white
												print(f"{backgroundColors.RED}The pixel color is not black or white{Style.RESET_ALL}")

				# Write the current pixel counters to the output file
				for x_grid, y_grid in SPLITS.items():
					with open(os.path.join(OUTPUT_PATH, f"{dataset_name}_pixel_count{OUTPUT_FILE_FORMAT}"), "a") as output_file:
						for digit_class in range(10):  # Assuming you have 10 digit classes
								output_file.write(f"{x_grid}x{y_grid},{digit_class},{image_path.split('/')[-1]},"
														f"{pixels_counter[f'{x_grid}x{y_grid}'][f'{digit_class}']['black']},"
														f"{pixels_counter[f'{x_grid}x{y_grid}'][f'{digit_class}']['white']}\n")

if __name__ == '__main__':
	main()