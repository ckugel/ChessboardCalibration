# About
### This repo is for a PLTW Engineeering Development and Design course
This project will handle the creation of the disparity map for the stereo cameras.
This project is made in C++ using OpenCV. The development platform itself is in Docker to avoid the need of installing the necessary libraries on every system that we use.

### Project
Our project is making a digital twin of a conflict zone in order to provide logistical and strategical information for victims in need of humanitarian aid and safe escape routes. The project will use a multitude of sensors such as drones, fixed cameras, and cameras on viechles in order to make the point cloud that the digital twin relies on for relating colected information to the real world.

# Use
## Building the Docker File 

## Running the image
docker run --device=/dev/video0:/dev/video0 -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY -p 5000:5000 -p 8888:8888 -it spmallick/opencv-docker:opencv /bin/bash  \
[<a href="https://learnopencv.com/install-opencv-docker-image-ubuntu-macos-windows">source</a>]

### flag explanations
--device /dev/video:0/dev/video0 allows us to pass in the devide at video0 (probably a camera) and pass it into the contianer

-v is to pass the graphics through to X11 which is the window manager on most linux distrobutions.

-e maps the Display in the docker bash terminal to the current &DISPLAY from the current bash env.

-p is exposing different ports

-it is the image you are building off of, in our case we are using: <a href="https://hub.docker.com/r/spmallick/opencv-docker"> spmallick/opencv-docker:opencv</a>

# Resources used
Followed parts of this tutorial for setting up the docker file: https://learnopencv.com/install-opencv-docker-image-ubuntu-macos-windows/
