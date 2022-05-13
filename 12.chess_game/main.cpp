#include "Pieces.h"
#include "Board.h"
//#include "Board.cpp"

#include <stdlib.h>
#include <stdio.h>

// Recomendacion: tener implementados los constructores, setters/getters y metodos basicos antes de utilizar este programa

/*static Board* b;
static float porcentage = 0.0f,evaluated = 0.0f;
static int count = 0, tests = 0;

template <class T> void evaluatePieceClass(char expectedType,const char* testname){
    T* object = new T(rand()%8,rand()%8,rand()%2);
    if(object->getType()==expectedType){
        count++;
    }else{
        printf("Failed test: %s\n",testname);
    }
    tests++;
    delete object;
}

void evaluate(char orcol,char orrow,char destcol,char destrow,bool expected,const char* testname){
    Piece* p = b->pieceAt(orcol,orrow);
    if(!p){ printf("Error fetching piece at: %c%i\n",'A'+orcol,1+orrow); b->printBoard(); return; }
    if(p->validMove(b,destcol,destrow)==expected){
        count++;
    }else{
        printf("Failed test: %s\n",testname);
    }
    tests++;
}

void addSubtotal(float value){
    porcentage += value * (double)(count)/(double)(tests);
    evaluated += value;
    count = 0;
    tests = 0;
}*/

int main(){
    //Metodo solicitado en el enunciado.
    const char *primerJuego = "/Users/emma/Documents/University/Programming 2/Exams/FinalExam/FinalExam/juego1.txt";
    const char *segundoJuego = "/Users/emma/Documents/University/Programming 2/Exams/FinalExam/FinalExam/juego2.txt";
    const char *juegoTramposo = "/Users/emma/Documents/University/Programming 2/Exams/FinalExam/FinalExam/juegotramposo.txt";
    const char *mensajeExitoso = "Juego ha finalizado con exito, nadie hizo trampa. FELICIDADES!!!";
    const char *mensajeTramposo = "Usted ha hecho trampa en el juego y por ello este ha salido de ejecucion.";
    
    Board *juego = new Board();
    bool jugar;
    //Cargar el primer juego.
    jugar = juego->loadLog(primerJuego);
    if(jugar==true){ std::cout<<mensajeExitoso<<std::endl; } else {std::cout<<mensajeTramposo<<std::endl;}
    juego->printBoard();
    //Cargar el segundo juego.
    jugar = juego->loadLog(segundoJuego);
    if(jugar==true){ std::cout<<mensajeExitoso<<std::endl; } else {std::cout<<mensajeTramposo<<std::endl;}
    juego->printBoard();
    //Carger el ultimo juego, el tramposo.
    jugar = juego->loadLog(juegoTramposo);
    if(jugar==true){ std::cout<<mensajeExitoso<<std::endl; } else {std::cout<<mensajeTramposo<<std::endl;}
    juego->printBoard();
    
    
    //SE ADJUNTA ESTE CODIGO PARA QUE EL PROFESOR PUEDA REVISAR EL EXAMEN CON MAYOR FACILIDAD.
    
    /*bool functional = true;
    
    char col=rand()%8,row = rand()%8;
    bool color = rand()%2;
    Piece* p = new Pawn(col,row,color);
    if(p->getColumn()==col){ count++; }
    if(p->getRow()==row){ count++; }
    if(p->getColor()==color){ count++; }
    tests = 3;
    printf("Testing constructor, passed: %i/%i\n",count,tests);
    addSubtotal(5.0f);
    col=rand()%8; row = rand()%8;
    p->setColumn(col);
    p->setRow(row);
    if(p->getColumn()==col){ count++; }
    if(p->getRow()==row){ count++; }
    if(p->getColor()==color){ count++; }
    tests = 3;
    printf("Testing setters/getters, passed: %i/%i\n",count,tests);
    addSubtotal(5.0f);
    
    evaluatePieceClass<Pawn>('P',"Pawn class type");
    evaluatePieceClass<Knight>('N',"Knight class type");
    evaluatePieceClass<Bishop>('B',"Bishop class type");
    evaluatePieceClass<Rook>('R',"Rook class type");
    evaluatePieceClass<Queen>('Q',"Queen class type");
    evaluatePieceClass<King>('K',"King class type");
    printf("Testing class types, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    if(porcentage != evaluated){ goto end; }
    
    b = new Board();
    b->blankBoard();
    
    for(int i=0;i<32;i++){
        col=rand()%8,row = rand()%8; color = rand()%2;
        if(!b->pieceAt(col,row)){ b->setPiece('P',col,row,color); }
        if(b->pieceAt(col,row)){ count++; }
        tests++;
    }
    if(count!=tests){ functional = false; }
    printf("Testing setPiece/pieceAt methods, passed: %i/%i\n",count,tests);
    addSubtotal(14.0f);

    b->blankBoard();
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(!b->pieceAt(i,j)){ count++; }
            tests++;
        }
    }
    if(count!=tests){ functional = false; }
    printf("Testing blank board method, passed: %i/%i\n",count,tests);
    addSubtotal(5.0f);
    
    // Requiere que funcionen los metodos blankBoard, setPiece y pieceAt
    if(!functional){ goto end; }
    
    b->blankBoard();
    b->setPiece('P',0,7,true);
    b->setPiece('P',0,6,true);
    b->setPiece('P',1,3,true);
    b->setPiece('P',4,1,true);
    b->setPiece('P',2,4,false);
    b->setPiece('P',2,3,true);
    b->setPiece('P',5,1,true);
    b->setPiece('K',5,2,true);
    
    evaluate(4,1,4,2,true,"Forward movement");
    evaluate(4,1,4,3,true,"Double forward movement");
    evaluate(1,3,2,4,true,"Capture movement");
    evaluate(0,7,0,8,false,"Out of bounds 1");
    evaluate(0,6,-1,5,false,"Out of bounds 2");
    evaluate(2,3,2,4,false,"Occupied space enemy");
    evaluate(0,6,0,7,false,"Occupied space friendly");
    evaluate(5,1,5,3,false,"Occupied space movement above friendly");
    evaluate(2,4,2,5,false,"Invalid direction movement");
    evaluate(2,4,2,7,false,"Invalid movement 1");
    evaluate(2,4,4,7,false,"Invalid movement 2");
    printf("Testing pawn movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    b->blankBoard();
    b->setPiece('N',6,6,true);
    b->setPiece('P',7,4,true);
    b->setPiece('P',4,5,false);
    b->setPiece('N',5,6,false);
    
    evaluate(6,6,5,4,true,"Normal movement");
    evaluate(6,6,4,5,true,"Capture movement");
    evaluate(6,6,8,7,false,"Out of bounds 1");
    evaluate(6,6,7,8,false,"Out of bounds 2");
    evaluate(6,6,7,4,false,"Occupied space friendly");
    evaluate(6,6,2,3,false,"Invalid movement");
    printf("Testing knight movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    b->setPiece('B',6,3,true);
    evaluate(6,3,5,4,true,"Normal movement 1");
    evaluate(6,3,7,2,true,"Normal movement 2");
    evaluate(6,3,4,5,true,"Capture movement");
    evaluate(6,3,7,4,false,"Occupied space friendly");
    evaluate(6,3,3,6,false,"Occupied space movement above friendly");
    evaluate(6,3,3,6,false,"Occupied space movement above enemy");
    evaluate(6,3,8,1,false,"Out of bounds 1");
    evaluate(6,3,2,-1,false,"Out of bounds 2");
    evaluate(6,3,5,5,false,"Invalid movement");
    printf("Testing bishop movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    b->setPiece('R',4,3,true);
    evaluate(4,3,4,0,true,"Normal movement vertical");
    evaluate(4,3,0,3,true,"Normal movement horizontal");
    evaluate(4,3,4,5,true,"Capture movement");
    evaluate(4,3,6,3,false,"Occupied space friendly");
    evaluate(4,3,7,3,false,"Occupied space movement above friendly");
    evaluate(4,3,4,6,false,"Occupied space movement above enemy");
    evaluate(4,3,4,-1,false,"Out of bounds 1");
    evaluate(4,3,-1,3,false,"Out of bounds 2");
    evaluate(4,3,6,2,false,"Invalid movement");
    printf("Testing rook movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    b->blankBoard();
    b->setPiece('Q',2,3,true);
    b->setPiece('P',5,3,true);
    b->setPiece('P',2,6,false);
    b->setPiece('B',4,5,false);
    evaluate(2,3,2,0,true,"Normal movement vertical");
    evaluate(2,3,0,3,true,"Normal movement horizontal");
    evaluate(2,3,3,4,true,"Normal movement diagonal");
    evaluate(2,3,2,6,true,"Capture movement 1");
    evaluate(2,3,4,5,true,"Capture movement 2");
    evaluate(2,3,5,3,false,"Occupied space friendly");
    evaluate(2,3,7,3,false,"Occupied space movement above friendly");
    evaluate(2,3,5,6,false,"Occupied space movement above enemy");
    evaluate(2,3,2,-1,false,"Out of bounds 1");
    evaluate(2,3,-1,3,false,"Out of bounds 2");
    evaluate(2,3,4,6,false,"Invalid movement");
    printf("Testing queen movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    b->setPiece('K',4,4,true);
    b->setPiece('K',7,7,false);
    evaluate(4,4,4,3,true,"Normal movement");
    evaluate(4,4,4,5,true,"Capture movement");
    evaluate(4,4,5,3,false,"Occupied space friendly");
    evaluate(7,7,7,8,false,"Out of bounds 1");
    evaluate(7,7,8,7,false,"Out of bounds 2");
    evaluate(7,7,5,6,false,"Invalid movement");
    printf("Testing king movements, passed: %i/%i\n",count,tests);
    addSubtotal(6.0f);
    
    delete b;
    count++;
    tests++;
    printf("Testing Board constructor/destructor, passed: %i/%i\n",count,tests);
    addSubtotal(5.0f);
    
end:
    
    printf("Total: %.2f/%.0f\n",porcentage,evaluated);
    
    
    printf("Press ENTER...");
    fgetc(stdin);*/
    
    return 0;
}

