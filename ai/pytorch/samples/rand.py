#!/bin/env python

import torch

def test_rand():
    # Positive
    print(torch.rand(5, 3))
    # Negative
    print(torch.randn(5, 3))
    print(torch.randn((2, 3, 4), dtype=torch.float))


if __name__ == "__main__":
    test_rand()
