"""
Example of how to use the k-NN classifier using the scikit-learn library.
"""

import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report
from sklearn.svm import SVC

data_sets = ["digits", "spam", "writer"]
data_set = data_sets[0]

for data_set in data_sets:
	# Load the data
	tr = np.loadtxt(f"./dataset/{data_set}/train.txt");
	ts = np.loadtxt(f"./dataset/{data_set}/test.txt");
	y_test = ts[:,-1]
	y_train = tr[:,-1]
	X_train = tr[:, 1 : -1]
	X_test = ts[:, 1 : -1]
			
	# k-NN classifier
	# Documentation: https://scikit-learn.org/stable/modules/generated/sklearn.neighbors.KNeighborsClassifier.html

	neigh = KNeighborsClassifier(n_neighbors = 20, metric = "euclidean")
	neigh.fit(X_train, y_train)
	print(classification_report(y_test, neigh.predict(X_test)))

	# class_counts = np.bincount(y_train.astype("int64"))

	# # Print the class counts
	# for class_label, count in enumerate(class_counts):
	# 	if count > 0:
	# 		print(f"Classe {class_label}: {count} amostra(s).")