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
        private ChessBoard2D chessBoard2D1;
        private Board m_currentBoard;

        public Form1()
        {
            InitializeComponent();

            // Putting this in the designer screws it up for some reason...
            this.chessBoard2D1 = new ChessWinForms.ChessBoard2D();
            this.chessBoard2D1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.chessBoard2D1.Location = new System.Drawing.Point(0, 0);
            this.chessBoard2D1.Name = "chessBoard2D1";
            this.chessBoard2D1.Size = new System.Drawing.Size(621, 534);
            this.chessBoard2D1.TabIndex = 0;
            this.panel3.Controls.Add(this.chessBoard2D1);

            m_currentBoard = Board.InitNewGame();

            this.chessBoard2D1.Board = m_currentBoard;
            this.chessBoard2D1.BoardUpdated += ChessBoard2D1_BoardUpdated;
        }

        private void ChessBoard2D1_BoardUpdated(object sender, BoardUpdateEventArgs e)
        {
            m_currentBoard = e.Board;
            double whitesScore = m_currentBoard.CalcWhitesScore();
            this.textBoxWhitesScore.Text = whitesScore.ToString("0.00");
        }

        private void buttonMove_Click(object sender, EventArgs e)
        {
            Board newBoard = m_currentBoard.ThinkAndMove();
            chessBoard2D1.Update(newBoard);
        }

    }
}
