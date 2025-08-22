#!/bin/env python

import numpy as np
from PIL import Image
import torch
import matplotlib.pyplot as plt

# wget https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png -O lenna.jpg
np_image = np.array(Image.open("lenna.png"))
# Or: torch.as_tensor(a, device=torch.device('cuda'))
image = torch.as_tensor(np_image)

print(image.shape)
print(image.dtype)
print(image.ndim)

plt.imshow(image)
plt.show()

plt.imshow(image[:, :256, :])
plt.show()

batch = image.unsqueeze(0).repeat(3, 1, 1, 1)
plt.imshow(image)
plt.show()
