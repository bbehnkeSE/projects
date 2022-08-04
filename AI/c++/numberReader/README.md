## Number Reader
---

A simple program used to learn about convolutional neural networks using <a href="https://www.sfml-dev.org/">SFML</a>.

The end goal is to write numbers in the drawing area (area above the black line), and have the program print the number you drew below the black line. Currently, you can draw and save the image into a buffer by pressing the number keys, and the area below the black line will display the buffer labels.

Example:

<img style="display: block;
            margin-right: auto;
            width: 30%" 
      src="https://github.com/bbehnkeSE/projects/blob/main/AI/c%2B%2B/numberReader/resources/examples/generating_training_data.PNG">
</img>

In the above image, pressing enter will save the screenshots previously taken for a 2, 3, 1, 7, 8, 5, and a 4. Pushing the "4" number key will save a screenshot of the "4" currently in the drawing area into the buffer.

Note: As the program currently has no way of knowing what you draw, you could also push the "1" key to save that "4" as a "1." For this reason, pushing the "U" key will remove the previous screenshot from the buffer in case of a mistake.

Provided training images must be unzipped first.

Controls:
* Esc - Closes window.
* Backspace - Clears screen.
* LMB - Draw on the screen.
* P - Take screenshot and save it in doc/screenshot directory.
* Num keys - Takes screenshot of drawing area and stores it in a buffer.
  * Ex. If you drew a "1," push the "1" key to save the screenshot as a "1." This will be used as the correct value when it comes time to train the neural network.
* U - Removes last screenshot from the buffer.
* Enter/Return - Saves screenshot in buffer to "resources/training_images" directory as a .png file.
  * First number of the .png filename is the correct value for training purposes.
