snakewindows: snake.c
	gcc -o snake.exe snake.c  -lm -lconio -Wall -std=c99
snakelinux: snake.c
	gcc -o snake snake.c -lm -Wall -std=c99