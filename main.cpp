#include <iostream>
#include "projective_tf.hpp"

int setOutput(int x, int y, int col, int row, char b, char g, char r, cv::Mat out) {
	if (0<=x && x<col && 0<=y && y<row) {
		out.data[3*(x + col*y)] = b;
		out.data[3*(x + col*y) + 1] = g;
		out.data[3*(x + col*y) + 2] = r;
	}
	return 0;
}

int main() {
	projective_tf pt;
	int x, y, t;
	int x0, y0, t0;

	cv::VideoCapture cap(1);
	cv::namedWindow("cap");
	cv::namedWindow("dst");

	if (!cap.isOpened())	return -1;
	std::cout << "start cap channel 1\n";

	pt.setMatPra(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	pt.out.create((int)cap.get(CV_CAP_PROP_FRAME_HEIGHT), (int)cap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
	
	pt.setFOV(2.0);

	while(1) {
		cap >> pt.in;
		//write main loop
		pt.culTf();

		cv::imshow("cap",pt.in);
		cv::imshow("dst",pt.out);
		if (cv::waitKey(100)!=-1)	break;
	}

	return 0;
}

