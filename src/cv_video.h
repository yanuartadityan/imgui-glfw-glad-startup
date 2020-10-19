//
// Created by mirkwood on 10/20/20.
//

#ifndef IMGUI_GLFW_GLAD_CV_VIDEO_H
#define IMGUI_GLFW_GLAD_CV_VIDEO_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

double getPSNR(const cv::Mat &I1, const cv::Mat &I2);
cv::Scalar getMSSIM(const cv::Mat &I1, const cv::Mat &I2);
int wrapper_main(int argc, char *argv[]);

#endif //IMGUI_GLFW_GLAD_CV_VIDEO_H
