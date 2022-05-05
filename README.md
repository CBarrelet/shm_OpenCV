# shm_OpenCV
Shared memory with OpenCV image between C++ program and Python program; works also with 2 C++ programs. 

C++ lib: OpenCV
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

