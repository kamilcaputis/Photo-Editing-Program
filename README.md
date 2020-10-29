![Untitled-Artwork (1)](https://user-images.githubusercontent.com/57468149/97618392-56ddf200-19f5-11eb-8939-3065402f24a6.png)
# Photo Editing Program
This project was created using c++. The purpose of this project is to explore how basic photo editing features work. It includes functions such as multiply, overlay, screen, and more.

# Implementation
The program reads .tga files and outputs modified .tga files. The modified files are compared to example output files. Gimp can be used to view the raw and modified files as well as the example outputs. 

* PIXEL CLASS:
The pixel class contains the red, blue and green values of each pixel in the image. Each image is represented as a vector of pixels 

* HEADER CLASS:
the header class reads the fundamental data about each image and stores it for writing once the pixels are modified. This data includes: id length, width, height, bits per pixel, and more.

* MAIN CLASS:
contains the implementation of all the functions and test cases. The main function calls all the test cases.

# Created with
Visual Studio and Gimp
