#ifndef RSTP_DATA_FETCH_H
#define RSTP_DATA_FETCH_H

#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "IDataFetch.hpp"
//#include "vlc/vlc.h"
extern "C"
{
#include "vlc/vlc.h"
};

using namespace std;

class RstpDataFetch : public IDataFetch
{
public:
	RstpDataFetch();
	RstpDataFetch(string& rstp_url);
	virtual ~RstpDataFetch();
	cv::Mat GetImage();
/*
	int     MediaOpen(void *opaque, void **datap,uint64_t *sizep);
	size_t	MediaRead(void *opaque, unsigned char *buf, size_t len);
	int		MediaSeek(void *opaque, uint64_t offset);
	void	MediaClose(void *opaque);
	*/
	void Init();

private:
	// libvlc_video_set_callbacks
	static void Display(void *data, void *id);

	static void Unlock(void *data, void *id, void *const *planes);

	static void* Lock(void *data, void **planes);

	string m_url;

	libvlc_instance_t* m_vlcInst;

	libvlc_media_t*    m_vlcMedia;
	
	libvlc_media_player_t* m_vlcPlayer;
};

#endif //RSTP_DATA_FETCH_H
