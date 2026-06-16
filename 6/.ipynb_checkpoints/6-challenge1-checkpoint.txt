#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// BLUE, GREEN, RED --> 0, 1, 2 --> blue = img[100,100,0]

float distance(int b, int g, int r, Vec3b split) {
      return sqrt(pow((float)b - (float)split[0], 2) + pow((float)g - (float)split[1], 2) + pow((float)r - (float)split[2], 2));
}

int main(int argc, char* argv[])
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    for(int picture = 0; picture < 9; picture++)
    {
        Mat img = imread("pictures/" + pictures[picture] + ".png");
        if(img.empty()){
            cerr << "Failed to load image: " << pictures[picture] << ".png" << endl;
            continue;
        }
        
        cout << pictures[picture] << endl;
        
        
        vector<Vec3b> splits; //k = whatever
        splits.push_back(Vec3b(51, 51, 51));
        splits.push_back(Vec3b(102, 102, 102));
        splits.push_back(Vec3b(153, 153, 153));
        splits.push_back(Vec3b(204, 204, 204));
        
        vector<Vec3b> prev; //k = whatever
        prev.push_back(Vec3b(255, 255, 255));
        prev.push_back(Vec3b(0, 0, 255));
        prev.push_back(Vec3b(0, 255, 0));
        prev.push_back(Vec3b(255, 0, 0));

        vector<Vec3b> comp; //k = whatever
        comp.push_back(Vec3b(255, 255, 255));
        comp.push_back(Vec3b(0, 0, 255));
        comp.push_back(Vec3b(0, 255, 0));
        comp.push_back(Vec3b(255, 0, 0));
        
        int COUNTME = 0;
        
        while(true){
            
            float sum[splits.size()][3] = {0.0};
            // x is the SPLIT and y is the COLOR

            float count[splits.size()] = {0.0};
            // how many points fall under each section?
                        
            for(int r = 0; r < img.rows; r++){
                for(int c = 0; c < img.cols; c++){
                    
                    int blue = img.at<Vec3b>(r,c)[0];
                    int green = img.at<Vec3b>(r,c)[1];
                    int red = img.at<Vec3b>(r,c)[2];
                                        
                    int whichSplit = 0;
                    float bestDist = distance(blue, green, red, splits[0]);

                    for(int split = 1; split < splits.size(); split++){
                        float d = distance(blue, green, red, splits[split]);
                        
                        if(d < bestDist){
                            bestDist = d;
                            whichSplit = split;
                        }
                    }

                    sum[whichSplit][0] += blue;
                    sum[whichSplit][1] += green;
                    sum[whichSplit][2] += red;
                    count[whichSplit]++;

                }
            }
            
            for(int s = 0; s < splits.size(); s++){
                Vec3f mean1 = sum[s][0]/(1.0*count[s]);
                Vec3f mean2 = sum[s][1]/(1.0*count[s]);
                Vec3f mean3 = sum[s][2]/(1.0*count[s]);
                splits[s] = Vec3b((int)mean1[0], (int)mean2[0], (int)mean3[0]);
            }
            
            
            for(int split = 0; split < splits.size(); split++){
                prev.push_back(splits[split]);
            }
            
            int breakNow = 1;
            
            for(int split = 1; split < splits.size(); split++){
                if(comp[split] == splits[split]){
                    breakNow *= 1;
                }else{
                    breakNow *= 0;
                }
            }
            
            if(breakNow == 1){
                break;
            }else{
               comp = splits;
               COUNTME += 1;
            }

        }
        
        cout << "Total Steps: " << COUNTME << endl;
        
        Mat format = imread("pictures/format.png");
        
        for(int r = 0; r < 6; r++){
            for(int c = 0; c < 4; c++){
                
                Vec3b color = prev.front();
                prev.erase(prev.begin());
                
                int blue = color[0];
                int green = color[1];
                int red = color[2];
                    
                for(int row = r*100; row < (r+1)*100; row++){
                    for(int col = c*100; col < (c+1)*100; col++){
                        format.at<Vec3b>(row, col)[0] = blue;
                        format.at<Vec3b>(row, col)[1] = green;
                        format.at<Vec3b>(row, col)[2] = red;
                    }
                }
                
            }
        }
        
        /* logging values but idc
        cout << splits[0] << endl;
        cout << splits[1] << endl;
        cout << COUNTME << endl;
        cout << "-----------------------------" << endl;
        */
        
        imwrite("challenge1/wrgb/" + string(pictures[picture]) + ".png", format);
    }

    return 0;
}