#!/bin/env python

import torch
import numpy as np

def test_tensor():
    torch.tensor([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]])
    torch.tensor(np.array([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]]))
    torch.zeros(2,3)
    torch.ones(2,3)
    torch.eye(3)

    x = torch.tensor([[ 0.1000, 1.2000], [ 2.2000, 3.1000], [ 4.9000, 5.2000]])
    x.shape
    x.size()
    x.dtype
    x.type()
    x.ndim


if __name__ == "__main__":
    test_tensor()
