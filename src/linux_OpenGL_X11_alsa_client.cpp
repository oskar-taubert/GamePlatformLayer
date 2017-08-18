
/*************************************
 *
 *  Filename : linux_OpenGL_X11_alsa_client.cpp
 *
 *  Projectname : GamePlatformLayer
 *
 *  Author : Oskar Taubert
 *
 *  Creation Date : Thu 10 Aug 2017 06:09:18 PM CEST
 *
 *  Last Modified : Fri 18 Aug 2017 08:51:12 PM CEST
 *
 * *************************************/

#include <X11/Xlib.h>
#include <GL/glx.h>

int main()
{
    Display                 *display = XOpenDisplay(NULL);
    Window                  rootWindow;
    GLint                   visualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XVisualInfo             *visualInfo;
    Colormap                colormap;
    XSetWindowAttributes    setWindowAttributes;
    Window                  window;
    GLXContext              glContext;
    XWindowAttributes       windowAttributes;
    XEvent                  xevent;

    if(display != NULL)
    {
        rootWindow = DefaultRootWindow(display);

        // TODO load which screen to pick from a config
        int screen = 0;
        // TODO query system to check maximum visual attributes for given hardware
        visualInfo = glXChooseVisual(display, screen, visualAttributes);
        if(visualInfo != NULL)
        {
            colormap = XCreateColormap(display, rootWindow, visualInfo->visual, AllocNone);
            setWindowAttributes.colormap = colormap;
            setWindowAttributes.event_mask = ExposureMask | KeyPressMask;

            window = XCreateWindow(
                    display, // display
                    rootWindow, // parent
                    0, 0, // position
                    600, 600, // width, height
                    0, // border width
                    visualInfo->depth, // 
                    InputOutput, // window type
                    visualInfo->visual,
                    CWColormap | CWEventMask, // flags which attributes in XSetWindowAttributes should be used
                    &setWindowAttributes);
            XMapWindow(display, window);

            // TODO title bar string
            XStoreName(display, window, "Game Client");

            glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
            glXMakeCurrent(display, window, glContext);

            // TODO 
            glEnable(GL_DEPTH_TEST);

            bool running = true;
            while(running)
            {
                XNextEvent(display, &xevent);

                switch(xevent.type)
                {
                    case Expose:
                        {
                            XGetWindowAttributes(display, window, &windowAttributes);
                            glViewport(0, 0, windowAttributes.width, windowAttributes.height);
                            // TODO draw a thing
                            glXSwapBuffers(display, window);
                        }
                        break;
                    case KeyPress:
                        {
                            running = false;
                            glXMakeCurrent(display, None, NULL);
                            glXDestroyContext(display, glContext);
                            XDestroyWindow(display, window);
                            XCloseDisplay(display);
                        }
                        break;
                    default:
                        {
                        }
                }
            }
        }
        else
        {
            // TODO error logging
        }
    }
    else
    {
        // TODO error logging
    }
}
