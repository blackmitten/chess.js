// chessvw.cpp : implementation of the CChessView class
//

#include "stdafx.h"
#include "chess.h"

#include "chessdoc.h"
#include "chessvw.h"
#include "mainfrm.h"
#include "rules.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static BOOL bNotMarked=TRUE;

class CDCWrapper : public CObject
// this class gets a DC, sets its axes AND RELEASES it on destruction so
// that I don't have to remember to and Windows doesn't run out of memory
{
public:
	CDCWrapper(CWnd* pWnd)
	{
		m_pDC=pWnd->GetDC();
		m_pDC->SetMapMode(MM_ISOTROPIC);
		RECT rc;
		pWnd->GetClientRect(&rc);
		m_pDC->SetWindowExt(1000,1000);
		m_pDC->SetViewportExt(rc.right,rc.bottom);
		m_pWnd=pWnd;
	};
	virtual ~CDCWrapper()
	{
		m_pWnd->ReleaseDC(m_pDC);
	};
	
	CDC * m_pDC;
	CWnd* m_pWnd;
};



/////////////////////////////////////////////////////////////////////////////
// CChessView

IMPLEMENT_DYNCREATE(CChessView, CView)

BEGIN_MESSAGE_MAP(CChessView, CView)
	//{{AFX_MSG_MAP(CChessView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_SPACEBAR, OnSpacebar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessView construction/destruction

CChessView::CChessView()
{
	m_bOnceThrough=FALSE;
}

CChessView::~CChessView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CChessView drawing

void CChessView::DrawSquare(CDC* pDC, int j, int i, BOOL bDrawPiece)
{
	pDC->SelectStockObject((div(i+j,2).rem==0) ? WHITE_BRUSH : DKGRAY_BRUSH);
	pDC->Rectangle(i*1000/8,j*1000/8,(i+1)*1000/8,(j+1)*1000/8);

	CPiece * pPiece;
	if(bDrawPiece&&(pPiece=GetOccupant(j,i)))
		pPiece->DrawMe(pDC);
}

void CChessView::OnDraw(CDC* pDC)
{
	CChessDoc* pDoc = GetDocument();
	pDC->SetMapMode(MM_ISOTROPIC);
	RECT rc;
	GetClientRect(&rc);
	pDC->SetWindowExt(1000,1000);
	pDC->SetViewportExt(rc.right,rc.bottom);

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			DrawSquare(pDC,i,j,TRUE);

	bNotMarked=TRUE;
	DrawCursor(pDC);
}

void CChessView::Box(CDC * pDC, BYTE row, BYTE col)
{
	RECT rc;
	rc.left=col*1000/8;
	rc.right=col*1000/8+15;
	rc.top=row*1000/8;
	rc.bottom=(row+1)*1000/8;
	pDC->InvertRect(&rc);
	rc.left=(col+1)*1000/8-15;
	rc.right=(col+1)*1000/8;
	rc.top=row*1000/8;
	rc.bottom=(row+1)*1000/8;
	pDC->InvertRect(&rc);
	rc.left=col*1000/8;
	rc.right=(col+1)*1000/8;
	rc.top=row*1000/8;
	rc.bottom=row*1000/8+15;
	pDC->InvertRect(&rc);
	rc.left=col*1000/8;
	rc.right=(col+1)*1000/8;
	rc.top=(row+1)*1000/8-15;
	rc.bottom=(row+1)*1000/8;
	pDC->InvertRect(&rc);
}

void CChessView::DrawCursor(CDC * pDC)
{
	CChessDoc* pDoc = GetDocument();
	Box(pDC,pDoc->m_CurRow,pDoc->m_CurCol);
	pDoc->m_LastCol=pDoc->m_CurCol;
	pDoc->m_LastRow=pDoc->m_CurRow;
	if(pDoc->m_pMover&&bNotMarked){
		Box(pDC,pDoc->m_pMover->m_row,pDoc->m_pMover->m_column);
		bNotMarked=FALSE;
	}
}

void CChessView::EraseOldCursor(CDC * pDC)
{
	CChessDoc* pDoc = GetDocument();
	Box(pDC,pDoc->m_LastRow,pDoc->m_LastCol);
}

void CChessView::RemoveMarker()
{
	CChessDoc* pDoc = GetDocument();
	if(pDoc->m_pMover&&!bNotMarked){
		CDCWrapper safeDC(this);
		Box(safeDC.m_pDC,pDoc->m_pMover->m_row,pDoc->m_pMover->m_column);
		bNotMarked=TRUE;
	}
}

void CChessView::OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint)
{
	CDCWrapper safeDC(this);
	switch (lHint){
		case CURSOR_MOVED:{
			CChessDoc* pDoc = GetDocument();
			if((pDoc->m_CurCol!=pDoc->m_LastCol)||(pDoc->m_CurRow!=pDoc->m_LastRow))
			{
				EraseOldCursor(safeDC.m_pDC);
				DrawCursor(safeDC.m_pDC);
			}
		}
		break;
		case PIECE_MOVING:{
			CPiece * pPiece = (CPiece*)pHint;
			DrawSquare(safeDC.m_pDC,pPiece->m_row,pPiece->m_column,FALSE);
		}
		break;
		case PIECE_MOVED:{
			CPiece * pPiece = (CPiece*)pHint;
			DrawSquare(safeDC.m_pDC,pPiece->m_row,pPiece->m_column,TRUE);
			Box(safeDC.m_pDC,pPiece->m_row,pPiece->m_column);
		}
		break;
		case BLACK_MOVED:{
			CPiece * pPiece = (CPiece*)pHint;
			DrawSquare(safeDC.m_pDC,pPiece->m_row,pPiece->m_column,TRUE);
			CChessDoc * pDoc = GetDocument();
			if(pDoc->m_CurCol==pPiece->m_column && pDoc->m_CurRow==pPiece->m_row)
				Box(safeDC.m_pDC,pPiece->m_row,pPiece->m_column);
		}
		break;
		case CASTLED:{
			CPiece * pPiece = (CPiece*)pHint;
			DrawSquare(safeDC.m_pDC,pPiece->m_row,pPiece->m_column,TRUE);
		}
		break;
		case REFRESH:
			OnDraw(safeDC.m_pDC);
		case MESSAGE_BAR:
		 	UpdateMessageBar();
		break;
		case SHOW_THINKING:
			CBoard * pBoard = (CBoard *)pHint;
			CChessDoc* pDoc = GetDocument();
			safeDC.m_pDC->SetMapMode(MM_ISOTROPIC);
			RECT rc;
			GetClientRect(&rc);
			safeDC.m_pDC->SetWindowExt(1000,1000);
			safeDC.m_pDC->SetViewportExt(rc.right,rc.bottom);
		
			for(int i=0; i<8; i++)
				for(int j=0; j<8; j++){
					safeDC.m_pDC->SelectStockObject((div(i+j,2).rem==0) ? WHITE_BRUSH : DKGRAY_BRUSH);
					safeDC.m_pDC->Rectangle(i*1000/8,j*1000/8,(i+1)*1000/8,(j+1)*1000/8);
				
					CPiece * pPiece;
					if(pPiece=pBoard->m_pOccupants[j][i])
						pPiece->DrawMe(safeDC.m_pDC);
				}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChessView diagnostics

#ifdef _DEBUG
void CChessView::AssertValid() const
{
	CView::AssertValid();
}

void CChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChessDoc* CChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChessView message handlers
		
void CChessView::OnMouseMove(UINT nFlags, CPoint point)
{
	CChessDoc* pDoc = GetDocument();
	{
		CDCWrapper safeDC(this);
		safeDC.m_pDC->DPtoLP(&point,1);
	}
	if(point.x<1000){
		pDoc->m_CurCol=point.x*8/1000;
		pDoc->m_CurRow=point.y*8/1000;
		pDoc->m_CurCol=min(pDoc->m_CurCol,7);
		pDoc->m_CurRow=min(pDoc->m_CurRow,7);
		pDoc->UpdateAllViews(NULL,CURSOR_MOVED,NULL);
	}
		
	CView::OnMouseMove(nFlags, point);
}

CPiece * CChessView::GetOccupant(BYTE row, BYTE column)
{
	CChessDoc* pDoc = GetDocument();
	return pDoc->m_CurrentBoard.m_pOccupants[row][column];
}

void CChessView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	OnSpacebar();
}

void CChessView::OnSpacebar()
{
	CChessDoc* pDoc = GetDocument();
	CPiece * pMover=pDoc->m_pMover;
	if(pMover){
		RemoveMarker();
		BOOL bMoved=FALSE;
		bMoved=pDoc->m_CurrentBoard.CheckNotInCheck(pMover,pDoc->m_CurRow,pDoc->m_CurCol);
		if(bMoved)
			bMoved=pDoc->m_CurrentBoard.Move(pMover,pDoc->m_CurRow,pDoc->m_CurCol);
		UpdateMessageBar();
		if(!bMoved){
			bNotMarked=FALSE;
			::MessageBeep(MB_ICONEXCLAMATION);
			if(pMover->m_type!=KING && (!pDoc->m_CurrentBoard.m_bInCheck[WHITE])&& !((pDoc->m_CurRow==pMover->m_row)&&(pDoc->m_CurCol==pMover->m_column))){
				RemoveMarker();
			}
		}
		else
			pDoc->m_bDirty=TRUE;	// this game is now officially unsaved		
		pDoc->m_pMover=NULL;
	}
	else{
		pDoc->m_pMover=GetOccupant(pDoc->m_CurRow,pDoc->m_CurCol);
		if(pDoc->m_pMover&&(pDoc->m_pMover->m_color==pDoc->m_CurrentBoard.m_WhosGo))
			bNotMarked=TRUE;
		else
			pDoc->m_pMover=NULL;
	}
}

void CChessView::UpdateMessageBar()
{
	if(m_bOnceThrough){   // otherwise we crash because it's called 
						  // before anything is set up - why???
		CMainFrame * pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pFrame->OnSetMessageString(AFX_IDS_IDLEMESSAGE,NULL);
	}
	m_bOnceThrough=TRUE;
}
