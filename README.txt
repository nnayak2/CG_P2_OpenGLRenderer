Usage:

Project and solution files are VS 2013. Static linking used for debug and release executables, so it should work without any dependency.
EXE files are in debug and release folders.(along with dependency glut32.dll)

Initial setup:
On the console, please enter parameters as asked. (how many textures and each texture name completely. ex: "xyz.bmp")

Files:
Have your image files in current drectory
Have view.txt and window.txt in current directory is you want to have custom viewing setup

Key Mapping:
Light toggle ->              l
Translate X and Y ->         Arrow keys
Translate Z ->               [ and ]
Scale ->                     q and w
Toggle between textures ->   , and .

Limitations:
Loading obj without normals and tex coords causes not so nice output and no textures.


Credits to external sources:

1. Code used:

a. Tiny Obj Loader: (with minor modifications so materials are loaded correctly)
For parsing obj files.
https://github.com/syoyo/tinyobjloader

b. GLUT:
For creating a window and rendering the pixels from my colorbuffer.

c. GLM:
For all vector calculations.

d. SOIL
For loading all image files.
http://www.lonesock.net/soil.html

2. Other sources:

Code from my ray tracer project reused at some places, like file parsing, obj loading.