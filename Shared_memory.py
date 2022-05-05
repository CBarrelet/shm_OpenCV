import sysv_ipc as ipc

import warnings
warnings.simplefilter("ignore")


class Shared_memory:
    key_dir = ""
    project_id = 0
    key = None
    shm = None

    def __init__(self, key_dir, project_id) -> None:
        self.key_dir = key_dir
        self.project_id = project_id
        self.key = ipc.ftok(key_dir, project_id)
        self.shm = ipc.SharedMemory(self.key, 0, 0)
        self.shm.attach(0, 0) # Otherwise set to Read Only

    def __del__(self):
        self.shm.detach()

    def isRead(self):
        return chr(self.shm.read(1)[0]) == 'R'

    def setWriteFlag(self):
        self.shm.write('W', 0)

    def setFreeflag(self):
        self.shm.write('F', 0)

    def setImage(self, img) -> None:
        bytes_img = img.tobytes()
        self.shm.write(bytes_img, 1)
    

if __name__ == "__main__":

    # Create a green image
    import numpy as np
    img = np.ones((500,500,3), np.uint8)
    img[:,:,1] = img[:,:,1]*125
    # Init shared memory
    shared_memory = Shared_memory("/tmp", 2333)
    # Check if shared memory is not currently read
    if(not(shared_memory.isRead())):
        # Set the Write flag
        shared_memory.setWriteFlag()
        # Write the image in the shared memory
        shared_memory.setImage(img)
        # Set the Free flaf
        shared_memory.setFreeflag()
    # Unlink the shared memory
    del shared_memory