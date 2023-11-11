import numpy as np # Linear Algebra
from sklearn.neighbors import KNeighborsClassifier # K-NN
from sklearn.metrics import classification_report # Classification report
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red
	CLEAR_TERMINAL = "\033[H\033[J" # Clear the terminal

DATA_SETS = ["digits", "spam", "writer"] # Data sets

# This is the main function
def main():
	for data_set in DATA_SETS: # Iterate over the data sets
		# Load the data
		train = np.loadtxt(f"./dataset/{data_set}/train.txt");
		test = np.loadtxt(f"./dataset/{data_set}/test.txt");

		# Get the labels and features
		test_label = test[:,-1] # Get the labels
		train_label = train[:,-1] # Get the labels
		train_features_values = train[:, 1 : -1] # Get the features
		test_features_values = test[:, 1 : -1] # Get the features

		# Print the data set name
		print(f"{backgroundColors.GREEN}K-NN Classifier:{backgroundColors.CYAN}")
		neigh = KNeighborsClassifier(n_neighbors = 20, metric = "euclidean") # Instantiate the classifier
		neigh.fit(train_features_values, train_label) # Train the classifier
		print(f"{classification_report(test_label, neigh.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

		# # Get the class counts
		# class_counts = np.bincount(test_label.astype("int64"))

		# # Print the class counts
		# for class_label, count in enumerate(class_counts):
		# 	if count > 0: # If the class has samples
		# 		print(f"Class {class_label}: {count} samples")

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function