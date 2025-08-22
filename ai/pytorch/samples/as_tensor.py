#!/bin/env python

import numpy as np
from PIL import Image
import torch
import matplotlib.pyplot as plt

# wget https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png -O lenna.jpg
np_image = np.array(Image.open("lenna.png"))
image = torch.as_tensor(np_image)
plt.imshow(image)
