<div align="center">
  
# [K-NN Digits Classification.](https://github.com/BrenoFariasdaSilva/University/tree/main/Artificial%20Intelligence/Work%2002%20-%20K-NN%20Digits%20Classification) <img src="https://github.com/devicons/devicon/blob/master/icons/python/python-original.svg"  width="3%" height="3%">

</div>

<div align="center">
  
---

This Python script reads training and test datasets that were gerenated by [Pixel Feature Extractor](https://github.com/BrenoFariasdaSilva/University/tree/main/Artificial%20Intelligence/Work%2001%20-%20Pixel%20Feature%20Extraction%20), and uses the K-Nearest Neighbors algorithm to classify the digits in the test dataset. The execution will generate a CSV file with the results of the classification with many different K values (1, 3, 5, 7, 9, 11, 13, 15, 17, 19), Training dataset sizes (0.25, 0.5, 1) and Grid sizes (1x1, 2x2, 3x3, 5x5).

</div>

- [K-NN Digits Classification. ](#k-nn-digits-classification-)
  - [Prerequisites](#prerequisites)
  - [Execution](#execution)
  - [Configuration Variables](#configuration-variables)
    - [Dataset](#dataset)
  - [K-NN Parameters](#k-nn-parameters)
  - [How It Works](#how-it-works)
    - [Function Explanations](#function-explanations)
  - [Results](#results)
  - [Contributing](#contributing)
  - [License](#license)


## Prerequisites
This code requires the following packages:
- Python 3.x
- atexit (for handling program exit)
- colorama (for terminal coloring)
- pandas (for data manipulation)
- tqdm (for generating progress bars)


You can install the required packages using pip:

```bash
pip3 install colorama pandas tqdm
# or
make dependencies
```

## Execution
In order to run the script, you must have a training dataset and a test dataset and must have already installed the code requirements. The script can be executed as follows:

```bash
make
# or
clear; time python3 main.py
```

## Configuration Variables
You can configure the script by modifying the following constants in the script:

### Dataset
The script uses two datasets for digit classification:

- **Training Dataset:** Contains images of digits used for training the K-NN model.
- **Test Dataset:** Contains images of digits used for testing the K-NN model.

Ensure that you have both datasets available in the specified paths before running the script.

## K-NN Parameters
The script allows you to customize the following K-NN parameters:


- `TRAINING_DATASET_SIZE`: Define the training dataset size you want to use for classification (e.g., 0.25, 0.5, 1). Choose a real number between 0 and 1.
- `NEIGHBOURS_VALUES`: Define the K values you want to use for classification (e.g., 1, 3, 5, 7, 9, 11, 13, 15, 17, 19). Note that the K value must be an odd number and can't be higher than the number of images in the training dataset.
- `SPLITS`: Define the grid sizes you want to use for feature extraction (e.g., 1x1, 2x2, 3x3, 5x5). You are able to choose any number, as long as it is in this four options that are available.

Feel free to adjust these parameters to explore the behavior of the K-NN algorithm for digit classification.


## How It Works

This Python script implements the K-Nearest Neighbors (K-NN) algorithm for digit classification. It performs the following steps:

1. **Dataset Verification:**
   - The script verifies the existence of the test and training datasets in the specified paths. If any dataset is missing, it displays an error message and exits.

2. **Output Directory Setup:**
   - It checks if the output directory exists; if not, it creates the directory to store result files.

3. **Results Initialization:**
   - The results dictionary is initialized to store accuracy and other metrics for different K values, feature extractor splits, and training dataset sizes.

4. **Dataset Processing:**
   - The script processes the datasets for various configurations:
     - Different K values (neighborhood sizes).
     - Different feature extractor splits (e.g., 1x1, 2x2, 3x3).
     - Different training dataset sizes (e.g., 25%, 50%, 100%).
   - For each configuration, it calculates the accuracy of the K-NN algorithm by comparing predicted labels with actual labels.

5. **Results Recording:**
   - The script records the accuracy results for each configuration in an output CSV file, including information about the K value, feature extractor split, and training dataset size.

6. **Results Sorting:**
   - The recorded results are sorted in descending order of accuracy in the output CSV file.

7. **Sound Notification:**
   - When the script finishes execution, it plays a notification sound to indicate completion (only if a sound file exists and the appropriate command is available for the operating system).

8. **Command-Line Execution:**
   - You can run the script from the command line to perform digit classification using the K-NN algorithm. Simply execute `python k_nn_digits_classification.py`.

This script offers flexibility in exploring different K values, feature extractor splits, and training dataset sizes to evaluate the performance of the K-NN algorithm for digit classification.


### Function Explanations

1. **verify_datasets():**
   - *Brief:* This function verifies if the test and training datasets exist.
   - *Returns:* `True` if the datasets exist, `False` otherwise.

2. **verify_output_directory(output_path):**
   - *Brief:* Verifies if the output directory exists; if not, it creates the output directory.
   - *Parameters:*
     - `output_path`: The path for the output directory.

3. **initialize_results():**
   - *Brief:* Initializes the results dictionary.
   - *Returns:* The results dictionary.

4. **process_datasets(results):**
   - *Brief:* Processes the datasets, applying the K-NN algorithm with different parameters and generating results.
   - *Parameters:*
     - `results`: The results dictionary.
   - *Returns:* The updated results dictionary.

5. **read_datasets(x_split, y_split, training_dataset_size):**
   - *Brief:* Reads and prepares the training and test datasets.
   - *Parameters:*
     - `x_split`: The x split for the feature extractor.
     - `y_split`: The y split for the feature extractor.
     - `training_dataset_size`: The size of the training dataset.
   - *Returns:* The training dataset and the test dataset.

6. **process_test_dataset(training_dataset, test_dataset, neighbours_value, x_split, y_split, training_dataset_size, results):**
   - *Brief:* Processes each test dataset row, calculating the Euclidean distance between the test dataset row and the training dataset.
   - *Parameters:*
     - `training_dataset`: The training dataset.
     - `test_dataset`: The test dataset.
     - `neighbours_value`: The K value for the K-NN algorithm.
     - `x_split`: The x split for the feature extractor.
     - `y_split`: The y split for the feature extractor.
     - `training_dataset_size`: The size of the training dataset.
     - `results`: The results dictionary.
   - *Returns:* The updated results dictionary.

7. **most_common_element(nearest_neighbours):**
   - *Brief:* Finds the most common element in a list.
   - *Parameters:*
     - `nearest_neighbours`: The list.
   - *Returns:* The most common element in the list.

8. **validate_results(results, neighbours_value, x_split, y_split, training_dataset_size, test_dataset_row, most_frequent_label):**
   - *Brief:* Validates the results by comparing the predicted label to the actual label (Digit Class).
   - *Parameters:*
     - `results`: The results dictionary.
     - `neighbours_value`: The K value for the K-NN algorithm.
     - `x_split`: The x split for the feature extractor.
     - `y_split`: The y split for the feature extractor.
     - `training_dataset_size`: The size of the training dataset.
     - `test_dataset_row`: The current test dataset row.
     - `most_frequent_label`: The most frequent label from the K nearest neighbors.

9. **write_results(results):**
   - *Brief:* Loops through the results dictionary and calls the `write_results_to_csv` function.
   - *Parameters:*
     - `results`: The results dictionary.
   - *Returns:* The path for the output file.

10. **initialize_output_file():**
    - *Brief:* Initializes the output file (creates the output file and writes the headers).
    - *Returns:* The path for the output file.

11. **write_results_to_csv(results, neighbours_value, x_split, y_split, training_dataset_size, output_file_path):**
    - *Brief:* Appends the results to a CSV file.
    - *Parameters:*
      - `results`: The results dictionary.
      - `neighbours_value`: The K value for the K-NN algorithm.
      - `x_split`: The x split for the feature extractor.
      - `y_split`: The y split for the feature extractor.
      - `training_dataset_size`: The size of the training dataset.
      - `output_file_path`: The path for the output file.

12. **sort_output_file(output_file_path):**
    - *Brief:* Sorts the output file by the accuracy column.
    - *Parameters:*
      - `output_file_path`: The path for the output file.

13. **play_sound():**
    - *Brief:* Defines the command to play a sound when the program finishes.

14. **main():**
    - *Brief:* The main function that orchestrates the execution of the program.

These functions collectively implement the K-NN algorithm for digit classification and manage dataset processing and result generation.

## Results
The script records the following results for different combinations of K values, feature extractor splits, and training dataset sizes:

- **Grid:** Describes the feature extractor split (e.g., 1x1, 2x2).
- **Training Dataset %:** Indicates the percentage of the training dataset used.
- **K Value:** Represents the neighborhood size in the K-NN algorithm.
- **Correct Predictions:** The number of correctly classified digits.
- **Total Predictions:** The total number of digit classifications performed.
- **Accuracy %:** The accuracy of the K-NN model in percentage.

The recorded results are sorted by accuracy, allowing you to identify the most effective K-NN configurations for digit classification.

Explore the results to gain insights into the performance of the K-NN algorithm under different settings.
My best results were for:

<div align="center" style="color: rgba(148, 239, 148, 1);">
Grid = 5x5 <br>
Training Dataset % = 1 <br>
K Value = 1 <br>
Correct Predictions = 974 <br>
Total Predictions = 1000 <br>
Accuracy = 97.4% <br>
</div>

## Contributing
Code improvement recommendations are very welcome and appreciated. If you would like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome here.

If you have any questions, feel free to open an issue or contact me.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
