#!/bin/bash

# TODO add makefile and rmakefile

clang -o ./bin/client ./src/linux_OpenGL_X11_alsa_client.cpp -lX11 -lGL
