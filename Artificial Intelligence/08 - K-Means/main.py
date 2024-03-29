import atexit # For playing a sound when the program finishes
import time # For getting the current time
import numpy as np # Import numpy
import os # Import os
import platform # For getting the operating system name
from colorama import Style # For coloring the terminal
from sklearn.cluster import KMeans # Import KMeans
from sklearn.neighbors import KNeighborsClassifier # Import KNeighborsClassifier
from sklearn.preprocessing import MinMaxScaler # Import MinMaxScaler

# Macros:
class BackgroundColors: # Colors for the terminal
   CYAN = "\033[96m" # Cyan
   GREEN = "\033[92m" # Green
   YELLOW = "\033[93m" # Yellow
   RED = "\033[91m" # Red
   BOLD = "\033[1m" # Bold
   UNDERLINE = "\033[4m" # Underline
   CLEAR_TERMINAL = "\033[H\033[J" # Clear the terminal

# Sound Constants:
SOUND_COMMANDS = {"Darwin": "afplay", "Linux": "aplay", "Windows": "start"}
SOUND_FILE = "./.assets/NotificationSound.wav" # The path to the sound file

# Folder Constants:
INPUT_DIRECTORY = "./dataset" # The path to the input directory
CENTROIDS_DIRECTORY = "./centroids" # The path to the centroids output directory
NORMALIZED_DATASET_DIRECTORY = "./normalized_dataset" # The path to the normalized dataset directory

# Input Files Constants:
INPUT_FILES = ["train.txt", "test.txt"] # The input files
NORMALIZED_TRAINING_FILE = f"{NORMALIZED_DATASET_DIRECTORY}/{INPUT_FILES[0]}" # The path to the normalized training file
NORMALIZED_TESTING_FILE = f"{NORMALIZED_DATASET_DIRECTORY}/{INPUT_FILES[1]}" # The path to the normalized testing file
STANDARD_TRAINING_FILE = f"{INPUT_DIRECTORY}/{INPUT_FILES[0]}" # The path to the training file
STANDARD_TESTING_FILE = f"{INPUT_DIRECTORY}/{INPUT_FILES[1]}" # The path to the testing file

# Clustering Constants:
SHOW_ACCURACY = True # Show the accuracy of the KNN algorithm
CLUSTERS = [1, 5, 10, 20] # The number of clusters / centroids per class
SAMPLES_PER_CLASS = 100 # The number of samples per class

# I/O Constants:
SAVE_ACCURACY_RESULTS = True # Save the accuracy results to a file
SAVE_CENTROID_DATA = True # Save the centroid data to a file
SAVE_NORMALIZED_DATA = True # Save the normalized data to a file

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
def create_directory(directory, ERASE=False):
   # If the directory exists and is not empty, delete all the files in it
   if os.path.exists(directory) and os.listdir(directory) and ERASE:
      os.system(f"rm -rf {directory}/*")

   # If the directory does not exist
   if not os.path.exists(directory):
      os.makedirs(directory) # Create the directory

# This function loads the data from a file
def load_data(file_path):
   data = np.loadtxt(file_path)
   features = data[:, :-1] # Get the features
   labels = data[:, -1] # Get the labels
   return features, labels # Return the features and labels

# This function normalizes the data
def normalize_data(features):
   normalizer = MinMaxScaler() # Create the MinMaxScaler object
   return normalizer.fit_transform(features) # Normalize the features

# This function saves the normalized data to a file
def save_normalized_data(features, labels, output_file):
   with open(f"{output_file}", "w") as file:
      for feature, label in zip(features, labels): # For each feature and label
         file.write("".join([f"{number:.5f} " for number in feature]) + f"{label:.0f}\n")

# This function pre-processes the data
def pre_process_data():
   # Normalize all of the input files: Training and Testing files
   for input_file in INPUT_FILES:
      # Load the data
      features, labels = load_data(f"{INPUT_DIRECTORY}/{input_file}")
      # Normalize the data
      features = normalize_data(features)
      # Write the normalized data to a file
      if SAVE_NORMALIZED_DATA:
         save_normalized_data(features, labels, f"{NORMALIZED_DATASET_DIRECTORY}/{input_file}")

# This function saves the centroids to a file
def save_centroids(centroid, label, output_file):
   with open(f"{output_file}", "a") as file:
      file.write("".join([f"{number:.5f} " for number in centroid]) + f"{label:.0f}\n")

# This function generates the centroids of the class
def generate_centroids(features, labels, current_cluster, output_file):
   centroids_features = [] # Create the centroids list
   centroids_labels = [] # Create the centroids labels list
   number_of_classes = len(np.unique(labels)) # Get the number of classes
   for i, class_number in enumerate(range(number_of_classes)):
      k_means = KMeans(n_clusters=current_cluster, n_init="auto") # Create the KMeans object
      k_means.fit(features[i * SAMPLES_PER_CLASS:(i + 1) * SAMPLES_PER_CLASS]) # Fit the KMeans object based on the features and labels

      # Append the centroids to the centroids list in order to each line contain the features and the label
      for centroid in k_means.cluster_centers_:
         centroids_features.append(list(centroid))
         centroids_labels.append(class_number)
         if SAVE_CENTROID_DATA:
            save_centroids(centroid, class_number, output_file)

   return centroids_features, centroids_labels # Return the centroids features and labels

# This function runs the KNN algorithm
def run_knn(centroids_features, centroids_labels, neighbors=1):
   testing_features, testing_labels = load_data(NORMALIZED_TESTING_FILE) # Load the normalized testing data

   # Create the KNN object
   knn = KNeighborsClassifier(n_neighbors=neighbors, weights="distance")
   knn.fit(centroids_features, centroids_labels) # Fit the KNN object

   accuracy = knn.score(testing_features, testing_labels) * 100 # Calculate the accuracy

   return accuracy # Return the accuracy

# This function outputs the accuracy
def output_accuracy(accuracy, cluster):
   print(f"{BackgroundColors.GREEN}Accuracy with {BackgroundColors.CYAN}{cluster}{BackgroundColors.GREEN} clusters/neighbors: {BackgroundColors.CYAN}{accuracy:.2f}%{Style.RESET_ALL}") # Output the accuracy

# This function runs the clustering algorithm
def run_clusters():
   accuracy_results = [] # Create the accuracy_results list

   # For each cluster
   for cluster in CLUSTERS:
      features, labels = load_data(NORMALIZED_TRAINING_FILE) # Load the normalized testing data
      
      output_directory = f"{CENTROIDS_DIRECTORY}/"
      create_directory(output_directory, False) # Create the output directory if it does not exist
      output_file = f"{output_directory}{cluster}-clusters.{NORMALIZED_TRAINING_FILE.split('.')[-1]}"

      # Generate the "cluster" number of centroids for each class
      centroids_features, centroids_labels = generate_centroids(features, labels, cluster, output_file)

      # Run the KNN algorithm
      accuracy = run_knn(centroids_features, centroids_labels)

      # Add the accuracy to the accuracy_results list
      accuracy_results.append(f"{cluster},{accuracy:.2f}%")

      if SHOW_ACCURACY:
         output_accuracy(accuracy, cluster)

   return accuracy_results # Return the accuracy_results list

# This function returns the current date and current time
def get_current_date_and_time():
   date = time.strftime("%d/%m/%Y") # Get the current date
   hour = time.strftime("%H") # Get the current time
   minutes = time.strftime("%M") # Get the current time
   seconds = time.strftime("%S") # Get the current time
   return date, f"{hour}h:{minutes}m:{seconds}s" # Return the current date and current time

# This function saves the accuracy results at the end of the csv file
def save_accuracy_results(accuracy_results, date, time):
   with open(f"Accuracy_Results.csv", "a") as file:
      file.write("Time and Date,Clusters,Accuracy\n")
      for accuracy_result in accuracy_results:
         file.write(f"{date} at {time},{accuracy_result}\n") # Write the accuracy results to a file
      file.write(f"{'-' * 3},{'-' * 3},{'-' * 3}\n")

# This is the Main function
def main():
   print(f"{BackgroundColors.CLEAR_TERMINAL}{BackgroundColors.BOLD}{BackgroundColors.GREEN}Welcome to the {BackgroundColors.CYAN}K-Means Clustering{BackgroundColors.GREEN}{BackgroundColors.GREEN} program!{Style.RESET_ALL}") # Output the Welcome message

   create_directory(CENTROIDS_DIRECTORY, True) # Create the centroids output directory if it does not exist
   create_directory(NORMALIZED_DATASET_DIRECTORY, True) # Create the input normalized directory if it does not exist

   pre_process_data() # Pre-process the data

   accuracy_results = run_clusters() # Run the clustering algorithm

   day, time = get_current_date_and_time() # Get the current date and current time

   if SAVE_ACCURACY_RESULTS:
      save_accuracy_results(accuracy_results, day, time) # Save the accuracy results to a file

   print(f"{BackgroundColors.BOLD}{BackgroundColors.GREEN}Program finished.{Style.RESET_ALL}") # Output the end of the program message

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
