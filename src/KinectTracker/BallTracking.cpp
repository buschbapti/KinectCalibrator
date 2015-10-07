#include "BallTracking.h"

BallTracking::BallTracking(){}

unsigned int BallTracking::coeffColor(int r, int g, int b) const{
  if(r+g+b > 255){
    return 255;
  }
  else if (r+g+b < 0){
    return 0;
  }
  else{
    return r+g+b;
  }
}

vector<float> BallTracking::get2DCoordinates(const Mat& image) const{
  // initialize restult vector
  vector<float> pos(2,-1);
  // clone image
  Mat clone_image = image.clone();
  // loop through all pixel coordinates
  for(int y=0;y<clone_image.rows;y++){
    for(int x=0;x<clone_image.cols;x++){
        // get pixel
        Vec3b pixel = clone_image.at<Vec3b>(Point(x,y));
        int r = pixel[2]*this->RedCoeff;
        int g = pixel[1]*this->GreenCoeff;
        int b = pixel[0]*this->BlueCoeff;
        // modify its color
        unsigned int red = this->coeffColor(r,g,b);
        pixel[2] = red;
        pixel[1] = red;
        pixel[0] = red;
        // set pixel
        clone_image.at<Vec3b>(Point(x,y)) = pixel;
    }
  }
  Mat tresh_image;
  threshold( clone_image, tresh_image, 200, 255, 3 );

  // Reduce the noise so we avoid false circle detection
  Mat gray_image;
  cvtColor(tresh_image, gray_image, CV_BGR2GRAY);
  GaussianBlur( gray_image, gray_image, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;
  /// Apply the Hough Transform to find the circles
  HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, 1, gray_image.rows/8, 100, 20, 0, 0 );
  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( clone_image, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( clone_image, center, radius, Scalar(0,0,255), 3, 8, 0 );
      pos[0] = center.x;
      pos[1] = center.y;
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", clone_image );
  waitKey(1);
  return pos;
}

float BallTracking::getDepthCoordinate(const float x, const float y) const{
  return 0;
}
  
int BallTracking::send3DCoordinates(const vector<float>& point) const{
  return 0;
}

/** @function main */
int main(int argc, char** argv)
{
  Mat bgr_image;
  BallTracking ball;

  /// Read the image
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
    return -1;

  for(;;){

    Mat bgr_image;
    cap >> bgr_image; // get a new frame from camera

    // get the 2D coordinates
    vector<float> pos = ball.get2DCoordinates(bgr_image);
    printf("x = %f, y = %f\n", pos[0], pos[1]);

    // // Threshold the HSV image, keep only the red pixels
    // Mat orange_hue_img;
    // inRange(hsv_image, cv::Scalar(10, 150, 150), cv::Scalar(20, 255, 255), orange_hue_img);

    /// Reduce the noise so we avoid false circle detection
    // GaussianBlur( orange_hue_img, orange_hue_img, Size(9, 9), 2, 2 );

    // vector<Vec3f> circles;
    
    // /// Apply the Hough Transform to find the circles
    // HoughCircles( orange_hue_img, circles, CV_HOUGH_GRADIENT, 1, orange_hue_img.rows/8, 100, 20, 0, 0 );

  
     imshow("BallTracking", bgr_image);
     waitKey(1);
 }

  return 0;
}