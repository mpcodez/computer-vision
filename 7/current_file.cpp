#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;


int getG(Mat gray, int r, int c){
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

    return G;
}

int main(int argc, char* argv[]) {
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah",
                         "chess", "crab_spider", "peppers", "peru", "seahorse"};

    double threshold = 75.0;

    for (int i = 0; i < 9; i++) {
        Mat temp = imread("pictures/" + pictures[i] + ".png", IMREAD_COLOR);

        cout << pictures[i] << endl;

        Mat gray;
        cvtColor(temp, gray, COLOR_BGR2GRAY);

        Mat color_img;
        cvtColor(gray, color_img, COLOR_GRAY2BGR);

        Mat Gx_mat = Mat::zeros(gray.size(), CV_32F);
        Mat Gy_mat = Mat::zeros(gray.size(), CV_32F);
        Mat mag_mat = Mat::zeros(gray.size(), CV_32F);

        for (int r = 2; r < gray.rows - 2; r++) {
            for (int c = 2; c < gray.cols - 2; c++) {
                
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
                
                
                // 4 3 2
                // 1 . 1
                // 2 3 4

                // 1 2 3
                // 4 . 5
                // 6 7 8
                
                if (G > threshold) {

                    double angle = atan2((double)Gy, (double)Gx) * 180.0 / M_PI;
                    if (angle < 0) angle += 180.0;
    
                    int neighbor1 ;//= 0.0f;
                    int neighbor2 ;//= 0.0f;
    
                    if ((angle >= 0.0 && angle < 22.5) || (angle >= 157.5 && angle < 180.0)) {
                        neighbor1 = getG(gray, r, c - 1);
                        neighbor2 = getG(gray, r, c + 1);
                    } else if (angle >= 22.5 && angle < 67.5) {
                        neighbor1 = getG(gray, r + 1, c + 1);
                        neighbor2 = getG(gray, r - 1, c - 1);
                    } else if (angle >= 67.5 && angle < 112.5) {
                        neighbor1 = getG(gray, r + 1, c);
                        neighbor2 = getG(gray, r - 1, c);
                    } else {
                        neighbor1 = getG(gray, r + 1, c - 1);
                        neighbor2 = getG(gray, r - 1, c + 1);
                    }
    
                    if (G > neighbor1 && G > neighbor2) {
                        color_img.at<Vec3b>(r, c)[0] = 0;
                        color_img.at<Vec3b>(r, c)[1] = 0;
                        color_img.at<Vec3b>(r, c)[2] = 255;
                    }
                }
            }
        }

        imwrite("challenge1/" + pictures[i] + ".png", color_img);
    }

    return 0;
}
