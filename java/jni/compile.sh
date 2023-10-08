#!/bin/bash

JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.382.b05-3.fc40.x86_64/

javac main.java
javah -jni swap poll

gcc -shared -fpic -o libswap.so -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux swap.c
gcc -shared -fpic -o libpoll.so -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux poll.c
