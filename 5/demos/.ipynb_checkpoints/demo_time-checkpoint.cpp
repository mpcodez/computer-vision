//
#include <time.h>
#include <stdlib.h>
//
#include <iostream>
//
using namespace std ;
//
int main( int argc , char* argv[] )
{
    int  seed , j , n    ;
    //
    seed = time( NULL )  ; // seed = your Student ID number
    //
    cout << seed << endl ;
    //
    cout << seed * 1.0 / ( 60 * 60 * 24 * 365 ) << endl ;
    //
    cout         << endl ; // leap day < one-tenth of one %
    //
    //
    //
    srand( seed )        ; // reproduce *same* observations
    //
    //
    //
    for( j = 0 ; j < 10 ; j++ )
    {
        n = ( 1 + rand() % 255 ) ; // threshold, instead of 128
        //
        cout << n << endl ;
    }
    //
    return 0 ;
}
//
// end
//
