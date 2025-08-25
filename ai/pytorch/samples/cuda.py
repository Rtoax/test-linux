#!/bin/env python

import torch

def check_env():
    print("Is GPU[cuda] available? ->", torch.cuda.is_available())
    device = torch.device('cuda:0') if torch.cuda.is_available() else torch.device('cpu')
    print("We will be using device: ", device)
    if torch.cuda.is_available():
        n_cudas = torch.cuda.device_count()
        for i in range(n_cudas):
            print("Totally CUDA:%d %s" % (i, torch.cuda.get_device_name(i)))


if __name__ == "__main__":
    check_env()
