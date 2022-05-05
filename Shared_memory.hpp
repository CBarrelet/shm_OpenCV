#pragma once
#include <opencv2/highgui.hpp>

class Shared_memory {
private:

    const char *KEY_DIR = "/tmp";
    const int PROJECT_ID = 2333;
    int shmid;

    const int FLAG_SIZE = 1;

    const int IMG_WIDTH = 500;
    const int IMG_HEIGHT = 500;
    const int IMG_CHANNELS = 3;
    const int IMG_SIZE = IMG_WIDTH * IMG_HEIGHT * IMG_CHANNELS;

    const int BUFFER_SIZE = FLAG_SIZE + IMG_SIZE;

    unsigned char *buffer;

public:
/*------------------------------------------------*/
/*                  CONSTRUCTOR
/*------------------------------------------------*/
    Shared_memory();
    int initSharedMemory();

/*------------------------------------------------*/
/*                  DESTRUCTOR
/*------------------------------------------------*/
    ~Shared_memory();
    void unlinkSharedMemory();

/*------------------------------------------------*/
/*                  GETTER
/*------------------------------------------------*/
    int getBufferSize();
    void getSharedMemory(unsigned char *data);
    char getFlag();
    bool isFree();
    bool isRead();
    cv::Mat getImage(cv::Mat img);

/*------------------------------------------------*/
/*                  SETTER
/*------------------------------------------------*/
    void setSharedMemory(unsigned char *data);
    void setReadFlag();
    void setWriteFlag();
    void setFreeFlag();
    void setImage(cv::Mat img);  
};
