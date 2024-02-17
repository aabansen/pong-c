#!/bin/sh

set -xe

clear
gcc -Wextra -Wall -o pong src/*.c $(pkg-config --libs --cflags raylib)
./pong