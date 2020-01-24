#pragma once
#include "dependents.h"
using namespace cv;

/*0 - error, 1 - black, 2 - gray, 3 - white, 4 - red, 5 - orange, 6 - yellow, 7 - green, 8 - cyan, 9 - blue, 10 - violet
Reset index 0
Need (Mat*) as a param*/
char Detectors_Easy_Recognise_color(Mat& picture, unsigned char start_br_level = 250);