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
        private Game m_game;

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

            m_game = new Game( new HumanPlayer(true, chessBoard2D1), new HumanPlayer(false, chessBoard2D1), chessBoard2D1);
            //m_game = new Game(false, true, this.chessBoard2D1);
            //m_game = new Game(true, true, this.chessBoard2D1);
            //m_game = new Game(false, false, this.chessBoard2D1);

        }


    }
}
