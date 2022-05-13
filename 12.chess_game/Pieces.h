#ifndef PIECES_H
#define PIECES_H
#include "Board.h"

class Board;

class Piece{
	protected:
		bool color;
		char row;
        char startRow;
		char col;
        char startCol;
        bool verificarVecinas(Board *tablero, int cantidadCasillas, int direccion, int startRow, int startCol, bool color); //Metodo que me va a permitir verificar las casillas en direccion de las que se encuentra para verificar que no pase por encima de otras.
        int averiguarDireccion(int currentRow, int currentCol, int targetRow, int targetCol, int &cantPasos); //Metodo para saber en que direccion es que se va a mover una ficha.
	public:
		Piece(char startCol,char startRow,bool newColor);
		~Piece();
		void setRow(char newRow);
		void setColumn(char newCol);
		char getRow();
		char getColumn();
		bool getColor();
		virtual bool validMove(Board* board,char targetCol,char targetRow)=0;
		virtual char getType()=0;
};

class Pawn : public Piece{
	public:
		Pawn(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

class Knight : public Piece{
	public:
		Knight(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

class Bishop : public Piece{
	public:
		Bishop(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

class Rook : public Piece{
	public:
		Rook(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

class Queen : public Piece{
	public:
		Queen(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

class King : public Piece{
	public:
		King(char startCol,char startRow,bool newColor);
		bool validMove(Board* board,char targetCol,char targetRow);
		char getType();
};

#endif
