//
//  Pieces.cpp
//  FinalExam
//
//  Created by Emmanuel Solis on 12/2/20.
//

#include <stdio.h>
#include "Pieces.h"

//CONSTRUCTOR - PADRE
Piece::Piece(char startCol,char startRow,bool newColor){
    this->col = startCol;
    this->startCol = startCol;
    this->row = startRow;
    this->startRow = startRow;
    this->color = newColor;
}

//CONSTRUCTOR - HIJOS
Pawn::Pawn(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}
King::King(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}
Rook::Rook(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}
Queen::Queen(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}
Bishop::Bishop(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}
Knight::Knight(char startCol,char startRow,bool newColor) : Piece (startCol, startRow, newColor) {
}

//DESTRUCTOR - PADRE
Piece::~Piece(){}

//SETTERS - PADRE
void Piece::setRow(char newRow){this->row = newRow;}
void Piece::setColumn(char newCol){this->col = newCol;}

//GETTERS - PADRE
char Piece::getRow(){return row;}
char Piece::getColumn(){return col;}
bool Piece::getColor(){return color;}

//GETTERS - HIJOS
char Pawn::getType(){return 'P';}
char Knight::getType(){return 'N';}
char Bishop::getType(){return 'B';}
char Rook::getType(){return 'R';}
char Queen::getType(){return 'Q';}
char King::getType(){return 'K';}

//VERIFICAR DIRECCION
bool Piece::verificarVecinas(Board *tablero, int cantidadCasillas, int direccion, int startRow, int startCol, bool color){
    // Direcciones: 1 Norte, 2 Sur, 3 Este, 4 Oeste, 5 Noreste, 6 Noroeste, 7 Sureste, 8 Suroeste.
    if(cantidadCasillas>=0){ //Es decir que no ha terminado de verificar
        if(tablero->posiciones[startRow][startCol] == NULL){
            switch (direccion) {
                case 1: //Norte
                    startRow += 1;
                    break;
                case 2: //Sur
                    startRow -= 1;
                    break;
                case 3: // Este
                    startCol += 1;
                    break;
                case 4: //Oeste
                    startCol -= 1;
                    break;
                case 5: //Noreste
                    startRow += 1;
                    startCol += 1;
                    break;
                case 6: //Noroeste
                    startRow += 1;
                    startCol -= 1;
                    break;
                case 7: //Sureste
                    startRow -= 1;
                    startCol += 1;
                    break;
                case 8: //Suroeste
                    startRow -= 1;
                    startCol -= 1;
                    break;
                default:
                    break;
            }
            return verificarVecinas(tablero, --cantidadCasillas, direccion, startRow, startCol, color);
        } else {
            if(tablero->posiciones[startRow][startCol]->getColor()==color) { //En caso de que haya alguien debo verificar si es de las mias.
                return false;
            } else{
                return true; //Es decir que no es una de las fichas mias sino que va a comer y si se puede mover.
            }
        }
    } else{
        return true; //Es decir que si llega a la ultima repeticion y no se dio un evento prohibido es que SI se puede mover.
    }
}

//AVERIGUAR DIRECCION QUE SE MUEVE
int Piece::averiguarDireccion(int currentRow, int currentCol, int targetRow, int targetCol, int &cantPasos){
    int direccion; //Direcciones: 1 Norte, 2 Sur, 3 Este, 4 Oeste, 5 Noreste, 6 Noroeste, 7 Sureste, 8 Suroeste.
    if(currentCol!=targetCol && currentRow!=targetRow){ //Saber si se mueve en las cuatro basicas. Aqui serian las otras cuatro.
        if((targetCol-1)==col && (targetRow-1)==row){ //Es Noreste.
            direccion = 5;
            cantPasos = targetCol-col;
        } else {
            if((targetCol+1)==col && (targetRow-1)==row){ //Es Noroeste.
                direccion = 6;
                cantPasos = col - targetCol;
            } else {
                if((targetCol-1)==col && (targetRow+1)==row){ //Es Sureste.
                    direccion = 7;
                    cantPasos = targetCol-col;
                } else { //Es Suroeste.
                    direccion = 8;
                    cantPasos = col - targetCol;
                }
            }
        }
    } else { //Aqui serian solo las cuatro basicas.
        if((targetRow-1)==row && targetCol==col){ //Es Norte.
            direccion = 1;
            cantPasos = targetRow-currentRow;
        } else {
            if((targetRow+1)==row && targetCol==col){ //Es Sur.
                direccion = 2;
                cantPasos = currentRow - targetRow;
            } else{
                if((targetCol-1)==col && targetRow==row){ //Es Este.
                    direccion = 3;
                    cantPasos = targetCol-col;
                } else{ //Es Oeste.
                    direccion = 4;
                    cantPasos = col - targetCol;
                }
            }
        }
    }
    return direccion;
}

//VALIDAR MOVIMIENTOS
bool Pawn::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = false;
    int pasosPermitidos = 1;
    if(col==startCol && row==startRow){ //Significa que NO se ha movido.
        pasosPermitidos = 2;
    }
    //Verificar si se sale.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else { //NO se sale.
        //Verificar que no avance mas de la cuenta.
        if(color==1){ //Es NEGRO, abajo.
            if(targetRow+pasosPermitidos!=row){
                movimientoValido = false;
            } else { //Verificar que sea una posicion valida.
                if (targetRow!=row){ //Verificar si quiere comer en diagonal y entonces verificar si se puede.
                    if(board->pieceAt(targetCol, targetRow)!=NULL){
                        if((board->pieceAt(targetCol, targetRow)->getColor()!=color) && ((targetRow-1==row&&targetCol-1==col) || (targetRow-1==row&&targetCol+1==col)) ){
                            movimientoValido = true;
                        } else {
                            if((board->pieceAt(targetCol, targetRow)->getColor()!=color) && targetRow+pasosPermitidos==row){
                                movimientoValido = true;
                            }
                        }
                    } else {
                        movimientoValido = false;
                    }
                }
            }
        } else { //Es BLANCO, arriba.
            if(targetRow-pasosPermitidos!=row){
                movimientoValido = false;
            } else { //Verificar que sea una posicion valida.
                if (targetRow!=row){ //Verificar si quiere comer en diagonal y entonces verificar si se puede.
                    if(board->pieceAt(targetCol, targetRow)!=NULL){
                        if((board->pieceAt(targetCol, targetRow)->getColor()!=color) && ((targetRow+1==row&&targetCol+1==col) || (targetRow+1==row&&targetCol-1==col)) ){
                            movimientoValido = true;
                        } else {
                            if((board->pieceAt(targetCol, targetRow)->getColor()!=color) && targetRow-pasosPermitidos==row){
                                movimientoValido = true;
                            }
                        }
                    } else {
                        movimientoValido = false;
                    }
                }
            }
        }
    }
    return movimientoValido;
}

bool Knight::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = false;
    //Verificar si se sale.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else { //NO se sale.
        //Verificar que sea posicion valida.
        if( (targetRow+1==row&&targetCol+2==col) || (targetRow+1&&targetCol-2==col) || (targetRow+2==row&&targetCol+1==col) || (targetRow+2==row&&targetCol-1==col) || (targetRow-2==row&&targetCol-1==col) || (targetRow-1&&targetCol+2==col) || (targetRow-2==row&&targetCol-1==col) || (targetRow-1==row&&targetCol-2==col) ){ //Verificar que para cualquiera de sus movimientos es valido.
            if(board->pieceAt(targetCol, targetRow)!=NULL){
                if(board->pieceAt(targetCol, targetRow)->getColor()!=color){ //Significa que NO es una ficha propia.
                    movimientoValido = true;
                }
            }
        }
    }
    return movimientoValido;
}

bool King::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = true;
    //Verificar que no se salga y que no se trate de mover en la misma.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else {
        if(board->pieceAt(targetCol, targetRow)!=NULL){ //Verificar que no compruebe una posicion que no existe.
            if (board->pieceAt(targetCol, targetRow)->getColor()==color){ //Verificar si a donde voy hay una mia.
                movimientoValido = false;
            } else {
                //Verificar que no vaya a avanzar mas de la cuenta.
                if (targetCol-col>1 || targetRow-row>1) { //La diferencia siempre deberia ser de solo una casilla.
                    movimientoValido = false;
                }
            }
        }
    }
    return movimientoValido;
}

bool Bishop::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = false;
    int cantidadPasos = 0;
    //Verificar que no se salga y que no se trate de mover en la misma.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else {
        if(row!=targetRow && col!=targetCol){ //Verificar que se mueve en DIAGONAL.
            //Tengo que averiguar en que direccion se esta moviendo.
            int direccion = averiguarDireccion(row, col, targetRow, targetCol, cantidadPasos);
            movimientoValido = verificarVecinas(board, cantidadPasos, direccion, row, col, color);
        } else { //Significa que no es un movimiento en diagonal.
            movimientoValido = false;
        }
    }
    return false;
}

bool Rook::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = false;
    int cantidadPasos = 0;
    //Verificar que no se salga y que no se trate de mover en la misma.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else {
        if(targetCol!=col && targetRow!=row){ //Verificar que se mueve en CRUZ.
            movimientoValido = false;
        } else {
            int direccion = averiguarDireccion(row, col, targetRow, targetCol, cantidadPasos);
            movimientoValido = verificarVecinas(board, cantidadPasos, direccion, row, col, color);
        }
    }
    return movimientoValido;
}

bool Queen::validMove(Board *board, char targetCol, char targetRow){
    bool movimientoValido = false;
    int cantidadPasos = 0;
    //Verificar que no se salga y que no se trate de mover en la misma.
    if (targetCol>7 || targetRow>7 || targetRow<0 || targetCol<0 || (col==targetCol && row==targetRow)) {
        movimientoValido = false;
    } else {
        int direccion = averiguarDireccion(row, col, targetRow, targetCol, cantidadPasos);
        movimientoValido = verificarVecinas(board, cantidadPasos, direccion, row, col, color);
    }
    return movimientoValido;
}
