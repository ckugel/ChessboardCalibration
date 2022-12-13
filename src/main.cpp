#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <filesystem>

using namespace std;

//TODO: find real values
double FOCAL_LENGTH = 26E-3; // 26 millimeters
double DISTANCE_BETWEEN_CAMERAS = 0.381; // meters

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
    int middlePointX = dimensionX / 2;
    int middlePointY = dimensionY / 2;
    double thetaX = std::asin((middlePointX - camera1X) / depth);
    double thetaY = std::asin((middlePointY - camera1Y) / depth);

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
                // Check if the current pixel has a higher saturation value than the most green pixel found so far
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
    double camera1RealCoordX = 0;
    double camera1RealCoordY = 0;
    double camera2RealCoordX = 0.381;
    double camera2RealCoordY = 0;

    int dimensionWidth = im1.size().width;
    int dimensionHeight = im1.size().height;

    int GreenDotXCam1 = -1;
    int GreenDotYCam2 = -1;

    // bounds for green
/*    cv::Scalar lowerBound(30, 80, 40);
    cv::Scalar upperBound(90, 255, 255);

    cv::Mat binImage;
    cv::inRange(im1, lowerBound, upperBound, binImage);*/

    const double REAL_DEPTH = 2.1082;
    const double REAL_HEIGHT = 0.30734;

    std::pair<int, int> im1Pos = getGreenPixel(im1);
    std::pair<int, int> im2Pos = getGreenPixel(im1);

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



