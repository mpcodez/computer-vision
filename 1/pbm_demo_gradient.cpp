//
#include <fstream>
//
using namespace std ;
//
typedef unsigned char uchar ;
//
//
void save( uchar img[][512] ) ;
//
//
int main( int argc , char* argv[] )
{
    //
    uchar    img[384][512] ;
    //
    //
    for( int c = 0 ; c < 512 ; c++ )
    {
        for( int r = 0 ; r < 384 ; r++ )
        {
            img[r][c] = (uchar)(int)(c/2);
        }
    }
    //
    save( img ) ;
    //
    return 0 ;
}
//
void save( uchar img[][512] )
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P5" << endl ;
    //
    fout << "512 384" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 384 ; r++ )
    {
        for( int c = 0 ; c < 512 ; c++ )
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
