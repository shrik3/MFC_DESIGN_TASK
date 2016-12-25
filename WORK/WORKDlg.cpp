
// WORKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WORK.h"
#include "WORKDlg.h"
#include "afxdialogex.h"
#include "OPTS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWORKDlg 对话框



CWORKDlg::CWORKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWORKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWORKDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CWORKDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_Login, &CWORKDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CWORKDlg 消息处理程序

BOOL CWORKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWORKDlg::OnPaint()
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
HCURSOR CWORKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWORKDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CWORKDlg::OnBnClickedLogin()
{
	_RecordsetPtr  m_pRecordset;//数据集连接
	_variant_t vPassword;	//存放取出来的数据的变量

	// ESTABLISH CONNECTION
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");//创建Connection对象
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			//连接数据库
		}
	}
	catch (_com_error e)//捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n错误信:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);//显示错误信息
		return;
	}

	// CHECK LOGIN INFO

	CString CPassword;
	try
	{
		CString strSQL;
		CString name,password;
		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(password);
		strSQL.Format(_T("SELECT * FROM login where USERNAME ='%s'"), name); // 有条件查找
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);
		if (m_pRecordset->EndOfFile) {    // INPUT USERNAME DOESN'T EXIST
			CString message;
			message.Format(_T("USER DOESN'T EXIST!"));
		}
		else {

			vPassword = m_pRecordset->GetCollect("PASSWORD");
			CPassword = vPassword;
			if (CPassword == password) {
				// AUTH PASSED, INIT DLG2
				this->ShowWindow(SW_HIDE);
				OPTS DLG;
				DLG.DoModal();

			}
		}


	}
	catch (_com_error e)
	{
		CString message;
		message.Format(_T("读取数据库失败!\n 错误信息为:%s"), e.Description());
		AfxMessageBox(message);///显示错误信息
	}// TODO: 在此添加控件通知处理程序代码选择读取前1个 测试用所以读的少点

	
	m_pConnection->Close();
}
