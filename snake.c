#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#include "grf_snake_lib.h"

#define SNAKE_SIZE 5
#define MATRIX_SIZE 10

int main(){
	Snake *snake = newSnake(SNAKE_SIZE);
	char key;
	
	printf("TAMANHO DA COBRA: %d\n",SNAKE_SIZE);
	printf("TAMANHO DO MAPA: %dX%d\n\n",MATRIX_SIZE,MATRIX_SIZE);
	
	//RECEBE AS COORDENADAS DAS PARTES DO CORPO DA COBRA
	printf("COORDENADAS INICIAIS DA COBRA:\n");
	
	scanf(" %d %d",&snake->x,&snake->y);
	
	//DESENHA A TELA
	for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
		printf("#");
	}
	printf("\n");
	
	for(int y = 0; y<MATRIX_SIZE; y++){
		printf("#");
		for(int x = 0; x<MATRIX_SIZE; x++){
			if(snake->y == y && snake->x == x){
				printf("@");
			}else if(isSnake(snake,x,y)){
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
		/*if(key=='W' || key=='A' || key=='S' || key=='D'){
			for(int i = SNAKE_SIZE-1; i>0; i--){
				snake[i].x = snake[i-1].x;
				snake[i].y = snake[i-1].y;
			}
		}*/
		
		//ATUALIZA POSIÇÃO DA CABEÇA DA COBRA
		int dir;
		switch(key){
			case 'W':
				//snake[0].y--;
				dir = _UP_;
				break;
			case 'A':
				//snake[0].x--;
				dir = _LEFT_;
				break;
			case 'S':
				//snake[0].y++;
				dir = _DOWN_;
				break;
			case 'D':
				//snake[0].x++;
				dir = _RIGHT_;
				break;
			case '+':
				increaseSnake(snake);
				break;
			case '-':
				if(getSnakeSize(snake) > 2)
					decreaseSnake(snake);
				break;
			case 'X':
				break;
		}
		if(key == 'W' || key == 'A' || key == 'S' || key == 'D'){
			moveSnake(snake,dir);
		}
		
		if(key != 'X'){
			
			//clrscr();
			//DESENHA A TELA
			for(int i = 0, size = MATRIX_SIZE+2; i<size; i++){
				printf("#");
			}
			printf("\n");
			
			for(int y = 0; y<MATRIX_SIZE; y++){
				printf("#");
				for(int x = 0; x<MATRIX_SIZE; x++){
					if(snake->y == y && snake->x == x){
						printf("@");
					}else if(isSnake(snake,x,y)){
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
	
	destroySnake(snake);
	
	return 0;
}
