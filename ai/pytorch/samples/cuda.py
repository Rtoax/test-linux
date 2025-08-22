#!/bin/env python

import torch

def check_env():
    print("Is GPU[cuda] available? ->", torch.cuda.is_available())
    device = torch.device('cuda:0') if torch.cuda.is_available() else torch.device('cpu')
    print("We will be using device: ", device)

if __name__ == "__main__":
    check_env()
