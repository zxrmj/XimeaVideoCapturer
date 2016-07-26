
// mfc_captureVideoNewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_captureVideoNew.h"
#include "mfc_captureVideoNewDlg.h"
#include "afxdialogex.h"
#include "xiApi.h"
#include <opencv.hpp>
#include <thread>
using namespace cv;
using namespace std;
#pragma comment(lib,"m3apiX64.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_captureVideoNewDlg �Ի���



Cmfc_captureVideoNewDlg::Cmfc_captureVideoNewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CAPTUREVIDEONEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_captureVideoNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_captureVideoNewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &Cmfc_captureVideoNewDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &Cmfc_captureVideoNewDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CAP, &Cmfc_captureVideoNewDlg::OnBnClickedCap)
END_MESSAGE_MAP()


void save(Cmfc_captureVideoNewDlg *dlg)
{
	// image buffer
	//ͼƬ������
	XI_IMG image;
	//����������
	memset(&image, 0, sizeof(image));
	image.size = sizeof(XI_IMG);

	// Sample for XIMEA API V2.10
	HANDLE xiH = NULL;
	XI_RETURN stat = XI_OK;

	// Get number of camera devices
	// ��ȡ����豸����
	DWORD dwNumberOfDevices = 0;
	stat = xiGetNumberDevices(&dwNumberOfDevices);
	if (stat != XI_OK)
	{
		return;
	}
	// Retrieving a handle to the camera device 
	stat = xiOpenDevice(0, &xiH);
	if (stat != XI_OK)
	{
		return;
	}
	// Setting "exposure" parameter (10ms=10000us)
	stat = xiSetParamInt(xiH, XI_PRM_EXPOSURE, 5000);
	if (stat != XI_OK)
	{
		return;
	}
	stat = xiSetParamInt(xiH, XI_PRM_IMAGE_DATA_FORMAT, XI_RGB24);
	if (stat != XI_OK)
	{
		return;
	}
	stat = xiStartAcquisition(xiH);
	if (stat != XI_OK)
	{
		return;
	}
	for (int images = 0; images < INT32_MAX; images++)
	{
		// getting image from camera
		// ������ͷ��ȡͼƬ
		stat = xiGetImage(xiH, 5000, &image);
		Mat dstImage(Size(image.width, image.height), CV_8UC3);
		memcpy(dstImage.data, image.bp, image.width*image.height * 3);
		imshow("Output", dstImage);
		waitKey(30);
		if (dlg->vws.size() >0 || dlg->isSaving == true)
		{
			int idx = dlg->vws.size() - 1;
			VideoWriter &vw = dlg->vws.at(idx);
			vw << dstImage;
			
		}
		if (dlg->capimg == true)
		{
			imwrite("image" + to_string(images) + ".jpg", dstImage);
			dlg->capimg = false;
		}
	}
}
// Cmfc_captureVideoNewDlg ��Ϣ�������

BOOL Cmfc_captureVideoNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	thread t1(save, this);
	t1.detach();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cmfc_captureVideoNewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cmfc_captureVideoNewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmfc_captureVideoNewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cmfc_captureVideoNewDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	VideoWriter vw;
	time_t tm = time(0);
	vw.open(".//11video" + to_string(vws.size()) + ".avi", CV_FOURCC('D', 'I', 'V', 'X'), 25.0, Size(1280, 1024), true);
	//vw.open(".//11video" + to_string(vws.size()) + ".mp4", CV_FOURCC('M', 'P', 'G', '4'), 25.0, Size(1280, 1024), true);
	vws.push_back(vw);
	isSaving = true;
	GetDlgItem(IDC_START)->EnableWindow(false);
	GetDlgItem(IDC_STOP)->EnableWindow(true);
}


void Cmfc_captureVideoNewDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	auto last = vws.back();
	last.release();
	isSaving = false;
	GetDlgItem(IDC_STOP)->EnableWindow(false);
	GetDlgItem(IDC_START)->EnableWindow(true);
}


void Cmfc_captureVideoNewDlg::OnBnClickedCap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	capimg = true;
}
