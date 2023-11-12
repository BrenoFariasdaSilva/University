import atexit # For playing a sound when the program finishes
import numpy as np # Import numpy
import os # Import os
import platform # For getting the operating system name
from colorama import Style  # For coloring the terminal
from sklearn.cluster import KMeans # Import KMeans
from sklearn.model_selection import train_test_split # Import train_test_split
from sklearn.neighbors import KNeighborsClassifier # Import KNeighborsClassifier
from sklearn.preprocessing import MinMaxScaler # Import MinMaxScaler

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

# Folder Constants:
INPUT_DIRECTORY = "./dataset" # The path to the input directory
OUTPUT_DIRECTORY = "./results" # The path to the output directory

# Input Files Constants:
INPUT_FILES = ["train.txt", "test.txt"] # The input files
TRAINING_FILE = f"{INPUT_DIRECTORY}/{INPUT_FILES[0]}" # The path to the training file
TESTING_FILE = f"{INPUT_DIRECTORY}/{INPUT_FILES[1]}" # The path to the testing file

# Clustering Constants:
CLUSTERS = [1, 5, 10, 20] # The number of clusters / centroids per class

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

# This function creates a directory if it does not exist
def create_directory(directory):
   # If the directory does not exist
   if not os.path.exists(directory):
      os.makedirs(directory) # Create the directory

# This function loads the data from a file
def load_data(file_path):
   data = np.loadtxt(file_path)
   features = data[:, :-1] # Get the features
   labels = data[:, -1] # Get the labels
   return features, labels

# This function normalizes the data
def normalize_data(features):
   normalizer = MinMaxScaler() # Create the MinMaxScaler object
   return normalizer.fit_transform(features) # Normalize the features

# This function generates the centroids of the class
def generate_centroids(features, labels, current_cluster, output_file):
   number_of_classes = len(np.unique(labels)) # Get the number of classes
   for class_number in range(number_of_classes):
      k_means = KMeans(n_clusters=current_cluster, n_init="auto") # Create the KMeans object
      k_means.fit(features[labels == class_number]) # Fit the KMeans object

      # Write the centroids to a file
      with open(output_file, "a") as file:
         for centroid in k_means.cluster_centers_:
            file.write("".join([f"{number:.5f} " for number in centroid]) + f"{class_number:.0f}\n")

# This function runs the clustering algorithm
def run_clusters(features, labels, clusters):
   for cluster in clusters:
      for input_file in INPUT_FILES:
         output_file = f"{OUTPUT_DIRECTORY}/{input_file.split('.')[0]}-{cluster}clusters.{input_file.split('.')[1]}"
         
         # Generate the centroids
         generate_centroids(features, labels, cluster, output_file)

# This is the Main function
def main():
   print(f"{BackgroundColors.CLEAR_TERMINAL}{BackgroundColors.BOLD}{BackgroundColors.GREEN}Welcome to the {BackgroundColors.CYAN}K-Means Clustering{BackgroundColors.GREEN}{BackgroundColors.GREEN} program!{Style.RESET_ALL}") # Output the Welcome message

   create_directory(OUTPUT_DIRECTORY) # Create the output directory if it does not exist

   features, labels = load_data(TRAINING_FILE) # Load the training data

   normalized_features = normalize_data(features) # Normalize the features

   run_clusters(normalized_features, labels, CLUSTERS) # Run the clustering algorithm

   print(f"{BackgroundColors.BOLD}{BackgroundColors.GREEN}Program finished.{Style.RESET_ALL}") # Output the end of the program message

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
    