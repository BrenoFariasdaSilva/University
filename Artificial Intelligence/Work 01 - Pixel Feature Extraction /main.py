import os # Import the os module for navigating the file system
import numpy as np # Import numpy for matrix operations
from colorama import Style # For coloring the terminal
from PIL import Image # Import the PIL module for image manipulation
from tqdm import tqdm # For Generating the Progress Bars

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# Constants:
TRAINNING_DATASET_PATH = "dataset/digits/trainning"
TEST_DATASET_PATH = "dataset/digits/test"
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor

# Define a main() 
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the trainning dataset exists
	if not os.path.exists(TRAINNING_DATASET_PATH):
		print(f"{backgroundColors.RED}The trainning dataset does not exist{Style.RESET_ALL}")
		return
	
	# Verify if the test dataset exists
	if not os.path.exists(TEST_DATASET_PATH):
		print(f"{backgroundColors.RED}The test dataset does not exist{Style.RESET_ALL}")
		return

	# Verify if the output directory exists
	if not os.path.exists("output"):
		# Create the output directory
		os.mkdir("output")

	# Open each digit class directory in the trainning dataset
	for digit_classes in sorted(os.listdir(TRAINNING_DATASET_PATH)):
		# Get the path for the current digit class
		digit_class_path = os.path.join(TRAINNING_DATASET_PATH, digit_classes)
		# Open each image in the digit class
		for image_path in os.listdir(digit_class_path):
			# Get the path for the current image
			image_path = os.path.join(digit_class_path, image_path)

			# Verify if the current file is a image
			if not image_path.endswith(".bmp"):
				continue

			# Open the image
			image = Image.open(image_path)
			# Load the image pixels
			image_pixels = image.load()
			# Get the image width and height
			image_width, image_height = image.size

			# For all of the splits: 1x1, 2x2, 3x3, 5x5, count the number of black and white pixels in each split
			for x_split, y_split in SPLITS.items():
				# Create a matrix to store the number of black and white pixels in each split
				split_pixels = np.zeros((image_width // x_split, image_height // y_split, 2))

				# For each split in the image
				for x in range(0, image_width, x_split):
					for y in range(0, image_height, y_split):
						# Count the number of black and white pixels in the split
						for x_offset in range(x_split):
							for y_offset in range(y_split):
								# Get the pixel color
								pixel_color = image_pixels[x + x_offset, y + y_offset]
								# If the pixel is black
								if pixel_color == 0:
									# Increment the number of black pixels in the split
									split_pixels[x // x_split, y // y_split, 0] += 1
								# If the pixel is white
								elif pixel_color == 255:
									# Increment the number of white pixels in the split
									split_pixels[x // x_split, y // y_split, 1] += 1

if __name__ == '__main__':
	main()