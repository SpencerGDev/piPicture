#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <csignal>

using namespace cv;
using namespace std;
volatile sig_atomic_t stopFlag = 0;

void signal_handler(int signal)
{
   cout << "Stop flag recieved\n";
   stopFlag = 1;
}

int main(int argc, char **argv)
{
   signal(SIGINT, signal_handler); // control c
   Mat frame;
   VideoCapture cap;

   cap.open(0); // opens the camera for capture
   if (!cap.isOpened())
   {
      cout << "Error opening camera\n";
      return -1;
   }
   cout << "Camera successfully opened\n";

   // setup video writer

   // get the widthxheight of frames of the video
   int frame_Width = cap.get(CAP_PROP_FRAME_WIDTH);
   int frame_Height = cap.get(CAP_PROP_FRAME_HEIGHT);

   cout << "Resolution = " << frame_Width << "x" << frame_Height << endl;

   VideoWriter outp;
   outp.open("output.avi", VideoWriter::fourcc('X', 'V', 'I', 'D'), 20, Size(frame_Width, frame_Height));

   if (!outp.isOpened())
   {
      cout << "Error opening videoWriter\n";
      return -1;
   }

   while (!stopFlag)
   {
      cap.read(frame);
      if (frame.empty())
      {
         cout << "No frame captured\n";
         return -1;
      }
      outp.write(frame); // writes to output file
   }

   outp.release();
   cap.release();
   return 0;
}