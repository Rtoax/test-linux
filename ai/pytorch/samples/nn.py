#!/bin/env python

import torch
import torch.nn as nn

def test_nn_base():
    model = torch.nn.Linear(20, 30)
    input = torch.randn(128, 20)
    output = model(input)
    print(input)
    print(output)

# Mean Squared Error
def test_nn_mse():
    # Defines a MSE loss function
    loss_fn = nn.MSELoss(reduction='mean')
    # This is a random example to illustrate the loss function
    predictions = torch.tensor([0.5, 1.0])
    labels = torch.tensor([2.0, 1.3])
    print(loss_fn(predictions, labels))

def test_nn_linear():
    linear = nn.Linear(1, 1)
    print(linear)
    linear.state_dict()


if __name__ == "__main__":
    test_nn_base()
    test_nn_mse()
    test_nn_linear()
