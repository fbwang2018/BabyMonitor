
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

		auto t = chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		struct tm ts;
		localtime_s(&ts, &t);
		if (ts.tm_hour == 6 && ts.tm_min == 30)
		{
			break;
		}
	}

	return 0;
}