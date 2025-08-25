#!/bin/env python

import torch
import numpy as np

def test_tensor():
    print(torch.tensor([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]]))
    print(torch.tensor(np.array([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]])))
    print(torch.zeros(2,3))
    print(torch.ones(2,3))
    print(torch.ones((2, 3), dtype=torch.float))
    print(torch.eye(3))

    print("---- Tensor x ----")
    x = torch.tensor([[ 1., 2.], [ 3., 4.], [ 5., 6.]])
    print(x)

    print("---- Tensor properties ----")
    print(x.shape)
    print(x.size())
    print(x.dtype)
    print(x.type())
    print(x.ndim)

    print("---- Tensor indexing ----")
    print(x[0, 1])
    print(x[2, :])
    print(x[:, 0])
    print(x[1:3, :])

    print("---- Tensor reshaping ----")
    y = x.reshape(6)
    print(y)
    y = x.view(6)
    print(y)

    print("---- Tensor type transformation ----")
    y = x.int()
    print(y.dtype)

    z = x.double()
    print(z.dtype)

    np_x = x.numpy()
    print(np_x.dtype)

    np_x = x.data.numpy()
    print(np_x.dtype)

    if torch.cuda.is_available():
        cuda_x = x.cuda()
        print(cuda_x.dtype)

        cpu_x = cuda_x.cpu()
        print(cpu_x.dtype)

    print("---- Tensor squeezing and unsqueezing ----")
    y = torch.unsqueeze(x, 0)
    print(y)
    z = torch.squeeze(y, 0)
    print(z)

    print("---- Tensor expansion ----")
    y = x.expand(3, 2)
    print(y)

    print("---- Tensor Addition, subtraction, multiplication and division ----")
    print(x + 3)
    print(x + x)
    print(x * 3)

    print("---- Tensor Addition, subtraction, multiplication and division ----")
    print(x.exp())
    print(x.log())
    print(x.pow(2))

    print("---- Tensor max/min/sum/mean ----")
    print(x.min())
    print(x.sum())
    print(x.sum(dim=0))
    print(x.sum(dim=1))
    print(x.mean())

def test_tensor_scaler():
    print("---- Tensor Scaler ----")
    scaler = torch.tensor(3.14)
    print(scaler)

def test_tensor_vector():
    print("---- Tensor Vector ----")
    vector = torch.tensor([1, 2, 3])
    print(vector)

def test_tensor_matrix():
    print("---- Tensor Dot product ----")
    a = torch.tensor([1., 2., 3.])
    b = torch.tensor([4., 5., 6.])
    print(torch.dot(a, b))

    print("---- Tensor Matrix multiplication ----")
    a = torch.tensor([[ 1., 2.], [ 3., 4.]])
    b = torch.tensor([[ 5., 6.], [ 7., 8.]])
    print(torch.mm(a, b))


if __name__ == "__main__":
    test_tensor()
    test_tensor_scaler()
    test_tensor_vector()
    test_tensor_matrix()
