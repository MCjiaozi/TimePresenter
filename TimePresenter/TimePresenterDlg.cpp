
// TimePresenterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TimePresenter.h"
#include "TimePresenterDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Settings.h"

#define UM_TRAYNOTIFY WM_USER + 1
#define WM_MSG1 WM_USER + 2

// CTimePresenterDlg 对话框



CTimePresenterDlg::CTimePresenterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMEPRESENTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_nid, 0, sizeof(m_nid)); // Initialize NOTIFYICONDATA struct
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
}

void CTimePresenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimePresenterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(UM_TRAYNOTIFY, &CTimePresenterDlg::OnTrayNotify)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MSG1, OnMsg1)
END_MESSAGE_MAP()


// CTimePresenterDlg 消息处理程序

BOOL CTimePresenterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	HANDLE m_hMutex = CreateMutex(NULL, FALSE, _T("TimePresenter"));
	DWORD nRet = GetLastError();
	if (nRet == ERROR_ALREADY_EXISTS)
	{

		HWND hWnd = ::FindWindow(NULL, _T("TimePresenter"));
		::PostMessage(hWnd, WM_MSG1, NULL, NULL);
		//MessageBox(_T("应用程序启动失败：\n程序已经在运行中，或存在其他程序与本程序进程互斥（Mutex）。\n请检查正在运行的程序，然后重试。\n\n要关闭本程序存在的其他实例，请单击托盘栏中的本程序图标，然后选择退出。"), _T("启动失败 - 时间悬浮窗"), MB_ICONERROR);
		OnOK();
	}
	ToTray();
	SetWindowText(_T("TimePresenter"));
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	ConInit();
	SetTimer(1, 1, NULL);
	SetTimer(2, 1, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimePresenterDlg::OnPaint()
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
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, BgrColor);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTimePresenterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimePresenterDlg::RefreshStatic(BOOL Force)
{
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format(TimeFormat);
	if (strTime != lTime || Force) {
		CRect rc;
		GetDlgItem(IDC_STATIC_TIME)->GetWindowRect(&rc);
		ScreenToClient(&rc);
		InvalidateRect(rc);
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText(strTime);
		lTime = strTime;
	}
}



HBRUSH CTimePresenterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
	{
		//pDC->SetTextColor(RGB(255, 165, 0));
		pDC->SetTextColor(FontColor);
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


void CTimePresenterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1) {
		HWND hWnd = ::FindWindow(NULL, _T("设置 - 时间悬浮窗"));
		if (hWnd == NULL && !MsgBox)BringWindowToTop();
		RefreshStatic(FALSE);
	}
	else if (nIDEvent == 2) {
		SetPosition();
		KillTimer(2);
	}
	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CTimePresenterDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = (UINT)lParam;
	switch (uMsg) {
	case WM_LBUTTONUP://左键
		OpenMenu();
		break;
	case WM_RBUTTONUP://右键
		OpenMenu();
		break;
	case WM_MBUTTONUP://中键
		OpenMenu();
		break;
	default:
		break;
	}
	return LRESULT();
}

void CTimePresenterDlg::ToTray()
{
	m_nid.hWnd = GetSafeHwnd();
	m_nid.uCallbackMessage = UM_TRAYNOTIFY;
	m_nid.hIcon = m_hIcon;
	CString strToolTip = _T("时间显示");
	_tcsncpy_s(m_nid.szTip, strToolTip, strToolTip.GetLength());
	Shell_NotifyIcon(NIM_ADD, &m_nid);
}

void CTimePresenterDlg::OpenMenu() {
	CMenu menuTray;
	CPoint point;
	int id;
	GetCursorPos(&point);
	menuTray.LoadMenu(IDR_MENU_TRAY);
	SetForegroundWindow();
	id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	switch (id) {
	case IDR_TRAY_EXIT:
		Shell_NotifyIcon(NIM_DELETE, &m_nid);
		OnOK();
		break;
	case IDR_MENU_ABOUT:
		MsgBox = TRUE;
		MessageBox(_T("程序名称：时间悬浮窗（TimePresenter）\n\n本程序使用进程互斥锁，互斥体对象名为TimePresenter。"), _T("程序信息 - 时间悬浮窗"), MB_ICONINFORMATION);
		MsgBox = FALSE;
		break;
	case IDR_MENU_SETTINGS:
		OpenSettings();
		break;
	default:
		break;
	}
}

void CTimePresenterDlg::OpenSettings() {
	Settings* pOneDlgObj = new Settings;
	if (pOneDlgObj)
	{
		Settings dlg(this);
		BOOL ret = pOneDlgObj->Create(IDD_SETTINGS, GetDesktopWindow());
	}
	pOneDlgObj->ShowWindow(SW_SHOW);
}

CString CTimePresenterDlg::GetConfig(CString AppName, CString KeyName) {
	return theApp.GetProfileString(AppName, KeyName, _T("default"));
}


void CTimePresenterDlg::WriteConfig(CString AppName, CString KeyName, CString Key) {
	theApp.WriteProfileString(AppName, KeyName, Key);
}

void CTimePresenterDlg::ConInit() {
	CString GetFormat = GetConfig(_T("Settings"), _T("Format")), strFormat;
	GetFormat.Replace(_T("%"), _T(""));
	if (GetFormat == _T("default") || GetFormat == _T(""))strFormat = _T("HH:MM:SS");
	else strFormat = GetFormat;
	WriteConfig(_T("Settings"), _T("Format"), strFormat);
	strFormat.Replace(_T("YY"), _T("%Y"));
	strFormat.Replace(_T("mm"), _T("%m"));
	strFormat.Replace(_T("dd"), _T("%d"));
	strFormat.Replace(_T("HH"), _T("%H"));
	strFormat.Replace(_T("MM"), _T("%M"));
	strFormat.Replace(_T("SS"), _T("%S"));
	strFormat.Replace(_T("\\n"), _T("\n"));

	CString GetFontSize = GetConfig(_T("Settings"), _T("FontSize")), strFontSize;
	if (GetFontSize == _T("default") || GetFontSize == _T(""))strFontSize = _T("28");
	else strFontSize.Format(_T("%d"), _ttoi(GetFontSize));
	WriteConfig(_T("Settings"), _T("FontSize"), strFontSize);

	int GetShiftX = _ttoi(GetConfig(_T("Settings"), _T("ShiftX"))), GetShiftY = _ttoi(GetConfig(_T("Settings"), _T("ShiftY")));
	CString strShiftX, strShiftY;
	strShiftX.Format(_T("%d"), GetShiftX);
	strShiftY.Format(_T("%d"), GetShiftY);
	WriteConfig(_T("Settings"), _T("ShiftX"), strShiftX);
	WriteConfig(_T("Settings"), _T("ShiftY"), strShiftY);

	CString GetPosition = GetConfig(_T("Settings"), _T("Position")), strPosition;
	if (GetPosition != _T("UR") && GetPosition != _T("UL") && GetPosition != _T("UC") && GetPosition != _T("C") && GetPosition != _T("CL") && GetPosition != _T("CR") && GetPosition != _T("BL") && GetPosition != _T("BC") && GetPosition != _T("BR")) {
		WriteConfig(_T("Settings"), _T("Position"), _T("UR"));
		strPosition = _T("UR");
	}
	else strPosition = GetPosition;

	CString GetRGB = GetConfig(_T("Settings"), _T("RGB")), strRGB;
	if (GetRGB == _T("default") || GetRGB == _T(""))strRGB = _T("255,165,0");
	else strRGB = GetRGB;
	CString strR = _T("255"), strG = _T("165"), strB = _T("0");
	int R = 255, G = 165, B = 0;
	if (AfxExtractSubString(strR, strRGB, 0, ',') && AfxExtractSubString(strG, strRGB, 1, ',') && AfxExtractSubString(strB, strRGB, 2, ',')) {
		R = _ttoi(strR);
		G = _ttoi(strG);
		B = _ttoi(strB);
		strR.Format(_T("%d"), R);
		strG.Format(_T("%d"), G);
		strB.Format(_T("%d"), B);
	}
	WriteConfig(_T("Settings"), _T("RGB"), strR + _T(",") + strG + _T(",") + strB);

	CString GetFontFamily = GetConfig(_T("Settings"), _T("FontFamily")), strFontFamily;
	if (GetFontFamily == _T("default") || GetFontFamily == _T("")) {
		strFontFamily = _T("微软雅黑");
		WriteConfig(_T("Settings"), _T("FontFamily"), GetFontFamily);
	}
	else strFontFamily = GetFontFamily;

	ShiftX = _ttoi(strShiftX);
	ShiftY = _ttoi(strShiftY);
	Position = strPosition;
	TimeFormat = strFormat;
	FontSize = _ttoi(strFontSize);
	FontColor = RGB(R, G, B);
	BgrColor = RGB(R, G, B + 1);
	::SetLayeredWindowAttributes(GetSafeHwnd(), BgrColor, 0, LWA_COLORKEY);
	dFont->CreateFont(int(FontSize * (GetDeviceCaps(::GetDC(NULL), LOGPIXELSY) / static_cast<double>(96))), 0, 0, 0, TRUE, FALSE, FALSE, 0, NULL, NULL, NULL, NULL, NULL, strFontFamily);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(dFont);
	RefreshStatic(TRUE);
	SetPosition();
}

void CTimePresenterDlg::SetPosition() {
	HDC desktopDc = ::GetDC(NULL);
	int x = GetDeviceCaps(desktopDc, HORZRES);
	int y = GetDeviceCaps(desktopDc, VERTRES);
	//部分字体数字宽度不同，取4作为最大宽度数字
	CString strFormat = TimeFormat;
	strFormat.Replace(_T("%Y"), _T("4444"));
	strFormat.Replace(_T("%m"), _T("44"));
	strFormat.Replace(_T("%d"), _T("44"));
	strFormat.Replace(_T("%H"), _T("44"));
	strFormat.Replace(_T("%M"), _T("44"));
	strFormat.Replace(_T("%S"), _T("44"));
	CClientDC dc(this);
	CRect rect;
	GetClientRect(rect);
	dc.SelectObject(dFont);
	CString cutFor;
	int ci = 0;
	int ccx = 0;
	for (;;) {
		if (!AfxExtractSubString(cutFor, strFormat, ci, '\n'))break;
		else {
			int ddx = dc.GetTextExtent(cutFor).cx;
			if (ddx > ccx)ccx = ddx;
			ci++;
		}
	}
	int ccy = dc.GetTextExtent(lTime).cy * ci;
	GetDlgItem(IDC_STATIC_TIME)->SetWindowPos(NULL, 0, 0, ccx, ccy, NULL);
	if (Position == _T("UR")) {
		SetWindowPos(NULL, x - ccx + ShiftX, ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_LEFT | SS_CENTER, SS_RIGHT);
	}
	else if (Position == _T("UL")) {
		SetWindowPos(NULL, ShiftX, ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_CENTER, SS_LEFT);
	}
	else if (Position == _T("UC")) {
		SetWindowPos(NULL, (x - ccx) / 2 + ShiftX, ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_LEFT, SS_CENTER);
	}
	else if (Position == _T("C")) {
		SetWindowPos(NULL, (x - ccx) / 2 + ShiftX, (y - ccy) / 2 + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_LEFT, SS_CENTER);
	}
	else if (Position == _T("CL")) {
		SetWindowPos(NULL, ShiftX, (y - ccy) / 2 + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_CENTER, SS_LEFT);
	}
	else if (Position == _T("CR")) {
		SetWindowPos(NULL, x - ccx + ShiftX, (y - ccy) / 2 + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_LEFT | SS_CENTER, SS_RIGHT);
	}
	else if (Position == _T("BL")) {
		SetWindowPos(NULL, ShiftX, y - ccy + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_CENTER, SS_LEFT);
	}
	else if (Position == _T("BC")) {
		SetWindowPos(NULL, (x - ccx) / 2 + ShiftX, y - ccy + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_RIGHT | SS_LEFT, SS_CENTER);
	}
	else if (Position == _T("BR")) {
		SetWindowPos(NULL, x - ccx + ShiftX, y - ccy + ShiftY, ccx, ccy, NULL);
		GetDlgItem(IDC_STATIC_TIME)->ModifyStyle(SS_LEFT | SS_CENTER, SS_RIGHT);
	}
}

BOOL CTimePresenterDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

LRESULT CTimePresenterDlg::OnMsg1(WPARAM wParam, LPARAM lParam) {
	OpenSettings();
	return 0;
}