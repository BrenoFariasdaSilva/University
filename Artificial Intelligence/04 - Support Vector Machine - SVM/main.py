import numpy as np # For loading the dataset files
from sklearn import svm # For the SVM classifier
from sklearn.metrics import classification_report # For the classification report
from sklearn.preprocessing import StandardScaler # For the standard scaler
from sklearn.pipeline import Pipeline # For the pipeline
from sklearn.model_selection import GridSearchCV # For the grid search
from colorama import Style # For coloring the terminal

# Macros:
class backgroundColors: # Colors for the terminal
	CYAN = "\033[96m" # Cyan
	GREEN = "\033[92m" # Green
	YELLOW = "\033[93m" # Yellow
	RED = "\033[91m" # Red

# This function loads the data from the dataset files and returns the training and test sets
def load_data():
    print(f"{backgroundColors.YELLOW}Remember to remove the header line from the dataset files. They should be in the format: {backgroundColors.CYAN}label feature1 feature2 ... featureN{Style.RESET_ALL}")
    print(f"{backgroundColors.GREEN}Loading data...{Style.RESET_ALL}")
    tr = np.loadtxt("./dataset/digits/training/5x5-normalized-pixel_count.txt")
    ts = np.loadtxt("./dataset/digits/test/5x5-normalized-pixel_count.txt")
    test_label = ts[:, 0]  # The first column is the label
    train_label = tr[:, 0]  # The first column is the label
    train_features_values = tr[:, 1:]  # The second column is the feature vector
    test_features_values = ts[:, 1:]  # The second column is the feature vector
    return train_features_values, train_label, test_features_values, test_label

# This function trains a SVM classifier with grid search and prints the classification report
def train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}SVM Classifier with Grid Search:{backgroundColors.CYAN}")
    C_range = 2. ** np.arange(-5, 15, 2) # The range of C values
    gamma_range = 2. ** np.arange(3, -15, -2) # The range of gamma values which defines the influence of a single training example
    k = ["rbf"] # The kernel

    # Instantiate the classifier with probability
    srv = svm.SVC(probability=True, kernel="rbf") # Instantiate the classifier
    ss = StandardScaler() # Instantiate the standard scaler
    pipeline = Pipeline([("scaler", ss), ("svm", srv)]) # Instantiate the pipeline

    # Define the parameters for the grid search
    param_grid = {
        "svm__C": C_range,
        "svm__gamma": gamma_range
    }

    # Perform Grid Search
    grid = GridSearchCV(pipeline, param_grid, n_jobs=-1, verbose=True) # Instantiate the grid search
    grid.fit(train_features_values, train_label) # Train the classifier

    # Retrieve the best model
    model = grid.best_estimator_ # Retrieve the best model
    print(f"{backgroundColors.GREEN}Best parameters set found on development set is {backgroundColors.CYAN}{model.get_params}{Style.RESET_ALL}") # Print the best parameters
    print(f"{classification_report(test_label, model.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This is the main function. It calls the other functions, building the project workflow
def main():
    train_features_values, train_label, test_features_values, test_label = load_data()
    train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label) # Train the SVM classifier with grid search

# This the boilerplate that calls the main function
if __name__ == "__main__":
    main() # Call the main function