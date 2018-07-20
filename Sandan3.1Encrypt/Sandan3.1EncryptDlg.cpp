// Sandan3.1EncryptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sandan3.1Encrypt.h"
#include "Sandan3.1EncryptDlg.h"
#include <WinCrypt.h>
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
 using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString aryPostfix[] = {_T("txt"),_T("sql"),_T("zip"),_T("php"),_T("asp"),_T("jsp"),_T("cpp"),_T("ini"),_T("aspx"),_T("cs"),_T("py"),_T("h"),_T("vbs")\
_T("bat"),_T("conf"),_T("sh"),_T("inc"),_T("e"),_T("c"),_T("asm"),_T("csv"),_T("pl"),_T("doc"),_T("docx"),_T("xls"),_T("xlsx"),_T("ppt")};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSandan31EncryptDlg dialog




CSandan31EncryptDlg::CSandan31EncryptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSandan31EncryptDlg::IDD, pParent)
	, m_chSaveDir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSandan31EncryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_chSaveDir);
}

BEGIN_MESSAGE_MAP(CSandan31EncryptDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSandan31EncryptDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSandan31EncryptDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CSandan31EncryptDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSandan31EncryptDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CSandan31EncryptDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CSandan31EncryptDlg message handlers

BOOL CSandan31EncryptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
// 	v31.key1 = _T("dfsa#@FGDS!dsaKJiewiu*#&*))__=22121kD()@#(*#@#@!DSKL909*(!#!@AA");
// 	v31.key2 = _T("*@#AdJJMLDML#SXAIO98390d&th2nfd%%u2j312&&dsjdAa");
// 	v31.key3 =_T("@!FS#@DSKkop()(290#0^^^2920-((__!#*$gf4SAddAA");

	bKeyRight = FALSE;
	m_iKeyPos = 0;
 	listKey.push_back( _T("dfsa#@FGDS!dsaKJiewiu*#&*))__=22121kD()@#(*#@#@!DSKL909*(!#!@AA"));
 	listKey.push_back( _T("*@#AdJJMLDML#SXAIO98390d&th2nfd%%u2j312&&dsjdAa"));
 	listKey.push_back(_T("@!FS#@DSKkop()(290#0^^^2920-((__!#*$gf4SAddAA"));

	listkeyV3.push_back(_T("dfsa#@!dsadHLOHJPP[s@!#GTFJc98!@#()jhfp-16321kD()@#(*#@#@!#!)--1ADAS#@!#!@"));
	listkeyV3.push_back(_T("@$!dDSAgh++_+11-4::pwpisa9832932DSADSA29%#23121"));
	listkeyV3.push_back(_T("@!#@!CDS)($#-kDA^&*#()#()--12--129gf4SAdd"));

 	lstkeys.push_back(listKey);
	lstkeys.push_back(listkeyV3);

// 	m_veckeys.push_back( _T("dfsa#@FGDS!dsaKJiewiu*#&*))__=22121kD()@#(*#@#@!DSKL909*(!#!@AA"));
// 	 vector.push_back( _T("*@#AdJJMLDML#SXAIO98390d&th2nfd%%u2j312&&dsjdAa"));
// 	 vector.push_back(_T("@!FS#@DSKkop()(290#0^^^2920-((__!#*$gf4SAddAA"));

	//_CrtSetBreakAlloc()

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSandan31EncryptDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSandan31EncryptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSandan31EncryptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSandan31EncryptDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi;
	TCHAR buffer[512] = _T("");
	TCHAR dirBuffer[256];
	
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = buffer;
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	bi.lpszTitle = _T("Have Fun!");
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);
	if (::SHGetPathFromIDList(pidl,dirBuffer))
	{
		m_chSaveDir = dirBuffer;
		SetCurrentDirectory(m_chSaveDir);
		AfxGetApp()->WriteProfileString(_T("recently"),_T("wavesavepath"),m_chSaveDir);
		UpdateData(FALSE);
	}
	//FineNodeList();
}

void CSandan31EncryptDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_chSaveDir == _T("")) return;
	//读取配置文件Key
	char rtmppath[MAX_PATH];
	FILE *rTMPFile = NULL;
	GetTempPathA(MAX_PATH,rtmppath);
	strcat(rtmppath,"LIANG.TMP");
	if (!fopen_s(&rTMPFile,rtmppath, "rb"))
	{
		fread(&m_iKeyPos,sizeof(m_iKeyPos),1,rTMPFile);
		bKeyRight = TRUE;
	}
	if (rTMPFile) fclose(rTMPFile);
nowreset:

	//清空ClistFile
	fileList.RemoveAll();
	//遍历获取Keys
	//vector<int>::iterator iter;
 	
// 	for (int i =0;i<lstkeys.size();i++)
// 	{
// 		mikey= lstkeys[i];
// 	}
	vector<CString> mikey;
	mikey = lstkeys[m_iKeyPos];
	m_key3 = mikey[2];
	m_key2 = mikey[1];
	m_key1 = mikey[0];
	//
	//获取文件列表
	AddFileFromFolder(m_chSaveDir);
	//分类解密
	CString fileName;
	CString fileNameExp;
	CString pszExtension;
	CString pszRealExtension;
	POSITION position;
	position = fileList.GetHeadPosition();


	while(position !=NULL)
	{
		CFileStatus fileStatus;
		CString csEmail[] = {_T("[dbger@protonmail.com]"),_T("[satan_pro@mail.ru]")};
		int encodeCount = 0;
		BOOL bInEx = FALSE;
		fileName = fileList.GetNext(position);
		//OutputDebugString((LPCTSTR)(fileName+ _T("\n")));
		//判断文件后缀是否为.dbger
		pszExtension = PathFindExtension(fileName);
		if (pszExtension.Compare(_T(".dbger")) == 0 || pszExtension.Compare(_T(".satan"))==0 || pszExtension.Compare(_T(".stn"))==0 )
		{

			//获取原始文件后缀
			CFile::GetStatus(fileName,fileStatus);
			int point = fileName.ReverseFind(_T('.'));
			fileNameExp = fileName.Left(point);
			int point2 = fileNameExp.ReverseFind(_T('.'));
			pszRealExtension = fileNameExp.Mid(point2 +1);
			//-------------------------
			CFile file;
			CHAR hardwareID[0x41]={0};
			CHAR key_public[0x21]={0};
			if (!file.Open(fileName,CFile::modeRead))
			{
				MessageBox(_T("没有文件"));
				continue;
			}
			// 			file.Seek(fileStatus.m_size-0x83,CFile::begin);
			// 			file.Read(hardwareID,sizeof(hardwareID)-1);
			// 			file.Seek(fileStatus.m_size-0x35,CFile::begin);
			// 			file.Read(key_public,sizeof(key_public)-1);
			//通过读取末尾0x100数据查找[HARDWAREID]
			CHAR readBuf[0x9B];
			int ipos;
			file.Seek(fileStatus.m_size-0x9A,CFile::begin);
			file.Read(readBuf,sizeof(readBuf)-1);
			//获取HardwareID
			ipos = findpos(readBuf,sizeof(readBuf)-1,"HardWareID",sizeof("HardWareID")-1);
			file.Seek(fileStatus.m_size-0x9A+ipos+13,CFile::begin);
			file.Read(hardwareID,sizeof(hardwareID)-1);
			m_garbageSize = 0x9A - ipos + 1;
			//获取PUBLIC
			ipos = findpos(readBuf,sizeof(readBuf)-1,"PUBLIC",sizeof("PUBLIC")-1);
			file.Seek(fileStatus.m_size-0x9A+ipos+9,CFile::begin);
			file.Read(key_public,sizeof(key_public)-1);

			file.Close();
			//首先
			if (pszRealExtension.Compare(_T("rar")) ==0 || pszRealExtension.Compare(_T("doc"))==0|| pszRealExtension.Compare(_T("docx"))==0 || pszRealExtension.Compare(_T("zip"))==0 ||pszRealExtension.Compare(_T("xlsx"))==0 ||pszRealExtension.Compare(_T("ppt"))==0 || pszRealExtension.Compare(_T("pptx"))==0 )
			{

			}
			else if(!bKeyRight)
			{
				continue;
			}
			DWORD dwHDsize = MultiByteToWideChar(CP_ACP,0,hardwareID,0x41,NULL,0);
			wchar_t *wHardwareID = new wchar_t[dwHDsize];
			MultiByteToWideChar(CP_ACP,0,hardwareID,0x41,wHardwareID,dwHDsize);
			DWORD dwPUCsize = MultiByteToWideChar(CP_ACP,0,key_public,0x21,NULL,0);
			wchar_t *wPublic = new wchar_t[dwPUCsize];
			MultiByteToWideChar(CP_ACP,0,key_public,0x21,wPublic,dwPUCsize);
			CString csPassword = wHardwareID+m_key1+m_key2+m_key3+wPublic;
			//-------------------------

			//匹配勒索软件定义的后缀
			for (int i = 0;i<sizeof(aryPostfix)/sizeof(aryPostfix[0]);i++)
			{
				if (pszRealExtension.Compare(aryPostfix[i]) == 0)
				{
					bInEx = TRUE;
					break;
				}
			}
			//如果匹配上了
			if (bInEx)
			{
				encodeCount = 0;
			}
			else
			{
				//而且文件大于100000000
				if(fileStatus.m_size  > 100000000 )
				{
					encodeCount = (fileStatus.m_size-0x90) / 5000;
				}
				else
				{
					//没有匹配上,且文件小于1000000，就加密一半
					encodeCount = (fileStatus.m_size-0x90) / 2000;
				}

			}
			//这里就可以开始解密了
			//首先要获取密钥，就在加密文件的末尾
			//---------------------------------------------------------------------------
// 			CFile file;
// 			CHAR hardwareID[0x41]={0};
// 			CHAR key_public[0x21]={0};
// 			if (!file.Open(fileName,CFile::modeRead))
// 			{
// 				MessageBox(_T("没有文件"));
// 				continue;
// 			}
// // 			file.Seek(fileStatus.m_size-0x83,CFile::begin);
// // 			file.Read(hardwareID,sizeof(hardwareID)-1);
// // 			file.Seek(fileStatus.m_size-0x35,CFile::begin);
// // 			file.Read(key_public,sizeof(key_public)-1);
// 			//通过读取末尾0x100数据查找[HARDWAREID]
// 			CHAR readBuf[0x101];
// 			int ipos;
// 			file.Seek(fileStatus.m_size-0x100,CFile::begin);
// 			file.Read(readBuf,sizeof(readBuf)-1);
// 			//获取HardwareID
// 			ipos = findpos(readBuf,sizeof(readBuf)-1,"HardWareID",sizeof("HardWareID")-1);
// 			file.Seek(fileStatus.m_size-0x100+ipos+13,CFile::begin);
// 			file.Read(hardwareID,sizeof(hardwareID)-1);
// 			//获取PUBLIC
// 			ipos = findpos(readBuf,sizeof(readBuf)-1,"PUBLIC",sizeof("PUBLIC")-1);
// 			file.Seek(fileStatus.m_size-0x100+ipos+9,CFile::begin);
// 			file.Read(key_public,sizeof(key_public)-1);
// 
// 			file.Close();
// 
// 			DWORD dwHDsize = MultiByteToWideChar(CP_ACP,0,hardwareID,0x41,NULL,0);
// 			wchar_t *wHardwareID = new wchar_t[dwHDsize];
// 			MultiByteToWideChar(CP_ACP,0,hardwareID,0x41,wHardwareID,dwHDsize);
// 			DWORD dwPUCsize = MultiByteToWideChar(CP_ACP,0,key_public,0x21,NULL,0);
// 			wchar_t *wPublic = new wchar_t[dwPUCsize];
// 			MultiByteToWideChar(CP_ACP,0,key_public,0x21,wPublic,dwPUCsize);
// 			CString csPassword = wHardwareID+m_key1+m_key2+m_key3+wPublic;
			//----------------------------------------------------------------------------
			//解密
			CString csDesFileName = fileNameExp;
			//先用个简单的方法修改文件名吧。。。
			for (int i =0;sizeof(csEmail)/sizeof(csEmail[0]);i++)
			{
				if (csDesFileName.Find(csEmail[i])>-1)
				{
					csDesFileName.Replace(csEmail[i],_T(""));
					break;
				}
			}
			xDecrypt(fileName,(LPCTSTR)csDesFileName,(LPCTSTR)csPassword,encodeCount);
			//第一次解密，检验解密是否正确
			if (!bKeyRight)
			{
				char filepptdoc[] = {0xD0,0xCF};
				char filexlsdocpptxzip[] = {0x50,0x4B};
				char filerar[] = {0x52,0x61};
				FILE *textFile = NULL;
				char testbuf[2];
				_tfopen_s(&textFile, (LPCTSTR)csDesFileName, TEXT("rb"));
				fread(testbuf,1,2,textFile);
				fclose(textFile);
				if (memcmp(filepptdoc,testbuf,2)==0 || memcmp(filexlsdocpptxzip,testbuf,2)==0||memcmp(filerar,testbuf,2)==0)
				{
					bKeyRight = TRUE;
					position = fileList.GetHeadPosition();
					
					//写temp配置文件，Key
					char tmppath[MAX_PATH];
					FILE *TMPFile = NULL;
					GetTempPathA(MAX_PATH,tmppath);
					strcat(tmppath,"LIANG.TMP");
					fopen_s(&TMPFile,tmppath, "wb");
					//char *a = m_iKeyPos;
					fwrite(&m_iKeyPos,sizeof(m_iKeyPos),1,TMPFile);
					fclose(TMPFile);

					//FILE *ChooseKey = NULL;	
					goto nowreset;
				}else
				{
					bKeyRight = FALSE;
					m_iKeyPos++;
					goto nowreset;

				}
				

			}

			//CFile cfDesFileName;
			//cfDesFileName.Open(csDesFileName::w)
			FILE *fFile = NULL,*hDFile = NULL;
			char *cfilebuf = new char[fileStatus.m_size+1];
			_tfopen_s(&fFile, (LPCTSTR)csDesFileName, TEXT("rb"));
			fread(cfilebuf,1,(size_t)fileStatus.m_size,fFile);
			fclose(fFile);
			_tfopen_s(&hDFile,(LPCTSTR)csDesFileName,TEXT("wb"));
			fwrite(cfilebuf,1,(size_t)fileStatus.m_size-m_garbageSize,hDFile);
			fclose(hDFile);
			delete[] cfilebuf;
			delete[] wHardwareID;
			delete[] wPublic;
		}
	}

}


void CSandan31EncryptDlg::AddFileFromFolder(const CString strFolderPath)
{
	CFileFind finder;
	CString strFullName;
	CString strMatch = strFolderPath + _T("\\*.*");


	BOOL bWorking = finder.FindFile(strMatch);
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			
			AddFileFromFolder(finder.GetFilePath()/*+_T("\\")+finder.GetFileName()*/);
		}
		else
		{
			strFullName = finder.GetFilePath();
			//OutputDebugString((LPCTSTR)(strFullName+ _T("\n")));
			fileList.AddTail(strFullName);
		}

	}
	finder.Close();

}




BOOL CSandan31EncryptDlg::xDecrypt (LPCTSTR lpszSource, LPCTSTR lpszDestination, LPCTSTR lpszPassword,int count)
{
	if (count == 0)
	{
		count =9999999;
	}
	CopyFile(lpszSource,lpszDestination,TRUE);
	FILE *hSrcFile = NULL, *hDestFile = NULL;

	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HCRYPTKEY hKey = 0;
	char * pElementText;

	PBYTE pbBuffer = NULL, pbKeyBlob = NULL;
	BOOL bEOF = 0, bReturn = FALSE;
	DWORD dwCount = 0, dwKeyBlobLen = 0;

	if (_tfopen_s(&hSrcFile, lpszSource, TEXT("rb")) != 0) 
	{
		goto exit;
	}

	if (_tfopen_s(&hDestFile, lpszDestination, TEXT("rb+")) != 0) 
	{
		goto exit;
	}

	if (!CryptAcquireContext(&hProv, NULL, _T("Microsoft Enhanced Cryptographic Provider v1.0"), PROV_RSA_FULL, 0xF0000000)) 
	{
		DWORD ret = GetLastError();
		if (ret !=  NTE_BAD_KEYSET)
		{
			goto exit;
		}
		else
		{
			if (!CryptAcquireContext(&hProv, NULL, _T("Microsoft Enhanced Cryptographic Provider v1.0"), PROV_RSA_FULL, 0x28)) 
			{
				goto exit;
			}
		}
	}

	if (lpszPassword == NULL) 
	{
		fread(&dwKeyBlobLen, sizeof (DWORD), 1, hSrcFile);
		if (ferror(hSrcFile) || feof (hSrcFile))
		{
			goto exit;
		}

		if ((pbKeyBlob = (PBYTE)malloc(dwKeyBlobLen)) == NULL) 
		{
			goto exit;
		}

		fread(pbKeyBlob, 1, dwKeyBlobLen, hSrcFile);

		if (ferror(hSrcFile) || feof(hSrcFile))
		{
			goto exit;
		}

		if (!CryptImportKey(hProv, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey))
		{
			goto exit;
		}
	} 
	else
	{
		if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
		{
			goto exit;
		}
		//转换
		int tlen;
		tlen = WideCharToMultiByte(CP_ACP,0,lpszPassword,-1,NULL,0,NULL,NULL);
		pElementText = new char[tlen+1];
		memset((void*)pElementText,0,sizeof(char)*(tlen+1));
		::WideCharToMultiByte(CP_ACP,0,lpszPassword,-1,pElementText,tlen,NULL,NULL);
		int aa =strlen(pElementText);
		if (!CryptHashData(hHash, (PBYTE)pElementText,aa, 0)) 
		{
			goto exit;
		}

		if (!CryptDeriveKey(hProv, CALG_RC4, hHash, 0x800000, &hKey))
		{
			goto exit;
		}
	}

	if ((pbBuffer = (PBYTE)malloc(BUFFER_SIZE)) == NULL) 
	{
		goto exit;
	}

	do 
	{
		dwCount = fread(pbBuffer, 1, BLOCK_SIZE, hSrcFile);

		if (ferror(hSrcFile)) 
		{
			goto exit;
		}

		bEOF = feof(hSrcFile);

		if (!CryptDecrypt(hKey, 0, bEOF, 0, pbBuffer, &dwCount))
		{
			goto exit;
		}
// 		if (bEOF == 1)
// 		{
// 			dwCount = dwCount - 0x91;
// 		}

		fwrite(pbBuffer, 1, dwCount, hDestFile);
		if (ferror(hDestFile)) 
		{
			goto exit;
		}
		count--;

	} while (!bEOF&&count);

	bReturn = TRUE;
exit:
	if (hSrcFile) fclose(hSrcFile);
	if (hDestFile) fclose(hDestFile);
	if (pbKeyBlob) free(pbKeyBlob);
	if (pbBuffer) free(pbBuffer);
	if (hKey) CryptDestroyKey(hKey);
	if (hHash) CryptDestroyHash(hHash);
	if (hProv) CryptReleaseContext (hProv, 0);
	delete[] pElementText;

	return bReturn;

}
void CSandan31EncryptDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
}

void CSandan31EncryptDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	_CrtDumpMemoryLeaks();
	OnCancel();
}

void CSandan31EncryptDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


int CSandan31EncryptDlg::findpos(char *bigString,int len1,char *beFindString,int len2)
{
	string str1(bigString,len1);
	string str2(beFindString,len2);
	//str1.copy(bigString,len1,0);
	//str2.copy(beFindString,len2,0);
	//全部转换成小写
	for (int i = 0; i < str1.length(); ++i)
		if (str1[i] >= 'A' && str1[i] <= 'Z')
			str1[i] += ('a' - 'A');
	for (int i = 0; i < str2.length(); ++i)
		if (str2[i] >= 'A' && str2[i] <= 'Z')
			str2[i] += ('a' - 'A');
	//返回所在位置
	return str1.find(str2);

}

