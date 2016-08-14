#include "led/contour.h"
#include "led/base.h"

int contour(const Mat src,
                Point2f &goal,
                Mat &result)
{

/*low exposure mode*/
    Mat dst;
    int key;
    bool find_object, WAWA; //00missing 01closer 10hippo 11octopus
    lowExposureWAWA(src, result, goal, find_object, WAWA);
    if(find_object)
    {
        if ( WAWA )
        {
            cout<<"*********************octopus*********************"<<endl;
            return 1;
        }                  //octopus
        else
        {
            return 2;
            cout<<"*********************hippo*********************"<<endl;
        }                 //hippo
    }
    else
    {
        if ( WAWA )
        {
             cout<<"closer"<<endl;
            return -1;
        }      //closer
        else
        {
            cout<<"miss"<<endl;
            return -2;
         }//miss
    }
    return 0;
    waitKey(0);
}

void lowExposureWAWA(const Mat src, Mat &result, Point2f &goal, bool &find_object, bool &WAWA)
{
    /*initialize the flag*/
    /*WAWA:false=hippo;*/
    find_object = false;
    WAWA = false;
    result = colorConversion(src, HSV_V);

    /*smooth using medianBlur*/
    medianBlur(result, result,5);


    /*binary*/
    threshold(result,result,10,255,THRESH_BINARY);
    imshow("binary", result);


    /*morphology closing*/
    Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
    morphologyEx(result,result,MORPH_CLOSE,element);
    imshow("CLOSEING", result);

    /*retrieve contours_external*/
    vector<vector<Point> >contours;
    vector<Vec4i> hierarchy;
    findContours(result, contours, hierarchy,CV_RETR_TREE,CHAIN_APPROX_SIMPLE);
    if (contours.size()==0)  return;
    cout<<"size_external"<<contours.size()<<endl;

    /*display source img with every contours*/
    drawContours(src,contours,-1,Scalar(200),3);
    imshow("src",src);
    /*return if there is no WAWA being targeted*/
    Vector<float> area;
    int idx;
    for(int i=0;i<contours.size();i++)
    {
        area.push_back(contourArea(contours[i]));
        if(area[i]==*max_element(area.begin(),area.end())) idx=i;
    }
    float Parea=area[idx]/(src.cols*src.rows);
    cout<<"Parea:"<<Parea<<endl;

    /*retrieve moments and output*/
    Moments mom=moments(contours[idx], false);
    goal = Point(mom.m10/mom.m00,mom.m01/mom.m00);
    Point2f center = Point(src.cols/2,src.rows/2);
    if(Parea<0.1)
    {
        getPosition(center, goal, goal);
        WAWA = true;
        return;
    }

    /*set ROI with filled contours*/
    int counter=0;
    for(int i=0;i<contours.size();i++)
    {
        if(hierarchy[i][3]==idx)    counter++;
    }
    drawContours(result,contours,-1,Scalar::all(255),2);
    cout<<"contoooooours:"<<counter<<endl;

    /*tell what the WAWA is*/
     find_object = true;
     if(counter>0|contours.size()>1)
     {
         WAWA = true;
         return;
     }
}
