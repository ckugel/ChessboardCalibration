//
// Created by calebkugel on 12/16/22.
//

#ifndef DISPMAP_SETTINGS_H
#define DISPMAP_SETTINGS_H

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <unordered_map>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


class Settings {
public:
    enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
    enum InputType { INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST };

    Settings() : goodInput(false) {
        pattern_map["CHESSBOARD"] = CHESSBOARD;
        pattern_map["CIRCLES_GRID"] = CIRCLES_GRID;
        pattern_map["ASYMMETRIC_CIRCLES_GRID"] = ASYMMETRIC_CIRCLES_GRID;

    }

    void write(FileStorage& fs) const;
    void read(const FileNode& node);
    void validate();
    Mat nextImage();

    static bool readStringList(const string& filename, vector<string>& l) {
        l.clear();
        FileStorage fs(filename, FileStorage::READ);
        if(!fs.isOpened()) {
            return false;
        }
        FileNode n = fs.getFirstTopLevelNode();
        if(n.type() != FileNode::SEQ) {
            return false;
        }
        FileNodeIterator it = n.begin(), it_end = n.end();
        // eeeewwwww file iterator for loops r so gross
        for(; it != it_end; ++it) {
            l.push_back((string) *it);
        }
        return true;
    }

    static bool isListOfImages( const string& filename) {
        string s(filename);
        // Look for file extension
        if(s.find(".xml") == string::npos && s.find(".yaml") == string::npos && s.find(".yml") == string::npos) {
            return false;
        }
        else {
            return true;
        }
    }

    // FFFIIIEEEELLLLLLDDDDDDSSSSSSSSSSS
public:
    Size boardSize;              // The size of the board -> Number of items by width and height
    Pattern calibrationPattern;  // One of the Chessboard, circles, or asymmetric circle pattern
    float squareSize;            // The size of a square in your defined unit (point, millimeter,etc).
    int nrFrames;                // The number of frames to use from the input for calibration
    float aspectRatio;           // The aspect ratio
    int delay;                   // In case of a video input
    bool writePoints;            // Write detected feature points
    bool writeExtrinsics;        // Write extrinsic parameters
    bool writeGrid;              // Write refined 3D target grid points
    bool calibZeroTangentDist;   // Assume zero tangential distortion
    bool calibFixPrincipalPoint; // Fix the principal point at the center
    bool flipVertical;           // Flip the captured images around the horizontal axis
    string outputFileName;       // The name of the file where to write
    bool showUndistorted;        // Show undistorted images after calibration
    string input;                // The input ->
    bool useFisheye;             // use fisheye camera model for calibration
    bool fixK1;                  // fix K1 distortion coefficient
    bool fixK2;                  // fix K2 distortion coefficient
    bool fixK3;                  // fix K3 distortion coefficient
    bool fixK4;                  // fix K4 distortion coefficient
    bool fixK5;                  // fix K5 distortion coefficient

    int cameraID;
    vector<string> imageList;
    size_t atImageList;
    VideoCapture inputCapture;
    InputType inputType;
    bool goodInput;
    int flag;

private:
string patternToUse;
unordered_map<string, Pattern> pattern_map;

};


#endif //DISPMAP_SETTINGS_H
