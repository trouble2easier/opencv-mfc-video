
// MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"
#include "ImageTransform.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDlg 对话框



CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PAUSEVIDEO, m_enable);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTVIDEO, &CMFCDlg::OnBnClickedStartvideo)
	ON_BN_CLICKED(IDC_PAUSEVIDEO, &CMFCDlg::OnBnClickedPausevideo)
	ON_BN_CLICKED(IDC_STOPVIDEO, &CMFCDlg::OnBnClickedStopvideo)
END_MESSAGE_MAP()


// CMFCDlg 消息处理程序

BOOL CMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
    //cv::namedWindow("view", 1);
	//HWND hwnd = (HWND)GetWindowDC("view");

	

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDlg::OnBnClickedStartvideo()
{
	//通过鼠标点击文档，打开视频文件
	CString filter;
	std::string  filename;
	filter = "所有文件(*.avi,*.3gp,*.mp4,*.rm,*rmvb,*flash) | *.avi;*.3gp;*.mp4;*.rm;*.rmvb;*flash";//视频文件类型。
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
	if (dlg.DoModal() == IDOK)  //用户单击OK按钮中止对话框的返回值
	{
		CString FileName = dlg.GetPathName();   //获取文件路径名 如D:\\1.jpg
		filename = (CStringA)FileName;   //把CString转换成filename
	}
	//char* file = (char*)filename.GetBuffer(filename.GetLength());
	//filename.ReleaseBuffer();
	cv::VideoCapture cap;
	cap.open(filename);
	if (!cap.isOpened())
	{
		AfxMessageBox(_T("无法找到视频"));
		return;
	}
	
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_STATIC);
	pWnd->GetClientRect(&rect);
	int x = rect.Width();
	int y = rect.Height();
	flage = TRUE;
	flag_stop = 0;
	while (flage)
	{
		flag_break = 0;
		cv::Mat frame;
		cap >> frame;
		if (!(cap.read(frame)))
		{
			AfxMessageBox(_T("读取视频结束"));
			return;
		}
		if (flag_stop)
		{
			while (TRUE)
			{
				cv::waitKey(30);
				if (flag_break)
					break;
			}
		}
		cv::Mat dst;
		cv::resize(frame, dst, cv::Size(x, y), 0, 0, 1);
		CImage image;
		ImageTransform mc;
		//mc.MatToCImage(dst, image);
		CDC *pDC = pWnd->GetDC();//获得pictrue控件的DC  
		//HDC hDC = pDC->GetSafeHdc();

		mc.MatToCImage(dst, image);
		image.Draw(pDC->m_hDC, rect);
		cv::waitKey(10);
		
	}



	// TODO: 在此添加控件通知处理程序代码
}


void CMFCDlg::OnBnClickedPausevideo()
{
	CString str;
	m_enable.GetWindowTextW(str);
	if (str == "暂停")
	{
		flag_stop = 1;
		m_enable.SetWindowTextW(_T("继续"));
	}
	else
	{
		flag_stop = 0;
		flag_break = 1;
		m_enable.SetWindowTextW(_T("暂停"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCDlg::OnBnClickedStopvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("退出吗"), _T("提示"),MB_YESNO | MB_ICONWARNING) == IDNO)
	{
		return;
	}
	flag_break = 1;
	flage = FALSE;
	SendMessage(WM_CLOSE, 0, 0);
}
