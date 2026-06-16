//
#include <fstream>
//
#include <iostream>
//
using namespace std ;


typedef unsigned char uchar ;
//
//
void save( uchar img[][440] ) ;


class Circle
{
   private : 
      //
      int x ;
      int y ;
      int r ;
   //
   public :
      //
      Circle( int xc=0 , int yc=0, int rc=0) : x(xc) , y(yc) , r(rc)
      {
      }
      //
      Circle( const Circle & c )
      {
         cout << "copy" << endl ;
         //
         x = c . x ;
         y = c . y ;
         r = c . r ;
      }
      //
      ~Circle()
      {
         cout << "destructor" << endl ;
      }
      //
      bool contains( int xp , int yp ) const
      {
         int dx = xp - x ;
         int dy = yp - y ;
         //
         return dx*dx + dy*dy <= r*r ;
      }
   //
} ;
//
//
//
int main( int argc , char* argv[] )
{
    
    Circle big = Circle(200,200,120);
    Circle small = Circle(200,200,40);
    
    uchar    img[400][440] ;
    //
    //
    for( int c = 0 ; c < 200 ; c++ )
    {
        for( int r = 0 ; r < 400 ; r++ )
        {
            if(big.contains(r, c) == true && small.contains(r, c) == false){
                img[r][c] = 85;
            }else{
                img[r][c] = 0;
            }
        }
    }
    
    for( int c = 200 ; c < 240 ; c++ )
    {
        for( int r = 0 ; r < 400 ; r++ )
        {
            img[r][c] = 255;
        }   
    }
    
    for( int c = 240 ; c < 440 ; c++ )
    {
        for( int r = 0 ; r < 400 ; r++ )
        {
            if(big.contains(r, c-40) == true && small.contains(r, c-40) == false){
                img[r][c] = 85;
            }else{
                img[r][c] = 170;
            }
        }
    }
    
    //
    save( img ) ;
    //
    return 0 ;
}
//
void save( uchar img[][440] )
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P5" << endl ;
    //
    fout << "440 400" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 400 ; r++ )
    {
        for( int c = 0 ; c < 440 ; c++ )
        {
            fout << img[r][c] << flush ;
            //
            //               NOT endl !!!
        }
    }
    //
    fout . close() ;
}
//
// end
//