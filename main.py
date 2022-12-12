import cv2
import numpy as np

dimensionsOfBoard = (8, 8)

red_lower_bound = (0, 0, 100)
red_upper_bound = (240, 240, 240)

# Read in the left and right images
left_img = cv2.imread("calibLeft.JPG")
right_img = cv2.imread("calibRight.JPG")

hsv_L = cv2.cvtColor(left_img, cv2.COLOR_BGR2HSV)
hsv_R = cv2.cvtColor(right_img, cv2.COLOR_BGR2HSV)

left_mask = cv2.inRange(left_img, red_lower_bound, red_upper_bound)
right_mask = cv2.inRange(right_img, red_lower_bound, red_upper_bound)

left_red_img = cv2.bitwise_and(left_img, left_img, mask=left_mask)
right_red_img = cv2.bitwise_and(right_img, right_img, mask=right_mask)

_, left_red_img = cv2.threshold(left_red_img, 1, 255, cv2.THRESH_BINARY)
_, right_red_img = cv2.threshold(right_red_img, 1, 255, cv2.THRESH_BINARY)

result_left = cv2.add(left_img, left_red_img)
result_right = cv2.add(right_img, right_red_img)

"""left_img[(left_mask == 0).all(-1)] = [255, 255, 255]
right_img[(right_mask == 0).all(-1)] = [255, 255, 255]"""

"""left_img = cv2.bitwise_or(left_img, left_img, mask=left_mask)
right_img = cv2.bitwise_or(right_img, right_img, mask=right_mask)"""
"""cv2.imshow("left-mask", left_mask)
cv2.imshow("right-mask", right_mask)"""

"""cv2.imshow("left-mask", left_img)
cv2.imshow("right-mask", right_img)"""

"""cv2.imshow("left", result_left)
cv2.imshow("right", result_right)
cv2.waitKey(0)"""

# Convert the images to grayscale
left_gray = cv2.cvtColor(result_left, cv2.COLOR_BGR2GRAY)
right_gray = cv2.cvtColor(result_right, cv2.COLOR_BGR2GRAY)

"""cv2.imshow("left", left_gray)
cv2.imshow("right", right_gray)
cv2.waitKey(0)"""

# print(right_gray.shape[1::-1]) # (4032, 3024)
# print(left_gray.shape[1::-1]) # (4032, 3024)

# Chess board extraction
"""resized_left = cv2.resize(left_gray, (1008, 756))
resized_right = cv2.resize(right_gray, (1008, 756))"""

resized_left = left_gray[1100:1600, 1700:2200]
resized_right = right_gray[1100:1600, 1100:1600]

"""cv2.imshow("left", resized_left)
cv2.imshow("right", resized_right)
cv2.waitKey(0)"""

krn_L = cv2.getStructuringElement(cv2.MORPH_RECT, (50, 30))
dlt_L = cv2.dilate(resized_left, krn_L, iterations=5)
res_L = 255 - cv2.bitwise_and(dlt_L, resized_left)

krn_R = cv2.getStructuringElement(cv2.MORPH_RECT, (50, 30))
dlt_R = cv2.dilate(resized_right, krn_R, iterations=5)
res_R = 255 - cv2.bitwise_and(dlt_R, resized_right)

"""cv2.imshow("left", res_L)
cv2.imshow("right", res_R)
cv2.waitKey(0)"""

res_L = np.uint8(res_L)
res_R = np.uint8(res_R)

"""cv2.imshow("left", res_L)
cv2.imshow("right", res_R)
cv2.waitKey(0)"""

# Find the chessboard corners in the left and right images
ret_left, corners_left = cv2.findChessboardCorners(res_R, dimensionsOfBoard, flags=cv2.CALIB_CB_ADAPTIVE_THRESH +
                                               cv2.CALIB_CB_NORMALIZE_IMAGE)
ret_right, corners_right = cv2.findChessboardCorners(res_L, dimensionsOfBoard, flags=cv2.CALIB_CB_ADAPTIVE_THRESH +
                                               cv2.CALIB_CB_NORMALIZE_IMAGE)

# If the chessboard corners were found in both images, proceed with calibration
if ret_left and ret_right:
    # Calculate the stereo calibration parameters
    ret, M1, d1, M2, d2, R, T, E, F = cv2.stereoCalibrate(
        (corners_left, corners_right),
        (left_gray, right_gray),
        (left_gray.shape[::-1], right_gray.shape[::-1]),
        None, None
    )

    # Print the stereo calibration parameters
    print("Camera matrix 1:", M1)
    print("Distortion coefficients 1:", d1)
    print("Camera matrix 2:", M2)
    print("Distortion coefficients 2:", d2)
    print("Rotation matrix:", R)
    print("Translation vector:", T)
    print("Essential matrix:", E)
    print("Fundamental matrix:", F)
else:
    print("Unable to find chessboard corners in the left and right images.")
