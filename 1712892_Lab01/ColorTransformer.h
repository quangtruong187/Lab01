#pragma once

#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

namespace ColorTransformer {
	/*
	hàm nhận vào 1 ảnh, trả ra histogram của ảnh
	Hàm trả về:
		trả ra 1 mảng chứa mảng các histogram
	*/
	vector<int[256]> Hist(const Mat& sourceImage) 
	{
    //vector chưa từng màu của kênh màu
		vector<int[256]> result; 
    // ảnh gốc rỗng
		if (sourceImage.empty())    
			return move(result);

		int widthStep = sourceImage.step[0];
		int Channel = sourceImage.step[1];
		int rows = sourceImage.rows;
		int cols = sourceImage.cols;

    //gán mỗi kênh màu tối đa 256 giá trị, khởi tạo bằng 0
		for (int i = 0; i < Channel; i++) 
		{
  		result.emplace_back();
		}

		uchar* pData = (uchar*)sourceImage.data;//duyệt ảnh
		for (int i = 0; i < rows; i++) 
		{
			uchar* pRow = pData;
			for (int j = 0; j < cols; j++) 
			{
				for (int z = 0; z < Channel; z++) 
				{
          //ứng với từng kênh màu, tăng giá trị tại vị trí giá trị của kênh màu đó thêm 1 (trong histogram equalization mới chia cho tất cả số điểm ảnh, theo thuật toán trên lớp lý thuyết)
					result[z][pRow[z]] += 1;
				}
				pRow += Channel;
			}
			pData += widthStep;
		}
		return move(result);
	}

	/*
	Hàm so sánh hai ảnh
	Tham so :
		image1 : ảnh thứ nhất
		image2 : ảnh thứ hai
	Hàm trả về:
		độ đo sự tương đồng giữa hai ảnh
	*/
	double CompareImage(const Mat& image1, const Mat& image2)
	{
		// Sử dụng độ đo Alternative Chi-Square
		vector<int[256]> imageRGB_1, imageRGB_2;
		int image1_chanel = image1.step[1];
		int image2_chanel = image2.step[1];

		if (image1_chanel != image2_chanel)
			return -1;

		imageRGB_1 = Hist(image1);
		imageRGB_2 = Hist(image2);

		double result = 0;

		for (int i = 0; i < image1_chanel; i++) 
		{
			for (int j = 0; j < 256; j++)
			{
				result += 2 * (imageRGB_1[i][j] - imageRGB_2[i][j]) * (imageRGB_1[i][j] - imageRGB_2[i][j]) / (imageRGB_1[i][j] + imageRGB_2[i][j]);
			}
		}
		return result;
	}
}



