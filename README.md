Group 2 C project-
Making a C programming tool to convert LZW compressed GIF image to 24-bit BMP image and rotate it by 90 degrees to right.

Group members-
IMT2020007 Yerra Niteesh Reddy
IMT2020105 Rakshit Sanjay Bang
IMT2020512 Aakash Khot
IMT2020523 Kedar Yogesh Deshpande
IMT2020537 Yash Mogal
IMT2020543 Rithvik Ramasani
IMT2020550 Attuluri Yathin Kumar

Guidelines for use-
The tool works for the two images given in the folder perfectly.

It may not work properly for the images which are interlaced, edited(like resized etc) or too big in size.

We have observed that whenever any edited image is used its given color data does not match with what it should have been, hence LZW decoder gives wrong indexes.
All the non-animated GIFs that we could find seemed to be edited as its own data contradicted itself.
The source_image1 is a pure gif image(Hence it works).

Converting source_image1.gif given in the folder clearly shows the image is rotated.
The LZW decoder function used here is fully created by our group member (before we were given help by TA Shyam Bhaiya) as it was difficult to change our code files to use the ready-made tool.

Make the executable file using command make my_project
To run the tool use- ./my_project < name of the image file >
e.g- ./my_project source_image1.gif
Check the folder to find the output image with name destination_image.

Contibution by each group member-
1. IMT2020007 Yerra Niteesh Reddy- Reading the header and logical screen descriptor of GIF using structs.
2. IMT2020105 Rakshit Sanjay Bang- Creating a function to rotate by 90 degrees the given 2d array containing pixel color indexes.
3. IMT2020512 Aakash Khot- Creating function for null padding in BMP.
4. IMT2020523 Kedar Yogesh Deshpande- Creating an algorithm to take variable size code and decode the color indexes using LZW method. Combining all code files to transfer appropriate data to BMP from GIF.
5. IMT2020537 Yash Mogal- Creating structs for BMP file header.
6. IMT2020543 Rithvik Ramasani- Reading and storing Global and Local color table of GIF.
7. IMT2020550 Attuluri Yathin Kumar- Creating structs for BMP image header.
