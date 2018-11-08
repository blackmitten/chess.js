// rules.cpp : implementation of the CPiece class
//

#include "stdafx.h"
#include "chess.h"

#include "chessdoc.h"
#include "rules.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static long GCount=0;


BOOL InBounds(BYTE row, BYTE column)
{
	return((row>=0)&&(column>=0)&&(row<=7)&&(column<=7));
}


/////////////////////////////////////////////////////////////////////////////
// CPiece derived objects

IMPLEMENT_SERIAL(CPiece,CObject,2)
IMPLEMENT_SERIAL(CBishop,CPiece,2)
IMPLEMENT_SERIAL(CKnight,CPiece,2)
IMPLEMENT_SERIAL(CQueen,CPiece,2)
IMPLEMENT_SERIAL(CKing,CPiece,2)
IMPLEMENT_SERIAL(CPawn,CPiece,2)
IMPLEMENT_SERIAL(CRook,CPiece,2)

CPiece::~CPiece()
// before the piece is deleted, it removes itself from the list of pieces
{
	POSITION pos = m_pOwnerList->Find(this);
	if(pos)
		m_pOwnerList->RemoveAt(pos);
}

void CPiece::InitialiseMe(BYTE row, BYTE column, BYTE color, CBitmap * pPic,CBitmap * pMask,CObList * pOwner,CBoard * pBoard)
// sets up the position, picture and tells the piece who's side its on and what board it's playing on
{
	m_row=row;
	m_column=column;
	m_color=color;
	m_pPic=pPic;
	m_pMask=pMask;
	m_pOwnerList=pOwner;
	m_pOwnerBoard=pBoard;
	pBoard->m_pOccupants[row][column]=this;
	pOwner->AssertValid();
	pBoard->AssertValid();

	if(m_type==KING){
		((CKing*)this)->m_bMoved=FALSE;
	}
	if(m_type==ROOK){
		((CRook*)this)->m_bMoved=FALSE;
	}
}

void CPiece::Serialize(CArchive& ar)
// save this piece's information to a file (CArchive)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_row;
		ar << m_column;
		ar << m_color;
	}
	else{
		ar >> m_row;
		ar >> m_column;
		ar >> m_color;
	}
}

void CKing::Serialize(CArchive& ar)
{
	CPiece::Serialize(ar);
	if (ar.IsStoring())
		ar << m_bMoved;
	else
		ar >> m_bMoved;
}

void CRook::Serialize(CArchive& ar)
{
	CPiece::Serialize(ar);
	if (ar.IsStoring())
		ar << m_bMoved;
	else
		ar >> m_bMoved;
}

void CPiece::DrawMe(CDC * pDC)
{
	CDC DCsource;
	DCsource.CreateCompatibleDC(pDC);
	DCsource.SelectObject(m_pMask);
	pDC->StretchBlt(m_column*1000/8,m_row*1000/8,1000/8,1000/8,
					&DCsource,0,0,60,60,SRCPAINT);
	DCsource.SelectObject(m_pPic);
	pDC->StretchBlt(m_column*1000/8,m_row*1000/8,1000/8,1000/8,
					&DCsource,0,0,60,60,SRCAND);
}

BOOL CPiece::MoveTo(BYTE row, BYTE column)
// move position, kill anyone we land on, see if anyone's in check
{
	CPiece * pCaptured=m_pOwnerBoard->m_pOccupants[row][column];
	if(IsMoveValid(row,column)){
		m_pOwnerBoard->m_pOccupants[m_row][m_column]=NULL;
		m_pOwnerBoard->m_pOccupants[row][column]=this;
		m_row=row;
		m_column=column;
		if(pCaptured)
			delete pCaptured;
		m_pOwnerBoard->m_WhosGo=!m_pOwnerBoard->m_WhosGo;
		return TRUE;
	}
	return FALSE;
}

// Both the Rook and the King need special MoveTo's, so that we 
// remember whether they've moved for castling.
BOOL CRook::MoveTo(BYTE row, BYTE column)
{
	if(CPiece::MoveTo(row,column)){
		m_bMoved=TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CKing::MoveTo(BYTE row, BYTE column)
{
	BOOL bCastling=FALSE;
	int nColumnInc=0;
	CRook * pRook=NULL;
	if(m_row==row)
		if(column==(m_column+2)||column==(m_column-2)){
			bCastling=TRUE;
			if(column==(m_column+2)){
				pRook=(CRook *)m_pOwnerBoard->m_pOccupants[m_row][7];
				nColumnInc=-2;	// rook moves left two spaces
			}
			if(column==(m_column-2)){
				pRook=(CRook *)m_pOwnerBoard->m_pOccupants[m_row][0];
				nColumnInc=+3;	// rook moves right three spaces
			}
			ASSERT(pRook);
			ASSERT(nColumnInc!=0);
		}
    if(CPiece::MoveTo(row,column)){
    	if(bCastling){
			CChessDoc * pDoc = m_pOwnerBoard->m_pOwnerDoc;
	
			m_pOwnerBoard->m_pOccupants[pRook->m_row][pRook->m_column]=NULL;
			if(!pDoc->m_bQuiet)
				pDoc->UpdateAllViews(NULL,PIECE_MOVING,pRook);
			pRook->m_column+=nColumnInc;
			m_pOwnerBoard->m_pOccupants[pRook->m_row][pRook->m_column]=pRook;
			if(!pDoc->m_bQuiet)
				pDoc->UpdateAllViews(NULL,CASTLED,pRook);
		}
		m_bMoved=TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CPawn::MoveTo(BYTE row, BYTE column)
{
	if(CPiece::MoveTo(row,column)){
		if(m_row==0||m_row==7){	// pawn promotion
			m_pPromoted=new CQueen();

			CObList * pList;
			CBitmap * pPic;
			switch (m_color){
				case BLACK : 
					pList = &m_pOwnerBoard->m_BlackPieces;
					pPic = &(m_pOwnerBoard->m_pOwnerDoc->m_bQueenPic);
				break;
				case WHITE :
					pList = &m_pOwnerBoard->m_WhitePieces;
					pPic = &(m_pOwnerBoard->m_pOwnerDoc->m_wQueenPic);
				break;
				default: ASSERT(FALSE);
			}
			CBitmap * pMask = &m_pOwnerBoard->m_pOwnerDoc->m_QueenMask;

			pList->AddTail(m_pPromoted);
			m_pPromoted->InitialiseMe(row, column, m_color, pPic, pMask, pList, m_pOwnerBoard);
		}			

		return TRUE;
	}
	return FALSE;
}

BOOL CPiece::IsNothingInTheWay(BYTE row, BYTE column)
// walk the piece up to the given square and see if anyone gets in the way
{
	int x=m_row-row;
	int y=m_column-column;
	int xinc = (x==0)? 0 : ((x<0)? 1 : -1);  // ie. either no horizontal move or left / right
	int yinc = (y==0)? 0 : ((y<0)? 1 : -1);  // ie. either no vertical move or up / down

	ASSERT(!((xinc==0)&&(yinc==0)));	// if this happens, we're stuffed - it shouldn't ever happen
		
	int r=m_row; 
	int c=m_column;
	BOOL bFoundSomeone=FALSE;
	do {	// walk in the specified direction until we get there or we find a piece
		r+=xinc;
		c+=yinc;
		if(r==row&&c==column)
			return TRUE;
		if(m_pOwnerBoard->m_pOccupants[r][c])
			bFoundSomeone=TRUE;
	
	}while (!bFoundSomeone);

	return FALSE;
}

////////////////////////////////
// IsMoveValid virtual functions

BOOL CPiece::IsMoveValid(BYTE row, BYTE column)
{
	CPiece * pCaptured=m_pOwnerBoard->m_pOccupants[row][column];
	BOOL bCorrectCapture=((!pCaptured)||(pCaptured->m_color!=m_color));
	// capture is good if either we didn't capture anyone, or they were on the other side
	
	ASSERT(m_pOwnerBoard);
	m_bCapturing=((bCorrectCapture)&&(::InBounds(row,column))&&(pCaptured!=NULL));
	return bCorrectCapture&&::InBounds(row,column);
}

BOOL CKing::IsMoveValid(BYTE row, BYTE column)
{
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
	if(!(m_bMoved)){	// castling
		if(m_row==row){
			if(column==(m_column+2)||column==(m_column-2)){
				if(m_pOwnerBoard->m_bInCheck[m_color])
					return FALSE; // can't castle out of check
				CRook * pRook=NULL;
				int nColumnInc=0;
				if(column==(m_column+2)){
					if(m_pOwnerBoard->Threatens(m_row,m_column+1,!m_color))
						return FALSE;  // can't castle through check
					pRook=(CRook *)m_pOwnerBoard->m_pOccupants[m_row][7];
					nColumnInc=-2;	// rook moves left two spaces
				}
				if(column==(m_column-2)){
					if(m_pOwnerBoard->Threatens(m_row,m_column-1,!m_color))
						return FALSE;  // can't castle through check
					pRook=(CRook *)m_pOwnerBoard->m_pOccupants[m_row][0];
					nColumnInc=+3;	// rook moves right three spaces
				}
				if((!pRook)||pRook->m_bMoved)
					return FALSE;
				ASSERT(nColumnInc!=0);
				if(pRook->IsMoveValid(row,pRook->m_column+nColumnInc)){
					return TRUE;
				}
				return FALSE;
			}
		}
	}
	if(abs(row-m_row)>1)  // either left or right (one space)
		return FALSE;
	if(abs(column-m_column)>1)  // either up or down (one space)
		return FALSE;
	return TRUE;
}

BOOL CBishop::IsMoveValid(BYTE row, BYTE column)
{
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
	if(abs(m_row-row)!=abs(m_column-column))  // only diagonally
		return FALSE;
	return IsNothingInTheWay(row,column);
}

BOOL CRook::IsMoveValid(BYTE row, BYTE column)
{
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
	if((row!=m_row)&&(column!=m_column))	// only horizontally/vertically
		return FALSE;
	return IsNothingInTheWay(row,column);
}

BOOL CQueen::IsMoveValid(BYTE row, BYTE column)
{
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
    // just the rook and bishop rules together
	if(abs(m_row-row)!=abs(m_column-column)){
		if((row!=m_row)&&(column!=m_column))
			return FALSE;
	}
	return IsNothingInTheWay(row,column);
}


BOOL CKnight::IsMoveValid(BYTE row, BYTE column)
{
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
	//  two spaces forward, one to either side...
	return (((abs(m_row-row)==2)&&(abs(m_column-column)==1)) || ((abs(m_row-row)==1)&&(abs(m_column-column)==2)));
}

BOOL CPawn::IsMoveValid(BYTE row, BYTE column)
{
	// haven't got en passant in yet
	if(!CPiece::IsMoveValid(row,column))
		return FALSE;
	int nDir = (m_color==WHITE) ? -1 : 1;  // which way can this pawn move?
	if((row-m_row)*nDir>2)   // can never go further than two spaces
		return FALSE;
	if((row-m_row)*nDir<=0)  // mustn't go backwards
		return FALSE;
	if(((row-m_row)*nDir>1)&&(m_row!=(m_color==WHITE ? 6 : 1)))  // can go two spaces if we haven't moved
		return FALSE;
	if((column==m_column)&&(m_pOwnerBoard->m_pOccupants[row][column]))  // can't take forwards
		return FALSE;
	if((column!=m_column)&&((!m_pOwnerBoard->m_pOccupants[row][column])||(abs(column-m_column)>1)))  // can take diagonally
		return FALSE;
	return IsNothingInTheWay(row,column);
}
////////////////////////
// routines to find all valid moves:

BOOL CPiece::AddMove(BYTE row, BYTE column)
// returns TRUE if given a valid move and adds it to the piece's list of good places to go
{
	if((row==m_row)&&(column==m_column))  // if we're there already ignore it
		return TRUE;
	if(::InBounds(row,column)&&IsMoveValid(row,column)){
		if(m_bCapturing){
			m_pOwnerBoard->m_MovesArray.InsertAt(0,row|(column<<8));
			m_pOwnerBoard->m_MovesArray.InsertAt(0,HIWORD(this));
			m_pOwnerBoard->m_MovesArray.InsertAt(0,LOWORD(this));
			m_bCapturing=FALSE;
		}
		else{
			m_pOwnerBoard->m_MovesArray.Add(LOWORD(this));
			m_pOwnerBoard->m_MovesArray.Add(HIWORD(this));
			m_pOwnerBoard->m_MovesArray.Add(row|(column<<8));
		}
		return TRUE;
	}
	return FALSE;
}

void CRook::GetAllMoves()
{
	BYTE r=m_row;
	BYTE c=m_column;
	while(AddMove(r++,c));	// down
	r=m_row;
	c=m_column;
	while(AddMove(r--,c));  // up
	r=m_row;
	c=m_column;
	while(AddMove(r,c--));  // left
	r=m_row;
	c=m_column;
	while(AddMove(r,c++));  // right
}

void CBishop::GetAllMoves()
{
	BYTE r=m_row;
	BYTE c=m_column;
	while(AddMove(r++,c++));  // down & right
	r=m_row;
	c=m_column;
	while(AddMove(r--,c++));  // up & right
	r=m_row;
	c=m_column;
	while(AddMove(r--,c--));  // up & left
	r=m_row;
	c=m_column;
	while(AddMove(r++,c--));  // down & left
}

void CKing::GetAllMoves()
{
	AddMove(m_row+1,m_column);
	AddMove(m_row-1,m_column);
	AddMove(m_row+1,m_column+1);
	AddMove(m_row-1,m_column+1);
	AddMove(m_row+1,m_column-1);
	AddMove(m_row-1,m_column-1);
	AddMove(m_row,m_column+1);
	AddMove(m_row,m_column-1);
	AddMove(m_row,m_column+2);
	AddMove(m_row,m_column-2);
}

void CQueen::GetAllMoves()
{
	BYTE r=m_row;
	BYTE c=m_column;
	while(AddMove(r++,c++));
	r=m_row;
	c=m_column;
	while(AddMove(r--,c++));
	r=m_row;
	c=m_column;
	while(AddMove(r--,c--));
	r=m_row;
	c=m_column;
	while(AddMove(r++,c--));
	r=m_row;
	c=m_column;
	while(AddMove(r++,c));
	r=m_row;
	c=m_column;
	while(AddMove(r--,c));
	r=m_row;
	c=m_column;
	while(AddMove(r,c--));
	r=m_row;
	c=m_column;
	while(AddMove(r,c++));
}

void CPawn::GetAllMoves()
{
	int nDir = (m_color==WHITE) ? -1 : 1;
	AddMove(m_row+nDir*1,m_column);
	AddMove(m_row+nDir*2,m_column);
	AddMove(m_row+nDir*1,m_column+1);
	AddMove(m_row+nDir*1,m_column-1);
}

void CKnight::GetAllMoves()
{
	AddMove(m_row+2,m_column+1);
	AddMove(m_row+2,m_column-1);
	AddMove(m_row-2,m_column+1);
	AddMove(m_row-2,m_column-1);
	AddMove(m_row+1,m_column+2);
	AddMove(m_row-1,m_column+2);
	AddMove(m_row+1,m_column-2);
	AddMove(m_row-1,m_column-2);
}

void CPiece::CopyPiece(CPiece * pPiece, CBoard * pOwnerBoard)
{
	m_row=pPiece->m_row;
	m_column=pPiece->m_column;
	m_color=pPiece->m_color;
	m_pPic=pPiece->m_pPic;
	m_pMask=pPiece->m_pMask;
	m_pOwnerList=m_color==BLACK ? &pOwnerBoard->m_BlackPieces : &pOwnerBoard->m_WhitePieces;
	m_pOwnerBoard=pOwnerBoard;
	m_pOwnerBoard->m_pOccupants[m_row][m_column]=this;
}

CPiece * CPiece::Clone(CBoard * pBoard)
// this should never get called, only CPiece derived objects can be cloned
{
	ASSERT(FALSE);
	return NULL;
}

CPiece * CPawn::Clone(CBoard * pBoard)
{
	CPawn * pPiece = new CPawn();
	pPiece->CopyPiece(this,pBoard);
	return pPiece;
}

CPiece * CKing::Clone(CBoard * pBoard)
{
	CKing * pPiece = new CKing();
	pPiece->CopyPiece(this,pBoard);
	pPiece->m_bMoved=m_bMoved;
	return pPiece;
}

CPiece * CQueen::Clone(CBoard * pBoard)
{
	CQueen * pPiece = new CQueen();
	pPiece->CopyPiece(this,pBoard);
	return pPiece;
}

CPiece * CKnight::Clone(CBoard * pBoard)
{
	CKnight * pPiece = new CKnight();
	pPiece->CopyPiece(this,pBoard);
	return pPiece;
}

CPiece * CBishop::Clone(CBoard * pBoard)
{
	CBishop * pPiece = new CBishop();
	pPiece->CopyPiece(this,pBoard);
	return pPiece;
}

CPiece * CRook::Clone(CBoard * pBoard)
{
	CRook * pPiece = new CRook();
	pPiece->CopyPiece(this,pBoard);
	pPiece->m_bMoved=m_bMoved;
	return pPiece;
}
