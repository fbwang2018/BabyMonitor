#include "RstpDataFetch.hpp"

using namespace cv;

int width = 640;

int height = 480;

static char* videobuf;

void RstpDataFetch::Display(void*data,void *id)
{
    IplImage *img = cvCreateImage(CvSize(width, height), IPL_DEPTH_8U, 4);

    img->imageData = videobuf;

    cvShowImage("test", img);

    waitKey(10);

    cvReleaseImage(&img);
}

void *RstpDataFetch::Lock(void *data, void**p_pixels)
{
    *p_pixels = videobuf;

    return NULL;
}

void RstpDataFetch::Unlock(void *data, void *id, void *const *p_pixels)
{
    (void)data;

    assert(id==NULL);
}

RstpDataFetch::RstpDataFetch():m_url(""), m_vlcInst(nullptr)
{
	Init();
}

RstpDataFetch::RstpDataFetch(string& rstp_url):m_url(rstp_url), m_vlcInst(nullptr)
{
	Init();
}

 RstpDataFetch::~RstpDataFetch()
 {
 	if(m_vlcMedia)
 	{
		libvlc_media_release(m_vlcMedia);
 	}

 	if(m_vlcPlayer)
 	{
		libvlc_media_player_release(m_vlcPlayer);
 	}

 	if(m_vlcInst)
 	{
 		libvlc_release(m_vlcInst);
 	}
 }



 cv::Mat RstpDataFetch::GetImage()
 {
 	 cv::Mat img;

 	 return img;
 }

 void RstpDataFetch::Init()
 {
 	m_vlcInst = libvlc_new(0, nullptr);

 	if(!m_vlcInst)
 	{
 		cout<<"Fail to init VLC instance"<<endl;

 		return;
 	}

    if(m_url.empty())
    {
		cout<<"The RTSP url is empty"<<endl;

		return;
    }

 	m_vlcMedia = libvlc_media_new_location (m_vlcInst, m_url.c_str());

 	if(!m_vlcMedia)
 	{
		cout<<"The media object is empty"<<endl;

		return;
 	}

 	m_vlcPlayer = libvlc_media_player_new_from_media(m_vlcMedia);

	libvlc_video_set_callbacks(m_vlcPlayer, Lock, Unlock, Display, NULL);

	libvlc_video_set_format(m_vlcPlayer, "RV32", width, height, width << 2);

 	libvlc_media_player_play(m_vlcPlayer);
 }