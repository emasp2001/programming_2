#ifndef BOARD_CPP
#define BOARD_CPP
//#include "Pieces.h"
#include "Board.h"
//#include <stdio.h>
#include <fstream>

Board::Board(){
    Board::setBoard();
}

Board::~Board(){
    Board::blankBoard();
}

void Board::setBoard(){
	blankBoard();
	for(int color=0;color<2;color++){
		int frontline = color?1:6;
		for(int i=0;i<8;i++){
			setPiece('P',i,frontline,color>0);
		}
		int backline = color?0:7;
		setPiece('R',0,backline,color>0);
		setPiece('N',1,backline,color>0);
		setPiece('B',2,backline,color>0);
		setPiece('Q',3,backline,color>0);
		setPiece('K',4,backline,color>0);
		setPiece('B',5,backline,color>0);
		setPiece('N',6,backline,color>0);
		setPiece('R',7,backline,color>0);
	}
}

void Board::printBoard(){
	for(int i=0;i < 8;i++){
		printf("%c  ",('H' - i));
		for(int j=0;j<8;j++){
			Piece* p = pieceAt(j,7-i);
			char t = ' ';
			if(p){
				t = p->getType()|(p->getColor()?0x0:0x20);
			}
			printf("%c  ",t);
		}
		printf("\n");
	}
	printf("%c  ",' ');
	for(int i=0;i<8;i++){ printf("%c  ",'0'+i+1); }
	printf("\n");
}

void Board::setPiece(char type, char col, char row, bool color){
    switch (type) {
        case 'P':
            posiciones[row][col] = new Pawn(col, row, color);
            break;
        case 'N':
            posiciones[row][col] = new Knight(col, row, color);
            break;
        case 'B':
            posiciones[row][col] = new Bishop(col, row, color);
            break;
        case 'R':
            posiciones[row][col] = new Rook(col, row, color);
            break;
        case 'Q':
            posiciones[row][col] = new Queen(col, row, color);
            break;
        case 'K':
            posiciones[row][col] = new King(col, row, color);
            break;
        default:
            break;
    }
}

void Board::blankBoard(){
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            //delete posiciones[i];
            posiciones[i][j] = NULL;
        }
    }
}

Piece *Board::pieceAt(char col, char row){ return posiciones[row][col] == NULL ? NULL : posiciones[row][col]; }

bool Board::loadLog(const char *filename){
    //Variables basicas de ejecucion.
    bool juegoExitoso = true; //Variable para saber si el juego ha sido jugado con exito, es decir nadie hizo trampa.
    std::fstream lector;
    lector.open(filename, std::ios::in);
    //1. Llamar al metodo setBoard().
    setBoard();
    //2. Leer el archivo y procesar las instrucciones.
    char *instrucciones = new char[256];
    if(lector.is_open()){
        lector.getline(instrucciones, sizeof(long));
        printf("%s", instrucciones);
    }
    
    return juegoExitoso;
}

void Board::procesarInstruccion(char *instrucciones){
    //Averiguar que ficha es la que se desea mover, este metodo asume que todo movimiento recibido es valido.
    char tipo;
    char columnaIndicada = -1;
    int filaIndicada = -1;
    bool comer;
    if(instrucciones[0]>=97){ //Es decir que no es una mayuscula por lo tanto estamos tratando de mover un peon.
        tipo = 'P';
    } else {
        tipo = instrucciones[0];
    }
    //Averiguar si desea mover o comer.
    if (instrucciones[1]=='x') {
        comer = true;
    } else {
        comer = false;
        //Averiguar si se sabe la ficha que va a mover o se esta indicando porque hay mas de una posible.
        if(instrucciones[2]>=97){ //Esto significa que hay dos letras minusculas seguidas por lo que se indica la columna de la que se desea tomar.
            columnaIndicada = instrucciones[2];
        } else {
            if(instrucciones[1]<97){ //Significa que hay un numero en la segunda posicion por lo que se indica es numero de fila.
                filaIndicada = instrucciones[1];
            } else { //Significa que es una fila normal por lo que se debe averiguar cual es la que se desea mover.
                for(int i=0; i<8; i++){
                    for(int j =0; j<8; j++){
                        if(posiciones[i][j]!=NULL){ //Busca en el tablero una ficha del tipo que se desea.
                            if(posiciones[i][j]->getType()==tipo){
                                //posiciones[i][j]->validMove(posiciones, (instrucciones[1]-97), instrucciones[2]); //Se le resta 97 por ser el inicio de los caracteres por su valor ASCII.
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif
