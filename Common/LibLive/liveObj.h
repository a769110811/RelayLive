#pragma once

#include "libLive.h"
#include "uv.h"

/**
 * �����ӿ�
 */
struct IAnalyzer
{
    /**
     * ����һ��PES��
     * @param[in] pBuf PES֡
     * @param[in] nLen PES֡����
     * @return 0�ɹ� -1ʧ��
     */
    virtual int InputBuffer(char* pBuf, long nLen) = 0;
};


/**
 * RTSP����ģ��ӿ�
 * ʹ��ǰ����������ȳ�ʼ��<ָUdpSocket�����ʼ������ʹ��>
 */
class CLiveObj : public IlibLive
{
public:
    CLiveObj(void);
    ~CLiveObj(void);

    /**
     * ���ñ��ؼ�����IP�Ͷ˿�
     * @param[in] strIP ����IP
     * @param[in] nPort ������UDP�˿�
     */
    void SetLocalAddr(string strIP, int nPort)
    {
        m_strLocalIP = strIP;
        m_nLocalRTPPort = nPort;
        m_nLocalRTCPPort = nPort + 1;
    }

    /**
     * ���û���֡����
     * @param[in] nPacketNum ֡��������,��ֵԽ���ӳ�Խ�󣬵���Ӧ�Ը��������״��
     */
    void SetCatchPacketNum(int nPacketNum);

    /** ����UDP�˿ڼ��� */
    void StartListen();

    /** ���յ�rtp���ݴ��� */
    void RtpRecv(char* pBuff, long nLen);

    /** ���ճ�ʱ���� */
    void RtpOverTime();

    /**
     * RTP����ص�
     * @param[in] pBuff PS֡����
     * @param[in] nLen PS֡����
     */
    void RTPParseCb(char* pBuff, long nLen);

    /**
     * PS֡�����ص�
     * @param[in] pBuff PES������
     * @param[in] nLen PES������
     */
    void PSParseCb(char* pBuff, long nLen);

    /**
     * PES֡�����ص�
     * @param[in] pBuff ES������
     * @param[in] nLen ES������
     * @param[in] pts չ��ʱ����ֶ�
     * @param[in] dts ����ʱ����ֶ�
     */
    void PESParseCb(char* pBuff, long nLen, uint64_t pts, uint64_t dts);

    /**
     * ES֡�����ص�
     * @param[in] pBuff H264֡����
     * @param[in] nLen H264֡����
     * @param[in] nNalType Nalu������
     */
    void ESParseCb(char* pBuff, long nLen, uint8_t nNalType);

    /** FLV�ϳɻص� */
    void FlvCb(flv_tag_type eType, char* pBuff, int nBuffSize);

    /** MP4�ϳɻص� */
    void Mp4Cb(MP4_FRAG_TYPE eType, char* pBuff, int nBuffSize);

    /** TS�ϳɻص� */
    void TsCb(char* pBuff, int nBuffSize);

    /** H264�ϳɻص� */
    void H264Cb(char* pBuff, int nBuffSize);

    /**
     * ���ô������ݻص��Ķ���
     * @param[in] pHandle
     */
    void SetCallback(IlibLiveCb* pHandle)
    {
        m_pCallBack = pHandle;
    }

private:
    string      m_strLocalIP;       // ����IP
    int         m_nLocalRTPPort;    // ����RTP�˿�
    int         m_nLocalRTCPPort;   // ����RTCP�˿�
    string      m_strRemoteIP;      // Զ��IP
    int         m_nRemoteRTPPort;   // Զ��RTP�˿�
    int         m_nRemoteRTCPPort;  // Զ��RTCP�˿�

    uv_udp_t    m_uvRtpSocket;      // rtp����
    uv_timer_t  m_uvTimeOver;       // ���ճ�ʱ��ʱ��

    IAnalyzer*  m_pRtpParser;       // rtp���Ľ�����
    IAnalyzer*  m_pPsParser;        // PS֡������
    IAnalyzer*  m_pPesParser;       // PES��������
    IAnalyzer*  m_pEsParser;        // ES��������
    IAnalyzer*  m_pTs;              // TS�����
    IAnalyzer*  m_pFlv;             // FLV�����
    IAnalyzer*  m_pMp4;             // MP4�����

    IlibLiveCb* m_pCallBack;        // �ص�����

    char*       m_pRtpBuff;         // rtp����ָ��
    uint32_t    m_nRtpLen;          // rtp���ݳ���
    char*       m_pPsBuff;          // ps����ָ��
    uint32_t    m_nPsLen;           // ps���ݳ���
    char*       m_pPesBuff;         // pes����ָ��
    uint32_t    m_nPesLen;          // pes���ݳ���
    char*       m_pEsBuff;          // es����ָ��
    uint32_t    m_nEsLen;           // es���ݳ���
    char*       m_pNaluBuff;        // h264ƬԪָ��
    uint32_t    m_nNaluLen;         // h264ƬԪ����
    uint64_t    m_pts;              // ��¼PES�е�pts
    uint64_t    m_dts;              // ��¼PES�е�dts
    uint8_t     m_nalu_type;        // h264ƬԪ����
};
