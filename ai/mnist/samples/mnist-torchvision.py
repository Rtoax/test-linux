#!/bin/env python
# Refs:
# - http://docs.pytorch.org/vision/main/_modules/torchvision/datasets/mnist.html
# - https://colab.research.google.com/github/skorch-dev/skorch/blob/master/notebooks/MNIST-torchvision.ipynb

import torchvision
from torchvision.datasets import MNIST

mnist_train = MNIST('datasets', train=True, download=True,
                    transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),]))

mnist_test = MNIST('datasets', train=False, download=True,
                   transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),]))
