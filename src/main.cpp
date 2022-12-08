#include <opencv2/core.hh>
#include <iostream>
#include <utility>
#include <assert.h>

using namespace std;

//TODO: find real values
double FOCAL_LENGTH = 0.5; // meters
double DISTANCE_BETWEEN_CAMERAS = 0.381; // meters

/**
* function to get distance
* parameters are in pixels
* @return an double[3] object that holds the rectengular coordinates 
    with the origin being camera 1
*/
double* depth(double camera1X, double camera1Y, double camera2X, int dimensionX, int dimensionY) {
    // depth from the plane of the cameras
    double depth = return (FOCAL_LENGTH * DISTANCE_BETWEEN_CAMERAS) / (camera2X - camera1X);
    // the ratio of the Xpixel / focal is equal to xPos / depth
    // therefore depth * (Xpixel/focal)
    double x = (camera1X / FOCAL_LENGTH) * depth;

    // return the rectengular coordinates
    return new double[] {x, camera1Y, depth};
}


int main() {
    string im1path;
    string im2path;

    Mat im1 = cv::imread(im1path);
    Mat im2 = cv::imread(im2path);
    
    int dimensionWidth = im1.size().with;
    int dimensionHeight = im1.size().height;
    
    return -1;
}

void test() {
    // saying that camera1 is the origin
    const std::pair<double, double> CAMERA_ONE_COORDS(0, 0);
    // x value is 15 inches to the right of camera 1
    const std::pair<double, double> CAMERA_TWO_COORDS(15, 0); //inches

    const double depth = 83; // inches
    const double height 12.1; // inches 
}
