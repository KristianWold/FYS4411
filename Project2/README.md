# Project 2 - An Autoregressive Model for Bosonic Quantum Dots 

<p align="center">
<b><a href="#overview">Overview</a></b>
|
<b><a href="#notebooks">Notebooks</a></b>
|
<b><a href="#usage">Usage </a></b>
|
<b><a href="#credits">Credits</a></b>
|
<b><a href="#license">License</a></b>
</p>
<br>


<img height="700px" align="center" src="latex/figures/hybrid.png?raw=true">

## Overview
The aim of this project is to develop a neural network architecture that manages to reproduce the wave function of
bosons trapped in an external potential. This is achieved with a hybrid model of a DNN and a RNN along with a brute force Metropolis sampler. The autoregressive property of the RNN allows for fast uncorrelated sampling of the position wave functions.
In addition, the behavior of depth, width, dimension, and activation functions are 
examined.

Most of the code is implemented in Jupyter Notebooks located in the `notebooks` directory. Running them will take
a while, but will faithfully reproduce the results presented.

The report itself and associated LaTeX files are available in the `latex` directory.

## Notebooks

There are a couple Jupyter notebooks which contains most of the code as well as plotting code.
Python >=3.8 and Tensorflow are required.

| Notebook | Function                                                                                                          |
| ------                  | --------                                                                                                          |
| `DNN one particle.ipynb` | Implements a proof-of-concept DNN to model the wave function of a single particle|
| `Autoregressive RNN Bosons.ipynb` | Code for the modeling many body systems with a hybrid DNN-RNN model|

## Usage

The code can be run by running the Jupyter notebooks.

The rapport and all supporting material is located in the `latex` directory.
The document is compatible with LuaTeX and XeLaTeX, not PdfLaTeX.

## Credits
The contributors of this project are Erlend Lima and Kristian Wold.

## License
This project is licensed under the terms of the **MIT** license.
You can check out the full license [here](../LICENSE)
