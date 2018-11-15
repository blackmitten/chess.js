using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public class Game
    {
        IUserInterface m_userInterface;
        Board m_currentBoard;
        bool m_whiteHuman;
        bool m_blackHuman;

        public Game(bool whiteHuman, bool blackHuman, IUserInterface userInterface)
        {
            m_whiteHuman = whiteHuman;
            m_blackHuman = blackHuman;
            m_userInterface = userInterface;
            m_currentBoard = Board.InitNewGame();

            userInterface.Board = m_currentBoard;
            userInterface.BoardUpdated += BoardUpdated;

            Play();
        }

        private void Play()
        {
            if (m_currentBoard.WhitesTurn && !m_whiteHuman)
            {
                Board newBoard = m_currentBoard.ThinkAndMove();
                m_userInterface.Update(newBoard);
            }
            else if (!m_currentBoard.WhitesTurn&&!m_blackHuman)
            {
                Board newBoard = m_currentBoard.ThinkAndMove();
                m_userInterface.Update(newBoard);
            }
        }

        private void BoardUpdated(object sender, BoardUpdateEventArgs e)
        {
            m_currentBoard = e.Board;
            Play();
        }


    }
}
