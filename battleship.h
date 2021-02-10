#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//estrutura que contém os tipos de barcos existentes
typedef enum {BARCO_C, BARCO_Q, BARCO_X, BARCO_L, BARCO_VH} BoatKind;

typedef struct {
	char** map;
} Bitmap;

typedef struct {
	int x;
	int y;
} Coordinates;

//estrutura dos barcos
typedef struct {
	Coordinates* coord;
	BoatKind kind;
	Bitmap* bit;
	int hits; //número de vezes que o barco foi atingido 
	int totalSize; //tamanho do barco
} Boat;

//estrutura de uma "Cell" da matriz de jogo  
typedef struct {
	char shot;
	char state;
	Boat* boat;
} Cell;

//estrutura da matri< de jogo que contém o tamanho e a estrutura Cell
typedef struct {
    int size;
    Cell** cell;
} Matrix;


Bitmap* newBitmap();
Coordinates* newCoordenadas (int x, int y);
Cell* newCell(Boat* boat);
Matrix* newMatrix(int r);
Boat* newBoat(BoatKind kind , Coordinates *coord);
void printMatrix(Matrix* m);
void rotateNinety(Bitmap* b);
void rotateOHEighty(Bitmap* b);
void rotateTHSeventy(Bitmap *b);
void printBoatC();
void printBoatL();
void printBoatQ();
void printBoatX();
void printBoatVH();
int insertBoats(Matrix* m, Boat* boat, int flag);
void rotation(int r, Bitmap* b);
void destroyBitmap(Bitmap* b);
void destroyCoordinate(Coordinates* c);
void destroyBoat(Boat* boat);
void manualChoice(Matrix* m, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH);
int randomRotation(int r);
void autoChoice(Matrix* m, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH,int size);
int boatsInsertion(Matrix* m, int size, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH);
int isFinished(Matrix* m1, Matrix* m2);
int startGame(Matrix* player1, Matrix* player2, int turno, char* p1, char* p2, int size);
