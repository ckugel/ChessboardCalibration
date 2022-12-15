#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <filesystem>
#include <array>

using namespace std;

//TODO: find real values
double FOCAL_LENGTH = 5.1E-3; // 5.1 millimeters
double DISTANCE_BETWEEN_CAMERAS = 0.381; // meters

double FOV_X = 1.2791860172; //radians
double FOV_Y = 0.71954217833; // radians

/**
* function to get distance
* parameters are in pixels
* @return an double[3] object that holds the polar
    thetaX is the angle between the hypotonuse and a a straight line out of the camera
    theta Y is the angle between the hypotonuse and a straight line out of the camera
    depth is the hypotonuse
    with the origin being camera 1
*/
double* getPolarCoord(double camera1X, double camera1Y, double camera2X, int dimensionX, int dimensionY) {
    // depth from the plane of the cameras
    double depth = (FOCAL_LENGTH * DISTANCE_BETWEEN_CAMERAS) / (camera2X - camera1X);
    // find the middle of the screen
    double middlePointX = (double) dimensionX / 2;
    double middlePointY = (double) dimensionY / 2;
    // get angles
    // convert from pixels to degrees
    double thetaX = (middlePointX - camera1X) * (FOV_X / dimensionX);
    double thetaY = (middlePointY - camera1Y) * (FOV_Y / dimensionY);

    // return the polar coordinates
    return new double[] {thetaX, thetaY, depth};
}

std::pair<int, int> getGreenPixel(cv::Mat& image) {
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV); // open the image in the hsrv colorspace

    // Define the range of hue values (first one) to look for gree
    const int MIN_HUE = 60;
    const int MAX_HUE = 150;

    // Define the minimum saturation value for a pixel to be considered green
    const int MIN_SAT = 50;

    // max placeholders for search
    cv::Vec3b mostGreenPixel(0, 0, 0);
    int maxSaturation = 0;

    // output values
    int y0 = 0;
    int x0 = 0;

    for (int y = 0; y < hsv.rows; y++) {
        for (int x = 0; x < hsv.cols; x++) {
            // Extract the hue and saturation values of the current pixel
            cv::Vec3b pixel = hsv.at<cv::Vec3b>(y, x);
            int hue = pixel[0];
            int saturation = pixel[1];

            // Check if in range
            if (hue >= MIN_HUE && hue <= MAX_HUE && saturation >= MIN_SAT) {
                if (saturation > maxSaturation) {
                    maxSaturation = saturation;
                    x0 = x;
                    y0 = y;
                }
            }
        }
    }

    return {x0, y0};

    // Print the RGB values of the most green pixel
    // std::cout << "Most green pixel: (" << (int)mostGreenPixel[0] << ", " << (int)mostGreenPixel[1] << ", " << (int)mostGreenPixel[2] << ")" << std::endl;
//    std::cout << "x: " << x0 << ", y: " << y0 << std::endl;

    // proof it worked:
/*    cv::circle(image, cv::Point(x0,y0), 5, cv::Scalar(0, 0, 255), 2);
    cv::imshow("Dot", image);
    cv::waitKey(0);*/
}

void test(cv::Mat& im1, cv::Mat& im2) {
    const double CAMERA_1_REAL_COORD_X = 0;
    const double CAMERA_1_REAL_COORD_Y = 0;
    const double CAMERA_2_REAL_COORD_X = 0.381;
    const double CAMERA_2_REAL_COORD_Y = 0;

    const double REAL_DEPTH = 2.1082;
    const double REAL_HEIGHT = 0.30734;

    const int dimensionWidth = im1.size().width;
    const int dimensionHeight = im1.size().height;

    // rect coords of pixels
    std::pair<int, int> im1Pos = getGreenPixel(im1);
    // only need X value
    int im2Pos = getGreenPixel(im2).first;

    double* polarCoord = getPolarCoord(im1Pos.first, im1Pos.second, im2Pos, dimensionWidth, dimensionHeight);
    std::cout << polarCoord[2] << std::endl;

    delete[] polarCoord;
}

int main() {
    string im1path = "../IMG_5289.JPG";
    string im2path = "../IMG_5288.JPG";

    cv::Mat im1 = cv::imread(im1path);
    cv::Mat im2 = cv::imread(im2path);

    int dimensionWidth = im1.size().width;
    int dimensionHeight = im1.size().height;

    test(im1, im2);

    return -1;
}


// ChatGPT SAD
/*

 * function to calculate the disparity between the two images using block matching

double getDisparity(double camera1X, double camera1Y, double camera2X, int dimensionX, int dimensionY) {
    // get the images from the two cameras
    Image image1 = getImageFromCamera(1);
    Image image2 = getImageFromCamera(2);

    // select a patch of pixels around the given coordinates in the first image
    int patchSize = 7; // patch size is 7x7 pixels
    int startX = camera1X - patchSize / 2;
    int startY = camera1Y - patchSize / 2;
    int endX = camera1X + patchSize / 2;
    int endY = camera1Y + patchSize / 2;
    Image patch1 = image1.getSubImage(startX, startY, endX, endY);

    // initialize the disparity to the maximum possible value
    double disparity = Double.MAX_VALUE;

    // search for the best matching patch in the second image
    for (int x = 0; x < dimensionX; x++) {
        for (int y = 0; y < dimensionY; y++) {
            // select a patch of pixels around the current coordinates in the second image
            startX = x - patchSize / 2;
            startY = y - patchSize / 2;
            endX = x + patchSize / 2;
            endY = y + patchSize / 2;
            Image patch2 = image2.getSubImage(startX, startY, endX, endY);

            // calculate the sum of absolute differences (SAD) between the two patches
            double sad = 0;
            for (int i = 0; i < patchSize; i++) {
                for (int j = 0; j < patchSize; j++) {
                    sad += Math.abs(patch1.getPixel(i, j) - patch2.getPixel(i, j));
                }
            }

            // update the disparity if the current patch has a lower SAD value
            if (sad < disparity) {
                disparity = sad;
            }
        }
    }

    // return the calculated disparity
    return disparity;
}

*/

