#include <fstream>
//
using namespace std ;
//
typedef unsigned char uchar ;
//
//
void save(uchar img[][512], int num) ;
//
//
int main( int argc , char* argv[] )
{
    uchar img[384][512] ;

    for( int c = 0 ; c < 512 ; c++ )
    {
        for( int r = 0 ; r < 384 ; r++ )
        {
            img[r][c] = (uchar)(int)(c/2);
            if(c >= 64 && c < 128 && r >= 64 && r < 128){
                img[r][c] = (uchar)127;
            }
            if(c >= 384 && c < 448 && r >= 64 && r < 128){
                img[r][c] = (uchar)127;
            }
            if(c >= 64 && c < 128 && r >= 192 && r < 256){
                    img[r][c] = (uchar)127;
            }
        }
    }
    
    
    for(int pic = 0; pic < 320; pic++){
        
        for( int c = 64-pic-1 ; c <= 128+pic ; c++ )
        {
            for( int r = 192 ; r < 256 ; r++ )
            {
                if(c == 64+pic-1){
                    img[r][c] = (uchar)(int)(c/2);
                }else if(c == 128+pic){
                    img[r][c] = (uchar)127;
                }
            }
        }
        
        save(img, pic);
    }
    return 0 ;
}
//
void save(uchar img[][512], int num)
{
    //
    ofstream fout          ;
    //
    //
    string name = "000" + to_string(num);
    fout.open( "img/frame" + name.substr(name.size()-3, name.size()) + ".pgm" ) ;
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
