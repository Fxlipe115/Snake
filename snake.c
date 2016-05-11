/********************************************************************
* Snake                                                                                                          *
* Felipe de Almeida Graeff                                                                                *
* 09-05-2016                                                                                                   *
*                                                                                                                    *
* Simulador de movimentação do jogo Snake.                                                   *
* O usuário primeiro deve entrar com as coordenadas das partes do                    *
* corpo da cobra de tamanho SNAKE_SIZE.                                                       *
* Será desenhada uma tela quadrada de lado MATRIX_SIZE com a                      *
* cobra na posição inicial definida e será pedido ao usuário a                              *
* entrada de comandos para a movimentação. A tela será atualiza e                    *
* reimpressa para cada comando enviado. Esse processo se repetirá                   *
* até que a entrada seja o caracter 'X'.                                                              *
*                                                                                                                    *
* Makefile enviado junto.                                                                                  *
* Compilação:                                                                                                 *
*   Windows: make snakewindows                                                                     *
*   Linux  : make snakelinux                                                                             *
*                                                                                                                    *
* Caso for compilar em uma IDE, usar flag -std=c99                                          *
********************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <conio2.h>

#define SNAKE_SIZE 5
#define MATRIX_SIZE 50

typedef struct Snake{
	int x;
	int y;
} Snake;

int main(){
	Snake snake[SNAKE_SIZE];
	char key;
	
	printf("TAMANHO DA COBRA: %d\n",SNAKE_SIZE);
	printf("TAMANHO DO MAPA: %dX%d\n\n",MATRIX_SIZE,MATRIX_SIZE);
	
	//RECEBE AS COORDENADAS DAS PARTES DO CORPO DA COBRA
	printf("COORDENADAS INICIAIS DA COBRA:\n");
	for(int i = 0; i < SNAKE_SIZE; i++){
		scanf(" %d %d",&snake[i].x,&snake[i].y);
	}
	
	//DESENHA A TELA
	for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
		printf("#");
	}
	printf("\n");
	
	for(int y = 0; y<MATRIX_SIZE; y++){
		printf("#");
		for(int x = 0; x<MATRIX_SIZE; x++){
			if(snake[0].y == y && snake[0].x == x){
				printf("@");
			}else if((snake[1].y == y && snake[1].x == x) ||
					 (snake[2].y == y && snake[2].x == x) ||
					 (snake[3].y == y && snake[3].x == x) ||
					 (snake[4].y == y && snake[4].x == x)){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("#\n");
	}
		
	for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
		printf("#");
	}
	printf("\n");
	//FIM DESENHA A TELA
	
	
	//MOVIMENTAÇÃO
	printf("ENTRADA DE COMANDOS: (DIGITE 'X' PARA SAIR)\n");
	do{
		//INPUT DE COMANDOS
		//scanf(" %c",&key);
		key = getch();
		key = toupper(key);
		
		//ATUALIZA POSIÇÃO DO CORPO DA COBRA
		if(key=='W' || key=='A' || key=='S' || key=='D'){
			for(int i = SNAKE_SIZE-1; i>0; i--){
				snake[i].x = snake[i-1].x;
				snake[i].y = snake[i-1].y;
			}
		}
		
		//ATUALIZA POSIÇÃO DA CABEÇA DA COBRA
		switch(key){
			case 'W':
				snake[0].y--;
				break;
			case 'A':
				snake[0].x--;
				break;
			case 'S':
				snake[0].y++;
				break;
			case 'D':
				snake[0].x++;
				break;
			case 'X':
				break;
		}
		
		if(key != 'X'){
			
			clrscr();
			//DESENHA A TELA
			for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
				printf("#");
			}
			printf("\n");
			
			for(int y = 0; y<MATRIX_SIZE; y++){
				printf("#");
				for(int x = 0; x<MATRIX_SIZE; x++){
					if(snake[0].y == y && snake[0].x == x){
						printf("@");
					}else if((snake[1].y == y && snake[1].x == x) ||
							(snake[2].y == y && snake[2].x == x) ||
							(snake[3].y == y && snake[3].x == x) ||
							(snake[4].y == y && snake[4].x == x)){
						printf("*");
					}else{
						printf(" ");
					}
				}
				printf("#\n");
			}
			
			for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
				printf("#");
			}
			printf("\n");
			//FIM DESENHA A TELA
		}
		
		
	}while(key != 'X');
	
	return 0;
}
