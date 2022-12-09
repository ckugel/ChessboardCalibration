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
    
    int dimensionWidth = im1.size().width;
    int dimensionHeight = im1.size().height;
    
    return -1;
}

void test() {
    double camera1RealCoordX = 0;
    double camera1RealCoordY = 0;
    double camera2RealCoordX = 15; // inches
    double camera2RealCoordY = 0;

    Mat im1 = cv::imread(im1path);
    Mat im2 = cv::imread(im2path);

    int dimensionWidth = im1.size().width;
    int dimensionHeight = im1.size().height;

    int GreenDotXCam1 = -1;
    int GreenDotYCam2 = -1;

    // bounds for green
    cv::Scalar lowerBound(30, 80, 40);
    cv::Scalar upperBound(90, 255, 255);

    Mat binImage;
    cv::inRange(im1, lowerBound, upperBound, binImage);

    const double REAL_DEPTH = 83; // inches
    const double REAL_HEIGHT 12.1; // inches 



}

void anothier() {
      cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Define the range of green hue values (in degrees)
  const int MIN_HUE = 60;
  const int MAX_HUE = 150;

  // Define the minimum saturation value for a pixel to be considered green
  const int MIN_SAT = 50;

  // Create variables to store the most green pixel found so far
  cv::Vec3b mostGreenPixel(0, 0, 0);
  int maxSaturation = 0;

  // Iterate over all the pixels in the image
  for (int y = 0; y < hsv.rows; y++) {
    for (int x = 0; x < hsv.cols; x++) {
      // Extract the hue and saturation values of the current pixel
      cv::Vec3b pixel = hsv.at<cv::Vec3b>(y, x);
      int hue = pixel[0];
      int saturation = pixel[1];

      // Check if the current pixel is a green pixel
      if (hue >= MIN_HUE && hue <= MAX_HUE && saturation >= MIN_SAT) {
        // Check if the current pixel has a higher saturation value than the most green pixel found so far
        if (saturation > maxSaturation) {
          // Update the most green pixel found so far
          mostGreenPixel = pixel;
          maxSaturation = saturation;
        }
      }
    }
  }

  // Print the RGB values of the most green pixel
  std::cout << "Most green pixel: (" << (int)mostGreenPixel[0] << ", " << (int)mostGreenPixel[1] << ", " << (int)mostGreenPixel[2] << ")" << std::endl;

}
