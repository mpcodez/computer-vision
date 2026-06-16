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
    cout << endl ;
    
    int vSize = v.size();
    
    while(vSize != 1){
        
     
        ///////
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

        if( ind < ind2 )
        {
            int t = ind ;
            ind = ind2 ;
            ind2 = t ;
        }
        v.erase(v.begin() + ind);
        v.erase(v.begin() + ind2);

        v.push_back(min + min2);

        ///////
        
        cout << v . size() << " : " << flush ;
        for( int val : v )
        {
            cout << val << " " << flush ;
        }
        cout << endl ;
        
        vSize -= 1;
    }

    return 0 ;
}
//

