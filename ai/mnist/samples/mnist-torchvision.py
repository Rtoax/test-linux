#!/bin/env python
# Refs:
# - http://docs.pytorch.org/vision/main/_modules/torchvision/datasets/mnist.html
# - https://colab.research.google.com/github/skorch-dev/skorch/blob/master/notebooks/MNIST-torchvision.ipynb
# - https://github.com/pytorch/examples/blob/main/mnist/

from itertools import islice

import torch
import torchvision
from torchvision.datasets import MNIST
import numpy as np
import matplotlib.pyplot as plt

def plot_example(X, y, n=5):
    """Plot the images in X and their labels in rows of `n` elements."""
    fig = plt.figure()
    rows = len(X) // n + 1
    for i, (img, y) in enumerate(zip(X, y)):
        ax = fig.add_subplot(rows, n, i + 1)
        ax.imshow(img.reshape(28, 28))
        ax.set_xticks([])
        ax.set_yticks([])
        ax.set_title(y)
    plt.tight_layout()
    return fig

mnist_train = MNIST('datasets', train=True, download=True,
                    transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),]))

mnist_test = MNIST('datasets', train=False, download=True,
                   transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),]))


X_example, y_example = zip(*islice(iter(mnist_train), 20))
plot_example(torch.stack(X_example), y_example);
plt.show()
