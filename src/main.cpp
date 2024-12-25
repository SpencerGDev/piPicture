#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
   Mat frame;
   VideoCapture cap; //

   cap.open(0); // opens the camera for capture
   if (!cap.isOpened())
   {
      cout << "Error opening camera\n";
      return -1;
   }
   else
   {
      cout << "Successful\n";
   }

   cap.read(frame);
   if (frame.empty())
   {
      cout << "No frame captured\n";
      return -1;
   }
   imwrite("image.png", frame);
   return 0;
}