#!/bin/env python
# Refs:
# https://storage.googleapis.com/tensorflow/tf-keras-datasets/mnist.npz

from keras.datasets import mnist
import matplotlib.pyplot as plt

(train_images, train_labels), (test_images, test_labels) = mnist.load_data(path='mnist.npz')

print(train_images.shape, train_labels.shape)
print(train_images.dtype)

print(train_labels[0])
plt.imshow(train_images[0], cmap="gray_r")
plt.show()
