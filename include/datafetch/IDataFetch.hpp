#ifndef INTERFACE_DATA_FETCH_H
#define INTERFACE_DATA_FETCH_H

#include <opencv2/opencv.hpp>
#include <string>
#ifdef _WIN64
	#pragma comment(lib, "libvlc.lib")
	#pragma comment(lib, "libvlccore.lib")
	#pragma comment(lib, "opencv_world343d.lib")
#endif
using namespace std;
class IDataFetch
{
public:
    virtual string GetImage() = 0;
	virtual void StartDevice() = 0;
	virtual void StopDevice() = 0;
};

#endif //INTERFACE_DATA_FETCH_H
