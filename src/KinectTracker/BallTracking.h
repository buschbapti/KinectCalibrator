#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace cv;

class BallTracking{
private:
	static const float RedCoeff = 1; // 100% de rouge
    static const float GreenCoeff = 0.5; // 80% du vert
    static const float BlueCoeff = -1; // - 200% du bleu

    unsigned int coeffColor(int r, int g, int b) const;

public:
	BallTracking();

	vector<float> get2DCoordinates(const Mat& image) const;

	float getDepthCoordinate(const float x, const float y) const;

	int send3DCoordinates(const vector<float>& point) const;
};