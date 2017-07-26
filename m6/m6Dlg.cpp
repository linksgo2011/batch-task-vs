
// m6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "m6.h"
#include "m6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cm6Dlg 对话框




Cm6Dlg::Cm6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cm6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cm6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cm6Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cm6Dlg::OnBnClickedOk)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &Cm6Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cm6Dlg 消息处理程序

BOOL Cm6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(false){
		CLoginDlg loginDlg;
	
		if(loginDlg.DoModal() != IDOK){
			OnOK();
		}

		if(loginDlg.userName != "admin" || loginDlg.pwd != "admin"){
			MessageBox(_T("密码错误"));
			OnOK();
		}
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cm6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cm6Dlg::OnPaint()
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
HCURSOR Cm6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cm6Dlg::OnBnClickedOk()
{
	CString path,
			fileExt,
			prefix,
			basePath,
			indexStr;
	int index = 0;
	bool bFound;
	CFileFind tempFind;
	CString fileName;

	// 获取路径
	GetDlgItem(IDC_EDIT1)->GetWindowText(path);
	GetDlgItem(IDC_EDIT2)->GetWindowText(prefix);

	if(path == ""){
		return;
	} 
	if(IDOK != AfxMessageBox(_T("当前目录为:"+path+",你确认要这样操作么？"),MB_OKCANCEL)){
		return;
	}

	bFound=tempFind.FindFile(path   +   "\\*.*");
	while(bFound){
		bFound = tempFind.FindNextFile();
		if(tempFind.IsDots()){
			continue;
		}
		index++;
		indexStr.Format("%d",index);
		fileName = tempFind.GetFilePath();
		fileExt = tempFind.GetFileName();
		fileExt = fileExt.Right(fileExt.GetLength()-fileExt.ReverseFind('.')-1); 
		
		CFile::Rename(fileName,path + "\\" + prefix + indexStr  +"."+fileExt);
		TRACE0(fileName);
	}

	CString outStr;
	outStr.Format(_T("操作成功,影响 %d 个文件"),index);
	MessageBox(outStr);
	tempFind.Close();
}


void Cm6Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar == VK_ESCAPE){
		return;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void Cm6Dlg::OnBnClickedButton1()
{
		char Buffer[512];

		BROWSEINFO bi;   
		bi.hwndOwner = m_hWnd;   
		bi.pidlRoot = NULL;   
		bi.pszDisplayName = Buffer;   
		bi.lpszTitle = _T("请选择需要打包的目录：");   
		bi.ulFlags = BIF_RETURNONLYFSDIRS;  
		bi.lpfn = NULL;   
		bi.lParam = 0;   
		bi.iImage = 0;   
		//弹出选择目录对话框
		LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

		if(lp) 
		{
			SHGetPathFromIDList(lp, Buffer);
			GetDlgItem(IDC_EDIT1)->SetWindowTextA(Buffer);
			TRACE0(Buffer);
		}else{
			AfxMessageBox(_T("无效的目录，请重新选择"));   
		}

}
