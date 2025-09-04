#!/bin/env python
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

sampling_rate = 1000
duration = 1.0
freq = 50

t = np.linspace(0.0, duration, int(sampling_rate * duration), endpoint=False)

signal = np.sin(2 * np.pi * freq * t)

yf = fft(signal)
xf = fftfreq(len(signal), 1 / sampling_rate)

positive_freq_mask = xf >= 0
xf_positive = xf[positive_freq_mask]
yf_positive = 2.0/len(signal) * np.abs(yf[positive_freq_mask])

plt.figure(figsize=(12, 8))

plt.subplot(2, 1, 1)
plt.plot(t, signal)
plt.title('Time domain signal - sin({} Hz)'.format(freq))
plt.xlabel('Time (s)')
plt.ylabel('Value')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(xf_positive, yf_positive)
plt.title('FFT')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Value')
plt.grid(True)
plt.xlim(0, 100)

plt.tight_layout()
plt.show()
