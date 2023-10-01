import os # Import the os module for navigating the file system
from colorama import Style # For coloring the terminal
from tqdm import tqdm # For Generating the Progress Bars

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# Define a main() 
def main():
	print(f"{backgroundColors.CYAN}Welcome to the Pixel Feature Extractor{Style.RESET_ALL}")

if __name__ == '__main__':
	main()