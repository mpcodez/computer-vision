//
#include <fstream>
//
using namespace std ;
//
typedef unsigned char uchar ;
//
const int W = 240 ;
const int H = 240 ;
//
void save( uchar img[][240] ) ;
//
int main( int argc , char* argv[] )
{
    ifstream fin       ;
    //
    int      r , c     ;
    //
    string   s         ;
    char     ch        ;
    //
    uchar    img[480][480] ;
    //
    //
    //
    fin . open( "teapot.pgm" ) ;
    //
    fin >> s ; // P5
    fin >> s ; // 775
    fin >> s ; // 900
    fin >> s ; // 255
    //
    // fin >> ch ; // would skip the newline
    //
    fin . read( &ch , 1 ) ; // reads newline
    //
    for( r = 0 ; r < 480 ; r++ )
    {
        for( c = 0 ; c < 480 ; c++ )
        {
            fin . read( &ch , 1 ) ;
            //
            img[r][c] = (uchar)ch ;
        }
    }
    //
    fin . close() ;
    
    uchar teapot[240][240];
    
    for( r = 0 ; r < 240 ; r=r+1 )
    {
        for( c = 0 ; c < 240 ; c=c+1 )
        {
            teapot[r][c] = (uchar)img[r*2][c*2];
        }
    }
    
    save( teapot ) ;
    
    /*
    //
    for( r = 0 ; r < H ; r++ )
    {
        for( c = 0 ; c * 2 < W ; c++ )
        {
            uchar tmp     = img[r][c]     ;
            img[r][c]     = img[r][W-c-1] ;
            img[r][W-c-1] = tmp           ;
        }
    }
    //
    save( img ) ;
    */
    //
    return 0 ;
}
//
void save( uchar img[][240] )
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P5" << endl ;
    //
    fout << "240 240" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 240 ; r++ )
    {
        for( int c = 0 ; c < 240 ; c++ )
        {
            fout << img[r][c] << flush ;
            //
            //               NOT endl !!!
        }
    }
    //
    fout . close() ;
}