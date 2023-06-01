#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const int DEVICE_ID = 0;
const int API_ID = cv::CAP_ANY;

int main() {
    Mat frame;
    VideoCapture cap;

    cap.open(DEVICE_ID, API_ID);

    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    while(true)
    {
        cap.read(frame);

        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        imshow("Camera Stream", frame);

        // If any key is pressed, convert the frame variable to a vector
        // Then you can have the FPGA process the vector
        if (waitKey(5) >= 0) {
            Mat flat = frame.reshape(1, frame.total() * frame.channels());
            vector<uchar> vec = frame.isContinuous() ? flat : flat.clone();
        }
    }

	return 0;
}
