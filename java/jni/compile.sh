#!/bin/bash

JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk

javac main.java
javah -jni swap poll

gcc -shared -fpic -o libswap.so -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux swap.c
gcc -shared -fpic -o libpoll.so -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux poll.c
