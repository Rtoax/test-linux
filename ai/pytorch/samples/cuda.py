#!/bin/env python

import torch

def check_env():
    if torch.cuda.is_available():
        print("Support cuda")
    else:
        print("Not support cuda")

if __name__ == "__main__":
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    check_env()
