﻿
// SampleMDIView.cpp : CSampleMDIView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "SampleMDI.h"
#endif

#include "SampleMDIDoc.h"
#include "SampleMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSampleMDIView

IMPLEMENT_DYNCREATE(CSampleMDIView, CView)

BEGIN_MESSAGE_MAP(CSampleMDIView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSampleMDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSampleMDIView コンストラクション/デストラクション

CSampleMDIView::CSampleMDIView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CSampleMDIView::~CSampleMDIView()
{
}

BOOL CSampleMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CSampleMDIView 描画

void CSampleMDIView::OnDraw(CDC* /*pDC*/)
{
	CSampleMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CSampleMDIView の印刷


void CSampleMDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSampleMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CSampleMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CSampleMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

void CSampleMDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSampleMDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSampleMDIView の診断

#ifdef _DEBUG
void CSampleMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSampleMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSampleMDIDoc* CSampleMDIView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSampleMDIDoc)));
	return (CSampleMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSampleMDIView メッセージ ハンドラー
