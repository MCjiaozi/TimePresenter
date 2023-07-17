#pragma once
#include "afxdialogex.h"


// Settings 对话框

class Settings : public CDialogEx
{
	DECLARE_DYNAMIC(Settings)

public:
	Settings(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Settings();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_format;
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	virtual void OnOK();
	virtual void PostNcDestroy();
	CString GetConfig(CString AppName, CString KeyName);
	void WriteConfig(CString AppName, CString KeyName, CString Key);
	void ApplySettings();
	BOOL CheckAutoRun();
	void EnableAutoRun();
	void DisableAutoRun();
	afx_msg void OnBnClickedButtonApply();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMFCColorButton m_color;
	static int CALLBACK EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, DWORD FontType, LPARAM lParam);
	CComboBox m_fontfamily;
	afx_msg void OnBnClickedButtonCde();
	void DeleteData();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedCancel();
};