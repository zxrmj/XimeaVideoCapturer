
// mfc_captureVideoNewDlg.h : 头文件
//

#pragma once
#include <opencv.hpp>
using namespace cv;
using namespace std;

// Cmfc_captureVideoNewDlg 对话框
class Cmfc_captureVideoNewDlg : public CDialogEx
{
// 构造
public:
	Cmfc_captureVideoNewDlg(CWnd* pParent = NULL);	// 标准构造函数
	vector<VideoWriter> vws;
	bool isSaving = false;
	bool capimg = false;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CAPTUREVIDEONEW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedCap();
};
