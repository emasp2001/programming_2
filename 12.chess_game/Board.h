#ifndef BOARD_H
#define BOARD_H
#include "Pieces.h"
#include <iostream>


class Piece;

class Board{
    private:
        void procesarInstruccion(char *instrucciones); //Metodo privado para procesar las instrucciones.
    public:
        Piece *posiciones[8][8];
		Board();
		~Board();
		void blankBoard();
		void setBoard();
		void setPiece(char type, char col, char row, bool color);
        Piece* pieceAt(char col,char row);
        bool loadLog(const char *filename);
		void printBoard();
};
#endif
