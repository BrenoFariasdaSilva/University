from sklearn.cluster import KMeans # For the K-Means clustering algorithm
from sklearn.datasets import load_digits # For loading the dataset files
from sklearn.decomposition import PCA # For the PCA algorithm
from sklearn.preprocessing import StandardScaler # For scaling the data
from sklearn.model_selection import train_test_split # For splitting the data into training and test sets
import matplotlib.pyplot as plt # For plotting the data
import numpy as np # For loading the dataset files

# This function loads the data from the dataset files and returns the training and test sets
def load_data():
    test, train = load_digits(return_X_y=True) # Load the dataset files
    return test, train # Return the training and test sets

# This function filters the data by the given classes
def filter_classes(train, test, classes):
    xc = [] # Create an empty list
    yc = [] # Create an empty list

    # For each class
    for c in classes:
        idxs = test == c # Get the indexes of the current class
        xc.append(train[idxs, :]) # Append the data points of the current class
        yc.extend(test[idxs]) # Append the labels of the current class

    xc = np.concatenate(xc) # Concatenate the data points
    yc = np.array(yc) # Convert the labels to a NumPy array
    return xc, yc # Return the filtered data

# This function splits the data into training and test sets
def split_data(train, test, test_size=0.2):
    # Split the data into training and test sets
    x_train, x_test, y_train, y_test = train_test_split(train, test, test_size=test_size)
    return x_train, x_test, y_train, y_test # Return the training and test sets

# This function scales the data
def scale_data(x_train, x_test):
    ss = StandardScaler() # Create the StandardScaler algorithm
    x_train_scaled = ss.fit_transform(x_train) # Apply the StandardScaler algorithm
    x_test_scaled = ss.transform(x_test) # Apply the StandardScaler algorithm
    return x_train_scaled, x_test_scaled # Return the scaled training and test sets

# This function applies the PCA algorithm
def apply_pca(x_train, x_test, n_components=2):
    # Create the PCA algorithm
    pca = PCA(n_components=n_components) # Create the PCA algorithm
    pca.fit(x_train) # Apply the PCA algorithm
    x_train_pca = pca.transform(x_train) # Apply the PCA algorithm
    x_test_pca = pca.transform(x_test) # Apply the PCA algorithm
    return x_train_pca, x_test_pca # Return the training and test sets

# This function plots the data clusters
def plot_data_clusters(x_train_pca, y_train):
    # For each class
    for digit_class in sorted(list(set(y_train))):
        indexes = y_train == digit_class # Get the indexes of the current class
        # Plot the data points of the current class
        plt.scatter(x_train_pca[indexes, 0], x_train_pca[indexes, 1], label=str(digit_class))
    plt.legend() # Show the legend

# This function applies the K-Means clustering algorithm
def apply_kmeans(x_train_pca, n_clusters=3):
    km = KMeans(n_clusters=n_clusters)  # Create the K-Means clustering algorithm
    km.fit(x_train_pca) # Apply the K-Means clustering algorithm
    return km # Return the K-Means clustering algorithm

# This function plots the cluster centers
def plot_cluster_centers(km):
    # Plot the cluster centers
    plt.scatter(km.cluster_centers_[:, 0], km.cluster_centers_[:, 1], s=100, marker='x')

# This is the main function. It calls the other functions, building the project workflow
def main():
    test, train = load_data() # Load the data

    classes = [0, 5, 8] # Define the classes to be used

    xc, yc = filter_classes(test, train, classes) # Filter the data by the given classes

    x_train, x_test, y_train, y_test = split_data(xc, yc) # Split the data into training and test sets

    x_train_scaled, x_test_scaled = scale_data(x_train, x_test) # Scale the data

    x_train_pca, x_test_pca = apply_pca(x_train_scaled, x_test_scaled) # Apply the PCA algorithm

    plot_data_clusters(x_train_pca, y_train) # Plot the data clusters

    km = apply_kmeans(x_train_pca) # Apply the K-Means clustering algorithm

    plot_cluster_centers(km) # Plot the cluster centers

    plt.show() # Show the plot

# This the boilerplate that calls the main function
if __name__ == "__main__":
    main() # Call the main function
