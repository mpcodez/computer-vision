#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    int ratio = 2;
    
    for(int i=1;i<=100;i++){
        
        int lowThres = i;
        int highThres = i*ratio;
        
        string path = "pictures/aloha.png";
        Mat img = imread(path, IMREAD_COLOR);

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Mat blurred;
        blur(gray, blurred, Size(3,3));

        Mat edges;
        Canny(blurred, edges, lowThres, highThres);

        Mat edges_inv;
        bitwise_not(edges, edges_inv);

        string name = "000" + to_string(i);
        imwrite("challenge2/frame" + name.substr(name.size()-3, name.size()) + ".png", edges_inv);
    }

    return 0;
}