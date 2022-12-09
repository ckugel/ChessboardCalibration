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
* @return an double[3] object that holds the polar 
    thetaX is the angle between the hypotonuse and a a straight line out of the camera
    theta Y is the angle between the hypotonuse and a straight line out of the camera
    depth is the hypotonuse
    with the origin being camera 1
*/
double* getPolarCoord(double camera1X, double camera1Y, double camera2X, int dimensionX, int dimensionY) {
    // depth from the plane of the cameras
    double depth = return (FOCAL_LENGTH * DISTANCE_BETWEEN_CAMERAS) / (camera2X - camera1X);
    // the ratio of the Xpixel / focal is equal to xPos / depth
    // therefore depth * (Xpixel/focal)
    int middlePointX = dimensionX / 2;
    int middlePointY = dimensionY / 2;
    double thetaX = std::asin((middlePoint - camera1X) / depth);
    double thetaY = std::asin((middlePointY - camera1Y) / depth);

    // return the polar coordinates
    return new double[] {thetaX, thetaY, depth};
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
    double camera1CoordX = 0;
    double camera1CoordY = 0;
    double camera2CoordX = 15; //incges
    double camera2CoordY = 0;
    // saying that camera1 is the origin
    const std::pair<double, double> CAMERA_ONE_COORDS(0, 0);
    // x value is 15 inches to the right of camera 1
    const std::pair<double, double> CAMERA_TWO_COORDS(15, 0); //inches

    const double REAL_DEPTH = 83; // inches
    const double REAL_HEIGHT 12.1; // inches 
}
