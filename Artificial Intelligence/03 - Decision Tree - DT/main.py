import numpy as np # For loading the dataset files
from sklearn import tree # For the decision tree classifier
from sklearn.metrics import classification_report # For the classification report
from colorama import Style # For coloring the terminal

# Macros:
class BackgroundColors: # Colors for the terminal
   CYAN = "\033[96m" # Cyan
   GREEN = "\033[92m" # Green
   YELLOW = "\033[93m" # Yellow
   RED = "\033[91m" # Red
   BOLD = "\033[1m" # Bold
   UNDERLINE = "\033[4m" # Underline
   CLEAR_TERMINAL = "\033[H\033[J" # Clear the terminal

# This function loads the data from the dataset files and returns the training and test sets
def load_data():
   print(f"{BackgroundColors.YELLOW}Remember to remove the header line from the dataset files. They should be in the format: {BackgroundColors.CYAN}label feature1 feature2 ... featureN{Style.RESET_ALL}")
   print(f"{BackgroundColors.GREEN}Loading data...{Style.RESET_ALL}")
   tr = np.loadtxt("./dataset/digits/training/5x5-normalized-pixel_count.txt")
   ts = np.loadtxt("./dataset/digits/test/5x5-normalized-pixel_count.txt")
   test_label = ts[:, 0]  # The first column is the label
   train_label = tr[:, 0]  # The first column is the label
   train_features_values = tr[:, 1:]  # The second column is the feature vector
   test_features_values = ts[:, 1:]  # The second column is the feature vector
   return train_features_values, train_label, test_features_values, test_label

# This function trains a decision tree classifier and prints the classification report
def train_decision_tree(train_features_values, train_label, test_features_values, test_label):
   print(f"{BackgroundColors.GREEN}Decision Tree Classifier:{BackgroundColors.CYAN}")
   clf = tree.DecisionTreeClassifier() # Instantiate the classifier
   clf = clf.fit(train_features_values, train_label) # Train the classifier
   print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This is the main function. It calls the other functions, building the project workflow
def main():
   train_features_values, train_label, test_features_values, test_label = load_data()
   train_decision_tree(train_features_values, train_label, test_features_values, test_label) # Train the decision tree classifier

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
