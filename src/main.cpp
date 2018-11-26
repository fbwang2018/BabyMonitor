
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "BabyMonitor.hpp"

using namespace std;
int main(int argc, char *argv[])
{
	//cvNamedWindow("image", CV_WINDOW_AUTOSIZE);

	string rtsp_url("rtsp://192.168.1.17:554/ch0_0.h264");
	
	BabyMonitor babyMonitor(rtsp_url);

	while(true)
	{
		string img = babyMonitor.GetImage();

		std::this_thread::sleep_for(300s);
	}

	return 0;
}