using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace ChessDotNetBackend
{
    public class Board
    {
        IList<IPiece> m_pieces = new List<IPiece>();

        public Board( Board board )
        {
            this.WhitesTurn = board.WhitesTurn;
            foreach( var piece in board.Pieces )
            {
                this.m_pieces.Add( piece.Copy() );
            }
        }

        public double CalcSidesScore( bool whitesTurn )
        {
            if( whitesTurn )
            {
                return CalcWhitesScore();
            }
            else
            {
                return -CalcWhitesScore();
            }
        }

        public double CalcWhitesScore()
        {
            double whitesScore = 0;
            foreach( var piece in m_pieces )
            {
                if( piece.White )
                {
                    whitesScore += piece.Value;
                }
                else
                {
                    whitesScore -= piece.Value;
                }
                if( piece.IsPawn )
                {
                    int spacesAdvanced = 0;
                    if( piece.White )
                    {
                        spacesAdvanced = 6 - piece.CurrentPosition.y;
                    }
                    else
                    {
                        spacesAdvanced = piece.CurrentPosition.y - 1;
                    }
                    whitesScore += 0.1 * spacesAdvanced * ( piece.White ? 1 : -1 );

                }
            }

            return whitesScore;
        }

        public Board()
        {
        }

        public IList<IPiece> Pieces => m_pieces;

        public bool WhitesTurn { get; set; }

        public static Board InitNewGame()
        {
            int pieceNumber = 0;
            Board b = new Board();
            for( int i = 0; i < 8; i++ )
            {
                b.m_pieces.Add( new Pawn( new Square( i, 1 ), false ) );
                b.m_pieces.Add( new Pawn( new Square( i, 6 ), true ) );
            }
            b.m_pieces.Add( new Rook( new Square( 0, 0 ), false ) );
            b.m_pieces.Add( new Rook( new Square( 7, 0 ), false ) );
            b.m_pieces.Add( new Knight( new Square( 1, 0 ), false ) );
            b.m_pieces.Add( new Knight( new Square( 6, 0 ), false ) );
            b.m_pieces.Add( new Bishop( new Square( 2, 0 ), false ) );
            b.m_pieces.Add( new Bishop( new Square( 5, 0 ), false ) );
            b.m_pieces.Add( new Queen( new Square( 3, 0 ), false ) );
            b.m_pieces.Add( new King( new Square( 4, 0 ), false ) );

            b.m_pieces.Add( new Rook( new Square( 0, 7 ), true ) );
            b.m_pieces.Add( new Rook( new Square( 7, 7 ), true ) );
            b.m_pieces.Add( new Knight( new Square( 1, 7 ), true ) );
            b.m_pieces.Add( new Knight( new Square( 6, 7 ), true ) );
            b.m_pieces.Add( new Bishop( new Square( 2, 7 ), true ) );
            b.m_pieces.Add( new Bishop( new Square( 5, 7 ), true ) );
            b.m_pieces.Add( new Queen( new Square( 3, 7 ), true ) );
            b.m_pieces.Add( new King( new Square( 4, 7 ), true ) );
            b.WhitesTurn = true;
            return b;
        }

        public IPiece GetPieceOnSquare( Square square )
        {
            foreach( var piece in m_pieces )
            {
                if( square == piece.CurrentPosition )
                {
                    return piece;
                }
            }
            return null;
        }

        /// <summary>
        /// Walk the piece up to the given square and see if anyone gets in the way
        /// </summary>
        /// <param name="piece"></param>
        /// <param name="square"></param>
        /// <returns></returns>
        public bool IsNothingInTheWay( IPiece piece, Square square )
        {
            int dx = piece.CurrentPosition.x - square.x;
            int dy = piece.CurrentPosition.y - square.y;
            int xinc = ( dx == 0 ) ? 0 : ( ( dx < 0 ) ? 1 : -1 );  // ie. either no horizontal move or left / right
            int yinc = ( dy == 0 ) ? 0 : ( ( dy < 0 ) ? 1 : -1 );  // ie. either no vertical move or up / down

            if( xinc == 0 && yinc == 0 )
            {
                throw new InvalidOperationException();  // if this happens, we're stuffed - it shouldn't ever happen
            }

            Square s = piece.CurrentPosition;
            for(; ; )
            {
                s = s.Offset( xinc, yinc );
                if( square == s )
                {
                    return true;
                }
                if( GetPieceOnSquare( s ) != null )
                {
                    return false;
                }
            }
        }

        public Board MovePiece( IPiece piece, Square destinationSquare )
        {
            Board board = new Board( this );
            var capturedPiece = GetPieceOnSquare( destinationSquare );
            if( capturedPiece != null )
            {
                if( capturedPiece.White != piece.White )
                {
                    board.RemovePiece( capturedPiece );
                }
                else
                {
                    throw new InvalidOperationException( "tried to move to a square occupied by a piece on our own side" );
                }
            }
            var pieceCopy = board.GetPieceOnSquare( piece.CurrentPosition );
            pieceCopy.CurrentPosition = destinationSquare;
            board.WhitesTurn = !WhitesTurn;
            return board;
        }

        private void RemovePiece( IPiece capturedPiece )
        {
            for( int i = 0; i < m_pieces.Count; i++ )
            {
                if( m_pieces[ i ].CurrentPosition == capturedPiece.CurrentPosition )
                {
                    m_pieces.RemoveAt( i );
                    break;
                }
            }
        }

        public override bool Equals( object obj )
        {
            if( obj == null || GetType() != obj.GetType() )
            {
                return false;
            }
            Board b = ( Board ) obj;
            if( WhitesTurn != b.WhitesTurn )
            {
                return false;
            }
            if( Pieces.Count != b.Pieces.Count )
            {
                return false;
            }
            for( int x = 0; x < 8; x++ )
            {
                for( int y = 0; y < 8; y++ )
                {
                    Square s = new Square( x, y );
                    IPiece piece1 = GetPieceOnSquare( s );
                    IPiece piece2 = b.GetPieceOnSquare( s );
                    if( piece1 == null && piece2 != null )
                    {
                        return false;
                    }
                    if( piece1 != null && piece2 == null )
                    {
                        return false;
                    }
                    if( piece1 != null && piece2 != null )
                    {
                        if( !piece1.Equals( piece2 ) )
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        private List<Board> GetAllNextBoards()
        {
            var boards = new List<Board>();
            foreach( var piece in m_pieces )
            {
                if( WhitesTurn == piece.White )
                {
                    var moves = piece.GetAllMoves( this );
                    foreach( var move in moves )
                    {
                        boards.Add( MovePiece( piece, move ) );
                    }
                }
            }
            return boards;
        }

        double Minimax( int depth, double alpha, double beta, bool maximizing, bool whitesTurn, ref long boardsConsidered )
        {
            bool sortOrder = ( maximizing && !whitesTurn ) || ( !maximizing && whitesTurn );
            if( depth == 0 )
            {
                boardsConsidered++;
                return CalcSidesScore( whitesTurn );
            }
            List<Board> boards = GetAllNextBoards();
            boards.Sort( ( a, b ) => a.CalcSidesScore( sortOrder ).CompareTo( b.CalcSidesScore( sortOrder ) ) );
            if( maximizing )
            {
                double max = double.MinValue;
                foreach( var board in boards )
                {
                    max = Math.Max( max, board.Minimax( depth - 1, alpha, beta, !maximizing, whitesTurn, ref boardsConsidered ) );
                    alpha = Math.Max( alpha, max );
                    if( alpha >= beta )
                    {
                        break;
                    }
                }
                return max;
            }
            else
            {
                double min = double.MaxValue;
                foreach( var board in boards )
                {
                    min = Math.Min( min, board.Minimax( depth - 1, alpha, beta, !maximizing, whitesTurn, ref boardsConsidered ) );
                    beta = Math.Min( beta, min );
                    if( alpha >= beta )
                    {
                        break;
                    }
                }
                return min;
            }

        }

        public Board ThinkAndMove()
        {
            DateTime t0 = DateTime.UtcNow;
            IEnumerable<Board> boards = GetAllNextBoards();
            double bestScore = double.MinValue;
            Board bestBoard = null;
            long boardsConsidered = 0;
            foreach( var board in boards )
            {
                var score = board.Evaluate( WhitesTurn, ref boardsConsidered );
                if( score > bestScore )
                {
                    bestScore = score;
                    bestBoard = board;
                }
            }
            TimeSpan dt = DateTime.UtcNow - t0;

            Console.WriteLine( "Considered {0} outcomes in {1}s, choosing move with score of {2}", boardsConsidered, dt.TotalSeconds, bestScore );
            return bestBoard;
        }

        public double Evaluate( bool whitesTurn, ref long boardsConsidered )
        {
            return Minimax( 4, double.MinValue, double.MaxValue, false, whitesTurn, ref boardsConsidered );
        }

        public Board StupidMove()
        {
            Board selectedBoard = null;

            IEnumerable<Board> boards = GetAllNextBoards();
            double maxScore = double.MinValue;
            double minScore = double.MaxValue;
            Board maxScoreBoard = null;
            Board minScoreBoard = null;
            foreach( var board in boards )
            {
                var score = board.CalcWhitesScore();
                if( score > maxScore )
                {
                    maxScore = score;
                    maxScoreBoard = board;
                }
                if( score < minScore )
                {
                    minScore = score;
                    minScoreBoard = board;
                }
            }
            if( WhitesTurn )
            {
                selectedBoard = maxScoreBoard;
            }
            else
            {
                selectedBoard = minScoreBoard;
            }
            return selectedBoard;
        }

        public override int GetHashCode()
        {
            int hashCode = 0.GetHashCode();
            foreach( var piece in m_pieces )
            {
                hashCode = hashCode ^ piece.GetHashCode();
                hashCode = hashCode ^ piece.CurrentPosition.GetHashCode();
            }
            return hashCode;
        }

    }
}
