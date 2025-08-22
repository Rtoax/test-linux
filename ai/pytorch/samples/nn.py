#!/bin/env python

import torch

def test_nn_base():
    model = torch.nn.Linear(20, 30)
    input = torch.randn(128, 20)
    output = model(input)
    print(input)
    print(output)


if __name__ == "__main__":
    test_nn_base()
