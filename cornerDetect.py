# from __future__ import print_function
import cv2 as cv
import numpy as np
import argparse
import random as rng

source_window = 'output'
maxTrackbar = 25
rng.seed(12345)
def goodFeaturesToTrack_Demo(val, src):
    maxCorners = max(val, 1)
    # Parameters
    qualityLevel = 0.01
    minDistance = 10
    blockSize = 3
    gradientSize = 3
    useHarrisDetector = True
    k = 0.04
    copy = np.copy(src)
    # Apply corner detection, you can choose whether to use the harris corner detector
    corners = cv.goodFeaturesToTrack(cv.cvtColor(src, cv.COLOR_BGR2GRAY), maxCorners, qualityLevel, minDistance, None, \
        blockSize=blockSize, gradientSize=gradientSize, useHarrisDetector=useHarrisDetector, k=k)
    # Draw corners detected
    print('Number of corners detected:', corners.shape[0])
    radius = 4
    for i in range(corners.shape[0]):
        cv.circle(copy, (corners[i,0,0], corners[i,0,1]), radius, \
            (0, 0, 255), cv.FILLED)
    cv.namedWindow(source_window)
    cv.imshow(source_window, copy)
    winSize = (5, 5)
    zeroZone = (-1, -1)
    criteria = (cv.TERM_CRITERIA_EPS + cv.TermCriteria_COUNT, 40, 0.001)
    corners = cv.cornerSubPix(cv.cvtColor(src, cv.COLOR_BGR2GRAY), corners, winSize, zeroZone, criteria)
    # print corner 
    for i in range(corners.shape[0]):
        print(" -- Refined Corner [", i, "]  (", corners[i,0,0], ",", corners[i,0,1], ")")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', default='checkerboard.png')
    args = parser.parse_args()
    src = cv.imread(cv.samples.findFile(args.input))
    if src is None:
        print('Could not open the image:')
        exit(0)
    cv.namedWindow(source_window)
    maxCorners = 100 
    cv.createTrackbar('Threshold: ', source_window, maxCorners, maxTrackbar, goodFeaturesToTrack_Demo)
    cv.imshow(source_window, src)
    goodFeaturesToTrack_Demo(maxCorners, src)
    cv.waitKey()
           
if __name__ == "__main__":
    main()
