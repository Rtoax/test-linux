#!/bin/env python

import torch
import numpy as np

def test_tensor():
    print(torch.tensor([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]]))
    print(torch.tensor(np.array([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]])))
    print(torch.zeros(2,3))
    print(torch.ones(2,3))
    print(torch.eye(3))

    x = torch.tensor([[ 0.1000, 1.2000], [ 2.2000, 3.1000], [ 4.9000, 5.2000]])
    print(x.shape)
    print(x.size())
    print(x.dtype)
    print(x.type())
    print(x.ndim)


if __name__ == "__main__":
    test_tensor()
