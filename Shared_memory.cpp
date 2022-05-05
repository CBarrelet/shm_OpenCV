#include "Shared_memory.hpp"

#include <iostream>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int errorExit(char *buff) {
    std::cout << buff << std::endl;
    return -1;
}

/*------------------------------------------------*/
/*                  CONSTRUCTOR
/*------------------------------------------------*/

Shared_memory::Shared_memory() {
    initSharedMemory();
}

int Shared_memory::initSharedMemory() {
    key_t key = ftok(this->KEY_DIR, this->PROJECT_ID);
    if (key < 0)
        return errorExit((char*)"ERROR: ftok");
        
    this->shmid = shmget(key, this->BUFFER_SIZE, IPC_CREAT | IPC_EXCL | 0664);
    if (this->shmid == -1) {
        if (errno == EEXIST) {
            std::cout << "Shared memory already exists" << std::endl;
            this->shmid = shmget(key, 0, 0);
            std::cout << "Reference shmid: " << this->shmid << std::endl;
        }
        else {
            perror("errno");
            return errorExit((char*)"ERROR: shmget");
        }
    }

    this->buffer = (unsigned char*) shmat(this->shmid, 0, 0);

    if ( buffer == (void*)-1) {
        if (shmctl(this->shmid, IPC_RMID, NULL) == -1)
            return errorExit((char*)"ERROR: shmctl");
        else {
            std::cout << "Attach shared memory failed" << std::endl;
            std::cout << "Remove shared memory identifier successful" << std::endl;
            return errorExit((char*)"ERROR: shmat");
        }
    }

    unsigned char data[this->BUFFER_SIZE];
    for (size_t i = 0; i < this->BUFFER_SIZE; i++)
        data[i] = 'I';
    memcpy(this->buffer, data, this->BUFFER_SIZE);
}

/*------------------------------------------------*/
/*                  DESTRUCTOR
/*------------------------------------------------*/

Shared_memory::~Shared_memory() {
    if ( shmdt(this->buffer) < 0) 
        std::cout << "ERROR: shmdt" << std::endl;
    if (shmctl(this->shmid, IPC_RMID, NULL) == -1)
        std::cout << "ERROR: shmctl" << std::endl;
}


/*------------------------------------------------*/
/*                  GETTER
/*------------------------------------------------*/

int Shared_memory::getBufferSize() { return this->BUFFER_SIZE; }

void Shared_memory::getSharedMemory(unsigned char *data) {
    memcpy(data, this->buffer, BUFFER_SIZE);
}

char Shared_memory::getFlag() { return this->buffer[0]; }

bool Shared_memory::isFree() { return this->buffer[0] == 'F'; }

bool Shared_memory::isRead() { return this->buffer[0] == 'R'; }

cv::Mat Shared_memory::getImage(cv::Mat img) {
    for (size_t i = FLAG_SIZE; i < FLAG_SIZE+IMG_SIZE; i++)
        img.data[i-1] = this->buffer[i];
    return img;
}

/*------------------------------------------------*/
/*                  SETTER
/*------------------------------------------------*/

void Shared_memory::setSharedMemory(unsigned char *data) {
    memcpy(this->buffer, data, BUFFER_SIZE);
}

void Shared_memory::setImage(cv::Mat img) {
    for (size_t i = FLAG_SIZE; i < FLAG_SIZE+IMG_SIZE; i++) {
        this->buffer[i] = img.data[i-1];
    }
}

void Shared_memory::setReadFlag() { this->buffer[0] = 'R'; }

void Shared_memory::setWriteFlag() { this->buffer[0] = 'W'; }

void Shared_memory::setFreeFlag() { this->buffer[0] = 'F'; }