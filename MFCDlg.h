
// MFCDlg.h: 头文件
//

#pragma once

#include "opencv2\opencv.hpp"
#include "opencv2\core\types_c.h"
// CMFCDlg 对话框
class CMFCDlg : public CDialogEx
{
// 构造
public:
	CMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	//
	CString FileName;//记录所选文件路径
	CRect rect;
	CStatic*pStc;//标识图像控件的矩形
	CDC* pDC;//视频显示控件设备上下文
	HDC hDC;//视频显示控件设备句柄
	CvCapture* pCapture;
	IplImage* pFrame;
	bool flage;
	int flag_stop;
	int flag_break;
	//
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_enable;
	afx_msg void OnBnClickedStartvideo();
	afx_msg void OnBnClickedPausevideo();
	afx_msg void OnBnClickedStopvideo();
};
