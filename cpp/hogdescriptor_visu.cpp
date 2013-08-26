#include "hogdescriptor_visu.h" 
#include "config.h"

using namespace cv;
using namespace std;

cv::Mat get_hogdescriptor_visu(const cv::Mat& origImg, cv::Mat& histo, int patch_x, int patch_y)
{   
    Mat color_origImg;
    cvtColor(origImg, color_origImg, CV_GRAY2RGB);
 
    float zoomFac = 3;
    Mat visu;
    resize(color_origImg, visu, Size(color_origImg.cols*zoomFac, color_origImg.rows*zoomFac));
 
    int cellSize        = PATCH_SIZE / PATCH_CELLS;
    int gradientBinSize = GRADIENT_BINS;
    float radRangeForOneBin = M_PI/(float)gradientBinSize;
 
    // prepare data structure: 9 orientation / gradient strenghts for each cell
    int cells_in_x_dir = PATCH_CELLS;
    int cells_in_y_dir = PATCH_CELLS;

    int binIdx = 0;

    // draw cells
    for (int celly=0; celly<cells_in_y_dir; celly++)
    {
        for (int cellx=0; cellx<cells_in_x_dir; cellx++)
        {
            int drawX = patch_x + cellx * cellSize;
            int drawY = patch_y + celly * cellSize;
 
            int mx = drawX + cellSize/2;
            int my = drawY + cellSize/2;
 
            rectangle(visu, Point(drawX*zoomFac,drawY*zoomFac), Point((drawX+cellSize)*zoomFac,(drawY+cellSize)*zoomFac), CV_RGB(100,100,100), 1);
 
            // draw in each cell all 9 gradient strengths
            for (int bin=0; bin<gradientBinSize; bin++)
            {
                float currentGradStrength = histo.at<float>(binIdx++);
 
                // no line to draw?
                if (currentGradStrength==0)
                    continue;
 
                float currRad = bin * radRangeForOneBin;// + radRangeForOneBin/2;
 
                float dirVecX = cos( currRad );
                float dirVecY = sin( currRad );
                float maxVecLen = cellSize/2;
                float scale = 2.5; // just a visualization scale, to see the lines better
 
                // compute line coordinates
                float x1 = mx - dirVecX * currentGradStrength * maxVecLen * scale;
                float y1 = my - dirVecY * currentGradStrength * maxVecLen * scale;
                float x2 = mx + dirVecX * currentGradStrength * maxVecLen * scale;
                float y2 = my + dirVecY * currentGradStrength * maxVecLen * scale;
 
                // draw gradient visualization
                line(visu, Point(x1*zoomFac,y1*zoomFac), Point(x2*zoomFac,y2*zoomFac), CV_RGB(0,255,0), 1);
 
            } // for (all bins)
 
        } // for (cellx)
    } // for (celly)
 
    return visu;
 
} // get_hogdescriptor_visu
