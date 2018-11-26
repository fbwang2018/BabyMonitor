
#ifndef BABY_MONITOR_H
#define BABY_MONITOR_H
#include <string>
#include <chrono>
#include <thread>

#include "IDataFetch.hpp"
#include "RstpDataFetch.hpp"

class BabyMonitor
{
public:
	BabyMonitor(string& rtsp_url);
	virtual ~BabyMonitor();
	string GetImage();

private:
	IDataFetch* m_dataFetch;
};

#endif //BABY_MONITOR_H