#include "colormid.h"

#include "consts.h"

using namespace std;
using namespace cv;

static Mat splm[3];

void Detectors_Easy_Reset(unsigned char detector, void *param) {
	if (detector == 0) {
		gray = Mat(((Mat*)param)->size(), CV_8UC1, Scalar(255));
		findContours(gray, contours, RetrievalModes::RETR_EXTERNAL, ContourApproximationModes::CHAIN_APPROX_SIMPLE);
		MAX_AREA = (unsigned int)(minAreaRect(contours[0]).size.area() / 2);
	}
}

char Detectors_Easy_Recognise_color(Mat& picture, unsigned char start_br_level) {
	Rect rc;
	rc.x = 300;
	rc.y = 220;
	rc.width = 40;
	rc.height = 40;
	split(picture(rc),splm);
	unsigned char h = (unsigned char)roundf(mean(splm[0]).val[0]), s = (unsigned char)roundf(mean(splm[1]).val[0]), v = (unsigned char)roundf(mean(splm[2]).val[0]);
	cout << "h: " << (int)h << " s: " << (int)s << "  v: " << (int)v << endl;
	if (v < 50) return 1;
	if (s < 50) {
		if (v < 190) return 2;
		return 3;
	}
	if (h < 11 || h > 151) return 4;
	if (h < 21) return 5;
	if (h < 33) return 6;
	if (h < 88) return 7;
	if (h < 96) return 8;
	if (h < 133) return 9;
	if (h < 152) return 10;
	
	return 0;
}