// Sandan3.1EncryptDlg.h : header file
//

#pragma once
using namespace std;


// CSandan31EncryptDlg dialog
class CSandan31EncryptDlg : public CDialog
{
// Construction
public:
	CSandan31EncryptDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SANDAN31ENCRYPT_DIALOG };
	#define BLOCK_SIZE            1000
	#define BUFFER_SIZE           1008

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CString m_chSaveDir;

 	CString m_key1;
 	CString m_key2;
 	CString m_key3;
	int m_iKeyPos;
	int m_garbageSize;
//	vector <CStringList> m_veckeys;
  	vector<CString> listKey;
	vector<CString> listkeyV3;
  	vector <vector<CString>>lstkeys;
 	CStringList fileList;
	BOOL bKeyRight;



	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void AddFileFromFolder(const CString strFolderPath);
	BOOL xDecrypt (LPCTSTR lpszSource, LPCTSTR lpszDestination, LPCTSTR lpszPassword,int count);
	int findpos(char *bigString,int len1,char *beFindString,int len2);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
};
