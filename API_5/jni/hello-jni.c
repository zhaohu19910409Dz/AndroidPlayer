/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "include/libavcodec/avcodec.h"
#include "include/libavformat/avformat.h"
#include "include/libavfilter/avfilter.h"
#include "include/libswscale/swscale.h"
#include "include/libswresample/swresample.h"
#include "include/libavutil/avutil.h"
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <pthread.h>
#include <unistd.h>
/* Header for class com_example_api_5_MainActivity */

#ifndef _Included_com_example_api_5_MainActivity
#define _Included_com_example_api_5_MainActivity

#undef com_example_api_5_MainActivity_BIND_ABOVE_CLIENT
#define com_example_api_5_MainActivity_BIND_ABOVE_CLIENT 8L
#undef com_example_api_5_MainActivity_BIND_ADJUST_WITH_ACTIVITY
#define com_example_api_5_MainActivity_BIND_ADJUST_WITH_ACTIVITY 128L
#undef com_example_api_5_MainActivity_BIND_ALLOW_OOM_MANAGEMENT
#define com_example_api_5_MainActivity_BIND_ALLOW_OOM_MANAGEMENT 16L
#undef com_example_api_5_MainActivity_BIND_AUTO_CREATE
#define com_example_api_5_MainActivity_BIND_AUTO_CREATE 1L
#undef com_example_api_5_MainActivity_BIND_DEBUG_UNBIND
#define com_example_api_5_MainActivity_BIND_DEBUG_UNBIND 2L
#undef com_example_api_5_MainActivity_BIND_EXTERNAL_SERVICE
#define com_example_api_5_MainActivity_BIND_EXTERNAL_SERVICE -2147483648L
#undef com_example_api_5_MainActivity_BIND_IMPORTANT
#define com_example_api_5_MainActivity_BIND_IMPORTANT 64L
#undef com_example_api_5_MainActivity_BIND_NOT_FOREGROUND
#define com_example_api_5_MainActivity_BIND_NOT_FOREGROUND 4L
#undef com_example_api_5_MainActivity_BIND_WAIVE_PRIORITY
#define com_example_api_5_MainActivity_BIND_WAIVE_PRIORITY 32L
#undef com_example_api_5_MainActivity_CONTEXT_IGNORE_SECURITY
#define com_example_api_5_MainActivity_CONTEXT_IGNORE_SECURITY 2L
#undef com_example_api_5_MainActivity_CONTEXT_INCLUDE_CODE
#define com_example_api_5_MainActivity_CONTEXT_INCLUDE_CODE 1L
#undef com_example_api_5_MainActivity_CONTEXT_RESTRICTED
#define com_example_api_5_MainActivity_CONTEXT_RESTRICTED 4L
#undef com_example_api_5_MainActivity_MODE_APPEND
#define com_example_api_5_MainActivity_MODE_APPEND 32768L
#undef com_example_api_5_MainActivity_MODE_ENABLE_WRITE_AHEAD_LOGGING
#define com_example_api_5_MainActivity_MODE_ENABLE_WRITE_AHEAD_LOGGING 8L
#undef com_example_api_5_MainActivity_MODE_MULTI_PROCESS
#define com_example_api_5_MainActivity_MODE_MULTI_PROCESS 4L
#undef com_example_api_5_MainActivity_MODE_NO_LOCALIZED_COLLATORS
#define com_example_api_5_MainActivity_MODE_NO_LOCALIZED_COLLATORS 16L
#undef com_example_api_5_MainActivity_MODE_PRIVATE
#define com_example_api_5_MainActivity_MODE_PRIVATE 0L
#undef com_example_api_5_MainActivity_MODE_WORLD_READABLE
#define com_example_api_5_MainActivity_MODE_WORLD_READABLE 1L
#undef com_example_api_5_MainActivity_MODE_WORLD_WRITEABLE
#define com_example_api_5_MainActivity_MODE_WORLD_WRITEABLE 2L
#undef com_example_api_5_MainActivity_RECEIVER_VISIBLE_TO_INSTANT_APPS
#define com_example_api_5_MainActivity_RECEIVER_VISIBLE_TO_INSTANT_APPS 1L
#undef com_example_api_5_MainActivity_DEFAULT_KEYS_DIALER
#define com_example_api_5_MainActivity_DEFAULT_KEYS_DIALER 1L
#undef com_example_api_5_MainActivity_DEFAULT_KEYS_DISABLE
#define com_example_api_5_MainActivity_DEFAULT_KEYS_DISABLE 0L
#undef com_example_api_5_MainActivity_DEFAULT_KEYS_SEARCH_GLOBAL
#define com_example_api_5_MainActivity_DEFAULT_KEYS_SEARCH_GLOBAL 4L
#undef com_example_api_5_MainActivity_DEFAULT_KEYS_SEARCH_LOCAL
#define com_example_api_5_MainActivity_DEFAULT_KEYS_SEARCH_LOCAL 3L
#undef com_example_api_5_MainActivity_DEFAULT_KEYS_SHORTCUT
#define com_example_api_5_MainActivity_DEFAULT_KEYS_SHORTCUT 2L
#undef com_example_api_5_MainActivity_RESULT_CANCELED
#define com_example_api_5_MainActivity_RESULT_CANCELED 0L
#undef com_example_api_5_MainActivity_RESULT_FIRST_USER
#define com_example_api_5_MainActivity_RESULT_FIRST_USER 1L
#undef com_example_api_5_MainActivity_RESULT_OK
#define com_example_api_5_MainActivity_RESULT_OK -1L
#define FFMPEG_VERSION

ANativeWindow* gNativeWindow = NULL;
int mWidth = 0;
int mHeight = 0;
pthread_cond_t cond;
pthread_mutex_t mutex;
struct timeval now;
struct timespec outtime;
void nSleep(int ms)
{
	gettimeofday(&now,NULL);
	now.tv_usec += 1000*ms;
	if(now.tv_sec > 1000000)
	{
		now.tv_sec += now.tv_usec / 1000000;
		now.tv_sec %= 1000000;
	}

	outtime.tv_sec = now.tv_sec;
	outtime.tv_sec = now.tv_usec * 1000;
	pthread_cond_timedwait(&cond,&mutex,&outtime);
}
void custom_log(void *ptr, int level, const char* fmt, va_list vl)
{
    FILE *fp=fopen("/storage/emulated/0/av_log.txt","a+");
    if(fp)
    {
        vfprintf(fp,fmt,vl);
        fflush(fp);
        fclose(fp);
    }
}

JNIEXPORT jstring JNICALL Java_com_example_api_15_MainActivity_stingFromJNI
  (JNIEnv *env, jobject obj)
{
	av_log_set_callback(custom_log);
	char info[1000]= { 0 };
	//sprintf(info,"info:%s\n",avcodec_configuration());
	//sprintf(info,"width:%d\t height:%d",mWidth,mHeight);
	//return (*env)->NewStringUTF(env,info);
	AVFormatContext* pFormatCtx = NULL;
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();
	//char* url="/sdcard/test.mp4";
	//char* url="/sdcard/2.mkv";
	char* url="rtmp://live.hkstv.hk.lxdns.com/live/hks";

	//      if(avformat_open_input(&pFormatCtx,url,NULL,NULL) != 0)
	//      {
	//          return (*env)->NewStringUTF(env,"open url failed!");
	//      }
	int ret = avformat_open_input(&pFormatCtx,url,NULL,NULL);
	      //char buf[1024] = { 0 };
	      //av_strerror(ret,buf,1024);
	      //sprintf(info,"Couldn't open file %s: %d(%s)\n",url,ret,buf);
	      //return (*env)->NewStringUTF(env,info);

	//      if(err_code=avformat_open_input(&pFormatCtx, url, NULL, NULL) )
	//      {
	//          av_strerror(err_code, buf, 1024);
	//          printf("Couldn't open file %s: %d(%s)", test_file, err_code, buf);
	//          return -1;
	//      }

	      if(!pFormatCtx)
	          return (*env)->NewStringUTF(env,"pFormat is NULL!");

	      if(avformat_find_stream_info(pFormatCtx,NULL) < 0)
	      {
	          return (*env)->NewStringUTF(env,"Did not find info");
	      }
	      int videoIndex = -1;
	      int i;
	      for (i = 0; i <pFormatCtx->nb_streams ; ++i)
	      {
	        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
	        {
	            videoIndex = i;
	            break;
	        }
	      }
	      if(videoIndex == -1)
	      {
	          return (*env)->NewStringUTF(env,"Did not find video steam!");
	      }

	      AVCodecContext* pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
	      AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

	      if(pCodec == NULL)
	          return (*env)->NewStringUTF(env,"Did not find video decoder");

	      if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0)
	      {
	          return (*env)->NewStringUTF(env,"avcodec_open2 failed!");
	      }


	      //sprintf(info,"%s\n",avcodec_configuration());
	      sprintf(info,"[Input:] %s\n",url);
	      sprintf(info,"%s[Format:] %s\n",info,pFormatCtx->iformat->name);
	      sprintf(info,"%s[codec:] %s\n",info,pCodecCtx->codec->name);
	      sprintf(info,"%s[Resolution:] %dx%d\n",info,pCodecCtx->width,pCodecCtx->height);

	      mWidth = pCodecCtx->width;
	      mHeight = pCodecCtx->height;
	    //解码一帧保存为图片
	    AVFrame* pFrame = av_frame_alloc();
	    AVFrame* pFrameYUV = av_frame_alloc();
	    char* out_buffer = NULL;
	    out_buffer = (unsigned char*)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGBA,mWidth,mHeight,1));

	#ifdef FFMPEG_VERSION
	    av_image_fill_arrays(pFrameYUV->data,pFrameYUV->linesize,out_buffer,AV_PIX_FMT_RGBA,mWidth,mHeight,1);
	#else
	    //avpicture_fill((AVPicture*)m_pRGBFrame, m_pRGBBuffer, AV_PIX_FMT_BGR24, w, h);
	#endif
	    AVPacket *packet = (AVPacket*)av_malloc(sizeof(AVPacket));
	    struct SwsContext   *img_convert_ctx = NULL;
	    img_convert_ctx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,
	    		mWidth,mHeight,AV_PIX_FMT_RGBA,SWS_BICUBIC,NULL,NULL,NULL);

	    if(ANativeWindow_setBuffersGeometry(gNativeWindow,mWidth,mHeight,WINDOW_FORMAT_RGBA_8888) < 0)
	    {
	    		ANativeWindow_release(gNativeWindow);
	    		return (*env)->NewStringUTF(env,"ANativeWindow_setBuffersGeometry Error.\n");
	    }
	    int frame_cnt = 0;
	    clock_t time_start,time_finish;
	    time_start = clock();

	    int got_picture,y_size;
	    while(av_read_frame(pFormatCtx,packet) >= 0)
	    {
	        if(packet->stream_index == videoIndex)
	        {
	            //avcodec_send_packet(pCodecCtx,packet);
	            //ret = avcodec_receive_frame(pCodecCtx,pFrame);
	            ret = avcodec_decode_video2(pCodecCtx,pFrame,&got_picture,packet);
	            if(ret < 0)
	            {
	                return (*env)->NewStringUTF(env,"Decode Error.\n");
	            }
	            if(got_picture)
	            {
	                int ret = sws_scale(img_convert_ctx,(const uint8_t* const*)pFrame->data,pFrame->linesize,0,pCodecCtx->height,
	                pFrameYUV->data,pFrameYUV->linesize);
	                //y_size = pCodecCtx->width * pCodecCtx->height;
	                ANativeWindow_Buffer windowBuffer = { 0 };
	                if(ANativeWindow_lock(gNativeWindow,&windowBuffer,NULL) < 0)
	                {
	                		return (*env)->NewStringUTF(env,"ANativeWindow_lock Error.\n");
	                }
	                else
	                {
	                		//sprintf(info,"width:%d,height:%d,stride:%d\n",windowBuffer.width,windowBuffer.height,windowBuffer.stride);
	                		//sprintf(info,"width:%d,height:%d,stride:%d\n",pFrameYUV->width,pFrameYUV->height,pFrameYUV->linesize[0]);
	                		//return (*env)->NewStringUTF(env,info);
	                		uint8_t *dst = (uint8_t*)windowBuffer.bits;
	                		int h = 0;
	                		for(h = 0; h < mHeight;h++)
	                		{
	                			memcpy(dst+h*windowBuffer.stride*4,pFrameYUV->data[0]+h*pFrameYUV->linesize[0],
	                					pFrameYUV->linesize[0]);

	                		}
	                		ANativeWindow_unlockAndPost(gNativeWindow);
	                }
	                frame_cnt++;

	                nSleep(40);
	                //LTSleep(40);
	                //if(frame_cnt == 100)
	                	//	break;
	            }
	        }
	        //av_free_packet(packet);
	        av_packet_unref(packet);
	    }
	    time_finish = clock();

	    sws_freeContext(img_convert_ctx);
	    av_frame_free(&pFrameYUV);
	    av_frame_free(&pFrame);
	    avcodec_close(pCodecCtx);
	    avformat_close_input(&pFormatCtx);

	    return (*env)->NewStringUTF(env,info);
}

JNIEXPORT jboolean JNICALL Java_com_example_api_15_MainActivity_loadFile
  (JNIEnv *env, jobject obj, jobject surface,jint width,jint height)
{
	//mWidth = width;
	//mHeight = height;
	//if(mWidth == 0) mWidth = 200;
	//if(mHeight == 0) mHeight = 300;
	ANativeWindow* nativeWindow = ANativeWindow_fromSurface(env,surface);
	if(nativeWindow)
	{
		gNativeWindow = nativeWindow;
		return JNI_TRUE;
	}
	return JNI_FALSE;
}
#endif
