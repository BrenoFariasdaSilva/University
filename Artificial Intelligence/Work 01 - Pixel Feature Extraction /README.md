<div align="center">
  
# [Pixel Feature Extractor.](https://github.com/BrenoFariasdaSilva/University/tree/main/Artificial%20Intelligence/Work%2001%20-%20Pixel%20Feature%20Extraction%20) <img src="https://github.com/devicons/devicon/blob/master/icons/python/python-original.svg"  width="3%" height="3%">

</div>

<div align="center">
  
---

This Python script reads training and test datasets, splitting each image into sections according to different grid sizes (1x1, 2x2, 3x3, and 5x5), and calculates the number of black and white pixels in each region of the split image. The results are stored in CSV files.
TODO: Normalize the number of pixels by the total number of pixels in the image.

</div>

- [Pixel Feature Extractor. ](#pixel-feature-extractor-)
	- [Prerequisites](#prerequisites)
	- [Execution](#execution)
	- [Configuration](#configuration)
	- [How It Works](#how-it-works)
	- [Functions](#functions)
		- [verify\_output\_directory](#verify_output_directory)
		- [verify\_datasets](#verify_datasets)
		- [create\_output\_file\_header](#create_output_file_header)
		- [process\_each\_image](#process_each_image)
		- [initialize\_pixel\_counter](#initialize_pixel_counter)
		- [count\_pixels](#count_pixels)
		- [write\_pixel\_counters](#write_pixel_counters)
		- [normalize\_data](#normalize_data)
	- [Contributing](#contributing)
	- [License](#license)


## Prerequisites
This code requires the following packages:
- Python 3.x
- colorama (for terminal coloring)
- Pillow (PIL, for image manipulation)
- tqdm (for generating progress bars)

You can install the required packages using pip:

```bash
pip3 install colorama pandas Pillow scikit-learn tqdm
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

## Configuration

You can configure the script by modifying the following constants in the script:

- `DATASETS_PATH`: Define the paths to your test and training datasets.
- `OUTPUT_PATH`: Define the output directory where CSV files will be saved.
- `SPLITS`: Define the grid sizes you want to use for feature extraction (e.g., 1x1, 2x2, 3x3, 5x5).
- `IMAGE_FILE_FORMAT`: Define the image file format (e.g., ".bmp").
- `OUTPUT_FILE_FORMAT`: Define the output CSV file format (e.g., ".csv").

## How It Works

The Pixel Feature Extractor performs the following steps:

1. **Directory Verification**: The script verifies the existence of required directories for both the test and training datasets. If any of these directories are missing, it displays an error message and exits.

2. **Grid Splitting**: The script loops through different grid sizes, such as 1x1, 2x2, 3x3, and 5x5, and processes each dataset (test and training) separately.

3. **Output Directory Creation**: For each grid size and dataset, the script creates an output directory structure if it doesn't exist.

4. **Header Creation**: It generates a header for the output CSV file, specifying columns for grid cell labels, digit class, and image name.

5. **Image Processing**: For each image in the dataset, the script opens the image, initializes a pixel counter dictionary, and counts the number of black and white pixels in each grid cell.

6. **Data Writing**: The pixel counts are written as a line in the output CSV file, creating a structured record for each image.

7. **Data Normalization**: After processing all images for a specific grid size, the script normalizes the pixel count data using Min-Max scaling.

8. **Progress Bar**: A progress bar is displayed for each grid size, indicating the progress of image processing.

## Functions

### verify_output_directory

- **Input**: `output_path` (The path for the output directory)
- **Output**: None
- **Purpose**: Verifies if the output directory exists; if not, it creates the output directory and subdirectories for each dataset (test and training).

### verify_datasets

- **Input**: None
- **Output**: True if the datasets exist, False otherwise
- **Purpose**: Verifies the existence of test and training datasets. If any dataset is missing, it displays an error message and exits.

### create_output_file_header

- **Input**: `x_split` (The number of splits in the x-axis), `y_split` (The number of splits in the y-axis), `output_file_path` (The path for the output file)
- **Output**: `output_file` (The output file object)
- **Purpose**: Creates the header for the output CSV file, specifying columns for grid cell labels, digit class, and image name. It returns the output file object for writing data.

### process_each_image

- **Input**: `image_path` (The path for the image), `x_grid` (The number of splits in the x-axis), `y_grid` (The number of splits in the y-axis), `output_file` (The output file object), `pixels_counter` (A dictionary for storing the number of black and white pixels in each split)
- **Output**: None
- **Purpose**: Opens each image in a digit class, counts black and white pixels in each grid cell, and writes the pixel counts to the output file.

### initialize_pixel_counter

- **Input**: `x_grid` (The number of splits in the x-axis), `y_grid` (The number of splits in the y-axis)
- **Output**: `pixels_counter` (A dictionary for storing the number of black and white pixels in each split)
- **Purpose**: Initializes the pixel counter dictionary, creating entries for each grid cell.

### count_pixels

- **Input**: `image` (The image), `x_grid` (The number of splits in the x-axis), `y_grid` (The number of splits in the y-axis), `pixels_counter` (A dictionary for storing the number of black and white pixels in each split)
- **Output**: `pixels_counter` (A dictionary for storing the number of black and white pixels in each split)
- **Purpose**: Counts the number of black and white pixels in each split of the image and updates the pixel counter dictionary accordingly.

### write_pixel_counters

- **Input**: `output_file` (The output file object), `image_path` (The path for the image), `pixels_counter` (A dictionary for storing the number of black and white pixels in each split), `x_grid` (The number of splits in the x-axis), `y_grid` (The number of splits in the y-axis)
- **Output**: None
- **Purpose**: Writes the pixel counters for each split, digit class, and image name to the output file.

### normalize_data

- **Input**: `output_file_path` (The path for the output file)
- **Output**: None
- **Purpose**: Normalizes the data in the output CSV file using Min-Max scaling for columns after "Image Name."

	#### Why it is Necessary to Normalize the Data

	Normalization is essential for the following reasons:

	1. **Consistent Scale**: Normalizing the data ensures that the pixel count values are on a consistent scale. This is crucial when working with machine learning algorithms that are sensitive to the magnitude of input features. Non-normalized data can lead to poor model performance due to the differences in the scale of the input features, for example, weights in kilograms and heights in centimeters. If you had the weight in grams in the same dataset, the model would be more likely to give more importance to the weight in grams than to the weight in kilogram, as the weight in grams has a higher value.

	2. **Improved Model Performance**: Many machine learning models perform better when the input features are on a similar scale. Normalization helps prevent features with larger values from dominating the learning process and doing this in this step makes us save time in the model training process, as it won't be necessary to normalize the data before training the model.

	3. **Comparability**: Normalized data allows for better comparability between different images and datasets. It ensures that pixel count values are comparable regardless of the image's size or complexity.

	By normalizing the pixel count data, we make it more suitable for further analysis, feature extraction, or machine learning tasks, ultimately leading to more accurate and meaningful results.

## Contributing
Code improvement recommendations are very welcome, but keep in mind that many exercises will be very simple, with a lot of room for improvement, after all here is all the history of my learning progress.

If you have any questions, feel free to open an issue or contact me.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
