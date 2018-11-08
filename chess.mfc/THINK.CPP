#include "stdafx.h"
#include "chess.h"

#include "chessdoc.h"
#include "rules.h"
#include <float.h>

unsigned long Gi=0;
BYTE GMaxDepth=3;

/////////////////////////////////////////////////////////////////////////////
// CBoard

CBoard::~CBoard()
{
	DeletePieces();
}

CBoard::CBoard(CBoard * pBoard)
// duplicate pBoard's data in this new CBoard object
{
	MakeThisBoard(pBoard);
}

void CBoard::MakeThisBoard(CBoard * pBoard)
{
	DeletePieces();
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			m_pOccupants[i][j]=NULL;
	POSITION pos;

	for(pos=pBoard->m_BlackPieces.GetHeadPosition(); pos; ){
		CPiece * pPiece = (CPiece*)pBoard->m_BlackPieces.GetNext(pos);
		CPiece * pNewPiece = pPiece->Clone(this);
		m_BlackPieces.AddTail(pNewPiece);
	}
	for(pos=pBoard->m_WhitePieces.GetHeadPosition(); pos; ){
		CPiece * pPiece = (CPiece*)pBoard->m_WhitePieces.GetNext(pos);
		CPiece * pNewPiece = pPiece->Clone(this);
		m_WhitePieces.AddTail(pNewPiece);
	}

	m_WhosGo=pBoard->m_WhosGo;
	m_pOwnerDoc=pBoard->m_pOwnerDoc;
	
	m_MovesArray.SetSize(3*35,3);	// set array size to average of 35 moves, grow by 3 elements (ie one move's worth)
	m_bInCheck[WHITE]=FALSE;
	m_bInCheck[BLACK]=FALSE;
	m_bCheckMate[WHITE]=FALSE;
	m_bCheckMate[BLACK]=FALSE;
}

void CBoard::DeletePieces()
{
	m_MovesArray.RemoveAll();
	
	while(m_BlackPieces.GetCount())
		delete m_BlackPieces.GetTail();
	while(m_WhitePieces.GetCount())
		delete m_WhitePieces.GetTail();
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			m_pOccupants[i][j]=NULL;
	for(i=0; i<2; i++){
		m_bInCheck[i]=FALSE;
		m_bCheckMate[i]=FALSE;
	}
}

void CBoard::NewBoard()
{
	DeletePieces();
	CPiece * pPiece;
	m_WhitePieces.AddTail(pPiece = new CRook());
	pPiece->InitialiseMe(7,0,WHITE,&m_pOwnerDoc->m_wRookPic,&m_pOwnerDoc->m_RookMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CRook());
	pPiece->InitialiseMe(7,7,WHITE,&m_pOwnerDoc->m_wRookPic,&m_pOwnerDoc->m_RookMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CKnight());
	pPiece->InitialiseMe(7,1,WHITE,&m_pOwnerDoc->m_wKnightPic,&m_pOwnerDoc->m_KnightMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CKnight());
	pPiece->InitialiseMe(7,6,WHITE,&m_pOwnerDoc->m_wKnightPic,&m_pOwnerDoc->m_KnightMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CBishop());
	pPiece->InitialiseMe(7,2,WHITE,&m_pOwnerDoc->m_wBishopPic,&m_pOwnerDoc->m_BishopMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CBishop());
	pPiece->InitialiseMe(7,5,WHITE,&m_pOwnerDoc->m_wBishopPic,&m_pOwnerDoc->m_BishopMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CQueen());
	pPiece->InitialiseMe(7,3,WHITE,&m_pOwnerDoc->m_wQueenPic,&m_pOwnerDoc->m_QueenMask,&m_WhitePieces,this);
	m_WhitePieces.AddTail(pPiece = new CKing());
	pPiece->InitialiseMe(7,4,WHITE,&m_pOwnerDoc->m_wKingPic,&m_pOwnerDoc->m_KingMask,&m_WhitePieces,this);

	m_BlackPieces.AddTail(pPiece = new CRook());
	pPiece->InitialiseMe(0,0,BLACK,&m_pOwnerDoc->m_bRookPic,&m_pOwnerDoc->m_RookMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CRook());
	pPiece->InitialiseMe(0,7,BLACK,&m_pOwnerDoc->m_bRookPic,&m_pOwnerDoc->m_RookMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CKnight());
	pPiece->InitialiseMe(0,1,BLACK,&m_pOwnerDoc->m_bKnightPic,&m_pOwnerDoc->m_KnightMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CKnight());
	pPiece->InitialiseMe(0,6,BLACK,&m_pOwnerDoc->m_bKnightPic,&m_pOwnerDoc->m_KnightMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CBishop());
	pPiece->InitialiseMe(0,2,BLACK,&m_pOwnerDoc->m_bBishopPic,&m_pOwnerDoc->m_BishopMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CBishop());
	pPiece->InitialiseMe(0,5,BLACK,&m_pOwnerDoc->m_bBishopPic,&m_pOwnerDoc->m_BishopMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CQueen());
	pPiece->InitialiseMe(0,3,BLACK,&m_pOwnerDoc->m_bQueenPic,&m_pOwnerDoc->m_QueenMask,&m_BlackPieces,this);
	m_BlackPieces.AddTail(pPiece = new CKing());
	pPiece->InitialiseMe(0,4,BLACK,&m_pOwnerDoc->m_bKingPic,&m_pOwnerDoc->m_KingMask,&m_BlackPieces,this);

	for(int i=0; i<8; i++){
		m_BlackPieces.AddTail(pPiece = new CPawn());
		pPiece->InitialiseMe(1,i,BLACK,&m_pOwnerDoc->m_bPawnPic,&m_pOwnerDoc->m_PawnMask,&m_BlackPieces,this);
		m_WhitePieces.AddTail(pPiece = new CPawn());
		pPiece->InitialiseMe(6,i,WHITE,&m_pOwnerDoc->m_wPawnPic,&m_pOwnerDoc->m_PawnMask,&m_WhitePieces,this);
	}
	m_WhosGo=WHITE;

	EvaluatePosition();
	m_bCheckMate[WHITE]=FALSE;
	m_bCheckMate[BLACK]=FALSE;
}

BOOL CBoard::Threatens(BYTE row, BYTE column, BYTE color)
{
	return FALSE;
}

BOOL CBoard::CheckNotInCheck(CPiece * pMover, BYTE row, BYTE col)
{
	CBoard * pNewPosition = new CBoard(this);
	pNewPosition->QuietMove(pNewPosition->m_pOccupants[pMover->m_row][pMover->m_column],row,col);
	pNewPosition->EvaluatePosition();
	BOOL bCheck=pNewPosition->m_bInCheck[WHITE]==FALSE;
	delete pNewPosition;
	return bCheck;
}

float CBoard::CalcScore(CObList * pPieces,BYTE color)
{
	float lScore=0;
	POSITION pos;
	BOOL bGetMoves=!m_MovesArray.GetSize();
		
//	m_MovesArray.RemoveAll();
	for(pos=pPieces->GetHeadPosition(); pos; ){
		CPiece * pPiece=(CPiece*)pPieces->GetNext(pos);
		lScore+=(float)pPiece->m_value;
		
		if((pPiece->m_row==3||pPiece->m_row==4) && (pPiece->m_column==3||pPiece->m_column==4)) {
			if(pPiece->m_type!=KING)
				lScore+=((float)pPiece->m_value)/((float)200.0);
		}
		if(pPiece->m_row>=2 && pPiece->m_row<=5 && pPiece->m_column>=2 && pPiece->m_column<=5) {
			if(pPiece->m_type!=KING)
				lScore+=((float)pPiece->m_value)/((float)200.0);
		}
		if(bGetMoves)
			pPiece->GetAllMoves();
	}
	int n=m_MovesArray.GetSize();
	for(int i=0; i<n;){
				
		WORD w3=m_MovesArray[i+2];
//		CPiece * pThisPiece = (CPiece *)MAKELONG(m_MovesArray[i],m_MovesArray[i+1]);
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
				
		CPiece * pOccupant = m_pOccupants[new_row][new_col];
		if(pOccupant){
			ASSERT(pOccupant->m_color!=color);
			if(pOccupant->m_type==KING){
				m_bInCheck[!color]=TRUE;
			}
			else
				lScore+=((float)pOccupant->m_value) / ((float)100.0);
		}
	}
	lScore += ((float)n)/((float)300.0);
	return lScore;
}

void CBoard::IsInCheck()
{
	POSITION pos;
	CObList * pPieces = (m_WhosGo==WHITE) ? &m_WhitePieces : &m_BlackPieces;
	m_MovesArray.RemoveAll();
	for(pos=pPieces->GetHeadPosition(); pos; ){
		CPiece * pPiece=(CPiece*)pPieces->GetNext(pos);

		pPiece->GetAllMoves();
	}
	
	int n=m_MovesArray.GetSize();
	for(int i=0; i<n;){
				
		WORD w3=m_MovesArray[i+2];
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
				
		CPiece * pOccupant = m_pOccupants[new_row][new_col];
		if(pOccupant){
			ASSERT(pOccupant->m_color!=m_WhosGo);
			if(pOccupant->m_type==KING)
				m_bInCheck[!m_WhosGo]=TRUE;
		}
	}
}

void CBoard::EvaluatePosition()
{
	m_bInCheck[WHITE]=FALSE;
	m_bInCheck[BLACK]=FALSE;
	float fBlackScore;
	float fWhiteScore;
	if(m_WhosGo==BLACK){
		m_MovesArray.RemoveAll();
		fWhiteScore=CalcScore(&m_WhitePieces,WHITE);
		m_MovesArray.RemoveAll();
		fBlackScore=CalcScore(&m_BlackPieces,BLACK);
	}
	else{
		m_MovesArray.RemoveAll();
		fBlackScore=CalcScore(&m_BlackPieces,BLACK);
		m_MovesArray.RemoveAll();
		fWhiteScore=CalcScore(&m_WhitePieces,WHITE);
	}
	m_lScore=fBlackScore-fWhiteScore;
}

BOOL CBoard::IsKingThreatend()
{
	m_MovesArray.RemoveAll();
	POSITION pos;
	CObList * pPieces = (m_WhosGo == BLACK) ? &m_BlackPieces : &m_WhitePieces;
	for(pos=pPieces->GetHeadPosition(); pos; ){
		CPiece * pPiece=(CPiece*)pPieces->GetNext(pos);
		pPiece->GetAllMoves();
	}
	int n=m_MovesArray.GetSize();
	for(int i=0; i<n;){
			
		WORD w3=m_MovesArray[i+2];
//		CPiece * pThisPiece = (CPiece *)MAKELONG(m_MovesArray[i],m_MovesArray[i+1]);
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
			
		CPiece * pOccupant = m_pOccupants[new_row][new_col];
		if(pOccupant){
			ASSERT(pOccupant->m_color!=m_WhosGo);
			if(pOccupant->m_type==KING)
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CBoard::CanIMove()
{
	m_MovesArray.RemoveAll();
	CPiece * pPiece;
	POSITION pos;
	CObList * pPieces = (m_WhosGo == BLACK) ? &m_BlackPieces : &m_WhitePieces;
	for(pos=pPieces->GetHeadPosition(); pos; ){
		pPiece=(CPiece*)pPieces->GetNext(pos);
		pPiece->GetAllMoves();
	}

	int n = m_MovesArray.GetSize();
	
	BOOL bCanMove=FALSE;
	for(int i=0; (i<n)&&(!bCanMove);){
		WORD w3=m_MovesArray[i+2];
		pPiece = (CPiece *)MAKELONG(m_MovesArray[i],m_MovesArray[i+1]);
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
		
		CBoard * pNewPosition = new CBoard(this);
		pNewPosition->QuietMove(pNewPosition->m_pOccupants[pPiece->m_row][pPiece->m_column],new_row,new_col);

		if(!pNewPosition->IsKingThreatend()){
			bCanMove=TRUE;
		}
		delete pNewPosition;
	}
	return bCanMove;		

}

/*
BOOL CBoard::IsItCheckMate(BYTE color, CPiece * pPiece, BYTE row, BYTE col)
{
	CBoard * pNewPosition = new CBoard(this);
	pNewPosition->m_WhosGo=color;
	pNewPosition->QuietMove(pNewPosition->m_pOccupants[pPiece->m_row][pPiece->m_column],row,col);
	BOOL bMate=!(pNewPosition->CanIMove());
	delete pNewPosition;
	return bMate;
}
*/

float CBoard::MakeMove(int nDepth)
{
	int nEscapes=0;
	m_MovesArray.RemoveAll();
	if ((m_pOwnerDoc->m_bStopThinking)||(nDepth==GMaxDepth)){
//		EvaluatePosition();
		return m_lScore;
	}
	
	CPiece * pPiece;
	POSITION pos;
	CObList * pPieces = (m_WhosGo == BLACK) ? &m_BlackPieces : &m_WhitePieces;
	for(pos=pPieces->GetHeadPosition(); pos; ){
		pPiece=(CPiece*)pPieces->GetNext(pos);
		pPiece->GetAllMoves();
	}

	int n = m_MovesArray.GetSize();
	
	float lBestScore = (m_WhosGo==BLACK) ? (-FLT_MAX) : FLT_MAX;

	for(int i=0; i<n;){
		((CChessApp*)AfxGetApp())->RunMessageLoop();
		Gi++;
		
		WORD w3=m_MovesArray[i+2];
		pPiece = (CPiece *)MAKELONG(m_MovesArray[i],m_MovesArray[i+1]);
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
		
		CBoard * pNewPosition = new CBoard(this);
		pNewPosition->QuietMove(pNewPosition->m_pOccupants[pPiece->m_row][pPiece->m_column],new_row,new_col);

		if(nDepth==(GMaxDepth-1)){
			pNewPosition->EvaluatePosition();
//			pNewPosition->m_MovesArray.RemoveAll();
		}
		else
			pNewPosition->IsInCheck();


		if(!pNewPosition->m_bInCheck[m_WhosGo]){
			nEscapes++;
			pNewPosition->m_lScore=pNewPosition->MakeMove(nDepth+1);
			switch (m_WhosGo){
				case BLACK : 
					if(pNewPosition->m_lScore>lBestScore){
						lBestScore=pNewPosition->m_lScore;
						m_FromRow=pPiece->m_row;
						m_FromCol=pPiece->m_column;
						m_ToRow=new_row;
						m_ToCol=new_col;
					}
				break;
				case WHITE : 
					if(pNewPosition->m_lScore<lBestScore){
						lBestScore=pNewPosition->m_lScore;
						m_FromRow=pPiece->m_row;
						m_FromCol=pPiece->m_column;
						m_ToRow=new_row;
						m_ToCol=new_col;
					}
				break;
				default : ASSERT(FALSE);
			}
		}
		delete pNewPosition;
	}
	if(nEscapes==0)
		lBestScore= (m_WhosGo == BLACK) ? -(100000.0-((float)nDepth)*1000.0) : (100000.0-((float)nDepth)*1000.0);

	return lBestScore;		
}

float CBoard::MakeMoveAB2(int nDepth,float a,float b)
{
	int nEscapes=0;
	if ((m_pOwnerDoc->m_bStopThinking)||(nDepth==GMaxDepth)){
		return m_lScore;
	}
	
	float alpha=a;
	float beta=b;
	float fReturn=0;
	
	CPiece * pPiece;
	int n = m_MovesArray.GetSize();

#ifdef _DEBUG
	m_MovesArray.RemoveAll();
	POSITION pos;
	CObList * pPieces = (m_WhosGo == BLACK) ? &m_BlackPieces : &m_WhitePieces;
	for(pos=pPieces->GetHeadPosition(); pos; ){
		pPiece=(CPiece*)pPieces->GetNext(pos);
		pPiece->GetAllMoves();
	}
	ASSERT(n==m_MovesArray.GetSize());
		
#endif

	((CChessApp*)AfxGetApp())->RunMessageLoop();
	for(int i=0; (i!=n)&&(alpha<beta);){
		Gi++;
		
		WORD w3=m_MovesArray[i+2];
		pPiece = (CPiece *)MAKELONG(m_MovesArray[i],m_MovesArray[i+1]);
		BYTE new_row = LOBYTE(w3);
		BYTE new_col = HIBYTE(w3);
		i+=3;
		ASSERT(pPiece->m_color==m_WhosGo);
		
		CBoard * pNewPosition = new CBoard(this);
		pNewPosition->QuietMove(pNewPosition->m_pOccupants[pPiece->m_row][pPiece->m_column],new_row,new_col);

		if(nDepth==(GMaxDepth-1)){
			pNewPosition->EvaluatePosition();
		}
		else
			pNewPosition->IsInCheck();


		if(!pNewPosition->m_bInCheck[m_WhosGo]){
			nEscapes++;		// this often results in stale-mate
//			nEscapes+=m_bInCheck[m_WhosGo];	// but this shouldn't
			pNewPosition->m_lScore=pNewPosition->MakeMoveAB2(nDepth+1,alpha,beta);
			switch (m_WhosGo){
				case WHITE : // min node
					if(pNewPosition->m_lScore<beta){
						beta=pNewPosition->m_lScore;
						m_FromRow=pPiece->m_row;
						m_FromCol=pPiece->m_column;
						m_ToRow=new_row;
						m_ToCol=new_col;
					}
					if(alpha>=beta){
						fReturn=alpha;
					}
					else
						fReturn=beta;
				break;
				case BLACK : // max node 
					if(pNewPosition->m_lScore>alpha){
						alpha=pNewPosition->m_lScore;
						m_FromRow=pPiece->m_row;
						m_FromCol=pPiece->m_column;
						m_ToRow=new_row;
						m_ToCol=new_col;
					}
					if(alpha>=beta){
						fReturn=beta;
					}
					else
						fReturn=alpha;
				break;
				default : ASSERT(FALSE);
			}
		}
		delete pNewPosition;
	}
	if(nEscapes==0)
		fReturn= (m_WhosGo == BLACK) ? -(100000.0-((float)nDepth)*1000.0) : (100000.0-((float)nDepth)*1000.0);
    
	return fReturn;		
}


void CBoard::QuietMove(CPiece * pMover, BYTE row, BYTE column)
// this gets called on the tree of moves - it's the same as ::Move, but doesn't change display
{
	pMover->MoveTo(row,column);
	if(pMover->m_type==PAWN&&((CPawn *) pMover)->m_pPromoted)
		delete pMover;	// the pawn that moved has been promoted so must die
}

BOOL CBoard::Move(CPiece * pMover, BYTE row, BYTE column)
{
	m_pOwnerDoc->UpdateAllViews(NULL,PIECE_MOVING,pMover);
	BOOL bMoved=pMover->MoveTo(row,column);
	if(pMover->m_type==PAWN&&((CPawn *) pMover)->m_pPromoted){
		m_pOwnerDoc->UpdateAllViews(NULL,pMover->m_color==BLACK ? BLACK_MOVED : PIECE_MOVED,((CPawn*)pMover)->m_pPromoted);
		delete pMover;	// the pawn that moved has been promoted so must die
	}
	else
		m_pOwnerDoc->UpdateAllViews(NULL,pMover->m_color==BLACK ? BLACK_MOVED : PIECE_MOVED,pMover);
	return bMoved;
}
