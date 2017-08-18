build/linux_OpenGL_X11_alsa_game : ./src/linux_OpenGL_X11_alsa_game.cpp
	clang -o build/linux_OpenGL_X11_alsa_game src/linux_OpenGL_X11_alsa_game.cpp -lX11 -lGL - lGLU
