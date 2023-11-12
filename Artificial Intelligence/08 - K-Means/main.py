import atexit # For playing a sound when the program finishes
import matplotlib.pyplot as plt # Import matplotlib
import numpy as np # Import numpy
import os # Import os
import platform # For getting the operating system name
from colorama import Style  # For coloring the terminal
from sklearn.cluster import KMeans # Import KMeans
from sklearn.model_selection import train_test_split # Import train_test_split
from sklearn.neighbors import KNeighborsClassifier # Import KNeighborsClassifier
from sklearn.preprocessing import minmax_scaler # Import MinMaxScaler

# Macros:
class BackgroundColors:  # Colors for the terminal
   CYAN = "\033[96m"  # Cyan
   GREEN = "\033[92m"  # Green
   YELLOW = "\033[93m"  # Yellow
   RED = "\033[91m"  # Red
   BOLD = "\033[1m"  # Bold
   UNDERLINE = "\033[4m"  # Underline
   CLEAR_TERMINAL = "\033[H\033[J"  # Clear the terminal

# Sound Constants:
SOUND_COMMANDS = {"Darwin": "afplay", "Linux": "aplay", "Windows": "start"}
SOUND_FILE = "./.assets/NotificationSound.wav" # The path to the sound file

# This function defines the command to play a sound when the program finishes
def play_sound():
   if os.path.exists(SOUND_FILE):
      if platform.system() in SOUND_COMMANDS: # If the platform.system() is in the SOUND_COMMANDS dictionary
         os.system(f"{SOUND_COMMANDS[platform.system()]} {SOUND_FILE}")
      else: # If the platform.system() is not in the SOUND_COMMANDS dictionary
         print(f"{BackgroundColors.RED}The {BackgroundColors.CYAN}platform.system(){BackgroundColors.RED} is not in the {BackgroundColors.CYAN}SOUND_COMMANDS dictionary{BackgroundColors.RED}. Please add it!{Style.RESET_ALL}")
   else: # If the sound file does not exist
      print(f"{BackgroundColors.RED}Sound file {BackgroundColors.CYAN}{SOUND_FILE}{BackgroundColors.RED} not found. Make sure the file exists.{Style.RESET_ALL}")

# Register the function to play a sound when the program finishes
atexit.register(play_sound)

# This is the Main function
def main():
   print(f"{BackgroundColors.CLEAR_TERMINAL}{BackgroundColors.BOLD}{BackgroundColors.GREEN}Welcome to the {BackgroundColors.CYAN}K-Means Clustering{BackgroundColors.GREEN}{BackgroundColors.GREEN} program!{Style.RESET_ALL}") # Output the Welcome message
   
   print(f"{BackgroundColors.BOLD}{BackgroundColors.GREEN}Program finished.{Style.RESET_ALL}") # Output the end of the program message

# This is the standard boilerplate that calls the main() function.
if __name__ == '__main__':
	main() # Call the main function
    