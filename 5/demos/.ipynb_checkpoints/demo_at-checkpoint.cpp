//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//
#include <iostream>
//
using namespace std ;
using namespace cv ;
//
int main( int argc , char* argv[] )
{
   Mat img = imread( "elvis.png" ) ;
   //
   cout << img . size() << endl ;
   //
   cout << img . channels() << endl ;
   //
   //
   //
   cout << img . at< Vec3b > ( 0 , 0 ) << endl ;
   //
   Vec3b pix = img . at< Vec3b > ( 0 , 0 ) ;
   //
   cout << ( (int)( pix[0] ) ) << endl ;
   cout << ( (int)( pix[1] ) ) << endl ;
   cout << ( (int)( pix[2] ) ) << endl ;
   //
   //
   //
   cvtColor( img , img , COLOR_BGR2GRAY ) ;
   //
   cout << img . size() << endl ;
   //
   cout << img . channels() << endl ;
   //
   uchar val = img . at< uchar > ( 0 , 0 ) ;
   //
   cout << ( (int)( val ) ) << endl ;
   //
   //
   //
   img = imread( "elvis.png" , IMREAD_UNCHANGED ) ;
   //
   cout << img . size() << endl ;
   //
   cout << img . channels() << endl ;
   //
   val = img . at< uchar > ( 0 , 0 ) ;
   //
   cout << ( (int)( val ) ) << endl ;
   //
   //
   //
   return 0 ;
}
//
// end
//
