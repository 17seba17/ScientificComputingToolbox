# SCIENTIFIC COMPUTING TOOLBOX
## A project by Nicola Sebastianutto (nicola.sebastianutto@gmail.com or NICOLA.SEBASTIANUTTO@studenti.units.it) and Federico Cernaz (FEDERICO.CERNAZ@studenti.units.it)

This **Scientific Computing Toolbox** implements two main modules: one for analyzing datasets in both <kbd>JSON</kbd> and <kbd>CSV</kbd> formats, and a second module that implements explicit Runge-Kutta methods, used for solving ordinary differential equations (ODEs) of the form $\frac{dx}{dt}=f(x,t)$.

***

## Instructions for Compilation, Libraries, and Running

To access the project repository on GitHub, ensure Git is installed on your system. From the project's root directory, download the necessary libraries using the following instructions:

**Eigen**
```bash
 git clone https://gitlab.com/libeigen/eigen.git
```

**MuParserX**
```bash
 git clone git@github.com:beltoforion/muparserx.git
```
To build <kbd>muparserx</kbd>, use the following instructions:
```bash
cd muparserx
mkdir build
cd build/
cmake ..
make
```

**Boost**
Download the **Boost** library from the following link: https://www.boost.org/releases/latest/

Unzip the file:
```bash
tar -xzf boost_1_89_0.tar.gz
```
Copy the unzipped library to the installation path */usr/local/*:
```bash
sudo cp -r boost_1_89_0 /usr/local
```

# Building the Project

Use the following commands to build the project:
```bash
cmake -S . -B build -G Ninja
cmake --build build
```

# Running the Project

To run the statistical analysis example, execute the following command, providing the path to the dataset and the desired output filename:
```bash
./build/apps/data_analysis_app dataset.csv output_file.txt
```
To demonstrate the second module (ODE Solver), run:
```bash
./build/apps/ode_solver_app
```
# Module Descriptions



# Member contributions 




# Discussion of Design Decisions

## First Module

In the first module, we structured the procedure by assigning each major processing step to a dedicated class: <kbd>RawData</kbd>, <kbd>ProcessedData</kbd>, and <kbd>DataAnalyser</kbd>.

The <kbd>RawData</kbd> class handles data extraction from the source file. Since individual cells can be numerical, categorical, or missing, we utilize <kbd>std::optional</kbd> to manage NA (missing) values, and <kbd>std::variant</kbd> to hold both categorical and numerical types within a single cell. Each column object stores essential metadata, including its variable name, a boolean flag indicating if the variable is categorical, and, for categorical variables, a list of possible labels.

To support various input formats, <kbd>RawData</kbd> is implemented as a virtual class. This design allows for polymorphism, ensuring the program can dynamically access the appropriate <kbd>readTable()</kbd> implementation at runtime. Specifically, the <kbd>RawDataJSON</kbd> class leverages the external <kbd>Boost</kbd> library for simpler and more efficient JSON parsing and data extraction.

The subsequent class is <kbd>ProcessedData</kbd>, which is responsible for imputing missing values (using the mean for numerical data and the mode/most frequent value for categorical data). This process generates an <kbd>Eigen</kbd> matrix, chosen for its efficiency and ability to perform fast mathematical operations. Furthermore, categorical values are transformed into their corresponding numerical indices, ensuring the resulting matrix contains only numerical entries.

Finally, the <kbd>DataAnalyser</kbd> utilizes the power of the <kbd>Eigen</kbd> library to quickly compute various statistical analyses on the cleaned numerical data.

## Second Module

Module two was designed with a general approach for implementing Explicit Runge–Kutta methods.

One class is dedicated to defining the Butcher tableau and verifying its consistency. A separate class utilizes the <kbd>MuParserX</kbd> library, allowing us to easily parse and compute the solutions for specific differential functions. Finally, the <kbd>"Ode.hpp"</kbd> file integrates these two components to execute the overall algorithm. This modular and general design easily facilitated the implementation of specific cases, such as the midpoint method and RK4.

# Results



https://www.kaggle.com/datasets/sudarshan24byte/online-food-dataset
