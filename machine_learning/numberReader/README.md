# Number Reader

A simple program used to learn about convolutional neural networks using <a href="https://www.sfml-dev.org/">SFML</a> and <a href="https://www.tensorflow.org/">Tensorflow</a>.

The end goal is to write numbers in the drawing area (area above the black line), and have the program print the number you drew below the black line. Currently, you can draw and save the image into a buffer by pressing the number keys, and the area below the black line will display the buffer labels.

Example:

<img style="display: block;
            margin-right: auto;
            width: 30%" 
      src="https://github.com/bbehnkeSE/projects/blob/main/machine_learning/numberReader/resources/examples/generating_training_data.PNG">
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
* Enter/Return - Saves screenshot(s) in buffer to "resources/training_images" directory as a .png file.
  * First number of the .png filename is the correct value for training purposes.
---

## Training the Model
The model was trained by passing approximately 10,000 images, 1,000 per digit between 0 and 9, through a Tensorflow convolutional neural network. The data was split into 6,733 training images (2/3rds) and 3,317 test images (1/3rd). Before training, the image dimensions had to be reduced from 200 x 200 x 4 to 200 x 200 x 1 due to the computational limitation of my home computer. This resulted in the plot below:

<img style="display: block;
            margin-right: auto;
            width: 30%" 
      src="https://github.com/bbehnkeSE/projects/blob/main/machine_learning/numberReader/resources/examples/training_image.PNG">
</img>

The network was comprised of three convolutional layers, the first two followed by max pooling layers, then the data was flattened before a dense layer followed by the output layer. The activation function used was the Rectified Linear Unit (ReLU) function.

```
  model = keras.models.Sequential()
  model.add(keras.layers.Conv2D(32, (4, 4), activation='relu', input_shape=(200, 200, 1)))
  model.add(keras.layers.MaxPooling2D((2, 2)))
  model.add(keras.layers.Conv2D(64, (3, 3), activation='relu'))
  model.add(keras.layers.MaxPooling2D((2, 2)))
  model.add(keras.layers.Conv2D(64, (3, 3), activation='relu'))
  model.add(keras.layers.Flatten())
  model.add(keras.layers.Dense(64, activation='relu'))
  model.add(keras.layers.Dense(10))
```

Finally, the model was compiled using the Adam optimizer and used Tensorflow's Sparse Categorical Crossentropy loss function.

```
  model.compile(
    optimizer='adam',
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    metrics=['accuracy']
  )
```
---

## Results

Fitting the model over 10 epochs resulted in a training accuracy of ~99.4% and a validation accuracy of 72.5%.

<img style="display: block;
            margin-right: auto;
            width: 30%" 
      src="https://github.com/bbehnkeSE/projects/blob/main/machine_learning/numberReader/resources/examples/training_results.PNG">
</img>

I suspect the overfitting of the model was due to two factors:
1. The relatively small size of the dataset used to train the model
2. All of the numbers were written by me over the course of a few hours, leading to relatively few differences between the digits, save for their position on the image
   
Overall, I am happy with the results of the model, though may spend more time generating a more robust training dataset to improve the validation accuracy further.