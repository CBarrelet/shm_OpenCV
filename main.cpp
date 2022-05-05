#include <iostream>
#include <opencv2/opencv.hpp>

#include "Shared_memory.hpp"

int main(int argc, char **argv) {

    Shared_memory memory;

    cv::Mat img = cv::Mat(500, 500, CV_8UC3);

    while(true) {

        if(memory.isFree()) {
            memory.setReadFlag();
            memory.getImage(img);
            cv::imshow("test", img);
            memory.setFreeFlag();
        }   
        cv::waitKey(50);
    }
    return 0;
}