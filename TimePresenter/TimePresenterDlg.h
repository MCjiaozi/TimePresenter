
// TimePresenterDlg.h: 头文件
//

#pragma once


// CTimePresenterDlg 对话框
class CTimePresenterDlg : public CDialogEx
{
// 构造
public:
	CTimePresenterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMEPRESENTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void RefreshStatic(BOOL Force);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	void ToTray();
	NOTIFYICONDATA m_nid;
	void OpenMenu();
	void OpenSettings();
	void ShowTime();
	CString lTime;
	CString GetConfig(CString AppName, CString KeyName);
	void WriteConfig(CString AppName, CString KeyName, CString Key);
	void ConInit();
	CString TimeFormat;
	void SetPosition();
	COLORREF FontColor;
	COLORREF BgrColor;
	CString FontFamily;
	int FontSize;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMsg1(WPARAM wParam, LPARAM lParam);
	CFont* dFont = new CFont;
	BOOL MsgBox = FALSE;
	CString Position;
	int ShiftX = 0;
	int ShiftY = 0;
};
