#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ColorTransformer.h"
#include "String"
#include "Converter.h"

using namespace cv;
using namespace std;

void ShowImages(Mat src, Mat dest) {
	namedWindow("Source Image");
	imshow("Source Image", src);
	namedWindow("Destination Image");
	imshow("Destination Image", des);
	waitKey(0);
}

int main(int argc, char** argv)
{
	Converter converter = Converter();
	//<ProgramName.exe> <Command> <InputPath> <CommandArguments>
	string command = string(argv[1]);
	string path = string(argv[2]);
	Mat source = imread(path, cv::IMREAD_COLOR);
	Mat des;
	if (command.find("rgb2hsv") != -1)
	{
		if (Converter::RGB2HSV(source, des))
  		ShowImages(source, dest);
		else cout << "Conversion failed";
		return 0;
	}
	else if (command.find("hsv2rgb") != -1)
	{
		if (Converter::HSV2RGB(source, des))
  		ShowImages(source, dest);
		else cout << "Conversion failed";
		return 0;
	}
	else if (command.find("compare") != -1) 
	{
		string DesPath = string(argv[3]);
		des = imread(DesPath, cv::IMREAD_COLOR);
		cout << "Compare result: " << ColorTransformer::CompareImage(source, des);
	}
}
