// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "chess.h"
#include "chessdoc.h"

#include "mainfrm.h"
#include <afxpriv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_MENUSELECT()
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,			// status line indicator
	ID_CHECK_STATUS,
	ID_STARTPOS,
	ID_ENDPOS,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;		// fail to create
	}

	int top=AfxGetApp()->GetProfileInt("Coords","top",100);
	int bottom=AfxGetApp()->GetProfileInt("Coords","bottom",400);
	int left=AfxGetApp()->GetProfileInt("Coords","left",100);
	int right=AfxGetApp()->GetProfileInt("Coords","right",500);
	if(top!=bottom&&left!=right)
		SetWindowPos(NULL,left,top,right-left,bottom-top,SWP_NOZORDER);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
	if(wParam=AFX_IDS_IDLEMESSAGE){
		CChessDoc * pDoc = ((CChessDoc*)GetActiveDocument());
		if(pDoc)
			wParam=(WPARAM)(pDoc->m_CurrentBoard.m_WhosGo==BLACK ? ID_THINKING : ID_YOUR_MOVE);
	}
	return CFrameWnd::OnSetMessageString(wParam, lParam);
}

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CFrameWnd::OnMenuSelect(nItemID,nFlags,hSysMenu);
	if(m_nIDTracking == AFX_IDS_IDLEMESSAGE)
		OnSetMessageString(m_nIDTracking,NULL);
}

void CMainFrame::OnClose()
{
	CChessDoc * pDoc = (CChessDoc *)GetActiveDocument();
	if(pDoc->WipeUnsavedGame()){
		RECT rc;
		GetWindowRect(&rc);
		AfxGetApp()->WriteProfileInt("Coords","top",rc.top);
		AfxGetApp()->WriteProfileInt("Coords","bottom",rc.bottom);
		AfxGetApp()->WriteProfileInt("Coords","left",rc.left);
		AfxGetApp()->WriteProfileInt("Coords","right",rc.right);
		CFrameWnd::OnClose();
	}
}
