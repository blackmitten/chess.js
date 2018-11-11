using ChessDotNetBackend;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessWinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Board board = Board.InitNewGame();
            this.chessBoard2D1.Board = board;
            this.chessBoard2D1.BoardUpdated += ChessBoard2D1_BoardUpdated;
        }

        private void ChessBoard2D1_BoardUpdated(object sender, BoardUpdateEventArgs e)
        {
            Board board = e.Board;
            double whitesScore = board.CalcWhitesScore();
        }
    }
}
