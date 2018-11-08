// chessdoc.cpp : implementation of the CChessDoc class
//

#include "stdafx.h"
#include "chess.h"

#include "chessdoc.h"
#include "rules.h"
#include "statsdlg.h"
#include <float.h>
#define MINIMAX 1
#define ALPHABETA 2

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const char * GetRowColStr(BYTE row, BYTE col)
{
	static char c[3];
	switch (col){
		case 0 : c[0] = 'A'; break;
		case 1 : c[0] = 'B'; break;
		case 2 : c[0] = 'C'; break;
		case 3 : c[0] = 'D'; break;
		case 4 : c[0] = 'E'; break;
		case 5 : c[0] = 'F'; break;
		case 6 : c[0] = 'G'; break;
		case 7 : c[0] = 'H'; break;
		default : ASSERT(FALSE);
	}
	char c1[2];
	itoa(8-row,c1,10);
	
	c[1]=c1[0];
	c[2]='\0';
	return c;
}

extern unsigned long Gi;
extern BYTE GMaxDepth;
BYTE GAlgorithm=ALPHABETA;

/////////////////////////////////////////////////////////////////////////////
// CChessDoc

IMPLEMENT_DYNCREATE(CChessDoc, CDocument)

BEGIN_MESSAGE_MAP(CChessDoc, CDocument)
	//{{AFX_MSG_MAP(CChessDoc)
	ON_COMMAND(ID_DOWN, OnDown)
	ON_COMMAND(ID_LEFT, OnLeft)
	ON_COMMAND(ID_RIGHT, OnRight)
	ON_COMMAND(ID_UP, OnUp)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_GAMESTATISTICS, OnViewGamestatistics)
	ON_COMMAND(ID_LEVEL_DEPTH1, OnLevelDepth1)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH1, OnUpdateLevelDepth1)
	ON_COMMAND(ID_LEVEL_DEPTH2, OnLevelDepth2)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH2, OnUpdateLevelDepth2)
	ON_COMMAND(ID_LEVEL_DEPTH3, OnLevelDepth3)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH3, OnUpdateLevelDepth3)
	ON_COMMAND(ID_LEVEL_DEPTH4, OnLevelDepth4)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH4, OnUpdateLevelDepth4)
	ON_COMMAND(ID_LEVEL_DEPTH5, OnLevelDepth5)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH5, OnUpdateLevelDepth5)
	ON_COMMAND(ID_LEVEL_DEPTH6, OnLevelDepth6)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_DEPTH6, OnUpdateLevelDepth6)
	ON_COMMAND(ID_ALGORITHM_MINIMAX, OnAlgorithmMinimax)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_MINIMAX, OnUpdateAlgorithmMinimax)
	ON_COMMAND(ID_ALGORITHM_MINIMAXWITHALPHABETA, OnAlgorithmMinimaxwithalphabeta)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_MINIMAXWITHALPHABETA, OnUpdateAlgorithmMinimaxwithalphabeta)
	ON_COMMAND(ID_LEVEL_FORCEMOVE, OnLevelForcemove)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_FORCEMOVE, OnUpdateLevelForcemove)
	ON_COMMAND(ID_GAME_RESTORESAVED, OnGameRestoresaved)
	ON_UPDATE_COMMAND_UI(ID_GAME_RESTORESAVED, OnUpdateGameRestoresaved)
	ON_COMMAND(ID_MOVE_UNDO, OnMoveUndo)
	ON_UPDATE_COMMAND_UI(ID_MOVE_UNDO, OnUpdateMoveUndo)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_STARTPOS, OnUpdateStartPos)
	ON_UPDATE_COMMAND_UI(ID_ENDPOS, OnUpdateEndPos)
	ON_UPDATE_COMMAND_UI(ID_CHECK_STATUS, OnUpdateCheckStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDoc construction/destruction

CChessDoc::CChessDoc()
{
	m_bUndoListed=FALSE;
	m_bMoving=FALSE;
	m_bStopThinking=FALSE;
	m_bDirty=FALSE;
	m_bPawnPic.LoadBitmap(IDB_BPAWN);
	m_wPawnPic.LoadBitmap(IDB_WPAWN);
	m_bRookPic.LoadBitmap(IDB_BROOK);
	m_wRookPic.LoadBitmap(IDB_WROOK);
	m_bKnightPic.LoadBitmap(IDB_BKNIGHT);
	m_wKnightPic.LoadBitmap(IDB_WKNIGHT);
	m_bBishopPic.LoadBitmap(IDB_BBISHOP);
	m_wBishopPic.LoadBitmap(IDB_WBISHOP);
	m_bQueenPic.LoadBitmap(IDB_BQUEEN);
	m_wQueenPic.LoadBitmap(IDB_WQUEEN);
	m_bKingPic.LoadBitmap(IDB_BKING);
	m_wKingPic.LoadBitmap(IDB_WKING);
	m_KingMask.LoadBitmap(IDB_MKING);
	m_PawnMask.LoadBitmap(IDB_MPAWN);
	m_RookMask.LoadBitmap(IDB_MROOK);
	m_KnightMask.LoadBitmap(IDB_MKNIGHT);
	m_BishopMask.LoadBitmap(IDB_MBISHOP);
	m_QueenMask.LoadBitmap(IDB_MQUEEN);
	m_sCheckMe.LoadString(ID_CHECK_ME);
	m_sCheckYou.LoadString(ID_CHECK_YOU);
	m_sMateMe.LoadString(ID_WHITEMATE);
	m_sMateYou.LoadString(ID_BLACKMATE);
	m_CurRow=7;
	m_CurCol=4;
	m_pMover=NULL;
	m_CurrentBoard.m_pOwnerDoc=this;
	((CChessApp*)AfxGetApp())->m_pDocument=this;
}

CChessDoc::~CChessDoc()
{
	while(m_UndoList.GetCount())
		delete m_UndoList.RemoveTail();
}

void CChessDoc::ClearName()
{
	m_strPathName="";
}

BOOL CChessDoc::WipeUnsavedGame()
{
	if(m_bMoving&&(!(m_CurrentBoard.m_bCheckMate[WHITE]||m_CurrentBoard.m_bCheckMate[BLACK]))){
		AfxMessageBox("I am thinking.  Use Force Move to stop me.");
		return FALSE;
	}
	if(!m_bDirty)
		return TRUE;
	return(AfxMessageBox("If you continue you will lose this unsaved game\nAre you sure?",MB_YESNO)==IDYES);
}

BOOL CChessDoc::OnOpenDocument( const char* pszPathName)
{
	if(!WipeUnsavedGame())
		return FALSE;
	m_pMover=NULL;
	if(!CDocument::OnOpenDocument(pszPathName))
		return FALSE;
	while(m_UndoList.GetCount())
		delete m_UndoList.RemoveTail();
	UpdateAllViews(NULL,REFRESH,NULL);
	m_CurrentBoard.EvaluatePosition();

	m_bMoving=FALSE;
	return TRUE;
}

BOOL CChessDoc::OnNewDocument()
{
	if(!WipeUnsavedGame())
		return FALSE;
	m_pMover=NULL;
	if (!CDocument::OnNewDocument())
		return FALSE;
	while(m_UndoList.GetCount())
		delete m_UndoList.RemoveTail();
	m_CurrentBoard.NewBoard();
	
	UpdateAllViews(NULL,REFRESH,NULL);	
	m_bDirty=FALSE;

	m_bMoving=FALSE;
	return TRUE;
}

void CChessDoc::DeleteContents()
{
	m_CurrentBoard.DeletePieces();
	m_bStopThinking=FALSE;
	m_bUndoListed=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CChessDoc serialization

void CChessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_CurrentBoard.m_BlackPieces.Serialize(ar);
		m_CurrentBoard.m_WhitePieces.Serialize(ar);
		ar << m_CurrentBoard.m_WhosGo;
	}
	else
	{
		m_CurrentBoard.m_BlackPieces.Serialize(ar);
		m_CurrentBoard.m_WhitePieces.Serialize(ar);
		ar >> m_CurrentBoard.m_WhosGo;
	}
	
	for(POSITION pos=m_CurrentBoard.m_BlackPieces.GetHeadPosition(); pos; ){
		CPiece * piece = (CPiece *)m_CurrentBoard.m_BlackPieces.GetNext(pos);
		m_CurrentBoard.m_pOccupants[piece->m_row][piece->m_column]=piece;

		piece->m_pOwnerList=&m_CurrentBoard.m_BlackPieces;
		AttachPiece(piece);
	}
	for(pos=m_CurrentBoard.m_WhitePieces.GetHeadPosition(); pos; ){
		CPiece * piece = (CPiece *)m_CurrentBoard.m_WhitePieces.GetNext(pos);
		m_CurrentBoard.m_pOccupants[piece->m_row][piece->m_column]=piece;

		piece->m_pOwnerList=&m_CurrentBoard.m_WhitePieces;
		AttachPiece(piece);
	}
	m_bDirty=FALSE;	// We've either saved or opened a game,
					// either way it has been saved.
}

void CChessDoc::AttachPiece(CPiece * pPiece)
// tell the piece who it belongs to, give it a picture, register kings
{
	pPiece->m_pOwnerBoard=&m_CurrentBoard;
	switch(pPiece->m_type){
		case PAWN : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bPawnPic : &m_wPawnPic;
			pPiece->m_pMask=&m_PawnMask;
		break;
		case ROOK : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bRookPic : &m_wRookPic;
			pPiece->m_pMask=&m_RookMask;
		break;
		case BISHOP : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bBishopPic : &m_wBishopPic;
			pPiece->m_pMask=&m_BishopMask;
		break;
		case KNIGHT : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bKnightPic : &m_wKnightPic;
			pPiece->m_pMask=&m_KnightMask;
		break;
		case QUEEN : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bQueenPic : &m_wQueenPic;
			pPiece->m_pMask=&m_QueenMask;
		break;
		case KING : 
			pPiece->m_pPic=(pPiece->m_color==BLACK) ? &m_bKingPic : &m_wKingPic;
			pPiece->m_pMask=&m_KingMask;
		break;
		default: ASSERT(FALSE);
	}
}

void CChessDoc::Think()
{
	if(m_CurrentBoard.m_bCheckMate[WHITE]||m_CurrentBoard.m_bCheckMate[BLACK])
		return;
	if(m_CurrentBoard.m_WhosGo==BLACK&&(!m_bMoving)){
		m_bMoving=TRUE;
		m_bUndoListed=FALSE;
	}
	if((!m_bUndoListed)&&(m_CurrentBoard.m_WhosGo==WHITE)&&(!m_bMoving)){
		m_bUndoListed=TRUE;
		m_UndoList.AddTail(new CBoard(&m_CurrentBoard));
	}
	if(m_CurrentBoard.m_WhosGo==WHITE&&(m_bMoving))
		m_bMoving=FALSE;

	if(m_bMoving){
		Gi=0;

		DWORD ticks = GetTickCount();
		m_bQuiet=TRUE;
		if(m_CurrentBoard.CanIMove()){
			m_CurrentBoard.EvaluatePosition();
			UpdateAllViews(NULL,MESSAGE_BAR,NULL);
			float fScore1 = m_CurrentBoard.m_lScore;
			
			m_CurrentBoard.m_MovesArray.RemoveAll();
			CPiece * pPiece;
			POSITION pos;
			CObList * pPieces = (m_CurrentBoard.m_WhosGo == BLACK) ? &m_CurrentBoard.m_BlackPieces : &m_CurrentBoard.m_WhitePieces;
			for(pos=pPieces->GetHeadPosition(); pos; ){
				pPiece=(CPiece*)pPieces->GetNext(pos);
				pPiece->GetAllMoves();
			}
			
			switch(GAlgorithm){
				case MINIMAX : m_CurrentBoard.MakeMove(0); break;
				case ALPHABETA : m_CurrentBoard.MakeMoveAB2(0,(-FLT_MAX), FLT_MAX); break;
				default : ASSERT(FALSE);
			}
			
			BOOL bMate = m_CurrentBoard.m_bCheckMate[WHITE]||m_CurrentBoard.m_bCheckMate[BLACK];
			m_bQuiet=FALSE;
	
			ticks = GetTickCount()-ticks;
			char buf[200];
			_ultoa(Gi,buf,10);
			CString	str(buf);
			double secs = ((double)ticks)/1000.0;
			char *p;
			int d, s;
			p=_fcvt(secs,2,&d,&s);
			::MessageBeep(-1);
			str+= " moves evaluated in ";
			
			int i=0;
			while(p[i]!='\0'){
				str+=p[i++];
				if(i==d)
					str+='.';
			}
			str+=" seconds, score diff ";
			
    		m_CurrentBoard.Move(m_CurrentBoard.m_pOccupants[m_CurrentBoard.m_FromRow][m_CurrentBoard.m_FromCol],m_CurrentBoard.m_ToRow,m_CurrentBoard.m_ToCol);
			m_CurrentBoard.EvaluatePosition();
			float fScore2 = m_CurrentBoard.m_lScore;
			fScore2-=fScore1;
			long lDiff=(long)fScore2;
			_ltoa(lDiff,buf,10);
			str+=buf;
//			AfxMessageBox(str);
			m_bStopThinking=FALSE;

		}
		else{
			AfxMessageBox("You win");
			m_CurrentBoard.m_bCheckMate[BLACK]=TRUE;
			m_bDirty=FALSE;
		}

		UpdateAllViews(NULL,MESSAGE_BAR,NULL);

		// see if white is in check-mate
		if((!m_CurrentBoard.m_bCheckMate[BLACK])&&(!m_CurrentBoard.CanIMove())){
			m_CurrentBoard.m_bCheckMate[WHITE]=TRUE;
			AfxMessageBox("I win");
			m_bDirty=FALSE;
			UpdateAllViews(NULL,MESSAGE_BAR,NULL);
		}
/*
		m_CurrentBoard.m_MovesArray.RemoveAll();
		BOOL bGood=FALSE;
		CPiece * pPiece;
		POSITION pos;
		for(pos=m_CurrentBoard.m_WhitePieces.GetHeadPosition(); pos; ){
			pPiece=(CPiece*)m_CurrentBoard.m_WhitePieces.GetNext(pos);
			pPiece->GetAllMoves();
		}
	
		int n= m_CurrentBoard.m_MovesArray.GetSize();
		for(int i=0; i<n;){
			
			WORD w3=m_CurrentBoard.m_MovesArray[i+2];
			pPiece = (CPiece *)MAKELONG(m_CurrentBoard.m_MovesArray[i],m_CurrentBoard.m_MovesArray[i+1]);
			BYTE new_row = LOBYTE(w3);
			BYTE new_col = HIBYTE(w3);
			i+=3;
			
			CBoard * pNewPosition = new CBoard(&m_CurrentBoard);
			m_bQuiet=TRUE;
			pNewPosition->QuietMove(pNewPosition->m_pOccupants[pPiece->m_row][pPiece->m_column],new_row,new_col);
			m_bQuiet=FALSE;
			pNewPosition->EvaluatePosition();
			if(!pNewPosition->m_bInCheck[WHITE])
				bGood=TRUE;
			delete pNewPosition;
		}
		if(!bGood){
			m_CurrentBoard.m_bCheckMate[WHITE]=TRUE;
			AfxMessageBox("I win");
			m_bDirty=FALSE;
			UpdateAllViews(NULL,MESSAGE_BAR,NULL);
		}
*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChessDoc diagnostics

#ifdef _DEBUG
void CChessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChessDoc commands

void CChessDoc::OnDown()
{
	if(m_CurRow<7)
		m_CurRow++;
	else
		m_CurRow=7;
	UpdateAllViews(NULL,CURSOR_MOVED,NULL);
}

void CChessDoc::OnLeft()
{
	if(m_CurCol>0)
		m_CurCol--;
	else
		m_CurCol=0;
	UpdateAllViews(NULL,CURSOR_MOVED,NULL);
}

void CChessDoc::OnRight()
{
	if(m_CurCol<7)
		m_CurCol++;
	else
		m_CurCol=7;
	UpdateAllViews(NULL,CURSOR_MOVED,NULL);
}

void CChessDoc::OnUp()
{
	if(m_CurRow>0)
		m_CurRow--;
	else
		m_CurRow=0;
	UpdateAllViews(NULL,CURSOR_MOVED,NULL);
}

void CChessDoc::OnUpdateStartPos(CCmdUI* pCmdUI)
{
	if(m_pMover)
		pCmdUI->SetText(::GetRowColStr(m_pMover->m_row,m_pMover->m_column));
	else
		pCmdUI->SetText(::GetRowColStr(m_CurRow,m_CurCol));
	pCmdUI->Enable(TRUE);
}

void CChessDoc::OnUpdateEndPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(::GetRowColStr(m_CurRow,m_CurCol));
	pCmdUI->Enable(!!m_pMover);
}

void CChessDoc::OnUpdateCheckStatus(CCmdUI* pCmdUI)
{
	if(m_CurrentBoard.m_bCheckMate[BLACK]||m_CurrentBoard.m_bCheckMate[WHITE])
		pCmdUI->SetText(m_CurrentBoard.m_bCheckMate[BLACK] ? m_sMateMe : m_sMateYou);
	else {
		if(m_CurrentBoard.m_bInCheck[WHITE])
			pCmdUI->SetText(m_sCheckYou);
		else
			pCmdUI->SetText("");
	}
	pCmdUI->Enable(m_CurrentBoard.m_bInCheck[WHITE]||m_CurrentBoard.m_bCheckMate[BLACK]||m_CurrentBoard.m_bCheckMate[WHITE]);
}


void CChessDoc::OnViewRefresh()
{
	UpdateAllViews(NULL,REFRESH,NULL);
}

void CChessDoc::OnViewGamestatistics()
{
	m_CurrentBoard.EvaluatePosition();
	CStatsDlg dlg;
	dlg.m_lScore=m_CurrentBoard.m_lScore;
	dlg.DoModal();
}

void CChessDoc::OnLevelDepth1()
{
	GMaxDepth=1;
}

void CChessDoc::OnUpdateLevelDepth1(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==1);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelDepth2()
{
	GMaxDepth=2;
}

void CChessDoc::OnUpdateLevelDepth2(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==2);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelDepth3()
{
	GMaxDepth=3;
}

void CChessDoc::OnUpdateLevelDepth3(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==3);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelDepth4()
{
	GMaxDepth=4;
}

void CChessDoc::OnUpdateLevelDepth4(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==4);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelDepth5()
{
	GMaxDepth=5;
}

void CChessDoc::OnUpdateLevelDepth5(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==5);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelDepth6()
{
	GMaxDepth=6;
}

void CChessDoc::OnUpdateLevelDepth6(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GMaxDepth==6);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnAlgorithmMinimax()
{
	GAlgorithm=MINIMAX;
}

void CChessDoc::OnUpdateAlgorithmMinimax(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GAlgorithm==MINIMAX);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnAlgorithmMinimaxwithalphabeta()
{
	GAlgorithm=ALPHABETA;
}

void CChessDoc::OnUpdateAlgorithmMinimaxwithalphabeta(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GAlgorithm==ALPHABETA);
	pCmdUI->Enable(!m_bMoving);
}

void CChessDoc::OnLevelForcemove()
{
	m_bStopThinking=TRUE;
}

void CChessDoc::OnUpdateLevelForcemove(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bMoving);
}

void CChessDoc::OnGameRestoresaved()
{
	CString sName = GetPathName();
	if(sName.GetLength()==0){
		AfxMessageBox("This game has not been saved");
		return;
	}
	ClearName();
	AfxGetApp()->OpenDocumentFile(sName);
}

void CChessDoc::OnUpdateGameRestoresaved(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bDirty);
}

void CChessDoc::OnMoveUndo()
{
	if(m_UndoList.GetCount()<2)
		return;
	delete m_UndoList.RemoveTail();
	CBoard * pBoard = (CBoard*)m_UndoList.GetTail();
	m_CurrentBoard.MakeThisBoard(pBoard);
	UpdateAllViews(NULL,REFRESH,NULL);
}

void CChessDoc::OnUpdateMoveUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((!m_bMoving)&&(m_UndoList.GetCount()>1));
}
