#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// tmp of image processing program

int setOutput(int x, int y, int col, int row, char b, char g, char r, cv::Mat out) {
	if (0<=x && x<col && 0<=y && y<row) {
		out.data[3*(x + col*y)] = b;
		out.data[3*(x + col*y) + 1] = g;
		out.data[3*(x + col*y) + 2] = r;
	}
	return 0;
}

int main() {
	cv::Mat in;
	cv::Mat out;
//	cv::Mat rtm;
//	rtm = (cv::Mat_<double>(3,3) << 1.0, .0, .0, .0, 1/cos(M_PI/3.0), .0, .0, .0, 1.0);
	double rtm[9] = {1.0, .0, .0, .0,  1/cos(4*M_PI/10.0), .0, .0, .0, 1.0};
	// rotation around x axis
	double stm[9] = {1.0, .0, .0, .0, 1.0, .0, .0, .0, 1.0};
	//

	int x, y, t;
	int x0, y0, t0;
	int row, col;
	double r0, r1, rz0, rz1;
	double a;

	cv::VideoCapture cap(1);
	cv::namedWindow("cap");
	cv::namedWindow("dst");

	if (!cap.isOpened())	return -1;
	std::cout << "start cap channel 1\n";

	row = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	col = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	out.create(row, col, CV_8UC3);
	stm[5] = -row;		//the tekito

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			a = rtm[j + i*3];
			std::cout << a << " ";
		}
		std::cout<<std::endl;
	}

	while(1) {
		cap >> in;
		//write main loop
		for (int i=row/4; i<3*row/4; i++) {			//y
			stm[0] = -2.0/row*i + 2.5;
			stm[2] = (double)(-col*stm[0]/2.0+col/2);
			for (int j=col/4; j<3*col/4; j++) {		//x
				x0 = (int)(rtm[0]*j + rtm[1]*i + rtm[2]);
				y0 = (int)(rtm[3]*j + rtm[4]*i + rtm[5]);
				t0 = (int)(rtm[6]*j + rtm[7]*i + rtm[8]);
				x = (int)(stm[0]*x0 + stm[1]*y0 + stm[2]);
				y = (int)(stm[3]*x0 + stm[4]*y0 + stm[5]);
				t = (int)(stm[6]*x0 + stm[7]*y0 + stm[8]);

				setOutput(x, y, col, row, in.data[3*(i*col+j)], in.data[3*(i*col+j)+1], in.data[3*(i*col+j)+2], out);
			}
		}

		cv::imshow("cap",in);
		cv::imshow("dst",out);
		if (cv::waitKey(100)!=-1)	break;
	}

	return 0;
}

