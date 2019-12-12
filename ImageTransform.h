#pragma once
#include <atlimage.h>
#include<opencv.hpp>
class ImageTransform {
public:
	ImageTransform() {};
	/*MatToCImage
	*��飺
	*	OpenCV��MatתATL/MFC��CImage����֧�ֵ�ͨ���ҶȻ���ͨ����ɫ
	*������
	*	mat��OpenCV��Mat
	*	cimage��ATL/MFC��CImage
	*/
	void MatToCImage(cv::Mat& mat, CImage& cimage);


	/*CImageToMat
	*��飺
	*	ATL/MFC��CImageתOpenCV��Mat����֧�ֵ�ͨ���ҶȻ���ͨ����ɫ
	*������
	*	cimage��ATL/MFC��CImage
	*	mat��OpenCV��Mat
	*/
	void CImageToMat(CImage& cimage, cv::Mat& mat);
};

