#include "battleship.h"

// Estrutura do Bit map
Bitmap* newBitmap() {
	Bitmap* aux = (Bitmap*)malloc(sizeof(Bitmap));
	aux -> map = (char**)malloc(5 * sizeof(char*));
	for(int i = 0;i < 5;i++) {
		aux -> map[i] = (char*)malloc(5 * sizeof(char));
	}
	return aux;
}

//Estrutura para as coordenadas
Coordinates* newCoordinates (int x, int y) {
	Coordinates* aux = (Coordinates*)malloc(sizeof(Coordinates));
	aux -> x = x;
	aux -> y = y;
	return aux;
}

//Estrutura para as células do barco
Cell* newCell(Boat* boat) {
	Cell* aux = (Cell*) malloc(sizeof(Cell));
	aux -> boat = boat;
	aux -> shot = '0';
	aux -> state = '0';
	return aux;
}

//Estrutura para criar matrizes (tabuleiros de jogo)
Matrix* newMatrix(int s) {
	Matrix* matrix = (Matrix *)malloc(sizeof(Matrix));
	matrix -> size = s;
	matrix -> cell = (Cell**)calloc(s, sizeof(Cell*));
	for(int i = 0;i < s;i++){
		matrix -> cell[i] = (Cell*)calloc(s, sizeof(Cell));
		for(int j = 0;j < s;j++) {
			matrix -> cell[i][j].shot = '0';
			matrix -> cell[i][j].state = '0';
			matrix -> cell[i][j].boat = NULL;
		}
	}
	return matrix;
}

//Estrutura para criar barcos
Boat* newBoat(BoatKind kind , Coordinates *coord) {
	Boat* boat = (Boat*)malloc(sizeof(Boat));
	boat -> coord = coord;
	boat -> kind = kind;
	boat -> bit = newBitmap();
	boat -> hits = 0;
	boat -> totalSize = 0;
	switch(kind) {
		/*
		0 0 0 0 0
		0 0 * * 0
		0 0 * 0 0
		0 0 * * 0
		0 0 0 0 0
		*/
		case BARCO_C:
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(i == 1 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 1 && j == 3) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 3 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 3 && j == 3) boat -> bit -> map[i][j] = '1';
				else boat -> bit -> map[i][j]= '0';
			}
		}
		boat -> totalSize = 5;
		break;
		/*
		0 0 0 0 0
		0 * * 0 0
		0 * * 0 0
		0 0 0 0 0
		0 0 0 0 0
		*/
		case BARCO_Q:
		for(int i = 0; i < 5;i++) {
			for(int j = 0;j < 5;j++) {
				if(i == 1 && j == 1) boat -> bit -> map[i][j] = '1';
				else if(i == 1 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 1) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 2) boat -> bit -> map[i][j]= '1';
				else boat -> bit -> map[i][j]= '0';
			}
		}
		boat -> totalSize = 4;
		break;
		/*
		0 0 0 0 0
		0 * 0 * 0
		0 0 * 0 0
		0 * 0 * 0
		0 0 0 0 0
		*/
		case BARCO_X:
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(i == 1 && j == 1) boat -> bit -> map[i][j] = '1';
				else if(i == 3 && j == 1) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 1 && j == 3) boat -> bit -> map[i][j] = '1';
				else if(i == 3 && j == 3) boat -> bit -> map[i][j] = '1';
				else boat -> bit -> map[i][j] = '0';
			}
		}
		boat -> totalSize = 5;
		break;
		/*
		0 0 * 0 0
		0 0 * 0 0
		0 0 * * 0
		0 0 0 0 0
		0 0 0 0 0
		*/
		case BARCO_L:
		for(int i = 0; i < 5; i++) {
			for(int j = 0;j < 5; j++) {
				if(i == 0 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 1 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 3) boat -> bit -> map[i][j] = '1';
				else boat -> bit -> map[i][j] = '0';
			}
		}
		boat -> totalSize = 4;
		break;
		/*
		0 0 * 0 0
		0 0 * 0 0
		0 0 * 0 0
		0 0 * 0 0
		0 0 * 0 0
		*/
		case BARCO_VH:
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(i == 0 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 1 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 2 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 3 && j == 2) boat -> bit -> map[i][j] = '1';
				else if(i == 4 && j == 2) boat -> bit -> map[i][j] = '1';
				else boat -> bit -> map[i][j] = '0';
			}
		}
		boat -> totalSize = 5;
		break;

		default:
		printf("Unknown boat type\n");
		break;
	}
	return boat;
}

//Imprime a matriz (tabuleiro de jogo)
void printMatrix(Matrix* m) {
	for(int i=0; i < m -> size; i++){
		printf("\n");
		for(int j=0; j < m -> size; j++){
			if(m -> cell[i][j].state == '0'){
				printf("\033[0;34m");
				printf("~");
			}
			else if(m -> cell[i][j].state == '1') printf("*");
			else if(m -> cell[i][j].state == '2'){
				printf("\033[0;31m");
				printf("X");
			}
			else if(m -> cell[i][j].shot == '3'){
				printf("\033[22;37m");
				printf("O");
			}
			else printf("%c", m -> cell[i][j].state);
			printf("\033[0m"); //Reset
		}
	}
}

//Imprime a matriz do adversário (tabuleiro de jogo)
void printMatrixGame(Matrix* m) {
	for(int i=0; i < m -> size; i++){
		printf("\n");
		for(int j=0; j < m -> size; j++){
			if(m -> cell[i][j].shot == '0'){
				printf("\033[0;34m");
				printf("~");
			}
			else if(m -> cell[i][j].shot == '1') printf("*");
			else if(m -> cell[i][j].shot == '2'){
				printf("\033[0;31m");
				printf("X");
			}
			else if(m -> cell[i][j].shot == '3'){
				printf("\033[22;37m");
				printf("O");
			}
			else printf("%c", m -> cell[i][j].shot);
			printf("\033[0m"); //Reset
		}
	}
}

//Rotações de 90º
void rotateNinety(Bitmap* b) {
	int size = 5;
	for (int i = 0; i < size/2; i++) {
		for (int j = i; j < size - i - 1; j++) {
			int aux = b -> map[i][j];
			b -> map[i][j] = b -> map[size - 1 - j][i];
			b -> map[size - 1 - j][i] = b -> map[size - 1 - i][size - 1 - j];
			b -> map[size - 1 - i][size - 1 - j] = b -> map[j][size - 1 - i];
			b -> map[j][size - 1 - i] = aux;
		}
	}
}

//Rotações de 180º
void rotateOHEighty(Bitmap* b) {
	int size = 5;
	for (int i = 0; i < size/2; i++) {
		for (int j = 0; j < size; j++){
			int aux = b -> map[i][j];
			b -> map[i][j] = b -> map[size - i - 1][size - j - 1];
			b -> map[size - i - 1][size - j - 1] = aux;
		}
	}
	for (int k = 0; k < size/2; k++) {
		int aux = b -> map[size / 2][k];
		b -> map[size/2][k] = b -> map[size/2][size - k - 1];
		b -> map[size/2][size - k - 1] = aux;
	}
}

//Rotações de 270º
void rotateTHSeventy(Bitmap *b) {
	int size = 5;
	for (int i = 0; i < size / 2; i++) {
		for (int j = i; j < size - i - 1; j++) {
			int aux = b -> map[i][j];
			b->map[i][j] = b->map[j][size - 1 - i];
			b->map[j][size - 1 - i] = b->map[size - 1 - i][size - 1 - j];
			b->map[size - 1 - i][size - 1 - j] = b->map[size - 1 - j][i];
			b->map[size - 1 - j][i] = aux;
		}
	}
}

//Imprime antes do jogo começar o tipo de barco C
void printBoatC() {
	printf("         \n");
	printf("    * *  \n");
	printf("    *    \n");
	printf("    * *  \n");
	printf("         \n");
	printf("Enter number of Type C boats:\n");
}
//Imprime antes do jogo começar o tipo de barco L
void printBoatL() {
	printf("    *    \n");
	printf("    *    \n");
	printf("    * *  \n");
	printf("         \n");
	printf("         \n");
	printf("Enter number of Type L boats:\n");
}
//Imprime antes do jogo começar o tipo de barco Q
void printBoatQ() {
	printf("         \n");
	printf("  * *    \n");
	printf("  * *    \n");
	printf("         \n");
	printf("         \n");
	printf("Enter number of square boats:\n");
}
//Imprime antes do jogo começar o tipo de barco X
void printBoatX() {
	printf("         \n");
	printf("   * *   \n");
	printf("    *    \n");
	printf("   * *   \n");
	printf("         \n");
	printf("Enter number of Type X boats:\n");
}
//Imprime antes do jogo começar o tipo de barco VH
void printBoatVH() {
	printf("    *    \n");
	printf("    *    \n");
	printf("    *    \n");
	printf("    *    \n");
	printf("    *    \n");
	printf("Enter number of vertical boats:\n");
}

//Verica se as coordenadas dadas para inserir o barco são válidas
int verify(Matrix*m, Boat* boat, int flag) {
	int bx = 0; int by = 0;
	for(int i = boat -> coord -> x-2;i <= boat -> coord -> x+2;i++) {
		bx = 0;
		for(int j = boat -> coord -> y-2;j <= boat -> coord -> y+2; j++) {
			if(boat -> bit -> map[by][bx] == '1') {
				if(j < 0 || i < 0 || j > m -> size -1 || i > m -> size - 1) {
					if(flag == 1) printf("You can't insert a boat outside of the game board\n");
					return 0;
				}
				else if(m -> cell[i][j].state == '1') {
					if(flag == 1) printf("This space is occupied, please try another one\n");
					return 0;
				}
			}
			bx++;
		}
		by++;
	}
	return 1;
}

//Insere os barcos no tabuleiro
int insertBoats(Matrix* m, Boat* boat,int flag) {
	int r = verify(m,boat,flag);
	if(r == 0) return 0;
	int bx2 = 0; int by2 = 0;
	for(int i = boat -> coord -> x-2;i <= boat -> coord -> x+2; i++) {
		bx2 = 0;
		for(int j = boat -> coord -> y-2;j <= boat -> coord -> y+2; j++) {
			if(boat -> bit -> map[by2][bx2] == '1') {
				m -> cell[i][j].state = '1';
				m -> cell[i][j].boat = boat;
				m -> cell[i][j].boat -> hits = 0;
			}
			bx2++;
		}
		by2++;
	}
	return 1;
}

//Roda os barcos de acorodo com a rotação dada
void rotation(int r, Bitmap* b) {
	switch(r) {
		case 0:
		break;
		case 90:
		rotateNinety(b);
		break;
		case 180:
		rotateOHEighty(b);
		break;
		case 270:
		break;
		rotateTHSeventy(b);
		case 360:
		break;
		default:
		printf("Invalid rotation number\n");
		break;
	}
}

//Destrói bit map
void destroyBitmap(Bitmap* b) {
	for(int i = 0;i < 5;i++) {
		free(b -> map[i]);
	}
	free(b -> map);
	free(b);
}

//Destrói coordenadas
void destroyCoordinate(Coordinates* c) {
	free(c);
}

//Destrói barcos desnecessários
void destroyBoat(Boat* boat) {
	destroyBitmap(boat -> bit);
	free(boat);
}

//Escolher as coordenadas e a rotação para inserir os barcos manualmente
void manualChoice(Matrix* m, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH) {
	int flag = 1;
	int cCount = 1;
	while(cCount <= barcosC) {
		int rotationCheck = 0;
		int a, b, r;
		printf("Insert the coordinates of your number %d type C boat:\n", cCount);
		printf("Insert the line!\n");
		scanf("%d", &a);
		printf("Insert the column!\n");
		scanf("%d", &b);
		printf("Insert the rotation number of your boat!(If you don't want one just insert 0)\n");
		while(rotationCheck == 0) {
			scanf("%d", &r);
			if(r == 0 || r == 90 || r == 180 || r == 270 || r == 360) rotationCheck = 1;
			else printf("Invalid rotation number. Please insert a new number\n");
		}
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_C, c);
		rotation(r,boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) cCount++;
		else printf("Insert your boat in an available position\n");
		printMatrix(m);
		printf("\n");
	}
	int qCount = 1;
	while(qCount <= barcosQ) {
		int rotationCheck = 0;
		int a,b, r;
		printf("Insert the coordinates of your number %d square boat:\n", qCount);
		printf("Insert the line!\n");
		scanf("%d", &a);
		printf("Insert the column!\n");
		scanf("%d", &b);
		printf("Insert the rotation number of your boat!(If you don't want one just insert 0)\n");
		while(rotationCheck == 0) {
			scanf("%d", &r);
			if(r == 0 || r == 90 || r == 180 || r == 270 || r == 360) rotationCheck = 1;
			else printf("Invalid rotation number. Please insert a new number\n");
		}
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_Q, c);
		rotation(r,boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) qCount++;
		else printf("Insert your boat in an available position\n");
		printMatrix(m);
		printf("\n");
	}

	int xCount = 1;
	while(xCount <= barcosX) {
		int rotationCheck = 0;
		int a, b,r;
		printf("Insert the coordinates of your number %d type X boat:\n", xCount);
		printf("Insert the line!\n");
		scanf("%d", &a);
		printf("Insert the column!\n");
		scanf("%d", &b);
		printf("Insert the rotation number of your boat!(If you don't want one just insert 0)\n");
		while(rotationCheck == 0) {
			scanf("%d", &r);
			if(r == 0 || r == 90 || r == 180 || r == 270 || r == 360) rotationCheck = 1;
			else printf("Invalid rotation number. Please insert a new number\n");
		}
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_X, c);
		rotation(r,boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) xCount++;
		else printf("Insert your boat in an available position\n");
		printMatrix(m);
		printf("\n");
	}

	int lCount = 1;
	while(lCount <= barcosL) {
		int rotationCheck = 0;
		int a, b,r;
		printf("Insert the coordinates of your number %d type L boat:\n", lCount);
		printf("Insert the line!\n");
		scanf("%d", &a);
		printf("Insert the column!\n");
		scanf("%d", &b);
		printf("Insert the rotation number of your boat!(If you don't want one just insert 0)\n");
		while(rotationCheck == 0) {
			scanf("%d", &r);
			if(r == 0 || r == 90 || r == 180 || r == 270 || r == 360) rotationCheck = 1;
			else printf("Invalid rotation number. Please insert a new number\n");
		}
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_L, c);
		rotation(r,boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) lCount++;
		else printf("Insert your boat in an available position\n");
		printMatrix(m);
		printf("\n");
	}

	int vhCount = 1;
	while(vhCount <= barcosVH) {
		int rotationCheck = 0;
		int a, b,r;
		printf("Insert the coordinates of your number %d vertical boat:\n", vhCount);
		printf("Insert the line!\n");
		scanf("%d", &a);
		printf("Insert the column!\n");
		scanf("%d", &b);
		printf("Insert the rotation number of your boat!(If you don't want one just insert 0)\n");
		while(rotationCheck == 0) {
			scanf("%d", &r);
			if(r == 0 || r == 90 || r == 180 || r == 270 || r == 360) rotationCheck = 1;
			else printf("Invalid rotation number. Please insert a new number\n");
		}
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_VH, c);
		rotation(r,boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) vhCount++;
		else printf("Insert your boat in an available position\n");
		printMatrix(m);
		printf("\n");
	}
}

//Rotações para a função autoChoice
int randomRotation(int r) {
	if(r == 1) return 0;
	else if(r == 2) return 90;
	else if(r == 3) return 180;
	else return 270;
}
// Rand escolhe as coordenadas e a rotação para inserir os barcos automaticamente
void autoChoice(Matrix* m, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH, int size) {
	int flag = 0;
	int cCount = 1;

	srand(time(NULL));
	while(cCount <= barcosC) {
		int a = rand()%size;
		int b = rand()%size;
		int r = rand() % (4 + 1 - 1) + 1;
		int random = randomRotation(r);
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_C, c);
		rotation(random, boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) cCount++;
		else {
			destroyCoordinate(c);
			destroyBoat(boatNew);
		}
	}

	int qCount = 1;
	while(qCount <= barcosQ) {
		int a = rand()%size;
		int b = rand()%size;
		int r = rand() % (4 + 1 - 1) + 1;
		int random = randomRotation(r);
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_Q, c);
		rotation(random, boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) qCount++;
		else {
			destroyCoordinate(c);
			destroyBoat(boatNew);
		}
	}

	int xCount = 1;
	while(xCount <= barcosX) {
		int a = rand()%size;
		int b = rand()%size;
		int r = rand() % (4 + 1 - 1) + 1;
		int random = randomRotation(r);
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_X, c);
		rotation(random, boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) xCount++;
		else {
			destroyCoordinate(c);
			destroyBoat(boatNew);
		}
	}

	int lCount = 1;
	while(lCount <= barcosL) {
		int a = rand()%size;
		int b = rand()%size;
		int r = rand() % (4 + 1 - 1) + 1;
		int random = randomRotation(r);
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_L, c);
		rotation(random, boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) lCount++;
		else {
			destroyCoordinate(c);
			destroyBoat(boatNew);
		}
	}

	int vhCount = 1;
	while(vhCount <= barcosVH) {
		int a = rand()%size;
		int b = rand()%size;
		int r = rand() % (4 + 1 - 1) + 1;
		int random = randomRotation(r);
		Coordinates* c = newCoordinates(a,b);
		Boat* boatNew = newBoat(BARCO_VH, c);
		rotation(random, boatNew -> bit);
		int temp = insertBoats(m,boatNew,flag);
		if(temp == 1) vhCount++;
		else {
			destroyCoordinate(c);
			destroyBoat(boatNew);
		}
	}
	printf("Game board after the boats insertion: \n");
	printMatrix(m);
	printf("\n");
	printf("\n");
}

//Menu para escolher forma de inserção de barcos (autoChoice ou manualChoice)
int boatsInsertion(Matrix* m, int size, int barcosC, int barcosL, int barcosQ, int barcosX, int barcosVH) {
	int resposta;
	printf("Would you like to insert the boats manually or automatically? Press the corresponding number \n");
	printf("\n");
	printf("1 - Manually\n");
	printf("2 - Automatically\n");
	scanf("%d", &resposta);
	if(resposta == 1) {
		manualChoice(m, barcosC, barcosL, barcosQ, barcosX, barcosVH);
	}

	else if(resposta == 2) {
		autoChoice(m,barcosC, barcosL, barcosQ, barcosX, barcosVH, size);
	}

	else printf("Invalid answer, please restart the game\n");
	return 0;
}

//Verifica se algum jogador já destruiu todos os barcos do adversário
int isFinished(Matrix* m1, Matrix* m2) {
	int count = 0;
	for(int i = 0;i < m1 -> size - 1; i++) {
		for(int j = 0;j < m1 -> size - 1; j++) {
			if(m1 -> cell[i][j].state == '1') count++;
		}
	}

	int count2 = 0;
	for(int i = 0;i < m2 -> size - 1;i++) {
		for(int j = 0;j < m2 -> size - 1;j++) {
			if(m2 -> cell[i][j].shot == '2') count2++;
		}
	}
	if(count == count2) return 1;
	else return 0;
}

//Inicia o jogo, muda os turnos dos jogadores até alguém ganhar
int startGame(Matrix* player1, Matrix* player2, int turno, char* p1, char* p2, int size) {
	//size = size+1-1;
	while((isFinished(player1,player2) != 1) || (isFinished(player2,player1) != 1)) {
		if(turno == 1) {
			printf("%s Game board:\n", p1);
			int a,b;
			printMatrixGame(player1);
			printf("\n");
			int flag = 1;
			int linesCheck = 0;
			int columnsCheck = 0;
			while(flag != 0) {
				printf("Insert the line\n");
				while(linesCheck == 0) {
					scanf("%d", &a);
					if(a >= 0 && a < size -1) linesCheck = 1;
					else printf("Please choose a number inside the limits\n");
				}

				printf("Insert the Column\n");
				while(columnsCheck == 0) {
					scanf("%d", &b);
					if(b >= 0 && b < size -1) columnsCheck = 1;
					else printf("Please choose a number inside the limits\n");
				}

				if(player1 -> cell[a][b].shot == '2' || player1 -> cell[a][b].shot == '3') {
					printf("You have already chosen this position, select a different one\n");
				}

				else {
					if(player2 -> cell[a][b].state == '1') {
						printf("You just hitted a boat! Keep going\n");
						player1 -> cell[a][b].shot = '2';
						player2 -> cell[a][b].boat -> hits++;
						if(player2 -> cell[a][b].boat -> hits == player2 -> cell[a][b].boat -> totalSize) {
							printf("Congratulations! You sunk a battleship\n");
						}
					}
					else {
						player1 -> cell[a][b].shot = '3';
						printf("\n");
						printf("You failed, better luck next time\n");
						printf("\n");
						printf("\n");
					}
					flag = 0;
				}
			}


			turno = 2;

			if(isFinished(player1,player2) == 1) {
				printf("%s just won the match\n", p2);
				break;
			}

			else if(isFinished(player2,player1) == 1) {
				printf("%s just won the match!\n", p1);
				break;
			}
		}

		if(turno == 2){
			printf("%s Game board:\n", p2);
			int a,b;
			printMatrixGame(player2);
			printf("\n");
			int flag2 = 1;
			int linesCheck = 0;
			int columnsCheck = 0;
			while(flag2 != 0) {
				printf("Insert the line\n");
				while(linesCheck == 0) {
					scanf("%d", &a);
					if(a >= 0 && a < size - 1) linesCheck = 1;
					else printf("Please choose a number inside the limits\n");
				}

				printf("Insert the column\n");
				while(columnsCheck == 0) {
					scanf("%d", &b);
					if(b >= 0 && b < size -1) columnsCheck = 1;
					else printf("Please choose a number inside the limits\n");
				}

				if(player2 -> cell[a][b].shot == '2' || player2 -> cell[a][b].shot == '3') {
					printf("You have already chosen this position, select a different one\n");
				}
				else {
					if(player1 -> cell[a][b].state == '1'){
						printf("You just hitted a boat! Keep going\n");
						player2 -> cell[a][b].shot = '2';
						player1 -> cell[a][b].boat -> hits++;
						if(player1 -> cell[a][b].boat -> hits == player1 -> cell[a][b].boat -> totalSize) {
							printf("Congratulations! You sunk a battleship\n");
						}
					}
					else {
						player2 -> cell[a][b].shot = '3';
						printf("\n");
						printf("You failed, better luck next time\n");
						printf("\n");
						printf("\n");
					}
					flag2 = 0;
				}
			}

			turno = 1;

			if(isFinished(player1,player2) == 1) {
				printf("%s just won the match!\n", p2);
				break;
			}

			else if(isFinished(player2,player1) == 1) {
				printf("%s just won the match!\n", p1);
				break;
			}
		}
	}
	return 0;
}
