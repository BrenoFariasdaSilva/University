import atexit # For playing a sound when the program finishes
import numpy as np # For the data manipulation
import os # For running a command in the terminal
import platform # For getting the operating system name
import time # For the timer
from colorama import Style # For coloring the terminal
from sklearn import svm # For the SVM classifier
from sklearn import tree # For the decision tree classifier
from sklearn.ensemble import RandomForestClassifier # For the random forest classifier
from sklearn.metrics import classification_report # For the classification report
from sklearn.metrics import confusion_matrix # For the confusion matrix
from sklearn.model_selection import GridSearchCV # For the grid search
from sklearn.naive_bayes import GaussianNB # For the Naive Bayes classifier
from sklearn.neighbors import KNeighborsClassifier # For the k-NN classifier
from sklearn.neural_network import MLPClassifier # For the MLP classifier
from sklearn.pipeline import Pipeline # For the pipeline
from sklearn.preprocessing import StandardScaler # For the standard scaler

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

# Constants:
INPUT_FILES = ["./dataset/digits/training/5x5-normalized-pixel_count.txt", "./dataset/digits/test/5x5-normalized-pixel_count.txt"] # The input files

# Output Constants:
SHOW_CONFUSION_MATRIX = False # If True, show the confusion matrix
SHOW_CLASSIFICATION_REPORT = False # If True, show the classification report
SHOW_DATASET_INFORMATION = True # If True, show the dataset information

# Classifiers Constants:
CLASSIFIERS = {
   "K-Nearest Neighbors": "grid_search_k_nearest_neighbors",
   "Decision Tree": "grid_search_decision_tree",
   "Support Vector Machine": "grid_search_support_vector_machine",
   "Multilayer Perceptron": "grid_search_multilayer_perceptron",
   "Random Forest": "grid_search_random_forest",
   "Naive Bayes": "grid_search_naive_bayes",
}

# Grid Search Constants:
CROSS_VALIDATION = None # The number of cross validation folds

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

# This function prints if the dataset is balanced or not
def dataset_balance(train_labels, test_labels):
   # Calculate the number of samples per class in the training and test sets
   qtd_labels_per_class_train = [np.count_nonzero(train_labels == label) for label in np.unique(train_labels)]
   qtd_labels_per_class_test = [np.count_nonzero(test_labels == label) for label in np.unique(test_labels)]
   if qtd_labels_per_class_train == qtd_labels_per_class_test:
      print(f"{BackgroundColors.GREEN}The dataset is {BackgroundColors.CYAN}balanced{BackgroundColors.GREEN}, as there are same amounts of samples per class.{Style.RESET_ALL}", end="\n\n")
   else:
      print(f"{BackgroundColors.GREEN}The dataset is {BackgroundColors.RED}not balanced{BackgroundColors.GREEN}, as there are different amounts of samples per class.{Style.RESET_ALL}", end="\n\n")


# This function prints the dataset information
def print_dataset_information(train_features, train_labels, test_features):
   print(f"{BackgroundColors.GREEN}Number of features: {BackgroundColors.CYAN}{train_features.shape[1]}{Style.RESET_ALL}")
   print(f"{BackgroundColors.GREEN}Number of training instances: {BackgroundColors.CYAN}{train_features.shape[0]}{Style.RESET_ALL}")
   print(f"{BackgroundColors.GREEN}Number of test instances: {BackgroundColors.CYAN}{test_features.shape[0]}{Style.RESET_ALL}")
   print(f"{BackgroundColors.GREEN}Number of classes: {BackgroundColors.CYAN}{len(np.unique(train_labels))}{Style.RESET_ALL}")

# This function loads the data from the dataset files and returns the training and test sets
def load_data():
   print(f"{BackgroundColors.BOLD}{BackgroundColors.YELLOW}Remember to remove the header line from the dataset files. They should be in the format: {BackgroundColors.CYAN}label feature1 feature2 ... featureN{Style.RESET_ALL}")
   print(f"\n{BackgroundColors.GREEN}Loading data...{Style.RESET_ALL}")
   tr = np.loadtxt(f"{INPUT_FILES[0]}") # Load the training data
   ts = np.loadtxt(f"{INPUT_FILES[1]}") # Load the test data
   train_labels = tr[:, 0] # The first column is the label
   test_labels = ts[:, 0] # The first column is the label
   train_features = tr[:, 1:] # The second column to the last is the feature vector
   test_features = ts[:, 1:] # The second column to the last is the feature vector
   return train_features, train_labels, test_features, test_labels # Return the data

# This fuction run every classifier
def run_classifiers(train_features, train_labels, test_features, test_labels):
   classifiers_execution = {} # Dictionary to store the classifiers execution time

   # Loop through the classifiers
   for classifier, function in CLASSIFIERS.items():
      # Run the classifier
      classifiers_execution[classifier] = globals()[function]
      classifiers_execution[classifier] = classifiers_execution[classifier](train_features, train_labels, test_features, test_labels)

   return classifiers_execution # Return the classifiers execution time

# This function creates a k-NN classifier and prints the classification report
def grid_search_k_nearest_neighbors(train_features, train_labels, test_features, test_labels):
   # Define the parameter grid for the grid search
   param_grid = {
      "metric": ["euclidean", "manhattan", "minkowski"], # Distance metric to use.
      "n_neighbors": [1, 3, 5, 7], # Neighbors to use.
   }

   knn = KNeighborsClassifier() # Instantiate the classifier

   # Instantiate GridSearchCV
   grid_search = GridSearchCV(knn, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, n_jobs=-1)

   start_time = time.time() # Start the timer
   grid_search.fit(train_features, train_labels) # Train the classifier with grid search

   # Get the best model from the grid search
   best_knn = grid_search.best_estimator_

   # Predict the test set using the best model
   y_pred = best_knn.predict(test_features)
   execution_time = time.time() - start_time # Calculate the execution time

   # Calculate the accuracy
   accuracy = best_knn.score(test_features, test_labels)

   # Get the best parameters from the grid search
   best_params = grid_search.best_params_

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN} Classification Report for K-Nearest Neighbors:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n")

   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred) # Calculate the confusion matrix
      print(f"{BackgroundColors.GREEN}K-Nearest Neighbors Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n") # Print the confusion matrix
   
   return accuracy, y_pred, {"Best Parameters": best_params, "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function creates a Decision Tree classifier with grid search and prints the classification report
def grid_search_decision_tree(train_features, train_labels, test_features, test_labels):
   # Define the parameter grid for the grid search
   param_grid = {
      "criterion": ["gini", "entropy"], # The function to measure the quality of a split.
      "max_depth": [None, 10, 20, 30], # The maximum depth of the tree.
      "splitter": ["best", "random"], # The strategy used to choose the split at each node.
   }

   # Instantiate the Decision Tree classifier
   dt = tree.DecisionTreeClassifier()

   # Instantiate GridSearchCV
   grid_search = GridSearchCV(dt, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, n_jobs=-1)

   start_time = time.time() # Start the timer
   grid_search.fit(train_features, train_labels) # Train the classifier with grid search

   # Get the best model from the grid search
   best_clf = grid_search.best_estimator_

   # Predict the test set using the best model
   y_pred = best_clf.predict(test_features)
   execution_time = time.time() - start_time # Calculate the execution time

   # Calculate the accuracy
   accuracy = best_clf.score(test_features, test_labels)

   # Get the best parameters from the grid search
   best_params = grid_search.best_params_

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN}Decision Tree Classification Report for Decision Tree:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n")
   
   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred) 
      print(f"{BackgroundColors.GREEN}Decision Tree Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n")

   return accuracy, y_pred, {"Best Parameters": best_params, "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function creates a SVM classifier with grid search and prints the classification report
def grid_search_support_vector_machine(train_features, train_labels, test_features, test_labels):
   svm_clf = svm.SVC(probability=True) # Instantiate the classifier with probability
   ss = StandardScaler() # Instantiate the standard scaler
   pipeline = Pipeline([("scaler", ss), ("svm", svm_clf)]) # Instantiate the pipeline

   # Define the parameters for the grid search
   param_grid = {
      "svm__C": [0.01, 0.1, 1, 10, 100], # The range of C values.
      "svm__gamma": [0.001, 0.01, 0.1, 1, 10], # The range of gamma values. The gamma defines the influence of a single training example.
      "svm__kernel": ["linear", "rbf", "poly", "sigmoid"], # The kernel to use.
   }

   # Perform Grid Search
   grid = GridSearchCV(pipeline, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, verbose=0, n_jobs=-1)
   start_time = time.time() # Start the timer
   grid.fit(train_features, train_labels) # Train the classifier

   # Retrieve the best model
   y_pred = grid.predict(test_features) # Predict the test set
   execution_time = time.time() - start_time # Calculate the execution time
   accuracy = grid.score(test_features, test_labels) # Calculate the accuracy

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN}Support Vector Machine Classification Report for Support Vector Machine:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n")

   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred)
      print(f"{BackgroundColors.GREEN}Support Vector Machine Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n")

   return accuracy, y_pred, {"C": grid.best_params_["svm__C"], "Gamma": grid.best_params_["svm__gamma"], "Kernel": grid.best_params_["svm__kernel"], "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function creates a Multilayer Perceptron classifier and prints the classification report
def grid_search_multilayer_perceptron(train_features, train_labels, test_features, test_labels):
   # Define the parameter grid for the grid search
   param_grid = {
      "alpha": [1e-5, 1e-4, 1e-3], # L2 penalty (regularization term) parameter.
      "hidden_layer_sizes": [(100,), (100, 100), (500, 500, 500, 500)], # Define the number of neurons in each hidden layer.
      "solver": ["adam", "lbfgs"], # The solver for weight optimization.
   }

   # Instantiate the Multilayer Perceptron classifier
   mlp = MLPClassifier(random_state=1, max_iter=2000)

   # Instantiate GridSearchCV
   grid_search = GridSearchCV(mlp, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, n_jobs=-1)

   start_time = time.time() # Start the timer
   grid_search.fit(train_features, train_labels) # Train the classifier with grid search

   # Get the best model from the grid search
   best_clf = grid_search.best_estimator_

   # Predict the test set using the best model
   y_pred = best_clf.predict(test_features)
   execution_time = time.time() - start_time # Calculate the execution time

   # Calculate the accuracy
   accuracy = best_clf.score(test_features, test_labels)

   # Get the best parameters from the grid search
   best_params = grid_search.best_params_

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN}Multilayer Perceptron Classification Report for Multilayer Perceptron:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n") # Print the classification report

   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred)
      print(f"{BackgroundColors.GREEN}Multilayer Perceptron Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n") # Print the confusion matrix

   return accuracy, y_pred, {"Best Parameters": best_params, "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function creates a Random Forest classifier and prints the classification report
def grid_search_random_forest(train_features, train_labels, test_features, test_labels):
   # Define the parameter grid for the grid search
   param_grid = {
      "max_depth": [None, 10, 20, 30], # The maximum depth of the tree.
      "n_estimators": [100, 500, 1000], # The number of trees in the forest. 
   }

   # Instantiate the Random Forest classifier
   rf = RandomForestClassifier(random_state=1)

   # Instantiate GridSearchCV
   grid_search = GridSearchCV(rf, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, n_jobs=-1)

   start_time = time.time() # Start the timer
   grid_search.fit(train_features, train_labels) # Train the classifier with grid search

   # Get the best model from the grid search
   best_clf = grid_search.best_estimator_

   # Predict the test set using the best model
   y_pred = best_clf.predict(test_features)
   execution_time = time.time() - start_time # Calculate the execution time

   # Calculate the accuracy
   accuracy = best_clf.score(test_features, test_labels)

   # Get the best parameters from the grid search
   best_params = grid_search.best_params_

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN}Random Forest Classification Report for Random Forest:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n") # Print the classification report

   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred) # Calculate the confusion matrix
      print(f"{BackgroundColors.GREEN}Random Forest Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n") # Print the confusion matrix

   return accuracy, y_pred, {"Best Parameters": best_params, "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function trains the Naive Bayes classifier and prints the classification report
def grid_search_naive_bayes(train_features, train_labels, test_features, test_labels):
   # Define the parameters for the grid search
   param_grid = {
      "priors": [None, [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]], # Prior probabilities of the classes.
      "var_smoothing": [1e-9, 1e-8, 1e-7, 1e-6, 1e-5], # The var_smoothing parameter is the value added to the variance for calculation stability to avoid division by zero.
   }

   # Instantiate Naive Bayes classifier
   nb = GaussianNB()

   # Instantiate GridSearchCV
   grid = GridSearchCV(nb, param_grid, scoring="accuracy", cv=CROSS_VALIDATION, verbose=0, n_jobs=-1)

   start_time = time.time() # Start the timer
   grid.fit(train_features, train_labels) # Train the classifier
   y_pred = grid.predict(test_features) # Predict the test set
   execution_time = time.time() - start_time # Calculate the execution time
   accuracy = grid.score(test_features, test_labels) # Calculate the accuracy

   if SHOW_CLASSIFICATION_REPORT: # Show the classification report if it is set to True
      print(f"{BackgroundColors.GREEN}Naive Bayes Classification Report for Naive Bayes:\n{BackgroundColors.CYAN}{classification_report(test_labels, y_pred)}{Style.RESET_ALL}", end="\n")

   if SHOW_CONFUSION_MATRIX: # Show the confusion matrix if it is set to True
      conf_matrix = confusion_matrix(test_labels, y_pred) # Calculate the confusion matrix
      print(f"{BackgroundColors.GREEN}Naive Bayes Confusion Matrix:\n{BackgroundColors.CYAN}{conf_matrix}{Style.RESET_ALL}", end="\n\n") # Print the confusion matrix

   return accuracy, y_pred, {"Var Smoothing": grid.best_params_["var_smoothing"], "Priors": grid.best_params_["priors"], "Execution Time": f"{execution_time:.5f} Seconds"} # Return the Accuracy and the Parameters

# This function sort the classifiers by accuracy
def sort_classifiers_execution(classifiers_execution):
   # Sort the classifiers by accuracy and return the sorted dictionary
   return dict(sorted(classifiers_execution.items(), key=lambda item: item[1][0], reverse=True))

# This function prints the execution time of the classifiers
def print_classifiers_execution(sorted_classifiers_execution):
   print(f"\n{BackgroundColors.GREEN}Classifiers Results:{BackgroundColors.CYAN}") # Print the classifiers results

   # loop through the classifiers name, accuracy and parameters
   for classifier, accuracy in sorted_classifiers_execution.items():
      print(f"{BackgroundColors.GREEN}{classifier}: {BackgroundColors.CYAN}{accuracy[0]*100:.2f}%{Style.RESET_ALL}")
      for parameter, value in accuracy[2].items():
         print(f"{BackgroundColors.GREEN}{parameter}: {BackgroundColors.CYAN}{value}{Style.RESET_ALL}")
      print(f"{Style.RESET_ALL}")


# This is the main function. It calls the other functions, building the project workflow
def main():
   print(f"{BackgroundColors.CLEAR_TERMINAL}{BackgroundColors.BOLD}{BackgroundColors.GREEN}Welcome to the Artificial Intelligence Supervised Learning Algorithms Comparison Project!{Style.RESET_ALL}") # Print the welcome message

   # Load the data
   train_features, train_labels, test_features, test_labels = load_data()

   if SHOW_DATASET_INFORMATION: # Show the dataset information if it is set to True
      print_dataset_information(train_features, train_labels, test_features) # Print the dataset information
      dataset_balance(train_labels, test_labels) # Print if the dataset is balanced or not
   
   # Run the classifiers
   classifiers_execution = run_classifiers(train_features, train_labels, test_features, test_labels)

   # Sort the classifiers by execution time
   sorted_classifiers_execution = sort_classifiers_execution(classifiers_execution)

   # Print the execution time
   print_classifiers_execution(sorted_classifiers_execution)

   print(f"{BackgroundColors.BOLD}{BackgroundColors.GREEN}Thank you for using the Artificial Intelligence Supervised Learning Algorithms Comparison Project!{Style.RESET_ALL}") # Print the goodbye message

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
