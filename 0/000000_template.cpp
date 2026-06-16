//
#include <iostream>
using namespace std;
typedef unsigned char uchar;
//

int main(int argc, char* argv[]){
    char x=0;
    uchar y=0;
    for(int z = 0; z < 256; z++){
        x++;
        y++;
        std::cout << (int)x << " " << (int)y << std::endl;
    }
    return 0;
}