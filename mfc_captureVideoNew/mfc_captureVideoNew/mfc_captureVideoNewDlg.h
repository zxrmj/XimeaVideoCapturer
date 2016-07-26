
// mfc_captureVideoNewDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv.hpp>
using namespace cv;
using namespace std;

// Cmfc_captureVideoNewDlg �Ի���
class Cmfc_captureVideoNewDlg : public CDialogEx
{
// ����
public:
	Cmfc_captureVideoNewDlg(CWnd* pParent = NULL);	// ��׼���캯��
	vector<VideoWriter> vws;
	bool isSaving = false;
	bool capimg = false;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CAPTUREVIDEONEW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
