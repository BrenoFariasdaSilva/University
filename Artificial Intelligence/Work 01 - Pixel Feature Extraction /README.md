<div align="center">
  
# [Pixel Feature Extractor](https://github.com/BrenoFariasdaSilva/University/tree/main/Artificial%20Intelligence/Work%2001%20-%20Pixel%20Feature%20Extraction%20) <img src="https://github.com/devicons/devicon/blob/master/icons/python/python-original.svg"  width="3%" height="3%">

</div>

<div align="center">
  
---

This Python script reads training and test datasets, splitting each image into sections according to different grid sizes (1x1, 2x2, 3x3, and 5x5), and calculates the number of black and white pixels in each region of the split image. The results are stored in CSV files.
TODO: Normalize the number of pixels by the total number of pixels in the image.

</div>

- [Pixel Feature Extractor ](#pixel-feature-extractor-)
	- [Prerequisites](#prerequisites)
	- [Execution](#execution)
	- [Configuration](#configuration)
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
pip install colorama Pillow tqdm
# or
make dependencies
```

## Execution
In order to run the script, you must have a training dataset and a test dataset and must have already installed the code requirements. The script can be executed as follows:

```bash
make
# or
clear; python3 main.py
```

## Configuration

You can configure the script by modifying the following constants in the script:

- `DATASETS_PATH`: Define the paths to your test and training datasets.
- `OUTPUT_PATH`: Define the output directory where CSV files will be saved.
- `SPLITS`: Define the grid sizes you want to use for feature extraction (e.g., 1x1, 2x2, 3x3, 5x5).
- `IMAGE_FILE_FORMAT`: Define the image file format (e.g., ".bmp").
- `OUTPUT_FILE_FORMAT`: Define the output CSV file format (e.g., ".csv").

## Contributing
Code improvement recommendations are very welcome, but keep in mind that many exercises will be very simple, with a lot of room for improvement, after all here is all the history of my learning progress.

If you have any questions, feel free to open an issue or contact me.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
