// Settings.cpp: 实现文件
//

#include "pch.h"
#include "TimePresenter.h"
#include "afxdialogex.h"
#include "Settings.h"
#include "TimePresenterDlg.h"


// Settings 对话框

IMPLEMENT_DYNAMIC(Settings, CDialogEx)

CTimePresenterDlg* pParentDlg;

Settings::Settings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTINGS, pParent)
{
	pParentDlg = (CTimePresenterDlg*)pParent;

}

Settings::~Settings()
{
}

void Settings::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_COMBO_SETTINGS_FORMAT, m_combo_format);
	DDX_Control(pDX, IDC_COMBO_STYLE_FF, m_fontfamily);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_FC, m_color);

	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, TRUE);
	SetIcon(icon, FALSE);

	SetWindowText(_T("设置 - 时间悬浮窗"));
	double sk = GetDeviceCaps(::GetDC(NULL), LOGPIXELSY) / static_cast<double>(96);
	CFont* f1 = new CFont;
	f1->CreateFont(int(38 * sk), 0, 0, 0, TRUE, FALSE, FALSE, 0, NULL, NULL, NULL, NULL, NULL, _T("微软雅黑"));
	GetDlgItem(IDC_SETTINGS_TITLE)->SetFont(f1);
	CFont* f2 = new CFont;
	f2->CreateFont(int(18 * sk), 0, 0, 0, TRUE, FALSE, FALSE, 0, NULL, NULL, NULL, NULL, NULL, _T("微软雅黑"));
	GetDlgItem(IDOK)->SetFont(f2);
	GetDlgItem(IDCANCEL)->SetFont(f2);
	GetDlgItem(IDC_BUTTON_APPLY)->SetFont(f2);
	GetDlgItem(IDC_SETTINGS_GROUP_FORMAT)->SetFont(f2);
	GetDlgItem(IDC_SETTINGS_GROUP_POSITION)->SetFont(f2);
	GetDlgItem(IDC_SETTINGS_FORMAT_1)->SetFont(f2);
	GetDlgItem(IDC_COMBO_SETTINGS_FORMAT)->SetFont(f2);
	GetDlgItem(IDC_CHECK_AUTORUN)->SetFont(f2);
	GetDlgItem(IDC_STATIC_FORMAT_D)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_UR)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_UL)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_UC)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_C)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_CL)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_CR)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_BL)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_BC)->SetFont(f2);
	GetDlgItem(IDC_RADIO_POSITION_BR)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POSITION_SHIFT)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POSITION_SHIFT_X)->SetFont(f2);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_X)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POSITION_SHIFT_Y)->SetFont(f2);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_Y)->SetFont(f2);
	GetDlgItem(IDC_STATIC_POSITION_D)->SetFont(f2);
	GetDlgItem(IDC_SETTINGS_GROUP_STYLE)->SetFont(f2);
	GetDlgItem(IDC_STATIC_STYLE_FS)->SetFont(f2);
	GetDlgItem(IDC_EDIT_STYLE_FS)->SetFont(f2);
	GetDlgItem(IDC_STATIC_STYLE_FC)->SetFont(f2);
	GetDlgItem(IDC_BUTTON_CDE)->SetFont(f2);
	GetDlgItem(IDC_BUTTON_RESET)->SetFont(f2);
	GetDlgItem(IDC_STATIC_SETTINGS_ADVANCE)->SetFont(f2);
	GetDlgItem(IDC_STATIC_STYLE_FF)->SetFont(f2);
	GetDlgItem(IDC_COMBO_STYLE_FF)->SetFont(f2);

	if (CheckAutoRun())((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->SetCheck(1);
	else ((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->SetCheck(0);

	CString GetFormat = GetConfig(_T("Settings"), _T("Format")), strFormat;
	if (GetFormat == _T("default") || GetFormat == _T("")) {
		strFormat = _T("HH:MM:SS");
	}
	else strFormat = GetFormat;
	WriteConfig(_T("Settings"), _T("Format"), strFormat);
	m_combo_format.InsertString(0, strFormat);
	m_combo_format.SetCurSel(0);

	CString Position = GetConfig(_T("Settings"), _T("Position"));
	if (Position == _T("UR"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_UR))->SetCheck(1);
	else if (Position == _T("UL"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_UL))->SetCheck(1);
	else if (Position == _T("UC"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_UC))->SetCheck(1);
	else if (Position == _T("C"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_C))->SetCheck(1);
	else if (Position == _T("CL"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_CL))->SetCheck(1);
	else if (Position == _T("CR"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_CR))->SetCheck(1);
	else if (Position == _T("BL"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_BL))->SetCheck(1);
	else if (Position == _T("BC"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_BC))->SetCheck(1);
	else if (Position == _T("BR"))((CButton*)GetDlgItem(IDC_RADIO_POSITION_BR))->SetCheck(1);
	else {
		((CButton*)GetDlgItem(IDC_RADIO_POSITION_UR))->SetCheck(1);
		WriteConfig(_T("Settings"), _T("Position"), _T("UR"));
	}

	CString strShiftX, strShiftY;
	strShiftX.Format(_T("%d"), _ttoi(GetConfig(_T("Settings"), _T("ShiftX"))));
	strShiftY.Format(_T("%d"), _ttoi(GetConfig(_T("Settings"), _T("ShiftY"))));
	WriteConfig(_T("Settings"), _T("ShiftX"), strShiftX);
	WriteConfig(_T("Settings"), _T("ShiftY"), strShiftY);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_X)->SetWindowText(strShiftX);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_Y)->SetWindowText(strShiftY);

	CString GetFontSize = GetConfig(_T("Settings"), _T("FontSize")), strFontSize;
	if (GetFontSize == _T("default") || GetFontSize == _T(""))strFontSize = _T("28");
	else strFontSize.Format(_T("%d"), _ttoi(GetFontSize));
	WriteConfig(_T("Settings"), _T("FontSize"), strFontSize);
	GetDlgItem(IDC_EDIT_STYLE_FS)->SetWindowText(strFontSize);

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
	m_color.SetColor(RGB(R, G, B));
	m_color.EnableAutomaticButton(_T("默认颜色"), RGB(255, 165, 0), TRUE);
	m_color.EnableOtherButton(_T("更多颜色"), TRUE, TRUE);

	CClientDC dc(this);
	EnumFontFamilies((HDC)dc, NULL, (FONTENUMPROCW)EnumFontFamProc, (LPARAM)this);

	CString GetFontFamily = GetConfig(_T("Settings"), _T("FontFamily")), strFontFamily;
	if (GetFontFamily == _T("default") || GetFontFamily == _T("")) {
		strFontFamily = _T("微软雅黑");
		WriteConfig(_T("Settings"), _T("FontFamily"), GetFontFamily);
	}
	else strFontFamily = GetFontFamily;
	m_fontfamily.InsertString(0, strFontFamily);
	m_fontfamily.SetCurSel(0);

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Settings, CDialogEx)
	ON_BN_CLICKED(IDOK, &Settings::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &Settings::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CDE, &Settings::OnBnClickedButtonCde)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &Settings::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDCANCEL, &Settings::OnBnClickedCancel)
END_MESSAGE_MAP()


// Settings 消息处理程序

void Settings::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ApplySettings();
	Settings::OnOK();
}

void Settings::ApplySettings()
{
	if (((CButton*)GetDlgItem(IDC_CHECK_AUTORUN))->GetCheck() == 1)EnableAutoRun();
	else DisableAutoRun();

	CString GetFormat, strFormat;
	GetDlgItem(IDC_COMBO_SETTINGS_FORMAT)->GetWindowText(GetFormat);
	GetFormat.Replace(_T("%"), _T(""));
	if (GetFormat == _T(""))strFormat = _T("HH:MM:SS");
	else strFormat = GetFormat;
	WriteConfig(_T("Settings"), _T("Format"), strFormat);
	m_combo_format.DeleteString(0);
	m_combo_format.InsertString(0, strFormat);
	m_combo_format.SetCurSel(0);
	strFormat.Replace(_T("YY"), _T("%Y"));
	strFormat.Replace(_T("mm"), _T("%m"));
	strFormat.Replace(_T("dd"), _T("%d"));
	strFormat.Replace(_T("HH"), _T("%H"));
	strFormat.Replace(_T("MM"), _T("%M"));
	strFormat.Replace(_T("SS"), _T("%S"));
	strFormat.Replace(_T("\\n"), _T("\n"));

	CString GetFontSize, strFontSize;
	GetDlgItem(IDC_EDIT_STYLE_FS)->GetWindowText(GetFontSize);
	if (GetFontSize == _T(""))strFontSize = _T("28");
	else strFontSize.Format(_T("%d"), _ttoi(GetFontSize));
	WriteConfig(_T("Settings"), _T("FontSize"), strFontSize);
	GetDlgItem(IDC_EDIT_STYLE_FS)->SetWindowText(strFontSize);

	CString GetShiftX, GetShiftY, strShiftX, strShiftY;
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_X)->GetWindowText(GetShiftX);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_Y)->GetWindowText(GetShiftY);
	int ShiftX = _ttoi(GetShiftX), ShiftY = _ttoi(GetShiftY);
	strShiftX.Format(_T("%d"), ShiftX);
	strShiftY.Format(_T("%d"), ShiftY);
	WriteConfig(_T("Settings"), _T("ShiftX"), strShiftX);
	WriteConfig(_T("Settings"), _T("ShiftY"), strShiftY);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_X)->SetWindowText(strShiftX);
	GetDlgItem(IDC_EDIT_POSITION_SHIFT_Y)->SetWindowText(strShiftY);

	CString GetPosition;
	if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_UR))->GetCheck() == 1)GetPosition = _T("UR");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_UL))->GetCheck() == 1)GetPosition = _T("UL");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_UC))->GetCheck() == 1)GetPosition = _T("UC");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_C))->GetCheck() == 1)GetPosition = _T("C");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_CL))->GetCheck() == 1)GetPosition = _T("CL");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_CR))->GetCheck() == 1)GetPosition = _T("CR");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_BL))->GetCheck() == 1)GetPosition = _T("BL");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_BC))->GetCheck() == 1)GetPosition = _T("BC");
	else if (((CButton*)GetDlgItem(IDC_RADIO_POSITION_BR))->GetCheck() == 1)GetPosition = _T("BR");
	else GetPosition = _T("UR");
	WriteConfig(_T("Settings"), _T("Position"), GetPosition);

	COLORREF GetColor;
	GetColor =m_color.GetColor();
	if (GetColor == -1)GetColor = m_color.GetAutomaticColor();
	COLORREF BakColor = RGB(GetRValue(GetColor), GetGValue(GetColor), GetBValue(GetColor) + 1);
	CString strR, strG, strB;
	strR.Format(_T("%d"), GetRValue(GetColor));
	strG.Format(_T("%d"), GetGValue(GetColor));
	strB.Format(_T("%d"), GetBValue(GetColor));
	WriteConfig(_T("Settings"), _T("RGB"), strR + _T(",") + strG + _T(",") + strB);

	CString GetFontFamily, strFontFamily;
	GetDlgItem(IDC_COMBO_STYLE_FF)->GetWindowText(GetFontFamily);
	if (GetFontFamily == _T(""))strFontFamily = _T("微软雅黑");
	else strFontFamily = GetFontFamily;
	WriteConfig(_T("Settings"), _T("FontFamily"), strFontFamily);
	m_fontfamily.DeleteString(0);
	m_fontfamily.InsertString(0, strFontFamily);
	m_fontfamily.SetCurSel(0);

	pParentDlg->ShiftX = ShiftX;
	pParentDlg->ShiftY = ShiftY;
	pParentDlg->Position = GetPosition;
	pParentDlg->TimeFormat = strFormat;
	pParentDlg->FontSize = _ttoi(strFontSize);
	pParentDlg->FontColor = GetColor;
	pParentDlg->BgrColor = BakColor;
	::SetLayeredWindowAttributes(pParentDlg->GetSafeHwnd(), BakColor, 0, LWA_COLORKEY);
	pParentDlg->dFont->CreateFont(int(_ttoi(strFontSize) * (GetDeviceCaps(::GetDC(NULL), LOGPIXELSY) / static_cast<double>(96))), 0, 0, 0, TRUE, FALSE, FALSE, 0, NULL, NULL, NULL, NULL, NULL, strFontFamily);
	pParentDlg->GetDlgItem(IDC_STATIC_TIME)->SetFont(pParentDlg->dFont);
	pParentDlg->RefreshStatic(TRUE);
	pParentDlg->SetPosition();
}

void Settings::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	DestroyWindow();
}


void Settings::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	DestroyWindow();
}


void Settings::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::PostNcDestroy();
	delete this;
}

CString Settings::GetConfig(CString AppName, CString KeyName) {
	return pParentDlg->GetConfig(AppName, KeyName);
}


void Settings::WriteConfig(CString AppName, CString KeyName, CString Key) {
	pParentDlg->WriteConfig(AppName, KeyName, Key);
}

BOOL Settings::CheckAutoRun()
{
	try
	{
		HKEY hKey;
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)MessageBox(_T("打开注册表启动项失败"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);
		TCHAR AutoRun[MAX_PATH] = {};
		DWORD nLongth = MAX_PATH;


		long result = RegGetValue(hKey, NULL, _T("TimePresenter"), RRF_RT_REG_SZ, 0, AutoRun, &nLongth);
		if (result == ERROR_SUCCESS)
		{
			DWORD dwType = REG_SZ;
			TCHAR dwValue[MAX_PATH] = {};
			DWORD dwSize = sizeof(dwValue);
			RegQueryValueEx(hKey, _T("TimePresenter"), 0, &dwType, (LPBYTE)&dwValue, &dwSize);
			CString GetPath;
			GetPath.Format(_T("%s"), dwValue);
			TCHAR pFileName[MAX_PATH] = {};
			GetModuleFileName(NULL, pFileName, MAX_PATH);
			CString FileName;
			FileName.Format(_T("%s"), pFileName);
			if (GetPath == FileName)return TRUE;
			else return FALSE;
		}
		else
		{
			return FALSE;
		}
		RegCloseKey(hKey);
	}
	catch (...) {
		MessageBox(_T("在检查开机自启时出现异常！"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		return FALSE;
	}
}

void Settings::EnableAutoRun() {
	try
	{
		HKEY hKey;
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)MessageBox(_T("打开注册表启动项失败"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);
		RegSetValueEx(hKey, _T("TimePresenter"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
		RegCloseKey(hKey);
	}
	catch (...) {
		MessageBox(_T("在设置启用开机自启时出现异常！"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		return;
	}
	return;
}

void Settings::DisableAutoRun() {
	try
	{
		HKEY hKey;
		CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)MessageBox(_T("打开注册表启动项失败"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		TCHAR pFileName[MAX_PATH] = {};
		GetModuleFileName(NULL, pFileName, MAX_PATH);
		RegDeleteValue(hKey, _T("TimePresenter"));
		RegCloseKey(hKey);
	}
	catch (...) {
		MessageBox(_T("在设置禁用开机自启时出现异常！"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		return;
	}
	return;
}

void Settings::DeleteData() {
	DisableAutoRun();
	try
	{
		HKEY hKey;
		CString lpPath = _T("SOFTWARE");
		long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpPath, 0, KEY_ALL_ACCESS, &hKey);
		if (lRet != ERROR_SUCCESS)MessageBox(_T("打开注册表失败"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		if (RegDeleteTree(hKey, _T("TimePresenter")) != ERROR_SUCCESS) {
			MessageBox(_T("删除注册表时出现异常！"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		}
		RegCloseKey(hKey);
	}
	catch (...) {
		MessageBox(_T("在设置注册表时出现异常！"), _T("错误 - 时间悬浮窗"), MB_ICONERROR);
		return;
	}
	return;
}

void Settings::OnBnClickedButtonApply()
{
	// TODO: 在此添加控件通知处理程序代码
	ApplySettings();
}


BOOL Settings::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((GetFocus() == GetDlgItem(IDC_EDIT_POSITION_SHIFT_X) || GetFocus() == GetDlgItem(IDC_EDIT_POSITION_SHIFT_Y)) && (pMsg->message == WM_CHAR)) {
		if (!((pMsg->wParam <= '9' && pMsg->wParam >= '0') || pMsg->wParam == '-' || pMsg->wParam == '\b' || GetAsyncKeyState(VK_CONTROL)))return TRUE;
	}
	else if (GetFocus() != NULL && GetFocus()->GetParent() == GetDlgItem(IDC_COMBO_SETTINGS_FORMAT) && (pMsg->message == WM_CHAR)) {
		if (pMsg->wParam == '%')return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void Settings::OnBnClickedButtonCde()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确实要清除所有数据并退出吗？此操作不可撤销！"), _T("清除所有数据并退出 - 时间悬浮窗"), MB_OKCANCEL | MB_ICONQUESTION) == 1) {
		DeleteData();
		Shell_NotifyIcon(NIM_DELETE, &(pParentDlg->m_nid));
		PostQuitMessage(0);
	}
}


void Settings::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	if (MessageBox(_T("确实要恢复默认设置吗？此操作不可撤销！"), _T("恢复默认设置 - 时间悬浮窗"), MB_OKCANCEL | MB_ICONQUESTION) == 1) {
		DeleteData();
		pParentDlg->ConInit();
		pParentDlg->OpenSettings();
		Settings::OnCancel();
	}
}

void Settings::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	Settings::OnCancel();
}

int CALLBACK Settings::EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam)
{
	Settings* pWnd = (Settings*)lParam;
	pWnd->m_fontfamily.AddString(lpelf->elfLogFont.lfFaceName);
	return 1;
}