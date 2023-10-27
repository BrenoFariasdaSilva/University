#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Exemplo do Algoritmo k-NN para scikit-learn.
@author: diegobertolini
"""
import sys
import numpy as np
from sklearn import svm
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report
from sklearn.neural_network import MLPClassifier
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.model_selection import GridSearchCV, train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification
from sklearn import tree

def main():

        # load data
        print ("Loading data...")
        #tr = np.loadtxt(dataTr) ;
        #ts = np.loadtxt(dataTs) ;
        tr = np.loadtxt('treinamento.txt') ;
        ts = np.loadtxt('teste.txt');
        y_test  = ts[:,132]
        y_train = tr[:,132]
        X_train = tr[:, 1 : 132]
        X_test  = ts[:, 1 : 132]
        
 # k-NN classifier
#        from sklearn.metrics import classification_report
#        neigh = KNeighborsClassifier(n_neighbors=1, metric='euclidean')
#        neigh.fit(X_train, y_train)
#        #neigh.score(X_test, y_test)
#        print(classification_report(y_test, neigh.predict(X_test)))
        
###SVM com Grid search
#        C_range = 2. ** np.arange(-5,15,2)
#        gamma_range = 2. ** np.arange(3,-15,-2)
#        k = [ 'rbf']
#        # instancia o classificador, gerando probabilidades
#        srv = svm.SVC(probability=True, kernel='rbf')
#        ss = StandardScaler()
#        pipeline = Pipeline([ ('scaler', ss), ('svm', srv) ])
#        
#        param_grid = {
#            'svm__C' : C_range,
#            'svm__gamma' : gamma_range
#        }
#        
#        # faz a busca
#        grid = GridSearchCV(pipeline, param_grid, n_jobs=-1, verbose=True)
#        grid.fit(X_train, y_train)
#        
#        # recupera o melhor modelo
#        model = grid.best_estimator_
#        print(classification_report(y_test, model.predict(X_test)))
#        
### MLP 
        scaler = StandardScaler()
        X_train = scaler.fit_transform(X_train)
        X_test = scaler.fit_transform(X_test)
        
        clf = MLPClassifier(solver='adam', alpha=1e-5, hidden_layer_sizes=(20), random_state=1)
        clf.fit(X_train, y_train)
        print(clf.predict(X_test))
        print(classification_report(y_test, clf.predict(X_test)))

## Random Forest Classifier
        #X, y = make_classification(n_samples=1000, n_features=4, n_informative=2, n_redundant=0, random_state=0, shuffle=False)
#        clf = RandomForestClassifier(n_estimators=10000, max_depth=30, random_state=1)
#        clf.fit(X_train, y_train)  
#        #print(clf.feature_importances_)
#        print(clf.predict(X_test))
#        print(classification_report(y_test, clf.predict(X_test)))
        

### Decision Tree
#        clf = tree.DecisionTreeClassifier()
#        clf.fit(X_train, y_train)
#        print(clf.predict(X_test))
#        print(classification_report(y_test, clf.predict(X_test)))
#        tree.plot_tree(clf)

if __name__ == "__main__":
        main()