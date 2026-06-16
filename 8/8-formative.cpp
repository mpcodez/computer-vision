#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    int lowThres = 50;
    int highThres = 150;
    
    for (int i = 0; i < 9; ++i) {
        string path = "pictures/" + pictures[i] + ".png";
        Mat img = imread(path, IMREAD_COLOR);

        cout << pictures[i] << " channels: " << img.channels() << endl;

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        cout << " size: " << gray.size() << " cols: " << gray.cols << " rows: " << gray.rows << endl;

        Mat blurred;
        blur(gray.clone(), blurred, Size(3,3));
        
        Mat tmp;
        blurred.convertTo(tmp, CV_32F);

        Mat tmp8;
        tmp.convertTo(tmp8, CV_8U);

        Mat edges;
        Canny(tmp8, edges, lowThres, highThres);

        Mat edges_inv;
        bitwise_not(edges, edges_inv);

        string out = "formative/" + pictures[i] + "_canny.png";
        imwrite(out, edges_inv);
        cout << " wrote: " << out << endl;
    }

    return 0;
}

