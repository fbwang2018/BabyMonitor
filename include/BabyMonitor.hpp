
#ifndef BABY_MONITOR_H
#define BABY_MONITOR_H
#include <string>

#include "IDataFetch.hpp"
#include "RstpDataFetch.hpp"

using namespace std;

class BabyMonitor
{
public:
	BabyMonitor(string& rtsp_url);
	virtual ~BabyMonitor();
	cv::Mat GetImage();

private:
	IDataFetch* m_dataFetch;
};

#endif //BABY_MONITOR_H