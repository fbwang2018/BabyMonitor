#ifndef RSTP_DATA_FETCH_H
#define RSTP_DATA_FETCH_H

#include <string>
#include <iostream>
#include <mutex>

#include <opencv2/opencv.hpp>
#include "IDataFetch.hpp"
extern "C"
{
	#include "vlc/vlc.h"
};

using namespace std;

class RstpDataFetch : public IDataFetch
{
public:
	typedef struct _CTX_
	{

		cv::Mat* m_img;
		//char* m_img;

		mutex m_mtx;

		uchar* pixels;

	}CTX, *PCTX;

public:
	RstpDataFetch();

	RstpDataFetch(string& rstp_url);

	virtual ~RstpDataFetch();

	cv::Mat GetImage();

private:
	void Init();
	// libvlc_video_set_callbacks
	static void Display(void *data, void *id);

	static void Unlock(void *data, void *id, void *const *planes);

	static void* Lock(void *data, void **planes);
	
	static char m_fileName[];
	
	static char* m_videoBuf;
	
	static const int m_width = 1280;
	static const int m_height = 720;

	string m_url;

	static bool m_saveImg;

	libvlc_instance_t* m_vlcInst;

	libvlc_media_t*    m_vlcMedia;
	
	libvlc_media_player_t* m_vlcPlayer;
	PCTX m_pCtx;
};

#endif //RSTP_DATA_FETCH_H
