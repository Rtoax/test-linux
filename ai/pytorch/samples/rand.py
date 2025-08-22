#!/bin/env python

import torch
import torchvision

def test_rand():
    x = torch.rand(5, 3)
    print(x)

if __name__ == "__main__":
    test_rand()
