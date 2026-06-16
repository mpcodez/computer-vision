#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah",
                         "chess", "crab_spider", "peppers", "peru", "seahorse"};
    
    for (int i = 0; i < 9; i++) {
        string inPath = "pictures/" + pictures[i] + ".png";
        Mat temp = imread(inPath, IMREAD_COLOR);
        if (temp.empty()) {
            cerr << "Failed to read " << inPath << endl;
            continue;
        }

        cout << pictures[i] << endl;

        Mat gray;
        cvtColor(temp, gray, COLOR_BGR2GRAY);

        Mat color_img;
        cvtColor(gray, color_img, COLOR_GRAY2BGR);

        for (int r = 1; r < gray.rows - 1; r++) {
            for (int c = 1; c < gray.cols - 1; c++) {
                int n1 = gray.at<uchar>(r - 1, c - 1);
                int n2 = gray.at<uchar>(r - 1, c);
                int n3 = gray.at<uchar>(r - 1, c + 1);
                int n4 = gray.at<uchar>(r, c - 1);
                int n5 = gray.at<uchar>(r, c + 1);
                int n6 = gray.at<uchar>(r + 1, c - 1);
                int n7 = gray.at<uchar>(r + 1, c);
                int n8 = gray.at<uchar>(r + 1, c + 1);

                int Gx = (n3 + (2 * n5) + n8) - (n1 + (2 * n4) + n6);
                int Gy = (n6 + (2 * n7) + n8) - (n1 + (2 * n2) + n3);

                int G = abs(Gx) + abs(Gy);

                if (G > 25) {
                    color_img.at<Vec3b>(r, c)[0] = 0;
                    color_img.at<Vec3b>(r, c)[1] = 0;
                    color_img.at<Vec3b>(r, c)[2] = 255;
                }
            }
        }

        imwrite("summative/" + pictures[i] + ".png", color_img);
    }

    return 0;
}
