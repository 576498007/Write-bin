// NewTransformationDlg.h : 头文件
//

#pragma once
#include "resource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define MA 128
#define LEN 16
#define EIGHT 8
#define FOUR 4
#define TWO 2
#define MAX 4096
#define MAXX 8192

// CNewTransformationDlg 对话框
class CNewTransformationDlg : public CDialog
{
// 构造
public:
	CNewTransformationDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CNewTransformationDlg();
// 对话框数据
	enum { IDD = IDD_NEWTRANSFORMATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Analysis();
	const int ReadPassword(CString& str);	
	const int ReadNum(CString& str);
	void ReadScale(CString& str, CString& x, CString& y);
	void ReadContent(CString& str, vector<string>& vec);
	void WriteBinFile();
	BOOL OpenFile();
	int CharToUnicode(char *pchIn, CString *pstrOut);
	BOOL ReadStringToUnicode(CString &str);
protected:
	CStdioFile m_newfile;
	CStdioFile m_oldfile;
	CStdioFile m_binfile;
	CStdioFile m_datFile;
public:
	typedef struct
	{
		int password,
			xscale,
			yscale;
	}PASSWORD;
	PASSWORD m_pwd;
	//#Dao Cha Data	
	typedef struct
	{
		int num,
			xo, yo,
			xa, ya,
			xb, yb,
			xc, yc,
			index,
			a_link,
			b_link,
			c_link,
			type;
		TCHAR name[MA];
	}DAOCHAR, *DAO;
	DAOCHAR m_tDaoChar;
	DAO m_dao;
	//#Xin Hao Data
	typedef struct
	{
		int num,
			xo,
			yo,
			DIR,
			TYPE,
			HIGH,
			FORBIDCLR,
			LX_INDEX,
			DX_INDEX,
			HIDABLE,
			T_DX,
			T_DY,
			DelayX,
			DelayY;
		TCHAR name[MA];
	}XINHAO, *XIN;
	XINHAO m_tXinHao;
	XIN m_xin;
	//#Wu Dian Lu Qu Duan Data
	typedef struct
	{
		int num,
			x1, y1,
			x2, y2;
	}WUDIANLU, *WD;
	WUDIANLU m_tWuDianLu;
	WD m_wd;
	//#Wu cha
	typedef struct
	{
		int num,
			x1, y1,
			x2, y2,
			index,
			x, y,
			HIDABLE,
			CANQGJ,
			CANPLQGJ,
			Fauces,
			CommandID,
			DelayX,
			DelayY;
		TCHAR name[MA];
	}WUCHAQUDUAN, *WC;
	WUCHAQUDUAN m_tWchar;
	WC m_wu;

	//#Jue Yuan Jie Data
	typedef struct
	{
		int num, TYPE,
			X0, Y0,
			X1, Y1,
			X2, Y2;
	}JUEYUANJIE, *JUE;
	JUEYUANJIE m_tJue;
	JUE m_jue;
	//#Jin Tou Xian Data
	typedef struct
	{
		int num,
			x, y,
			type, dir;
	}JINTOUXIAN, *JIN;
	JINTOUXIAN m_tJin;
	JIN m_jin;
	//#Ping Mu Han Zi Data
	typedef struct
	{
		int num,
			x, y,
			HIDABLE,
			FontFamily,
			FontSize,
			FontStyle,
			FontColor;
		TCHAR TEXT[MA];
	}PINGMUHANZI, *PIN;
	PINGMUHANZI m_tPing;
	PIN m_pin;
	//#An Niu Data
	typedef struct
	{
		int num,
			sumo,
			x, y,
			TYPE,
			CommandID,
			Relate1, Relate2,
			deltax,deltay,
			SHOW, HIDABLE,
			Fauces;
		TCHAR NAME[MA];
	}ANNIU, *AN;
	ANNIU m_tAn;
	AN m_an;
	//#Dao Cha An Niu Data
	typedef struct
	{
		int num,
			x, y,
			CANPLQGJ,
			QD_INDEX,
			CommandID,
			Fauces,
			X1, Y1,
			DelayX,
			DelayY;
		TCHAR TEXT[MA],
			QDNAME[MA];
	}DAOCHAANNIU, *NIU;
	DAOCHAANNIU m_tNiu;
	NIU m_niu;
	//#Qu Duan Map Data
	typedef struct
	{
		int num,
			Index,
			iPrDC;
	}QUDUANMAP, *MP;
	QUDUANMAP m_tMap;
	MP m_mp;
	//#Dao Cha Jiao Cha Huan Wei Data
	typedef struct
	{
		int num,
			DC1,
			DWZG1,
			DC2,
			DWZG2;
	}DAOCHAJIAO, *DCJ;
	DAOCHAJIAO m_tDaoJiao;
	DCJ m_dcj;
	//#Biao Shi Deng Data
	typedef struct
	{
		int num,
			Type,
			X, Y,
			Dir,
			Index,
			Xt, Yt,
			Hiable;
		TCHAR Text[MA];
	}BIAOSHIDENG, *BIAO;
	BIAOSHIDENG m_tBiao;
	BIAO m_bi;
	//#Zi Mian Ban Pan Kuang Data     
	typedef struct
	{
		int num,
			Left,
			Top,
			Right,
			Botton;
	}ZIMIAN, *ZI;
	ZIMIAN m_tZi;
	ZI m_zi;
	//#Qian Fen Zhi Liu Data
	typedef struct
	{
		int num,
			x, y,
			dir;
	}QIANFEN, *QF;
	QIANFEN m_tfen;
	QF m_qf;
	//#Ping Liu Duan Kou Data
	typedef struct
	{
		int num,
			ID,
			X, Y,
			Index,
			Fauces;
		TCHAR Text[MA];
	}PINGDUAN, *PL;
	PINGDUAN m_tpduan;
	PL m_pl;
	//#Ping Liu Fen Qu Data
	typedef struct
	{
		int num,
			ID,
			DkID0,
			DkID1,
			DkID2,
			DkID3;
		TCHAR Text[MA];
	}PINGFEN, *PF;
	PINGFEN m_tpf;
	PF m_pf;
	//#Ping Liu Gu Dao Data
	typedef struct
	{
		int num,
			FqID,
			CommandID;
		TCHAR Text[MA];
	}PINGGU, *GU;
	PINGGU m_tPgu;
	GU m_gu;
	//#Station Name Image
	typedef struct
	{
		int num,
			x, y;
		TCHAR name[MA],
			namet[MA];
	}STATIONNAME, *ST;
	STATIONNAME m_tSta;
	ST m_st;
	//#Te Shu Delay Message
	typedef struct
	{
		int num,
			Index,
			X, Y;
		TCHAR Text[MA];
	}TESHU, *TE;
	TESHU m_tTeshu;
	TE m_te;
	//#Zhe Xian Data
	typedef struct
	{
		int num,
			x, y,
			ATTR;
	}ZHEXIAN, *ZH;
	ZHEXIAN m_tZhe;
	ZH m_th;
	//#Button Cap Position Data
	typedef struct
	{
		int num,
			iCommandID,
			x, y;
	}CAP, *CP;
	CAP m_tCap;
	CP m_cp;
	//#DaoCha Button  DC_INDEX Data
	typedef struct
	{
		int num,
			DC_INDEX;
	}DCINDEX, *DC;
	DCINDEX m_tDc;
	DC m_dc;
	//#Train Number Box Position Data
	typedef struct
	{
		int num,
			x,y,
			qdIndex,
			type;
	}TRAIN, *TR;
	TRAIN m_tTra;
	TR m_tr;
	//#Zhan Tai Data
	typedef struct
	{
		int num,
			x1,
			y1,
			x2,
			y2,
			Type;
	}ZHAN, *ZA;
	ZHAN m_tzhan;
	ZA m_za;
	//#Fang Xiang Biao Data
	typedef struct
	{
		int num,
			x,y,
			type;
	}FANG, *FA;
	FANG m_tfan;
	FA m_fa;
};
