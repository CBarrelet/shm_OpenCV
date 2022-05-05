# shm_OpenCV
This shared memory class for C++ and Python allows sending an OpenCV image from Python to C++.
It could also be used to communicate between two or more C++ programs.

## pre-requisites:
C++ lib: OpenCV <br/>
Python libs: OpenCV and Sysv_ipc

## Usage:
1. ./main
2. python Shared_memory.py

## Explanations:
1. The main initializes a shared memory
2. The python script writes an image into this memory address
3. The main shows the image

## Notes:
1. The key directory and project id are hardcoded in the Shared_memory.hpp and the Shared_memory.py
2. The image size, and thus the buffer size, is also hardcoded in both files
3. The flag allows to read the memory only when the image is fully written

