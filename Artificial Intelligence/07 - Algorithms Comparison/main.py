import numpy as np # For the data manipulation
from colorama import Style # For coloring the terminal
from sklearn import svm # For the SVM classifier
from sklearn import tree # For the decision tree classifier
from sklearn.ensemble import RandomForestClassifier # For the random forest classifier
from sklearn.metrics import classification_report # For the classification report
from sklearn.model_selection import GridSearchCV # For the grid search
from sklearn.neighbors import KNeighborsClassifier # For the k-NN classifier
from sklearn.neural_network import MLPClassifier # For the MLP classifier
from sklearn.pipeline import Pipeline # For the pipeline
from sklearn.preprocessing import StandardScaler # For the standard scaler

# Macros:
class backgroundColors: # Colors for the terminal
    CYAN = "\033[96m" # Cyan
    GREEN = "\033[92m" # Green
    YELLOW = "\033[93m" # Yellow
    RED = "\033[91m" # Red
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

# This function trains a k-NN classifier and prints the classification report
def train_knn(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}1º K-NN Classifier:{backgroundColors.CYAN}")
    neigh = KNeighborsClassifier(n_neighbors=1, metric="euclidean") # Instantiate the classifier
    neigh.fit(train_features_values, train_label) # Train the classifier
    print(f"{classification_report(test_label, neigh.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This function trains a SVM classifier with grid search and prints the classification report
def train_decision_tree(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}2º Decision Tree Classifier:{backgroundColors.CYAN}")
    clf = tree.DecisionTreeClassifier() # Instantiate the classifier
    clf.fit(train_features_values, train_label) # Train the classifier
    print(clf.predict(test_features_values)) # Print the predictions
    print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This function trains a SVM classifier with grid search and prints the classification report
def train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}3º SVM Classifier with Grid Search:{backgroundColors.CYAN}")
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
    print(f"{classification_report(test_label, model.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This function trains a SVM classifier with grid search and prints the classification report
def train_multilayer_perceptron(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}4º Artificial Neural Network/Multilayer Perceptron Classifier:{backgroundColors.CYAN}")
    scaler = StandardScaler() # Instantiate the standard scaler
    train_features_values = scaler.fit_transform(train_features_values) # Scale the training features
    test_features_values = scaler.fit_transform(test_features_values) # Scale the test features
    clf = MLPClassifier(solver="adam", alpha=1e-5, hidden_layer_sizes=(500, 500, 500, 500), random_state=1) # Instantiate the classifier
    clf.fit(train_features_values, train_label) # Train the classifier
    print(clf.predict(test_features_values)) # Print the predictions
    print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This function trains a SVM classifier with grid search and prints the classification report
def train_random_forest(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}5º Random Forest Classifier:{backgroundColors.CYAN}")
    clf = RandomForestClassifier(n_estimators=10000, max_depth=30, random_state=1) # Instantiate the classifier
    clf.fit(train_features_values, train_label) # Train the classifier
    print(clf.predict(test_features_values)) # Print the predictions
    print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}") # Print the classification report

# This is the main function. It calls the other functions, building the project workflow
def main():
    train_features_values, train_label, test_features_values, test_label = load_data() # Load the data
    train_knn(train_features_values, train_label, test_features_values, test_label) # Train the K-NN classifier
    train_decision_tree(train_features_values, train_label, test_features_values, test_label) # Train the Decision Tree classifier
    train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label) # Train the SVM classifier
    train_multilayer_perceptron(train_features_values, train_label, test_features_values, test_label) # Train the ANN - Multilayer Perceptron classifier
    train_random_forest(train_features_values, train_label, test_features_values, test_label) # Train the Random Forest classifier

# This the boilerplate that calls the main function
if __name__ == "__main__":
    main() # Call the main function