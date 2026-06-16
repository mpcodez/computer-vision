//
#include <vector>
//
#include <iostream>
//
#include <fstream>
//
using namespace std ;
//
int main( int argc , char* argv[] )
{
    ifstream    fin    ;
    //
    vector<int> v      ;
    //
    int         val    ;
    //
    string      fname  ;
    //
    //
    //
    cout << "Filename: " << flush ;
    //
    cin  >> fname ;
    //
    //
    //
    fin . open( fname + ".txt" ) ;
    //
    while( fin >> val )
    {
        v . push_back( val ) ;    
    }
    //
    fin . close() ;
    //
    //
    //
    cout << v . size() << " : " << flush ;
    //
    for( int val : v )
    {
        cout << val << " " << flush ;
    }
    
    int min = 1000;
    int ind = 0;
    int count = 0;
    
    for( int val : v )
    {
        if(min > val){
            min = val;
            ind = count;
        }
        count += 1;
    }
    
    int min2 = 1000;
    int ind2 = 0;
    count = 0;
    
    for( int val : v )
    {
        if(min2 > val && count != ind){
            min2 = val;
            ind2 = count;
        }
        count += 1;
    }
    
    cout << endl ;
    cout << "Minimum Value Of " << min << " at index: " << ind << endl ;
    cout << "Minimum Value Of " << min2 << " at index: " << ind2 << endl ;
    cout << endl ;
    //
    //
    //
    return 0 ;
}
//
