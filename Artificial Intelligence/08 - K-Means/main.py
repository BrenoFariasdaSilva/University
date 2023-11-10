from sklearn.cluster import KMeans
from sklearn.datasets import load_digits
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import numpy as np

x, y = load_digits(return_X_y=True)

classes = [0, 5, 8]

xc = []
yc = []

for c in classes:
    idxs = y == c
    xc.append(x[idxs,:])
    yc.extend(y[idxs])
    
xc = np.concatenate(xc)
yc = np.array(yc)
    
x_train, x_test, y_train, y_test = train_test_split(xc, yc, test_size=0.2)

ss = StandardScaler()
x_train = ss.fit_transform(x_train)
x_test = ss.transform(x_test)

pca = PCA(n_components=2)
pca.fit(x_train)
x_train_pca = pca.transform(x_train)
x_test_pca = pca.transform(x_test)

for digit_class in sorted(list(set(y_train))):
    indexes = y_train == digit_class
    plt.scatter(x_train_pca[indexes,0], x_train_pca[indexes,1], label=str(digit_class))
plt.legend()

km = KMeans(n_clusters=3)
km.fit(x_train_pca)

plt.scatter(km.cluster_centers_[:,0], km.cluster_centers_[:,1], s=100, marker='x')
