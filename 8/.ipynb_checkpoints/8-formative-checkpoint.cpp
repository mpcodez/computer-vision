#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    for (int i = 0; i < 9; ++i) {
        string path = "pictures/" + pictures[i] + ".png";
        Mat img = imread(path, IMREAD_COLOR);
        if (img.empty()) {
            cerr << "Could not open " << path << endl;
            continue;
        }

        int nch = img.channels();
        cout << pictures[i] << " channels: " << nch << endl;

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Size s = gray.size();
        int cols = gray.cols;
        int rows = gray.rows;
        Mat gray_clone = gray.clone();
        cout << " size: " << s << " cols: " << cols << " rows: " << rows << endl;

        Mat blurred;
        blur(gray_clone, blurred, Size(3,3));

        Mat blurred32f, blurred64f;
        blurred.convertTo(blurred32f, CV_32F);
        blurred.convertTo(blurred64f, CV_64F);

        Mat kx1, ky1, kx0, ky0;
        getDerivKernels(kx1, ky1, 1, 0, 3, true, CV_32F);
        getDerivKernels(kx0, ky0, 0, 1, 3, true, CV_32F);

        Mat kernelX = kx1 * ky1.t();
        Mat kernelY = kx0 * ky0.t();

        Mat gradX_fd_16s, gradY_fd_16s;
        filter2D(blurred32f, gradX_fd_16s, CV_16S, kernelX);
        filter2D(blurred32f, gradY_fd_16s, CV_16S, kernelY);

        Mat gradX_fd_32s, gradY_fd_32s;
        filter2D(blurred32f, gradX_fd_32s, CV_32S, kernelX);
        filter2D(blurred32f, gradY_fd_32s, CV_32S, kernelY);

        Mat filtered_same_depth;
        filter2D(blurred, filtered_same_depth, -1, Mat::ones(3,3,CV_32F) / 9.0f);

        Mat sobelX, sobelY;
        Sobel(blurred, sobelX, CV_16S, 1, 0, 3);
        Sobel(blurred, sobelY, CV_16S, 0, 1, 3);

        Mat abs_sobelX, abs_sobelY;
        convertScaleAbs(sobelX, abs_sobelX);
        convertScaleAbs(sobelY, abs_sobelY);

        Mat grad_mag;
        addWeighted(abs_sobelX, 0.5, abs_sobelY, 0.5, 0, grad_mag);

        Mat edges;
        Canny(grad_mag, edges, 50, 150);

        Mat edges_inv;
        bitwise_not(edges, edges_inv);

        string out = "formative/" + pictures[i] + "_canny.png";
        imwrite(out, edges_inv);
        cout << " wrote: " << out << endl;
    }

    return 0;
}
