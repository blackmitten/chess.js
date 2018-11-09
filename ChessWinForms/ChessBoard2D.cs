using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ChessDotNetBackend;

namespace ChessWinForms
{
    public partial class ChessBoard2D : UserControl, IPieceVisitor
    {
        private int m_width = 400;
        private Brush m_darkBrush;
        private Brush m_lightBrush;
        private Pen m_selectionPen = new Pen(Color.Red, 3);
        private Pen m_highlightPen = new Pen(Color.White, 2);
        private Board m_board;
        private Brush m_whiteBrush = new SolidBrush(Color.White);
        private Brush m_blackBrush = new SolidBrush(Color.Black);
        private Square m_selectedSquare = new Square(-1, -1);
        private List<Square> m_highlightedSquares = new List<Square>();

        private int SquareWidth => m_width / 8;

        public ChessBoard2D()
        {
            InitializeComponent();
            m_darkBrush = new SolidBrush(Color.FromArgb(0x70, 0x70, 0x70));
            m_lightBrush = new SolidBrush(Color.FromArgb(0xa0, 0xa0, 0xa0));
        }

        public Board Board
        {
            set
            {
                m_board = value;
                this.Invalidate();
            }
        }

        private void ChessBoard2D_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            if (m_board != null)
            {
                bool dark = false;
                for (var x = 0; x < 8; x++)
                {
                    dark = !dark;
                    for (var y = 0; y < 8; y++)
                    {
                        dark = !dark;
                        Brush brush;
                        if (dark)
                        {
                            brush = m_darkBrush;
                        }
                        else
                        {
                            brush = m_lightBrush;
                        }
                        e.Graphics.FillRectangle(brush, x * m_width / 8, y * m_width / 8, m_width / 8, m_width / 8);
                    }
                }
                e.Graphics.DrawRectangle(Pens.Black, 0, 0, m_width, m_width);
                foreach (var piece in m_board.Pieces)
                {
                    piece.Accept(this, e.Graphics);
                }
                if (m_selectedSquare.InBounds)
                {
                    e.Graphics.DrawRectangle(m_selectionPen, m_selectedSquare.x * SquareWidth, m_selectedSquare.y * SquareWidth, SquareWidth, SquareWidth);
                }
                foreach(var square in m_highlightedSquares)
                {
                    e.Graphics.DrawRectangle(m_highlightPen, square.x * SquareWidth, square.y * SquareWidth, SquareWidth, SquareWidth);
                }
            }
        }

        #region piece drawing

        public void Visit(Pawn piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            g.FillEllipse(brush, pt.X - squareWidth / 5, pt.Y - squareWidth / 5, 2 * squareWidth / 5, 2 * squareWidth / 5);
        }

        public void Visit(Rook piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            g.FillRectangle(brush, pt.X - squareWidth / 7, pt.Y - squareWidth / 4, 2 * squareWidth / 7, 2 * squareWidth / 4);
            g.FillRectangle(brush, pt.X - squareWidth / 5, pt.Y - squareWidth / 4, 2 * squareWidth / 5, squareWidth / 8);
            g.FillRectangle(brush, pt.X - squareWidth / 5, pt.Y + squareWidth / 4 - squareWidth / 8, 2 * squareWidth / 5, squareWidth / 8);

        }

        public void Visit(Knight piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            g.FillRectangle(brush, pt.X - squareWidth / 5, pt.Y - squareWidth / 4, 2 * squareWidth / 7, 2 * squareWidth / 4);
            g.FillRectangle(brush, pt.X - squareWidth / 5, pt.Y - squareWidth / 4, 2 * squareWidth / 5, 2 * squareWidth / 8);
        }

        public void Visit(Bishop piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            PointF[] pts = new PointF[] {
                new PointF( pt.X - squareWidth / 5, pt.Y + squareWidth / 4 ),
                new PointF(pt.X+squareWidth/5,pt.Y+squareWidth/4),
                new PointF(pt.X,pt.Y-squareWidth/4)
            };
            g.FillPolygon(brush, pts);
        }

        public void Visit(Queen piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            PointF[] pts = new PointF[] {
                new PointF( pt.X-squareWidth/3.5f,pt.Y+squareWidth/7),
                new PointF(pt.X+squareWidth/3.5f,pt.Y+squareWidth/7),
                new PointF(pt.X,pt.Y-squareWidth/3)
            };
            g.FillPolygon(brush, pts);
            pts = new PointF[] {
                new PointF( pt.X-squareWidth/3.5f,pt.Y-squareWidth/7),
                new PointF(pt.X+squareWidth/3.5f,pt.Y-squareWidth/7),
                new PointF(pt.X,pt.Y+squareWidth/3)
            };
            g.FillPolygon(brush, pts);
        }

        public void Visit(King piece, object data)
        {
            int squareWidth = m_width / 8;
            Graphics g = data as Graphics;
            drawPiecePreamble(piece, out Brush brush, out PointF pt);
            g.FillRectangle(brush, pt.X - squareWidth / 7, pt.Y - squareWidth / 3.5f, 2 * squareWidth / 7, 2 * squareWidth / 3.5f);
            g.FillRectangle(brush, pt.X - squareWidth / 3.5f, pt.Y - squareWidth / 7, 2 * squareWidth / 3.5f, 2 * squareWidth / 7);
        }

        void drawPiecePreamble(IPiece piece, out Brush brush, out PointF pt)
        {
            int squareWidth = m_width / 8;
            brush = piece.White ? m_whiteBrush : m_blackBrush;
            pt = new Point(piece.Square.x * squareWidth + squareWidth / 2, piece.Square.y * squareWidth + squareWidth / 2);

        }

        #endregion


        private void ChessBoard2D_MouseClick(object sender, MouseEventArgs e)
        {
            double squareWidth = m_width / 8;
            int x = (int)Math.Floor(e.X / squareWidth);
            int y = (int)Math.Floor(e.Y / squareWidth);
            SquareClicked(new Square(x, y));
        }

        private void SquareClicked(Square square)
        {
            Console.WriteLine("Clicked " + square);
            m_selectedSquare = square;
            IPiece clickedPiece = m_board.GetPieceOnSquare(square);
            if (clickedPiece != null)
            {
                m_highlightedSquares.Clear();
                m_highlightedSquares.AddRange(clickedPiece.GetAllMoves(m_board));
            }
            Invalidate();
        }
    }
}
