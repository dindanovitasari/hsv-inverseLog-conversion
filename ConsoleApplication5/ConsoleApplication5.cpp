// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

Mat calculateLog(Mat hsvChannel)
{
	//clone image
	Mat var_inputImage = hsvChannel.clone();
	//convert to float
	hsvChannel.convertTo(hsvChannel, CV_32FC1);

	for (int vrow = 0; vrow < hsvChannel.rows; vrow++) {
		for (int vcol = 0; vcol < hsvChannel.cols; vcol++) {
			unsigned char varInput = var_inputImage.at<uchar>(vcol, vrow);
			float d_logx = 32 * (log(varInput + 1 * 1.0) / log(2.0));
			hsvChannel.at<float>(vcol, vrow) = d_logx;
		}
	}

	hsvChannel.convertTo(hsvChannel, CV_8UC1);
	return hsvChannel;
}
Mat calculateInvLog(Mat hsvChannel)
{
	Mat var_inputImage = hsvChannel.clone();
	hsvChannel.convertTo(hsvChannel, CV_32FC1);

	for (int vrow = 0; vrow < hsvChannel.rows; vrow++) {
		for (int vcol = 0; vcol < hsvChannel.cols; vcol++) {
			float d_logx = pow(2.0, (var_inputImage.at<uchar>(vcol, vrow)*1.0 / 32)) - 1;
			hsvChannel.at<float>(vcol, vrow) = d_logx;
		}
	}
	hsvChannel.convertTo(hsvChannel, CV_8UC1);
	return hsvChannel;
}

int main()
{
	Mat image, hsvResult, hsvChannel[3];
	//int i, col, row, index;
	image = imread("image.jpg");
	imshow("Lena.jpg", image);
	//convert RGB to HSV
	cvtColor(image, hsvResult, CV_BGR2HSV);
	imshow("HSV Image", hsvResult);
	imwrite("HSV image.jpg", hsvResult);
	//split HSV channel
	split(hsvResult, hsvChannel);
	imshow("Channel H", hsvChannel[0]);
	imshow("Channel S", hsvChannel[1]);
	imshow("Channel V", hsvChannel[2]);
	imwrite("Channel H.jpg", hsvChannel[0]);
	imwrite("Channel S.jpg", hsvChannel[1]);
	imwrite("Channel V.jpg", hsvChannel[2]);
	// perform log and invers log grey array 
	Mat hsvClonelog[3], hsvCloneInv[3];
	// for 32 * log2(x+1)
	for (int k = 0; k < 3; k++) {
		hsvClonelog[k] = hsvChannel[k].clone();
		hsvClonelog[k] = calculateLog(hsvClonelog[k]);
	}

	// image 1
	imwrite("LOG_0.jpg", hsvClonelog[0]);
	imshow("Image LOG 0", hsvClonelog[0]);

	// image 2
	imwrite("LOG_1.jpg", hsvClonelog[1]);
	imshow("Image LOG 1", hsvClonelog[1]);

	// image 3
	imwrite("LOG_2.jpg", hsvClonelog[2]);
	imshow("Image LOG 2", hsvClonelog[2]);

	// for pow(2, x / 32) - 1
	for (int f = 0; f < 3; f++) {
		hsvCloneInv[f] = hsvChannel[f].clone();
		hsvCloneInv[f] = calculateInvLog(hsvCloneInv[f]);
	}

	// image 1
	imwrite("InversLOG_0.jpg", hsvCloneInv[0]);
	imshow("InversImage LOG 0", hsvCloneInv[0]);

	// image 2
	imwrite("InversLOG_1.jpg", hsvCloneInv[1]);
	imshow("InversImage LOG 1", hsvCloneInv[1]);

	// image 3
	imwrite("InversLOG_2.jpg", hsvCloneInv[2]);
	imshow("InversImage LOG 2", hsvCloneInv[2]);

	waitKey(0);
	return 0;
}
