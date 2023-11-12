import matplotlib.pyplot as plt # Import matplotlib
import numpy as np # Import numpy
import os # Import os
from sklearn.cluster import KMeans # Import KMeans
from sklearn.model_selection import train_test_split # Import train_test_split
from sklearn.neighbors import KNeighborsClassifier # Import KNeighborsClassifier
from sklearn.preprocessing import minmax_scaler # Import MinMaxScaler
from colorama import Style  # For coloring the terminal

# Macros:
class BackgroundColors:  # Colors for the terminal
   CYAN = "\033[96m"  # Cyan
   GREEN = "\033[92m"  # Green
   YELLOW = "\033[93m"  # Yellow
   RED = "\033[91m"  # Red
   BOLD = "\033[1m"  # Bold
   UNDERLINE = "\033[4m"  # Underline
   CLEAR_TERMINAL = "\033[H\033[J"  # Clear the terminal

