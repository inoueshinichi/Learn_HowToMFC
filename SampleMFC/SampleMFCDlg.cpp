﻿// SampleMFCDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "SampleMFC.h"
#include "SampleMFCDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ImageMFCDlg.h"


// SampleMFCDlg ダイアログ

IMPLEMENT_DYNAMIC(SampleMFCDlg, CDialogEx)

SampleMFCDlg::SampleMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SampleMFCDlg, pParent)
	, mEditString(_T(""))
	, mCheckVB(FALSE)
	, mCheckCSharp(FALSE)
	, mCheckCpp(FALSE)
	, mValidParent(false)
	, mMainFrame(nullptr)
	, mRadioMan(FALSE)
	, mRadioWoman(FALSE)
{
	if (dynamic_cast<CMainFrame*>(pParent))
	{
		mValidParent = true;
		mMainFrame = dynamic_cast<CMainFrame*>(pParent);
		mMainFrame->AddDialog(this);
	}
	else
	{
		mValidParent = false;
		mMainFrame = nullptr;
	}

	mhIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

SampleMFCDlg::~SampleMFCDlg()
{
	if (mValidParent)
	{
		mMainFrame->RemoveDialog(this);
	}
}

/*以下, 自作関数*/


void SampleMFCDlg::AddDialog(class CDialogEx* dlg)
{
	mMFCDlgs.push_back(dlg);
}

void SampleMFCDlg::RemoveDialog(class CDialogEx* dlg)
{
	auto iter = std::find(mMFCDlgs.begin(), mMFCDlgs.end(), dlg);
	if (iter != mMFCDlgs.end())
	{
		std::iter_swap(iter, mMFCDlgs.end() - 1);
		mMFCDlgs.pop_back();
	}
}

void SampleMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mEditString);
	DDX_Check(pDX, IDC_CHECK_VB, mCheckVB);
	DDX_Check(pDX, IDC_CHECK_CSHARP, mCheckCSharp);
	DDX_Check(pDX, IDC_CHECK_CPP, mCheckCpp);
	DDX_Radio(pDX, IDC_RADIO_MAN, mRadioMan);
	DDX_Radio(pDX, IDC_RADIO_WOMAN, mRadioWoman);
}


BEGIN_MESSAGE_MAP(SampleMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &SampleMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_PAINT, &SampleMFCDlg::OnBnClickedButtonPaint)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &SampleMFCDlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_RADIO_MAN, &SampleMFCDlg::OnBnClickedRadioMan)
	ON_BN_CLICKED(IDC_RADIO_WOMAN, &SampleMFCDlg::OnBnClickedRadioWoman)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &SampleMFCDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_DATETIME, &SampleMFCDlg::OnBnClickedButtonDatetime)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, &SampleMFCDlg::OnBnClickedButtonImage)
END_MESSAGE_MAP()


// SampleMFCDlg メッセージ ハンドラー


BOOL SampleMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void SampleMFCDlg::PostNcDestroy()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	// UI消滅時に所属するオブジェクト(自身)を消す.
	delete this;

	CDialogEx::PostNcDestroy();
}


void SampleMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if ((nID & 0xFFF0) == IDD_ABOUTBOX)
	{
		if (dynamic_cast<CSampleMFCApp*>(AfxGetApp()))
		{
			dynamic_cast<CSampleMFCApp*>(AfxGetApp())->OnAppAbout();
		}
	}
	CDialogEx::OnSysCommand(nID, lParam);
}


void SampleMFCDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ここにメッセージ ハンドラー コードを追加します。
					   // 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CXICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, mhIcon);
	}
	else
	{
		CPen myPen;
		myPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		CPen* oldPen = dc.SelectObject(&myPen);
		dc.MoveTo(100, 20);
		dc.LineTo(200, 120);
		dc.SelectObject(oldPen);

		// 白
		dc.Rectangle(10, 10, 150, 100);
		dc.Ellipse(180, 10, 300, 100);

		// ブラシで指定した色
		CBrush solidBrush;
		solidBrush.CreateSolidBrush(RGB(0, 255, 0));
		CBrush* oldBrush = dc.SelectObject(&solidBrush);
		dc.Rectangle(10, 10, 150, 100);
		CBrush hatchBrush;
		hatchBrush.CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
		dc.Ellipse(180, 10, 300, 100);
		dc.SelectObject(oldBrush);

		// 文字列
		COLORREF oldColor = dc.SetTextColor(RGB(0, 0, 255));
		LOGFONT lf;
		std::memset(&lf, 0, sizeof(LOGFONT));
		_tcscpy_s(lf.lfFaceName, _T("Arial"));
		lf.lfHeight = 100;
		lf.lfItalic = true;
		lf.lfWeight = FW_BOLD;
		lf.lfUnderline = true;
		CFont font;
		font.CreateFontIndirect(&lf);
		CFont* oldFont = dc.SelectObject(&font);
		CRect rect(50, 100, 700, 200);
		dc.DrawText(_T("Visual C++"), -1, rect, DT_LEFT);
		dc.SetTextColor(oldColor);
		dc.SelectObject(oldFont);
		font.DeleteObject();
	}
}


HCURSOR SampleMFCDlg::OnQueryDragIcon()
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	return CDialogEx::OnQueryDragIcon();
}


void SampleMFCDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(true);
	AfxMessageBox(mEditString);
}


void SampleMFCDlg::OnBnClickedButtonPaint()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void SampleMFCDlg::OnBnClickedButtonApply()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(true);

	CString genderStr;
	if (mRadioMan == true && mRadioWoman == false)
	{
		genderStr = _T("男性");
	}
	else
	{
		genderStr = _T("女性");
	}

	CString languageStr;
	if (mCheckVB)
	{
		languageStr += "Visual Basic ";
	}
	if (mCheckCSharp)
	{
		languageStr += "Visual C# ";
	}
	if (mCheckCpp)
	{
		languageStr += "Visual C++ ";
	}

	CString showMessage;
	showMessage = _T("性別は") + genderStr + _T("です。\n");
	if (languageStr.IsEmpty())
	{
		showMessage += _T("得意な言語はありません。");
	}
	else
	{
		showMessage += _T("得意な言語は") + languageStr + _T("です。");
	}

	AfxMessageBox(showMessage);
}


void SampleMFCDlg::OnBnClickedRadioMan()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	mRadioMan = true;
	mRadioWoman = false;
}


void SampleMFCDlg::OnBnClickedRadioWoman()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	mRadioMan = false;
	mRadioWoman = true;
}


#include <iostream>
#include <cstdio>

void SampleMFCDlg::OnBnClickedButtonFile()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// ファイル操作
	CFile writeFile;
	CString fileName(_T("sample_text.txt"));
	CString relPath(_T("..\\"));
	CString filePath = relPath + fileName;
	bool isExistFile = false;
	if (writeFile.Open(filePath.GetString(), CFile::modeCreate | CFile::modeWrite))
	{
		CString writedStr(_T("Visual C++"));
		writeFile.Write(writedStr, writedStr.GetLength() * sizeof(TCHAR));
		writeFile.Close();

		isExistFile = true;

		CString msg;
		msg.Format(_T("ファイル名 %s を書き込みました."), fileName.GetString());
		AfxMessageBox(msg);
	}


	// 読み込み
	CFile readFile;
	TCHAR buffer[MAX_PATH];
	if (readFile.Open(filePath.GetString(), CFile::modeRead))
	{
		int readLenTchar = readFile.Read(buffer, MAX_PATH);
		size_t fileSize = readFile.GetLength();
		readFile.Close();
		
		std::cout << "aaaa" << std::endl;
		std::printf("yyyy\n");
		wprintf(L"llll\n");
		_tprintf(_T("ファイルサイズ(byte) %ld\n"), fileSize);
		_tprintf(_T("読み込んだバイト % d\n"), readLenTchar);
		AfxMessageBox(filePath + _T("を読み込みました"));
	}

	// リネーム
	CString newFilePath = relPath + _T("sample_new.txt");
	CFile::Rename(filePath, newFilePath);
	// 削除
	CFile::Remove(newFilePath);

	// ファイル情報
	CFileStatus fileStatus;
	bool isFileExist = CFile::GetStatus(newFilePath, fileStatus);

	if (isFileExist)
	{
		_tprintf(_T("%s ファイルは存在します\n"), newFilePath.GetString());
	}
	else
	{
		_tprintf(_T("%s ファイルは存在しません\n"), newFilePath.GetString());
	}

}


void SampleMFCDlg::OnBnClickedButtonDatetime()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// 日時と時刻を設定する
	COleDateTime oleDatetime;
	oleDatetime.SetDateTime(2016, 10, 30, 11, 22, 33); // 2016年10月30日11時22分33秒
	COleDataObject pcOleDatetime;// = COleDateTime::GetCurrentTime(); // システム時刻を取得

	// 時刻の解析
	COleDateTime parsedTime;
	if (parsedTime.ParseDateTime(_T("2018/05/21 21:47:45")))
	{
		_tprintf(_T("時刻は解析された\n"));
		
		int pYear = parsedTime.GetYear();
		int pMonth = parsedTime.GetMonth();
		int pDay = parsedTime.GetDay();
		int pHour = parsedTime.GetHour();
		int pMinute = parsedTime.GetMinute();
		int pSecond = parsedTime.GetSecond();
		_tprintf(_T("\n%d/%d/%d %d:%d:%d\n"), pYear, pMonth, pDay, pHour, pMinute, pSecond);

		// フォーマット指定で文字列化
		CString timeStr = parsedTime.Format(_T("%Y/%m/%d %H:%M:%S"));
		_tprintf(_T("%s\n"), timeStr.GetString());
	
	}
	else
	{
		_tprintf(_T("時刻は解析できなかった\n"));
	}
}


void SampleMFCDlg::OnBnClickedButtonImage()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	/*ImageMFCDlgの生成*/
	ImageMFCDlg* mImageDlg = new ImageMFCDlg(this);
	mImageDlg->Create(IDD_ImageMFCDlg);
	mImageDlg->ShowWindow(SW_SHOW);
}
