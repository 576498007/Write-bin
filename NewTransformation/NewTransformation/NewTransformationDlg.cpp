// NewTransformationDlg.cpp : 实现文件
//



#include "stdafx.h"
#include "NewTransformation.h"
#include "NewTransformationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewTransformationDlg 对话框



CNewTransformationDlg::CNewTransformationDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNewTransformationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CNewTransformationDlg::~CNewTransformationDlg()
{
	delete[]m_dao;
	m_dao = NULL;
	delete[]m_xin;
	m_xin = NULL;
	delete[]m_wd;
	m_wd = NULL;
	delete[]m_wu;
	m_wu = NULL;
	delete[]m_jue;
	m_jue = NULL;
	delete[]m_jin;
	m_jin = NULL;
	delete[]m_pin;
	m_pin = NULL;
	delete[]m_an;
	m_an = NULL;
	delete[]m_niu;
	m_niu = NULL;
	delete[]m_mp;
	m_mp = NULL;
	delete[]m_dcj;
	m_dcj = NULL;
	delete[]m_bi;
	m_bi = NULL;
	delete[]m_zi;
	m_zi = NULL;
	delete[]m_qf;
	m_qf = NULL;
	delete[]m_pl;
	m_pl = NULL;
	delete[]m_pf;
	m_pf = NULL;
	delete[]m_gu;
	m_gu = NULL;
	delete[]m_st;
	m_st = NULL;
	delete[]m_te;
	m_te = NULL;
	delete[]m_th;
	m_th = NULL;
	delete[]m_cp;
	m_cp = NULL;
	delete[]m_dc;
	m_dc = NULL;
	delete[]m_tr;
	m_tr = NULL;
	delete[]m_za;
	m_za = NULL;


	m_oldfile.Close();
	m_newfile.Close();
	m_binfile.Close();
}
void CNewTransformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewTransformationDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CNewTransformationDlg 消息处理程序

BOOL CNewTransformationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	OpenFile();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNewTransformationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNewTransformationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CNewTransformationDlg::ReadStringToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1]; 

	for (int i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (CHAR)str.GetAt(i);
	}
	szBuf[str.GetLength()] = '\0'; 

	BOOL bok = CharToUnicode(szBuf, &str);
	delete[]szBuf;
	return bok;
}

int CNewTransformationDlg::CharToUnicode(char *pchIn, CString *pstrOut)
{
	int nLen;
	WCHAR *ptch;

	if (pchIn == NULL)
	{
		return 0;
	}

	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);//取得所需缓存的多少
	ptch = new WCHAR[nLen];//申请缓存空间
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);//转码
	pstrOut->Format(_T("%s"), ptch);
	delete[] ptch;

	return nLen;
}

const int CNewTransformationDlg::ReadPassword(CString& str)
{
	CString text = str;
	text.TrimLeft();
	text.TrimRight();
	if (text.IsEmpty())
	{
		return 0;
	}
	return _ttoi(text);
}

const int CNewTransformationDlg::ReadNum(CString& str)
{
	CString text = str;
	text.TrimLeft();
	text.TrimRight();
	if (text.IsEmpty())
	{
		return 0;
	}
	return _ttoi(text);
}

void CNewTransformationDlg::ReadScale(CString& str, CString& x, CString& y)
{
	CString text = str;
	text.TrimLeft();
	text.TrimRight();
	if (text.IsEmpty())
	{
		return;
	}
	x = text.Left(2);
	y = text.Right(2);
}

void CNewTransformationDlg::ReadContent(CString& str, vector<string>& vec)
{
	USES_CONVERSION;
	vector<string> rq;
	int i = 0;
	int comma = 0;
	str.Replace(_T("\t"), _T(" "));
	str.TrimLeft();
	str.TrimRight();
	string sstr(W2A(str)); //= str.GetBuffer(0);
	string::iterator it;
	/*for (it = sstr.begin(); it != sstr.end(); it++)
	{
		if (*it == '\t')
		{
			sstr.erase(it);

		}
	}*/
	//sstr.erase(remove(sstr.begin(), sstr.end(), '\t'), sstr.end());
	do
	{
		string temp = "";

		comma = sstr.find(" ");
		if (comma == -1)
		{
			temp = sstr.substr(0, sstr.length());
			rq.push_back(temp);
			break;
		}
		temp = sstr.substr(0, comma);
		sstr.erase(0, comma + 1);
		rq.push_back(temp);

		vector<string>::iterator it = rq.begin();
		for (; it != rq.end();)
		{
			if (*it == "")
				it = rq.erase(it);
			else
				++it;
		}

	} while (true);
	vec = rq;
}
void CNewTransformationDlg::Analysis()
{
	CString line;
	CString x, y;
	for (;;)
	{
		if (m_oldfile.ReadString(line) == NULL)
			break;
		line.TrimRight();
		line.TrimLeft();
		if (line.Find(_T("#Password"), 0) == 0)
		{
			m_oldfile.ReadString(line);
			m_pwd.password = ReadPassword(line);
		}
		else if (line.Find(_T("#Xscale"), 0) == 0)
		{
			m_oldfile.ReadString(line);
			ReadScale(line, x, y);
			m_pwd.xscale = _ttoi(x);
			m_pwd.yscale = _ttoi(y);
		}
		else if (line == "#Dao Cha Data")
		{
			m_oldfile.ReadString(line);
			m_tDaoChar.num = ReadNum(line);
			m_dao = new DAOCHAR[m_tDaoChar.num];
			if (m_dao == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tDaoChar.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if(ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_dao[i].xo = atoi(vec[0].c_str());
				m_dao[i].yo = atoi(vec[1].c_str());
				m_dao[i].xa = atoi(vec[2].c_str());
				m_dao[i].ya = atoi(vec[3].c_str());
				m_dao[i].xb = atoi(vec[4].c_str());
				m_dao[i].yb = atoi(vec[5].c_str());
				m_dao[i].xc = atoi(vec[6].c_str());
				m_dao[i].yc = atoi(vec[7].c_str());
				m_dao[i].index = atoi(vec[8].c_str());
				m_dao[i].a_link = atoi(vec[9].c_str());
				m_dao[i].b_link = atoi(vec[10].c_str());
				m_dao[i].c_link = atoi(vec[11].c_str());
				m_dao[i].type = atoi(vec[12].c_str());
				string NameW = vec[13].c_str();
				CString cstr(NameW.c_str());
				memset(m_dao[i].name, 0, sizeof(m_dao[i].name));
				wcscpy_s(m_dao[i].name, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Xin Hao Data")
		{
			m_oldfile.ReadString(line);
			m_tXinHao.num = ReadNum(line);
			m_xin = new XINHAO[m_tXinHao.num];
			if (m_xin == NULL)
			{
				AfxMessageBox(_T("m_xin分配存储空间错误"));
			}
			for (int i = 0; i < m_tXinHao.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_xin[i].xo = atoi(vec[0].c_str());
				m_xin[i].yo = atoi(vec[1].c_str());
				m_xin[i].DIR = atoi(vec[2].c_str());
				m_xin[i].TYPE = atoi(vec[3].c_str());
				m_xin[i].HIGH = atoi(vec[4].c_str());
				m_xin[i].FORBIDCLR = atoi(vec[5].c_str());
				m_xin[i].LX_INDEX = atoi(vec[6].c_str());
				m_xin[i].DX_INDEX = atoi(vec[7].c_str());
				m_xin[i].HIDABLE = atoi(vec[8].c_str());
				m_xin[i].T_DX = atoi(vec[9].c_str());
				m_xin[i].T_DY = atoi(vec[10].c_str());
				string NameW = vec[11].c_str();
				CString cstr(NameW.c_str());
				memset(m_xin[i].name, 0, sizeof(m_xin[i].name));
				wcscpy_s(m_xin[i].name, wcslen(cstr) + 1, cstr);
				m_xin[i].DelayX = atoi(vec[12].c_str());
				m_xin[i].DelayY = atoi(vec[13].c_str());
				++i;
			}
		}
		else if (line == "#Wu Dian Lu Qu Duan Data")
		{
			m_oldfile.ReadString(line);
			m_tWuDianLu.num = ReadNum(line);
			m_wd = new WUDIANLU[m_tWuDianLu.num];
			if (m_wd == NULL)
			{
				AfxMessageBox(_T("m_wu分配存储空间错误"));
			}
			for (int i = 0; i < m_tWuDianLu.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_wd[i].x1 = atoi(vec[0].c_str());
				m_wd[i].y1 = atoi(vec[1].c_str());
				m_wd[i].x2 = atoi(vec[2].c_str());
				m_wd[i].y2 = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Wu Cha Qu Duan Data")
		{
			m_oldfile.ReadString(line);
			m_tWchar.num = ReadNum(line);
			m_wu = new WUCHAQUDUAN[m_tWchar.num];
			if (m_wu == NULL)
			{
				AfxMessageBox(_T("m_wu分配存储空间错误"));
			}
			for (int i = 0; i < m_tWchar.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				if (line == " ")
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_wu[i].x1 = atoi(vec[0].c_str());
				m_wu[i].y1 = atoi(vec[1].c_str());
				m_wu[i].x2 = atoi(vec[2].c_str());
				m_wu[i].y2 = atoi(vec[3].c_str());
				m_wu[i].index = atoi(vec[4].c_str());
				m_wu[i].x = atoi(vec[5].c_str());
				m_wu[i].y = atoi(vec[6].c_str());
				m_wu[i].HIDABLE = atoi(vec[7].c_str());
				m_wu[i].CANQGJ = atoi(vec[8].c_str());
				m_wu[i].CANPLQGJ = atoi(vec[9].c_str());
				m_wu[i].Fauces = atoi(vec[10].c_str());
				m_wu[i].CommandID = atoi(vec[11].c_str());
				memset(m_wu[i].name, 0, sizeof(m_wu[i].name));
				string NameW = vec[12].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_wu[i].name, wcslen(cstr) + 1, cstr);
				m_wu[i].DelayX = atoi(vec[13].c_str());
				m_wu[i].DelayY = atoi(vec[14].c_str());
				++i;
			}
		}
		else if (line == "#Jue Yuan Jie Data")
		{
			m_oldfile.ReadString(line);
			m_tJue.num = ReadNum(line);
			m_jue = new JUEYUANJIE[m_tJue.num];
			if (m_jue == NULL)
			{
				AfxMessageBox(_T("m_tJue分配存储空间错误"));
			}
			for (int i = 0; i < m_tJue.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_jue[i].TYPE = atoi(vec[0].c_str());
				m_jue[i].X0 = atoi(vec[1].c_str());
				m_jue[i].Y0 = atoi(vec[2].c_str());
				m_jue[i].X1 = atoi(vec[3].c_str());
				m_jue[i].Y1 = atoi(vec[4].c_str());
				m_jue[i].X2 = atoi(vec[5].c_str());
				m_jue[i].Y2 = atoi(vec[6].c_str());
				++i;
			}
		}
		else if (line == "#Jin Tou Xian Data")
		{
			m_oldfile.ReadString(line);
			m_tJin.num = ReadNum(line);
			m_jin = new JINTOUXIAN[m_tJue.num];
			if (m_jin == NULL)
			{
				AfxMessageBox(_T("m_jin分配存储空间错误"));
			}
			for (int i = 0; i < m_tJin.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_jin[i].x = atoi(vec[0].c_str());
				m_jin[i].y = atoi(vec[1].c_str());
				m_jin[i].type = atoi(vec[2].c_str());
				m_jin[i].dir = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Ping Mu Han Zi Data")
		{
			m_oldfile.ReadString(line);
			m_tPing.num = ReadNum(line);
			m_pin = new PINGMUHANZI[m_tPing.num];
			if (m_pin == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tPing.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_pin[i].x = atoi(vec[0].c_str());
				m_pin[i].y = atoi(vec[1].c_str());
				m_pin[i].HIDABLE = atoi(vec[2].c_str());
				memset(m_pin[i].TEXT, 0, sizeof(m_pin[i].TEXT));
				string NameW = vec[3].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_pin[i].TEXT, wcslen(cstr) + 1, cstr);
				m_pin[i].FontFamily = atoi(vec[4].c_str());
				m_pin[i].FontSize = atoi(vec[5].c_str());
				m_pin[i].FontStyle = atoi(vec[6].c_str());
				m_pin[i].FontColor = atoi(vec[7].c_str());
				++i;
			}
		}
		else if (line == "#An Niu Data")
		{
			m_oldfile.ReadString(line);
			m_tAn.sumo = ReadNum(line);
			m_oldfile.ReadString(line);
			m_tAn.num = ReadNum(line);
			m_an = new ANNIU[m_tAn.num];
			if (m_an == NULL)
			{
				AfxMessageBox(_T("m_an分配存储空间错误"));
			}
			for (int i = 0; i < m_tAn.num;)
			{

				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}

				m_an[i].x = atoi(vec[0].c_str());
				m_an[i].y = atoi(vec[1].c_str());
				if (vec[2] == "0X01")
				{
					m_an[i].TYPE = 1;
				}
				if (vec[2] == "0X21")
				{
					m_an[i].TYPE = 33;
				}

				if (vec[2] == "0X02")
				{
					m_an[i].TYPE = 2;
				}
				if (vec[2] == "0x03")
				{
					m_an[i].TYPE = 3;
				}
				if (vec[2] == "0X27")
				{
					m_an[i].TYPE = 39;
				}
				if (vec[2] == "0X07")
				{
					m_an[i].TYPE = 7;
				}
				//m_an[i].TYPE = atoi(vec[2].c_str());
				m_an[i].CommandID = atoi(vec[3].c_str());
				m_an[i].Relate1 = atoi(vec[4].c_str());
				m_an[i].Relate2 = atoi(vec[5].c_str());
				m_an[i].deltax = atoi(vec[6].c_str());
				m_an[i].deltay = atoi(vec[7].c_str());
				m_an[i].SHOW = atoi(vec[8].c_str());
				m_an[i].HIDABLE = atoi(vec[9].c_str());
				m_an[i].Fauces = atoi(vec[10].c_str());
				memset(m_an[i].NAME, 0, sizeof(m_an[i].NAME));
				string NameW = vec[11].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_an[i].NAME, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Dao Cha An Niu Data")
		{
			m_oldfile.ReadString(line);
			m_tNiu.num = ReadNum(line);
			m_niu = new DAOCHAANNIU[m_tNiu.num];
			if (m_niu == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tNiu.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_niu[i].x = atoi(vec[0].c_str());
				m_niu[i].y = atoi(vec[1].c_str());
				memset(m_niu[i].TEXT, 0, sizeof(m_niu[i].TEXT));
				string NameW = vec[2].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_niu[i].TEXT, wcslen(cstr) + 1, cstr);
				m_niu[i].CANPLQGJ = atoi(vec[3].c_str());
				m_niu[i].QD_INDEX = atoi(vec[4].c_str());
				m_niu[i].CommandID = atoi(vec[5].c_str());
				m_niu[i].Fauces = atoi(vec[6].c_str());
				m_niu[i].X1 = atoi(vec[7].c_str());
				m_niu[i].Y1 = atoi(vec[8].c_str());
				memset(m_niu[i].QDNAME, 0, sizeof(m_niu[i].QDNAME));
				NameW = vec[9].c_str();
				CString ccstr(NameW.c_str());
				wcscpy_s(m_niu[i].QDNAME, wcslen(ccstr) + 1, ccstr);
				m_niu[i].DelayX = atoi(vec[10].c_str());
				m_niu[i].DelayY = atoi(vec[11].c_str());
				++i;
			}
		}
		else if (line == "#Qu Duan Map Data")
		{
			m_oldfile.ReadString(line);
			m_tMap.num = ReadNum(line);
			m_mp = new QUDUANMAP[m_tMap.num];
			if (m_mp == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tMap.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_mp[i].Index = atoi(vec[0].c_str());
				m_mp[i].iPrDC = atoi(vec[1].c_str());
				++i;
			}
		}
		else if (line == "#Dao Cha Jiao Cha Huan Wei Data")
		{
			m_oldfile.ReadString(line);
			m_tDaoJiao.num = ReadNum(line);
			m_dcj = new DAOCHAJIAO[m_tDaoJiao.num];
			if (m_dcj == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tDaoJiao.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_dcj[i].DC1 = atoi(vec[0].c_str());
				m_dcj[i].DWZG1 = atoi(vec[1].c_str());
				m_dcj[i].DC2 = atoi(vec[2].c_str());
				m_dcj[i].DWZG2 = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Biao Shi Deng Data")
		{
			m_oldfile.ReadString(line);
			m_tBiao.num = ReadNum(line);
			m_bi = new BIAOSHIDENG[m_tBiao.num];
			if (m_bi == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tBiao.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_bi[i].Type = atoi(vec[0].c_str());
				m_bi[i].X = atoi(vec[1].c_str());
				m_bi[i].Y = atoi(vec[2].c_str());
				m_bi[i].Dir = atoi(vec[3].c_str());
				m_bi[i].Index = atoi(vec[4].c_str());
				m_bi[i].Xt = atoi(vec[5].c_str());
				m_bi[i].Yt = atoi(vec[6].c_str());
				m_bi[i].Hiable = atoi(vec[7].c_str());
				memset(m_bi[i].Text, 0, sizeof(m_bi[i].Text));
				string NameW = vec[8].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_bi[i].Text, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Zi Mian Ban Pan Kuang Data")
		{
			m_oldfile.ReadString(line);
			m_tZi.num = ReadNum(line);
			m_zi = new ZIMIAN[m_tZi.num];
			if (m_zi == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tZi.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_zi[i].Left = atoi(vec[0].c_str());
				m_zi[i].Top = atoi(vec[1].c_str());
				m_zi[i].Right = atoi(vec[2].c_str());
				m_zi[i].Botton = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Qian Fen Zhi Liu Data")
		{
			m_oldfile.ReadString(line);
			m_tfen.num = ReadNum(line);
			m_qf = new QIANFEN[m_tfen.num];
			if (m_qf == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tfen.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_qf[i].dir = atoi(vec[0].c_str());
				m_qf[i].x = atoi(vec[1].c_str());
				m_qf[i].y = atoi(vec[2].c_str());
				++i;
			}
		}
		else if (line == "#Fang Xiang Biao Data")
		{
			m_oldfile.ReadString(line);
			m_tfan.num = ReadNum(line);
			m_fa = new FANG[m_tfan.num];
			if (m_fa == NULL)
			{
				AfxMessageBox(_T("m_fa分配存储空间错误"));
			}
			for (int i = 0; i < m_tfan.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_fa[i].x = atoi(vec[0].c_str());
				m_fa[i].y = atoi(vec[1].c_str());
				m_fa[i].type = atoi(vec[2].c_str());
				++i;
			}
		}
		else if (line == "#Ping Liu Duan Kou Data")
		{
			m_oldfile.ReadString(line);
			m_tpduan.num = ReadNum(line);
			m_pl = new PINGDUAN[m_tpduan.num];
			if (m_pl == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tpduan.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_pl[i].ID = atoi(vec[0].c_str());
				m_pl[i].X = atoi(vec[1].c_str());
				m_pl[i].Y = atoi(vec[2].c_str());
				m_pl[i].Index = atoi(vec[3].c_str());
				m_pl[i].Fauces = atoi(vec[4].c_str());
				memset(m_pl[i].Text, 0, sizeof(m_pl[i].Text));
				string NameW = vec[5].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_pl[i].Text, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Ping Liu Fen Qu Data")
		{
			m_oldfile.ReadString(line);
			m_tpf.num = ReadNum(line);
			m_pf = new PINGFEN[m_tpf.num];
			if (m_pf == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tpf.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_pf[i].ID = atoi(vec[0].c_str());
				m_pf[i].DkID0 = atoi(vec[1].c_str());
				m_pf[i].DkID1 = atoi(vec[2].c_str());
				m_pf[i].DkID2 = atoi(vec[3].c_str());
				m_pf[i].DkID3 = atoi(vec[4].c_str());
				memset(m_pf[i].Text, 0, sizeof(m_pf[i].Text));
				string NameW = vec[5].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_pf[i].Text, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Ping Liu Gu Dao Data")
		{
			//PINGGU m_tPgu;
			//GU m_gu;
			m_oldfile.ReadString(line);
			m_tPgu.num = ReadNum(line);
			m_gu = new PINGGU[m_tPgu.num];
			if (m_gu == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tPgu.num;)
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_gu[i].FqID = atoi(vec[0].c_str());
				m_gu[i].CommandID = atoi(vec[1].c_str());
				memset(m_gu[i].Text, 0, sizeof(m_gu[i].Text));
				string NameW = vec[2].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_gu[i].Text, wcslen(cstr) + 1, cstr);
				++i;
			}
		}
		else if (line == "#Station Name Image")
		{
			m_oldfile.ReadString(line);
			m_tSta.num = ReadNum(line);
			m_st = new STATIONNAME[m_tSta.num];
			if (m_st == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tSta.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_st[i].x = atoi(vec[0].c_str());
				m_st[i].y = atoi(vec[1].c_str());
				memset(m_st[i].name, 0, sizeof(m_st[i].name));
				string NameW = vec[2].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_st[i].name, wcslen(cstr) + 1, cstr);
				memset(m_st[i].namet, 0, sizeof(m_st[i].namet));
				NameW = vec[3].c_str();
				CString csstr(NameW.c_str());
				wcscpy_s(m_st[i].namet, wcslen(csstr) + 1, csstr);
				++i;
			}
		}
		else if (line == "#Te Shu Delay Message")
		{
			m_oldfile.ReadString(line);
			m_tTeshu.num = ReadNum(line);
			m_te = new TESHU[m_tTeshu.num];
			if (m_te == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tTeshu.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_te[i].Index = atoi(vec[0].c_str());
				memset(m_te[i].Text, 0, sizeof(m_te[i].Text));
				string NameW = vec[1].c_str();
				CString cstr(NameW.c_str());
				wcscpy_s(m_te[i].Text, wcslen(cstr) + 1, cstr);
				m_te[i].X = atoi(vec[2].c_str());
				m_te[i].Y = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Zhe Xian Data")
		{
			m_oldfile.ReadString(line);
			m_tZhe.num = ReadNum(line);
			m_th = new ZHEXIAN[m_tZhe.num];
			if (m_te == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tZhe.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_th[i].x = atoi(vec[0].c_str());
				m_th[i].y = atoi(vec[1].c_str());
				m_th[i].ATTR = atoi(vec[2].c_str());
				++i;
			}
		}
		else if (line == "#Button Cap Position Data")
		{
			m_oldfile.ReadString(line);
			m_tCap.num = ReadNum(line);
			m_cp = new CAP[m_tCap.num];
			if (m_cp == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tCap.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_cp[i].iCommandID = atoi(vec[0].c_str());
				m_cp[i].x = atoi(vec[1].c_str());
				m_cp[i].y = atoi(vec[2].c_str());
				++i;
			}
		}
		else if (line == "#DaoCha Button  DC_INDEX Data")
		{
			m_oldfile.ReadString(line);
			m_tDc.num = ReadNum(line);
			m_dc = new DCINDEX[m_tDc.num];
			if (m_dc == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tDc.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_dc[i].DC_INDEX = atoi(vec[0].c_str());
				++i;
			}
		}
		else if (line == "#Train Number Box Position Data")
		{
			m_oldfile.ReadString(line);
			m_tTra.num = ReadNum(line);
			m_tr = new TRAIN[m_tTra.num];
			if (m_tr == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tTra.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_tr[i].x = atoi(vec[0].c_str());
				m_tr[i].y = atoi(vec[1].c_str());
				m_tr[i].qdIndex = atoi(vec[2].c_str());
				m_tr[i].type = atoi(vec[3].c_str());
				++i;
			}
		}
		else if (line == "#Zhan Tai Data")
		{
			//	ZHAN m_tzhan;
			//ZA m_za;
			m_oldfile.ReadString(line);
			m_tzhan.num = ReadNum(line);
			m_za = new ZHAN[m_tzhan.num];
			if (m_za == NULL)
			{
				AfxMessageBox(_T("m_dao分配存储空间错误"));
			}
			for (int i = 0; i < m_tzhan.num; )
			{
				m_oldfile.ReadString(line);
				if (line.Find(_T("#"), 0) == 0)
				{
					continue;
				}
				vector<string> vec;
				if (ReadStringToUnicode(line))
				{
					ReadContent(line, vec);
				}
				m_za[i].x1 = atoi(vec[0].c_str());
				m_za[i].y1 = atoi(vec[1].c_str());
				m_za[i].x2 = atoi(vec[2].c_str());
				m_za[i].y2 = atoi(vec[3].c_str());
				m_za[i].Type = atoi(vec[4].c_str());
				++i;
			}
		}
	}
}
void CNewTransformationDlg::WriteBinFile()
{
	int headNum = 0;
	const char title[4] = { 'J','D','W','L' };
	m_binfile.Seek(0, CFile::begin);
	m_binfile.Write(title, 4);
	const char num[2] = {'G','2'};
	m_binfile.Write(num, 2);
	int titlenum = 14;
	m_binfile.Write(&titlenum, 4);
	headNum = m_binfile.GetPosition();
	int nuum = 254;
	m_binfile.Write(&nuum, 4);
	m_binfile.Seek(14, CFile::begin);
	//#password
	int vul = 0x01;
	m_binfile.Write(&vul, 2);
	int sum = 0;
	m_binfile.Write(&sum, 2);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(254, CFile::begin);
	CString str;
	WCHAR psw[LEN];
	memset(psw, 0, sizeof(psw));
	wsprintfW(psw, L"%d", m_pwd.password);
	m_binfile.Write(psw, 16);
	int valueNum = m_binfile.GetPosition();

	//#xcaleycale
	m_binfile.Seek(headNum, CFile::begin);
	nuum = 254;
	m_binfile.Write(&nuum, 4);
	vul = 0x02;
	m_binfile.Write(&vul, 2);
	sum = 0;
	m_binfile.Write(&sum, 2);
	int add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(add, CFile::begin);
	INT xcale = m_pwd.xscale;
	INT ycale = m_pwd.yscale;
	m_binfile.Write(&xcale, 4);
	m_binfile.Write(&ycale, 4);
	valueNum = m_binfile.GetPosition();

	//daochadata
	m_binfile.Seek(headNum, CFile::begin);
	CStringW wname;
	vul = 0x03;
	m_binfile.Write(&vul, 2);
	sum = 70;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tDaoChar.num;)
	{
		m_binfile.Write(&m_dao[i].xo, 4);
		m_binfile.Write(&m_dao[i].yo, 4);
		m_binfile.Write(&m_dao[i].xa, 4);
		m_binfile.Write(&m_dao[i].ya, 4);
		m_binfile.Write(&m_dao[i].xb, 4);
		m_binfile.Write(&m_dao[i].yb, 4);
		m_binfile.Write(&m_dao[i].xc, 4);
		m_binfile.Write(&m_dao[i].yc, 4);
		m_binfile.Write(&m_dao[i].index, 4);
		m_binfile.Write(&m_dao[i].a_link, 4);
		m_binfile.Write(&m_dao[i].b_link, 4);
		m_binfile.Write(&m_dao[i].c_link, 4);
		m_binfile.Write(&m_dao[i].type, 4);
		m_binfile.Write(&m_dao[i].name, 128);//
		++i;
	}
	 
	valueNum = m_binfile.GetPosition();

	//#Xin Hao Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x04;
	m_binfile.Write(&vul, 2);
	sum = 84;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tXinHao.num;)
	{
		m_binfile.Write(&m_xin[i].xo, 4);
		m_binfile.Write(&m_xin[i].yo, 4);
		m_binfile.Write(&m_xin[i].DIR, 4);
		m_binfile.Write(&m_xin[i].TYPE, 4);
		m_binfile.Write(&m_xin[i].HIGH, 4);
		m_binfile.Write(&m_xin[i].FORBIDCLR, 4);
		m_binfile.Write(&m_xin[i].LX_INDEX, 4);
		m_binfile.Write(&m_xin[i].DX_INDEX, 4);
		m_binfile.Write(&m_xin[i].HIDABLE, 4);
		m_binfile.Write(&m_xin[i].T_DX, 4);
		m_binfile.Write(&m_xin[i].T_DY, 4);
		m_binfile.Write(&m_xin[i].DelayX, 4);
		m_binfile.Write(&m_xin[i].DelayY, 4);
		m_binfile.Write(&m_xin[i].name, 128);//
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Wu Dian Lu Qu Duan Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x05;
	m_binfile.Write(&vul, 2);
	sum = 9;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tWuDianLu.num;)
	{
		m_binfile.Write(&m_wd[i].x1, 4);
		m_binfile.Write(&m_wd[i].y1, 4);
		m_binfile.Write(&m_wd[i].x2, 4);
		m_binfile.Write(&m_wd[i].y2, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();//28142 28176

	//#Wu Cha Qu Duan Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x06;
	m_binfile.Write(&vul, 2);
	sum = 57;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tWchar.num;)
	{
		vul = 3;
		m_binfile.Write(&m_wu[i].x1, 4);
		m_binfile.Write(&m_wu[i].y1, 4);
		m_binfile.Write(&m_wu[i].x2, 4);
		m_binfile.Write(&m_wu[i].y2, 4);
		m_binfile.Write(&m_wu[i].index, 4);
		m_binfile.Write(&m_wu[i].x, 4);
		m_binfile.Write(&m_wu[i].y, 4);
		m_binfile.Write(&m_wu[i].HIDABLE, 4);
		m_binfile.Write(&m_wu[i].CANQGJ, 4);
		m_binfile.Write(&m_wu[i].CANPLQGJ, 4);
		m_binfile.Write(&vul, 4);
		m_binfile.Write(&m_wu[i].CommandID, 4);
		m_binfile.Write(&m_wu[i].DelayX, 4);
		m_binfile.Write(&m_wu[i].DelayY, 4);
		m_binfile.Write(&m_wu[i].name, 128);//
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Jue Yuan Jie Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x07;
	m_binfile.Write(&vul, 2);
	sum = 130;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(add, CFile::begin);
	for (int i = 0; i < m_tJue.num;)
	{
		m_binfile.Write(&m_jue[i].TYPE, 4);
		m_binfile.Write(&m_jue[i].X0, 4);
		m_binfile.Write(&m_jue[i].Y0, 4);
		m_binfile.Write(&m_jue[i].X1, 4);
		m_binfile.Write(&m_jue[i].Y1, 4);
		m_binfile.Write(&m_jue[i].X2, 4);
		m_binfile.Write(&m_jue[i].Y2, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Jin Tou Xian Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x08;
	m_binfile.Write(&vul, 2);
	sum = 5;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(add, CFile::begin);
	for (int i = 0; i < m_tJin.num;)
	{
		m_binfile.Write(&m_jin[i].x, 4);
		m_binfile.Write(&m_jin[i].y, 4);
		m_binfile.Write(&m_jin[i].type, 4);
		m_binfile.Write(&m_jin[i].dir, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Ping Mu Han Zi Date
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x09;
	m_binfile.Write(&vul, 2);
	sum = 29;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tPing.num;)
	{
		
		m_binfile.Write(&m_pin[i].x, 4);
		m_binfile.Write(&m_pin[i].y, 4);
		m_binfile.Write(&m_pin[i].HIDABLE, 4);
		m_binfile.Write(&m_pin[i].FontFamily, 4);
		m_binfile.Write(&m_pin[i].FontSize, 4);
		m_binfile.Write(&m_pin[i].FontStyle, 4);
		m_binfile.Write(&m_pin[i].FontColor, 4);
		m_binfile.Write(&m_pin[i].TEXT, 128);//
		++i;
	}
	valueNum = m_binfile.GetPosition();  //46880 46874

	//#An Niu Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x10;
	m_binfile.Write(&vul, 2);
	sum = 162;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	m_binfile.Write(&m_tAn.sumo, 4);
	for (int i = 0; i < m_tAn.num;)
	{
		//53248
		vul = 3;
		m_binfile.Write(&m_an[i].x, 4);
		m_binfile.Write(&m_an[i].y, 4);
		m_binfile.Write(&m_an[i].TYPE, 4);
		m_binfile.Write(&m_an[i].CommandID, 4);
		m_binfile.Write(&m_an[i].Relate1, 4);
		m_binfile.Write(&m_an[i].Relate2, 4);
		m_binfile.Write(&m_an[i].deltax, 4);
		m_binfile.Write(&m_an[i].deltay, 4);
		m_binfile.Write(&m_an[i].SHOW, 4);
		m_binfile.Write(&m_an[i].HIDABLE, 4);
		m_binfile.Write(&vul, 4);
		m_binfile.Write(&m_an[i].NAME, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();//74742

	//#Dao Cha An Niu Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x11;
	m_binfile.Write(&vul, 2);
	sum = 70;
	m_binfile.Write(&sum, 2);
	add = valueNum;
	m_binfile.Write(&add, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tNiu.num;)
	{
		int Fauces =3;
		m_binfile.Write(&m_niu[i].x, 4);
		m_binfile.Write(&m_niu[i].y, 4);
		m_binfile.Write(&m_niu[i].CANPLQGJ, 4);
		m_binfile.Write(&m_niu[i].QD_INDEX, 4);
		m_binfile.Write(&m_niu[i].CommandID, 4);
		m_binfile.Write(&Fauces, 4);
		m_binfile.Write(&m_niu[i].X1, 4);
		m_binfile.Write(&m_niu[i].Y1, 4);
		m_binfile.Write(&m_niu[i].DelayX, 4);
		m_binfile.Write(&m_niu[i].DelayY, 4);
		m_binfile.Write(&m_niu[i].TEXT, 128);
		m_binfile.Write(&m_niu[i].QDNAME, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Qu Duan Map Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x12;
	m_binfile.Write(&vul, 2);
	sum = 45;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tMap.num;)
	{
		m_binfile.Write(&m_mp[i].Index, 4);
		m_binfile.Write(&m_mp[i].iPrDC, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Dao Cha Jiao Cha Huan Wei Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x13;
	m_binfile.Write(&vul, 2);
	sum = 12;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tDaoJiao.num;)
	{
		m_binfile.Write(&m_dcj[i].DC1, 4);
		m_binfile.Write(&m_dcj[i].DWZG1, 4);
		m_binfile.Write(&m_dcj[i].DC2, 4);
		m_binfile.Write(&m_dcj[i].DWZG2, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	////#Biao Shi Deng Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x14;
	m_binfile.Write(&vul, 2);
	sum = 44;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tBiao.num;)
	{
		m_binfile.Write(&m_bi[i].Type, 4);
		m_binfile.Write(&m_bi[i].X, 4);
		m_binfile.Write(&m_bi[i].Y, 4);
		m_binfile.Write(&m_bi[i].Dir, 4);
		m_binfile.Write(&m_bi[i].Index, 4);
		m_binfile.Write(&m_bi[i].Xt, 4);
		m_binfile.Write(&m_bi[i].Yt, 4);
		m_binfile.Write(&m_bi[i].Hiable, 4);
		m_binfile.Write(&m_bi[i].Text, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Zi Mian Ban Pan Kuang Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x15;
	m_binfile.Write(&vul, 2);
	sum = 12;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tZi.num;)
	{
		m_binfile.Write(&m_zi[i].Left, 4);
		m_binfile.Write(&m_zi[i].Top, 4);
		m_binfile.Write(&m_zi[i].Right, 4);
		m_binfile.Write(&m_zi[i].Botton, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Qian Fen Zhi Liu Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x16;
	m_binfile.Write(&vul, 2);
	sum = 1;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tfen.num;)
	{
		m_binfile.Write(&m_qf[i].dir, 4);
		m_binfile.Write(&m_qf[i].x, 4);
		m_binfile.Write(&m_qf[i].y, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Fang Xiang Biao Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x17;
	m_binfile.Write(&vul, 2);
	sum = 0;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	/*for (int i = 0; i < m_tfan.num;)
	{
		m_binfile.Write(&m_fa[i].x, 4);
		m_binfile.Write(&m_fa[i].y, 4);
		m_binfile.Write(&m_fa[i].type, 4);
		++i;
	}*/
	valueNum = m_binfile.GetPosition();

	//#Ping Liu Duan Kou Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x18;
	m_binfile.Write(&vul, 2);
	sum = 1;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tpduan.num;)
	{
		m_binfile.Write(&m_pl[i].ID, 4);
		m_binfile.Write(&m_pl[i].X, 4);
		m_binfile.Write(&m_pl[i].Y, 4);
		m_binfile.Write(&m_pl[i].Index, 4);
		m_binfile.Write(&m_pl[i].Fauces, 4);
		m_binfile.Write(&m_pl[i].Text, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Ping Liu Fen Qu Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x19;
	m_binfile.Write(&vul, 2);
	sum = 1;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tpf.num;)
	{
		m_binfile.Write(&m_pf[i].ID, 4);
		m_binfile.Write(&m_pf[i].DkID0, 4);
		m_binfile.Write(&m_pf[i].DkID1, 4);
		m_binfile.Write(&m_pf[i].DkID2, 4);
		m_binfile.Write(&m_pf[i].DkID3, 4);
		m_binfile.Write(&m_pf[i].Text, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Ping Liu Gu Dao Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x20;
	m_binfile.Write(&vul, 2);
	sum = m_tPgu.num;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tPgu.num;)
	{
		m_binfile.Write(&m_gu[i].FqID, 4);
		m_binfile.Write(&m_gu[i].CommandID, 4);
		m_binfile.Write(&m_gu[i].Text, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Station Name Image
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x21;
	m_binfile.Write(&vul, 2);
	sum = 2;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tSta.num;)
	{
		m_binfile.Write(&m_st[i].x, 4);
		m_binfile.Write(&m_st[i].y, 4);
		m_binfile.Write(&m_st[i].name, 128);
		m_binfile.Write(&m_st[i].namet, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Te Shu Delay Message
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x22;
	m_binfile.Write(&vul, 2);
	sum = 3;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tTeshu.num;)
	{
		m_binfile.Write(&m_te[i].Index, 4);
		m_binfile.Write(&m_te[i].X, 4);
		m_binfile.Write(&m_te[i].Y, 4);
		m_binfile.Write(&m_te[i].Text, 128);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Zhe Xian Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x23;
	m_binfile.Write(&vul, 2);
	sum = 2;
	m_binfile.Write(&sum, 2);
	vul = 105046;
	m_binfile.Write(&vul, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tZhe.num;)
	{
		m_binfile.Write(&m_th[i].x, 4);
		m_binfile.Write(&m_th[i].y, 4);
		m_binfile.Write(&m_th[i].ATTR, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Console Button Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x24;
	m_binfile.Write(&vul, 2);
	sum = 0;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	//m_binfile.Write(&sum, 2);
	valueNum = m_binfile.GetPosition();

	//#Button Cap Position Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x25;
	m_binfile.Write(&vul, 2);
	sum = 124;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tCap.num;)
	{
		m_binfile.Write(&m_cp[i].iCommandID, 4);
		m_binfile.Write(&m_cp[i].x, 4);
		m_binfile.Write(&m_cp[i].y, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#DaoCha Button  DC_INDEX Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x26;
	m_binfile.Write(&vul, 2);
	sum = 70;
	m_binfile.Write(&sum, 2);
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tDc.num;)
	{
		m_binfile.Write(&m_dc[i].DC_INDEX, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Train Number Box Position Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x27;
	m_binfile.Write(&vul, 2);
	sum = m_tTra.num;
	m_binfile.Write(&sum, 2);
	/**/m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tTra.num;)
	{
		m_binfile.Write(&m_tr[i].x, 4);
		m_binfile.Write(&m_tr[i].y, 4);
		m_binfile.Write(&m_tr[i].qdIndex, 4);
		m_binfile.Write(&m_tr[i].type, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();

	//#Zhan Tai Data
	m_binfile.Seek(headNum, CFile::begin);
	vul = 0x28;
	m_binfile.Write(&vul, 2);
	sum = m_tzhan.num;
	m_binfile.Write(&sum, 2);	
	m_binfile.Write(&valueNum, 4);
	headNum = m_binfile.GetPosition();
	m_binfile.Seek(valueNum, CFile::begin);
	for (int i = 0; i < m_tzhan.num;)
	{
		m_binfile.Write(&m_za[i].x1, 4);
		m_binfile.Write(&m_za[i].y1, 4);
		m_binfile.Write(&m_za[i].x2, 4);
		m_binfile.Write(&m_za[i].y2, 4);
		m_binfile.Write(&m_za[i].Type, 4);
		++i;
	}
	valueNum = m_binfile.GetPosition();
	
}

BOOL CNewTransformationDlg::OpenFile()
{
	CString oldFilePath;
	CString newFilePath;
	CString fileext;
	CString filetitle;
	CString binPath;
	CString datPath;

	oldFilePath = "C:\\Users\\ruanm\\Documents\\Visual Studio 2008\\Projects\\Project2\\NewTransformation\\INI\\yard.DAT";
	while (oldFilePath)
	{
		int dirpos = oldFilePath.ReverseFind('.');
		fileext = oldFilePath.Right(oldFilePath.GetLength() - dirpos - 1);
		dirpos = oldFilePath.ReverseFind('\\');
		CString filedir1 = oldFilePath.Left(dirpos + 1) + _T("new\\");
		BOOL m_b = CreateDirectory(filedir1, NULL);
		CString fname = oldFilePath.Right(oldFilePath.GetLength() - dirpos - 1);
		dirpos = fname.ReverseFind('.');
		filetitle = fname.Left(dirpos);
		newFilePath = filedir1 + filetitle + _T(".txt");
		binPath = filedir1 + filetitle + _T(".bin");
		datPath = filedir1 + filetitle + _T(".dat");
		if (m_oldfile.Open(oldFilePath, CFile::modeRead) == NULL)
		{
			AfxMessageBox(_T("文件打开失败"));
			return FALSE;
		}
		Analysis();
		//从.dat转换到.text文件
		CFileException fileException;
		/*if (m_newfile.Open(newFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText), &fileException)
		{
			WriteTextFile();
		}
		else
		{
			TRACE("Can't open file %s,error=%u/n", newFilePath, fileException.m_cause);
			return FALSE;
		}*/
		//从.dat文件转换到.bin文件
		CFileException fileexception;
		if (m_binfile.Open(binPath, CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary), &fileexception)
		{
			WriteBinFile();
		}
		else
		{
			TRACE("Can't open file %s,error=%u/n", binPath, fileexception.m_cause);
			return FALSE;
		}
		/*//从.bin文件转换到.dat文件
		CFileException exception;
		if (m_datFile.Open(datPath, CFile::modeCreate | CFile::modeWrite | CFile::typeText), &exception)
		{
			WriteDatFile();
		}
		else
		{
			TRACE("Can't open file %s,error=%u/n", datPath, exception.m_cause);
			return FALSE;
		}*/
		break;
	}
	SendMessage(WM_CLOSE);
	return TRUE;
}