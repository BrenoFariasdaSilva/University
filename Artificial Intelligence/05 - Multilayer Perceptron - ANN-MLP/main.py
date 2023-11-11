import numpy as np # For the data manipulation
from sklearn.metrics import classification_report # For the classification report
from sklearn.neural_network import MLPClassifier # For the MLP classifier
from sklearn.preprocessing import StandardScaler # For the standard scaler
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
   CYAN = "\033[96m" # Cyan
   GREEN = "\033[92m" # Green
   YELLOW = "\033[93m" # Yellow
   RED = "\033[91m" # Red
   BOLD = "\033[1m" # Bold
   UNDERLINE = "\033[4m" # Underline
   CLEAR_TERMINAL = "\033[H\033[J" # Clear the terminal

# This function loads the data from the dataset files and returns the training and test sets
def load_data():
   print(f"{backgroundColors.YELLOW}Remember to remove the header line from the dataset files. They should be in the format: {backgroundColors.CYAN}label feature1 feature2 ... featureN{Style.RESET_ALL}")
   print(f"{backgroundColors.GREEN}Loading data...{Style.RESET_ALL}")
   tr = np.loadtxt("./dataset/digits/training/5x5-normalized-pixel_count.txt")
   ts = np.loadtxt("./dataset/digits/test/5x5-normalized-pixel_count.txt")
   test_label = ts[:, 0] # The first column is the label
   train_label = tr[:, 0] # The first column is the label
   train_features_values = tr[:, 1:] # The second column to the last is the feature vector
   test_features_values = ts[:, 1:] # The second column to the last is the feature vector
   return train_features_values, train_label, test_features_values, test_label # Return the data

# This function trains a SVM classifier with grid search and prints the classification report
def train_multilayer_perceptron(train_features_values, train_label, test_features_values, test_label):
   print(f"{backgroundColors.GREEN}Artificial Neural Network/Multilayer Perceptron Classifier:{backgroundColors.CYAN}")
   scaler = StandardScaler() # Instantiate the standard scaler
   train_features_values = scaler.fit_transform(train_features_values) # Scale the training features
   test_features_values = scaler.fit_transform(test_features_values) # Scale the test features
   clf = MLPClassifier(solver="adam", alpha=1e-5, hidden_layer_sizes=(500, 500, 500, 500), random_state=1) # Instantiate the classifier
   clf.fit(train_features_values, train_label) # Train the classifier
   print(clf.predict(test_features_values)) # Print the predictions
   print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This is the main function. It calls the other functions, building the project workflow
def main():
   train_features_values, train_label, test_features_values, test_label = load_data() # Load the data
   train_multilayer_perceptron(train_features_values, train_label, test_features_values, test_label) # Train the ANN - Multilayer Perceptron classifier

# This the boilerplate that calls the main function
if __name__ == "__main__":
   main() # Call the main function