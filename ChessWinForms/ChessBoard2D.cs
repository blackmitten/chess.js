using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessWinForms
{
    public partial class ChessBoard2D : UserControl
    {
        private int width = 400;

        public ChessBoard2D()
        {
            InitializeComponent();
        }

        private void ChessBoard2D_Paint( object sender, PaintEventArgs e )
        {
            bool dark = false;
            for ( var x = 0; x < 8; x++ )
            {
                dark = !dark;
                for ( var y = 0; y < 8; y++ )
                {
                    dark = !dark;
                    Brush brush;
                    if ( dark )
                    {
                        brush = Brushes.DarkGray;
                    }
                    else
                    {
                        brush = Brushes.LightGray;
                    }
                    e.Graphics.FillRectangle( brush, x * width / 8, y * width / 8, width / 8, width / 8 );
                }
            }
            e.Graphics.DrawRectangle( Pens.Black, 0, 0, width, width );
        }
    }
}
