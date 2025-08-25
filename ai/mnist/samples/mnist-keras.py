#!/bin/env python

from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Input
from keras.utils import to_categorical
from keras.optimizers import RMSprop
import matplotlib.pyplot as plt
import numpy as np
import os

os.environ["CUDA_VISIBLE_DEVICES"] = "-1"

(X_train, y_train), (X_test, y_test) = mnist.load_data()

X_train = X_train.astype('float32')/255
X_test = X_test.astype('float32')/255

X_train = np.reshape(X_train, (60000, 784))
X_test = np.reshape(X_test, (10000, 784))

y_train = to_categorical(y_train, 10)
y_test = to_categorical(y_test, 10)

model = Sequential()
model.add(Input(shape=(784,)))
model.add(Dense(500, activation="relu"))
model.add(Dropout(0.4))
model.add(Dense(300, activation="relu"))
model.add(Dropout(0.4))
model.add(Dense(10, activation="softmax"))

rms = RMSprop()
model.compile(loss='categorical_crossentropy',
              optimizer=rms, metrics=['accuracy'])

model.summary()

epochs = 20
batch_size = 256
model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size,
          validation_data=(X_test, y_test), verbose=2)

loss_value, accuracy = model.evaluate(X_test, y_test, batch_size=16)
print(accuracy)

np.argmax(model.predict(np.array([X_test[0]])))

wrong = 0
max_wrong = 10

for n, (x, y) in enumerate(zip(X_test, y_test)):
    try:
        res = model.predict(np.array([x]), verbose=0)
        if np.argmax(res) != np.argmax(y):
            print(f"test {n}: prediction = {np.argmax(res)}, truth is {np.argmax(y)}")
            plt.imshow(x.reshape(28, 28), cmap="gray_r")
            plt.show()
            wrong += 1
            if (wrong > max_wrong-1):
                break
    except KeyboardInterrupt:
        print("stopping")
        break
