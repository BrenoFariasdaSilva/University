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
TRAINNING_DATASET_PATH = "dataset/digits/trainning" # The path for the trainning dataset
TEST_DATASET_PATH = "dataset/digits/test" # The path for the test dataset
OUTPUT_PATH = "output" # The path for the output directory
SPLITS = {1:1, 2:2, 3:3, 5:5} # The splits for the feature extractor
IMAGE_FILE_FORMAT = ".bmp" # The image file format
OUTPUT_FILE_FORMAT = ".csv" # The output file format

# Define a main() 
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

	# Verify if the trainning dataset exists
	if not os.path.exists(TRAINNING_DATASET_PATH):
		print(f"{backgroundColors.RED}The trainning dataset does not exist{Style.RESET_ALL}")
		return # Exit the program
	
	# Verify if the test dataset exists
	if not os.path.exists(TEST_DATASET_PATH):
		print(f"{backgroundColors.RED}The test dataset does not exist{Style.RESET_ALL}")
		return # Exit the program

	# Verify if the output directory exists
	if not os.path.exists(OUTPUT_PATH):
		# Create the output directory
		os.mkdir(OUTPUT_PATH)

	# Create the output file csv header:
	with open(os.path.join(OUTPUT_PATH, f"pixel_count{OUTPUT_FILE_FORMAT}"), "w") as output_file:
		output_file.write("black,white\n")

	pixels_counter = {} # A dictionary for storing the number of black and white pixels in each split

	# Open each digit class directory in the trainning dataset
	with tqdm(total=len(os.listdir(TRAINNING_DATASET_PATH)), desc=f"{backgroundColors.CYAN}Trainning Dataset{Style.RESET_ALL}") as pbar:
		for digit_class in sorted(os.listdir(TRAINNING_DATASET_PATH)):
			# Get the path for the current digit class
			digit_class_path = os.path.join(TRAINNING_DATASET_PATH, digit_class)
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

				# For all of the splits: 1x1, 2x2, 3x3, 5x5, count the number of black and white pixels in each split
				for x_split, y_split in SPLITS.items():
					# For each split in the image
					for x_split_iterator in range(0, x_split):
						for y_split_iterator in range(0, y_split):
							for i in range(0, image_width // x_split):
								for j in range(0, image_height // y_split):
									# Get the pixel color
									pixel_color = image_pixels[i + (x_split_iterator * (image_width // x_split)), j + (y_split_iterator * (image_height // y_split))]
									
									if pixel_color == BLACK: # Verify if the pixel is black
										# Increment the number of black pixels
										pixels_counter[f"{x_split}x{y_split}"][f"{digit_class}"][f"black"] += 1
									elif pixel_color == WHITE: # Verify if the pixel is white
										# Increment the number of white pixels
										pixels_counter[f"{x_split}x{y_split}"][f"{digit_class}"][f"white"] += 1
									else: # The pixel color is not black or white
										print(f"{backgroundColors.RED}The pixel color is not black or white{Style.RESET_ALL}")
										return
					# Write the current pixel counter to the output file
					with open(os.path.join(OUTPUT_PATH, f"{x_split}x{y_split}{OUTPUT_FILE_FORMAT}"), "a") as output_file:
						# Write the number of black and white pixels in the current split
						output_file.write(f"{pixels_counter[f'{x_split}x{y_split}'][f'{digit_class}'][f'black']},{pixels_counter[f'{x_split}x{y_split}'][f'{digit_class}'][f'white']}\n")
							
			# Update the progress bar
			pbar.update(1)

if __name__ == '__main__':
	main()