//
#include <fstream>
//
#include <iostream>
//
using namespace std ;


typedef unsigned char uchar ;
//
//
void save( uchar img[][640] ) ;


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
    
    ifstream fin   ;
    Circle arr[12] ;
    int j , x , y  ;

    fin . open( "xy.txt" ) ;
    for( j = 0 ; j < 12 ; j++ )
    {
       fin >> x ;
       fin >> y ;
       //
       arr[j] = Circle( x , y , 40 );
    }
    fin . close() ;

    
    //
    uchar    img[480][640] ;
    //
    //
    
    int count = 3;
    int color = 1;
    // 1 = 0 = red
    // 2 = 40 = green
    // 3 = 80 = blue
    // 5 = 120 = red
    // 6 = 160 = green
    // 7 = 200 = blue
    
    for( int r = 0 ; r < 480 ; r++ )
    {
        if(count >= 0 && count < 6){
            color = 1;
        }else if(count >= 6 && count < 12){
            color = 2;
        }else if(count >= 12 && count < 18){
            color = 3;
        }
        
        
        for( int c = 0 ; c < 640 ; c++ )
        {
            
            img[r][c] = color;
            
            int cnt = 0;
                
            for( Circle & circ : arr )
            {   
                if(circ.contains(c, r)){
                    
                    if(cnt >= 0 && cnt < 4){
                        img[r][c] = 5;
                    }
                    if(cnt >= 4 && cnt < 8){
                        img[r][c] = 6;
                    }
                    if(cnt >= 8 && cnt < 12){
                        img[r][c] = 7;
                    }
                    break;
                }
                cnt += 1;
            }
        }
        
        count += 1;
            
        if(count == 18){
            count = 0;
        }
    }
    
    //
    save( img ) ;
    //
    return 0 ;
}
//
void save( uchar img[][640] )
{
    //
    ofstream fout          ;
    //
    
    // 1 = 0 = red
    // 2 = 40 = green
    // 3 = 80 = blue
    // 5 = 120 = red
    // 6 = 160 = green
    // 7 = 200 = blue
    
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P6" << endl ;
    //
    fout << "640 480" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 480 ; r++ )
    {
        for( int c = 0 ; c < 640 ; c++ )
        {
            if(img[r][c] == 1){
                fout << (uchar) 255 << (uchar) 0 << (uchar) 0 << flush ;
            }
            if(img[r][c] == 2){
                fout << (uchar) 0 << (uchar) 255 << (uchar) 0 << flush ;
            }
            if(img[r][c] == 3){
                fout << (uchar) 0 << (uchar) 0 << (uchar) 255 << flush ;
            }
            if(img[r][c] == 5){
                fout << (uchar) 200 << (uchar) 0 << (uchar) 0 << flush ;
            }
            if(img[r][c] == 6){
                fout << (uchar) 0 << (uchar) 176 << (uchar) 0 << flush ;
            }
            if(img[r][c] == 7){
                fout << (uchar) 0 << (uchar) 0 << (uchar) 165 << flush ;
            }
            
            /**
            if(img[r][c] == 0){
                fout << (uchar) 255 << (uchar) 255 << (uchar) 255 << flush ;
            }else if(img[r][c] == 100){
                fout << (uchar) 0 << (uchar) 255 << (uchar) 0 << flush ;
            }else{
                fout << (uchar) 255 << (uchar) 0 << (uchar) 0 << flush ;
            }
            **/
            
            
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