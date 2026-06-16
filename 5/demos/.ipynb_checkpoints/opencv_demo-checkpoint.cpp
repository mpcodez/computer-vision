//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
//
#include <iostream>
//
using namespace std ;
using namespace cv ;
//
int main( int argc , char* argv[] )
{
   //     height width   uchar
   //
   Mat img( 480 , 640 , CV_8UC3 , Scalar(0,0,255) )    ; // red (not blue)
   //
   //        x     y
   //
   Point p( 160 , 100 ) , q( 240 , 180 ) ;
   //
   rectangle( img , p , q , Scalar(255,0,0) , FILLED ) ; // blue (not red)
   //
   imwrite( "one_square.png" , img ) ;
   //
   return 0 ;
}
//
// end
//