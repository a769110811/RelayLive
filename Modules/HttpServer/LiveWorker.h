#pragma once
#include "libLive.h"

namespace HttpWsServer
{
    struct pss_http_ws_live;
    enum MediaType;

    struct LIVE_BUFF {
        char *pBuff;
        int   nLen;
    };

    class CLiveWorker : public IlibLiveCb
    {
    public:
        CLiveWorker(string strCode, int rtpPort);
        ~CLiveWorker();

        /** �ͻ������� */
        bool AddConnect(pss_http_ws_live* pss);
        bool DelConnect(pss_http_ws_live* pss);

		/** �ͻ���ȫ���Ͽ�����ʱ������ʵ�� */
		void Clear2Stop();
        bool m_bStop;          //< ���붨ʱ���ص�����Ϊtrue��close��ʱ���ص������ٶ���
        bool m_bOver;          //< ��ʱ����Ϊtrue���ͻ���ȫ���Ͽ�����ʱ����������

        /** ����˻�ȡ��Ƶ���� */
        LIVE_BUFF GetFlvHeader();
        LIVE_BUFF GetFlvVideo(uint32_t *tail);
        //------------------------------------------
        LIVE_BUFF GetH264Video(uint32_t *tail);
        //------------------------------------------
        LIVE_BUFF GetMp4Header();
        LIVE_BUFF GetMp4Video(uint32_t *tail);
        //------------------------------------------
        void NextWork(pss_http_ws_live* pss);

        /** ��ȡ�ͻ�����Ϣ */
        string GetClientInfo();

        /**
         * ��Դ��������Ƶ���ݣ����߳����� 
         * ���¼̳���IlibLiveCb�ķ�����rtp�������ڵ�loop�̵߳���
         * �������������������졢��������http���ڵ�loop�̵߳���
         */
        void push_flv_frame(FLV_FRAG_TYPE eType, char* pBuff, int nLen);
        void push_h264_stream(char* pBuff, int nLen);
        void push_ts_stream(char* pBuff, int nLen);
        void push_mp4_stream(MP4_FRAG_TYPE eType, char* pBuff, int nBuffSize);
        void stop();
    private:
        void cull_lagging_clients(MediaType type);


    private:
        string                m_strCode;     // ����ý����

        /**
         * lws_ring�������λ�������ֻ��һ���߳�д�룬һ���̶߳�ȡ
         * m_pFlvRing��m_pH264Ring��m_pMP4Ring��rtp��ȡ��loop�߳�д�룬http�������ڵ�loop�̶߳�ȡ
         */
        //flv
        LIVE_BUFF             m_stFlvHead;  //flvͷ���ݱ�����libLiveģ�飬�ⲿ����Ҫ�ͷ�
        struct lws_ring       *m_pFlvRing;
        pss_http_ws_live      *m_pFlvPssList;

        //h264
        struct lws_ring       *m_pH264Ring;
        pss_http_ws_live      *m_pH264PssList;

        //fMP4
        LIVE_BUFF             m_stMP4Head;  //mp4ͷ���ݱ�����libLiveģ�飬�ⲿ����Ҫ�ͷ�
        struct lws_ring       *m_pMP4Ring;
        pss_http_ws_live      *m_pMP4PssList;

        int                   m_nType;          //< 0:liveֱ����1:record��ʷ��Ƶ
        IlibLive*             m_pLive;          //< ֱ�����ݽ��պͽ��װ��
        int                   m_nPort;          //< rtp���ն˿�

        uv_timer_t            m_uvTimerStop;    //< http���Ŷ�ȫ���������Ӻ��ӳ����٣��Ա�ҳ��ˢ��ʱ���ٲ���
    };

    /** ipc ��ʼ�� */
    void ipc_init();

    /** ֱ�� */
    CLiveWorker* CreatLiveWorker(string strCode);
    CLiveWorker* GetLiveWorker(string strCode);
    bool DelLiveWorker(string strCode);

    /** �㲥 */

    /** ��ȡ������Ϣ������json */
    string GetClientsInfo();
	/** ��ȡ�豸�б� */
	int GetDevList(int pss);
	/** �����豸��ѯ���� */
	int QueryDirtionary();
};