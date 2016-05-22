#include <stdlib.h>

struct snake{
	int x;
	int y;
	int food;
	struct snake *next;
};

int getSnakeSize(struct snake *head){
	int size = 0;
	while(head->next != NULL){
		size++;
		head = head->next;
	}
	return size;
}

void increaseSnake(struct snake *head,int food){
	struct snake *newbody = malloc(sizeof(struct snake));
	
	newbody->x = head->x;
	newbody->y = head->y;
	newbody->food = food;
	
	newbody->next = head->next;
	head->next = newbody;
}

void decreaseSnake(struct snake *head){
	if(getSnakeSize(head) > 1){
		while(head->next->next != NULL){
			head = head->next;
		}
		free(head->next);
		head->next = NULL;
	}   
}

struct snake* newSnake(int size,int x,int y){
	struct snake *head = malloc(sizeof(struct snake));
	head->x = x;
	head->y = y;
	head->food = 0;

	struct snake *tail = malloc(sizeof(struct snake));
	tail->x = x;
	tail->y = y;
	tail->food = 0;

	head->next = tail;
	tail->next = NULL;
	size -= 1;

	for(int i = 0; i<size; i++){
		increaseSnake(head,0);
	}

	return head;
}

void destroySnake(struct snake *head){
	while(head != NULL){
		struct snake *tmp = head;
		head = head->next;
		free(tmp);
	}
}

void moveSnake(struct snake *head,int dir,int xSize,int ySize){
	
	decreaseSnake(head);
	increaseSnake(head,0);
	
	switch(dir){
		case 0:
			head->x = (head->x + 1) % xSize;
			break;
		case 90:
			head->y--;
			if(head->y < 0){
				head->y = ySize-1;
			}
			break;
		case 180:
			head->x--;
			if(head->x < 0){
				head->x = xSize-1;
			}
			break;
		case 270:
			head->y = (head->y + 1) % ySize;
			break;
		//default:
	}			
}

	
int isSnake(struct snake *head,int x,int y){
	int isSnake = 0;
	
	while(head->next != NULL && isSnake == 0){
		if((head->x == x) && (head->y == y)){
			isSnake = 1;
		}
		head = head->next;
	}
	return isSnake;
}

int hasFood(struct snake *head,int x,int y){
	int hasFood = 0;

	while(head->next != NULL){
		if((head->x == x) && (head->y == y) && head->food){
			hasFood = 1;
		}
		head = head->next;
	}
	return hasFood;
}
