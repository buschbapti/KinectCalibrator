#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace cv;

class BallTracking{
private:
	static const float RedCoeff;
    static const float GreenCoeff;
    static const float BlueCoeff;

    unsigned int coeffColor(int r, int g, int b) const;

public:
	BallTracking();

	vector<int> get2DCoordinates(const Mat& image) const;

	float getDepthCoordinate(const float x, const float y) const;

	int send3DCoordinates(const vector<int>& point) const;
};

const float BallTracking::RedCoeff = 1;
const float BallTracking::GreenCoeff = 0.5;
const float BallTracking::BlueCoeff = -1;