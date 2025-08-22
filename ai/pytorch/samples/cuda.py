#!/bin/env python

import torch
import torchvision

def check_env():
    if torch.cuda.is_available():
        print("Support cuda")
    else:
        print("Not support cuda")

if __name__ == "__main__":
    check_env()
