import numpy as np
from sklearn import tree
from sklearn import svm
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.model_selection import GridSearchCV
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

# This function trains a k-NN classifier and prints the classification report
def train_knn(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}K-NN Classifier:{backgroundColors.CYAN}")
    neigh = KNeighborsClassifier(n_neighbors=1, metric='euclidean')
    neigh.fit(train_features_values, train_label)
    print(f"{classification_report(test_label, neigh.predict(test_features_values))}{Style.RESET_ALL}")

# This function trains a SVM classifier with grid search and prints the classification report
def train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}SVM Classifier with Grid Search:{backgroundColors.CYAN}")
    C_range = 2. ** np.arange(-5, 15, 2)
    gamma_range = 2. ** np.arange(3, -15, -2)
    k = ['rbf']

    # Instantiate the classifier with probability
    srv = svm.SVC(probability=True, kernel='rbf')
    ss = StandardScaler()
    pipeline = Pipeline([('scaler', ss), ('svm', srv)])

    param_grid = {
        'svm__C': C_range,
        'svm__gamma': gamma_range
    }

    # Perform Grid Search
    grid = GridSearchCV(pipeline, param_grid, n_jobs=-1, verbose=True)
    grid.fit(train_features_values, train_label)

    # Retrieve the best model
    model = grid.best_estimator_
    print(f"{classification_report(test_label, model.predict(test_features_values))}{Style.RESET_ALL}")

# This function trains a decision tree classifier and prints the classification report
def train_decision_tree(train_features_values, train_label, test_features_values, test_label):
    print(f"{backgroundColors.GREEN}Decision Tree Classifier:{backgroundColors.CYAN}")
    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(train_features_values, train_label)
    print(f"{classification_report(test_label, clf.predict(test_features_values))}{Style.RESET_ALL}")

def main():
    train_features_values, train_label, test_features_values, test_label = load_data()
    train_knn(train_features_values, train_label, test_features_values, test_label)
    train_svm_with_grid_search(train_features_values, train_label, test_features_values, test_label)
    train_decision_tree(train_features_values, train_label, test_features_values, test_label)

if __name__ == "__main__":
    main() # Call the main function