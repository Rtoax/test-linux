#!/bin/env python

import torch

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
