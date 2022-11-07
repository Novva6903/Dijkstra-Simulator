#include <queue>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stack>

#define H 19
#define W 109

using namespace std;

void menuDijkstra();

void blue() {
    printf("\033[0;34m");
}

void red() {
    printf("\033[0;31m");
}

void yellow() {
    printf("\033[1;33m");
}

void green() {
    printf("\033[0;32m");
}

void resetColor(){
    printf("\033[0m");
}

void setCursorPosition(int x, int y) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(output, pos);
}

enum MenuSystem {
	SHOWMENU, MOVECURSOR, EXITPROGRAM
};

void hidecursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int startX, startY;
int finishY, finishX;

int StartY, StartX, FinishY, FinishX;

void printMenu() {
	puts("      _____ _______   _ _  __ _____ _______ _____             ");
    puts("      |  __ \\_   _|   | | |/ // ____|__   __|  __ \\     /\\");
    puts("      | |  | || |     | | ' /| (___    | |  | |__) |   /  \\ ");
    puts("      | |  | || | _   | |  <  \\___ \\   | |  |  _  /   / /\\ \\ ");
    puts("      | |__| || || |__| | . \\ ____) |  | |  | | \\ \\  / ____ \\");
    puts("      |_____/_____\\____/|_|\\_\\_____/   |_|  |_|  \\_\\/_/    \\_\\");
    puts("");
    puts("        _____ _____ __  __ _    _ _            _______ ____  _____");
    puts("       / ____|_   _|  \\/  | |  | | |        /\\|__   __/ __ \\|  __ \\");
    puts("      | (___   | | | \\  / | |  | | |       /  \\  | | | |  | | |__) |");
    puts("       \\___ \\  | | | |\\/| | |  | | |      / /\\ \\ | | | |  | |  _  /");
    puts("       ____) |_| |_| |  | | |__| | |____ / ____ \\| | | |__| | | \\ \\");
    puts("      |_____/|_____|_|  |_|\\____/|______/_/    \\_\\_|  \\____/|_|  \\_\\");
    puts("");
    printf("      [w s Enter]\n");
    puts("");
    printf("      Start Simulation\n");
    printf("      Start Simulation (Not Perfect Maze)\n");
    printf("      Exit\n");
    puts("");
    printf("      Created by Novva (C) 2022\n");
}

bool showGenerate = false;
void menuShowGenerateMaze() {
	system("cls");
	int where = 1;
    bool valid = true;
	printMenu();
	setCursorPosition(6, 16);
	printf("Show Generate Maze Process\n");
	setCursorPosition(6, 17);
	printf("Don't Show Generate Maze Process      \n");
	setCursorPosition(6, 18);
	printf("Go Back\n");
	do {
        if (where == 1) {
        	setCursorPosition(4, 17);
        	printf(" ");
        	setCursorPosition(4, 18);
        	printf(" ");
            setCursorPosition(4, 16);
            printf("%c", char(16));
        }
        if (where == 2) {
        	setCursorPosition(4, 18);
        	printf(" ");
        	setCursorPosition(4, 16);
        	printf(" ");
            setCursorPosition(4, 17);
            printf("%c", char(16));
        }
        else if (where == 3) {
        	setCursorPosition(4, 16);
        	printf(" ");
        	setCursorPosition(4, 17);
        	printf(" ");
            setCursorPosition(4, 18);
            printf("%c", char(16));
        }
        char ch = getch();
        switch (ch) {
        case 'w':
            if (where != 1) where--;
            break;
        case 's':
            if (where != 3) where++;
            break;
        case 13:
            if (where == 1 || where == 2) {
            	if (where == 1) showGenerate = true;
                menuDijkstra();
                return;
            }
            else if (where == 3) {
            	system("cls");
            	printMenu();
                valid = false;
            }
        default:
            break;
        }
    } while (valid);
}

bool notPerfectMaze = false;
int main() {
	hidecursor();
    int where = 1;
    bool valid = true;
    printMenu();
    do {
        if (where == 1) {
        	setCursorPosition(4, 17);
        	printf(" ");
        	setCursorPosition(4, 18);
        	printf(" ");
            setCursorPosition(4, 16);
            printf("%c", char(16));
        }
        if (where == 2) {
        	setCursorPosition(4, 18);
        	printf(" ");
        	setCursorPosition(4, 16);
        	printf(" ");
            setCursorPosition(4, 17);
            printf("%c", char(16));
        }
        else if (where == 3) {
        	setCursorPosition(4, 16);
        	printf(" ");
        	setCursorPosition(4, 17);
        	printf(" ");
            setCursorPosition(4, 18);
            printf("%c", char(16));
        }
        char ch = getch();
        switch (ch) {
        case 'w':
            if (where != 1) where--;
            break;
        case 's':
            if (where != 3) where++;
            break;
        case 13:
            if (where == 1 || where == 2) {
            	if (where == 2) notPerfectMaze = true;
                menuShowGenerateMaze();
            }
            else if (where == 3) {
                valid = false;
            }
        default:
            break;
        }
    } while (valid);
    

    return 0;
}

struct Node {
    int x, y;

    Node(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

char maze[H+1][W+1];

struct Tile{
    Tile *prev;
    char symbol;
    char symbol_2;
    int x, y;
    int cost;
    int minDistance;
    bool visited;
}*myMaze[201][201];

Tile *construct(int y, int x, char symbol, char symbol_2){
    Tile *newTile = (Tile*)malloc(sizeof(Tile));
    newTile->y = y;
    newTile->x = x;
    newTile->symbol = symbol;
    newTile->symbol_2 = symbol_2;
    newTile->cost = 1;
    newTile->visited = false;
    newTile->minDistance = INT_MAX;
    return newTile;
}

struct Path{
    Tile *source;
    Tile *destination;
    double distance;

    //overload operator
    bool operator () (const Path* lhs, const Path* rhs) const{
        return lhs->distance > rhs->distance;
    }

    Path(Tile *source, Tile *destination, double distance){
        this->source = source;
        this->destination = destination;
        this->distance = distance;
    }

    Path(){
    }
};

int directionX[] = {0, 2, 0, -2};
int directionY[] = {-2, 0, 2, 0};

Tile *startTile;
Tile *finishTile;
Tile *currentDest;
Path *currentPath;
priority_queue<Path*, vector<Path*>, Path> priorityQueue;
stack<int> xStack;
stack<int> yStack;

const int directionsX[] = {0, 0, -1, 1};
const int directionsY[] = {-1, 1, 0, 0};

void initializeDijkstraMap() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            myMaze[i][j] = construct(i, j, maze[i][j], maze[i][j]);
        }
    }
}

void addNeighborsToQueue(Tile *tile){
    for (int i = 0; i < 4; i++){
        int newY = tile->y + directionsY[i];
        int newX = tile->x + directionsX[i];
        
        if(myMaze[newY][newX]->symbol != (char)219 && myMaze[newY][newX]->visited == false) {
            Tile *nextTile = myMaze[newY][newX];
            double newDistance = tile->minDistance + nextTile->cost;
            Path *newPath = new Path(tile, nextTile, newDistance);
            priorityQueue.push(newPath);
        }
    }
}

void printMap(int state) {
    for (int i = 0; i < H; i++) {
        printf("      ");
        for (int j = 0; j < W; j++) {
            if (myMaze[i][j]->symbol == 'a') {
                red();
                printf("%c", myMaze[i][j]->symbol_2);
                resetColor();
            }
            else if (myMaze[i][j]->symbol == 'w') {
                yellow();
                printf("%c", myMaze[i][j]->symbol_2);
                resetColor();
            }
            else if (myMaze[i][j]->symbol == 'o') {
                green();
                printf("%c", myMaze[i][j]->symbol_2);
                resetColor();
            }
            else printf("%c", myMaze[i][j]->symbol);
        }
        puts("");
    }
}

int minMove;
void backTrack(Tile *currTile, int move){
    if(currTile != startTile && currTile != finishTile){
        currTile->symbol = 'o';
        currTile->symbol_2 = 219;
        xStack.push(currTile->x);
        yStack.push(currTile->y);
    }

    if(currTile != startTile){
        backTrack(currTile->prev, move+1);
    }
    else {
        minMove = move;
    }
}

bool viewFullProcess = false;
void dijkstra() {
    while(!priorityQueue.empty() && finishTile->visited == false){
        currentPath = priorityQueue.top();
        priorityQueue.pop();

        currentDest = currentPath->destination;

        if(currentDest->visited == false){
            currentDest->minDistance = currentPath->distance;
            currentDest->prev = currentPath->source;
            currentDest->visited = true;
            if (currentDest != finishTile){
                if (viewFullProcess) {
                    currentDest->symbol = 'w';
                    currentDest->symbol_2 = 219;
                    setCursorPosition(currentDest->x+6, currentDest->y);
                    yellow();
                	printf("%c", 219);
                	resetColor();
                	Sleep(5);
                }
                else if (!viewFullProcess) {
                    currentDest->symbol = ' ';
                }
            }
            addNeighborsToQueue(currentDest);
        }

        delete currentPath;
    }

    while (!priorityQueue.empty()) {
        priorityQueue.pop();
    }
}

void initializeStartAndFinishTile(int state){
    bool validCoor = false;
    char X1, X2;
    int x1, x2;
    int Y1, Y2;
    int where = 1;
    system("cls");
    printMap(1);
    puts("");
    printf("      [w s Enter]\n");
    puts("");
    if (state == 1) {
		printf("      Randomize Start & Finish Point\n");
		printf("      Set Start & Finish Point\n");
        red();
        printf("      Start Simulation\n");
        resetColor();
        printf("      Reset Start & Finish Point\n");
        printf("      Go Back\n");
	}
	else if (state == 2) {
		red();
        printf("      Randomize Start & Finish Point\n");
        printf("      Set Start & Finish Point\n");
        resetColor();
        printf("      Start Simulation\n");
        printf("      Reset Start & Finish Point\n");
        printf("      Go Back\n");
	}
	else if (state == 3) {
		red();
        printf("      Randomize Start & Finish Point\n");
        printf("      Set Start & Finish Point\n");
        printf("      Start Simulation\n");
        resetColor();
        printf("      Reset Start & Finish Point\n");
        printf("      Go Back\n");
	}
	
    while (!validCoor) {
        if (where == 1) {
        	setCursorPosition(4, 23);
        	printf(" ");
        	setCursorPosition(4, 24);
        	printf(" ");
        	setCursorPosition(4, 25);
        	printf(" ");
        	setCursorPosition(4, 26);
        	printf(" ");
            setCursorPosition(4, 22);
            if (state == 2 || state == 3) red();
            printf("%c", char(16));
            resetColor();
        }
        else if (where == 2) {
        	setCursorPosition(4, 22);
        	printf(" ");
        	setCursorPosition(4, 24);
        	printf(" ");
        	setCursorPosition(4, 25);
        	printf(" ");
        	setCursorPosition(4, 26);
        	printf(" ");
            setCursorPosition(4, 23);
            if (state == 2 || state == 3) red();
            printf("%c", char(16));
            resetColor();
        }
        else if (where == 3) {
        	setCursorPosition(4, 22);
        	printf(" ");
        	setCursorPosition(4, 23);
        	printf(" ");
        	setCursorPosition(4, 25);
        	printf(" ");
        	setCursorPosition(4, 26);
        	printf(" ");
            setCursorPosition(4, 24);
            if (state == 1 || state == 3) red();
            printf("%c", char(16));
            resetColor();
        }
        else if (where == 4) {
        	setCursorPosition(4, 22);
        	printf(" ");
        	setCursorPosition(4, 23);
        	printf(" ");
        	setCursorPosition(4, 24);
        	printf(" ");
        	setCursorPosition(4, 26);
        	printf(" ");
            setCursorPosition(4, 25);
            printf("%c", char(16));
		}
		else if (where == 5) {
        	setCursorPosition(4, 22);
        	printf(" ");
        	setCursorPosition(4, 23);
        	printf(" ");
        	setCursorPosition(4, 24);
        	printf(" ");
        	setCursorPosition(4, 25);
        	printf(" ");
            setCursorPosition(4, 26);
            printf("%c", char(16));
		}
        char ch = getch();
        switch (ch) {
        case 'w':
            if (where != 1) where--;
            break;
        case 's':
            if (where != 5) where++;
            break;
        case 13:
            if (where == 1 && state == 1) {
            	setCursorPosition(6, 28);
            	printf("Loading...");
                int randNum1, randNum2;
                randNum1 = randNum2 = -1;
                
                bool validStart = false;
                do {
                    randNum1 = rand() % H;
                    randNum2 = rand() % W;
                    if (myMaze[randNum1][randNum2]->symbol != (char)219) {
                    	validStart = true;
                    }
                } while (!validStart);
                startY = randNum1;
                startX = randNum2;
                
                myMaze[startY][startX]->symbol = 'a';
                myMaze[startY][startX]->symbol_2 = 219;
                
                setCursorPosition(startX+6, startY);
		        red();
		        printf("%c", 219);
		        resetColor();
                Sleep(1000);
                
                bool validFinish = false;
                do {
                    randNum1 = rand() % H;
                    randNum2 = rand() % W;
                    if (myMaze[randNum1][randNum2]->symbol != (char)219) {
                        if (randNum1 != startY && randNum2 != startX) validFinish = true;
                    }
                } while (!validFinish);
                
                finishY = randNum1;
                finishX = randNum2;

                myMaze[finishY][finishX]->symbol = 'a';
                myMaze[finishY][finishX]->symbol_2 = 219;

                return initializeStartAndFinishTile(2);
            }
            else if (where == 2 && state == 1) {
            	int count = 1;
            	while (count <= 2) {
            		bool validPlace = false;
	            	int x = 7;
	            	int y = 1;
	            	system("cls");
	            	printMap(1);
	            	puts("");
	    			printf("      [w a s d Enter]\n");
	    			puts("");
	    			if (count == 1) printf("      Please choose your starting point! [Press Enter to commit]\n");
	    			else printf("      Please choose your finish point! [Press Enter to commit]\n");
	            	do {
		            	setCursorPosition(x, y);
		            	red();
				        printf("%c", 219);
				        resetColor();
	        			char c = getch();
	        			switch (c) {
	                    case 'w':
	                        if (myMaze[y-1][x-6]->symbol != (char)219) {
	                    		setCursorPosition(x, y);
	                        	if (y != startY || x != startX+6) printf(" ");
	                        	y--;
							}
	                        break;
	                    case 'a':
	                        if (myMaze[y][x-7]->symbol != (char)219) {
	                        	setCursorPosition(x, y);
	                        	if (y != startY || x != startX+6) printf(" ");
	                        	x--;
							}
	                        break;
	                    case 'd':
	                    	setCursorPosition(x, y);
	                        if (myMaze[y][x-5]->symbol != (char)219) {
	                        	setCursorPosition(x, y);
	                        	if (y != startY || x != startX+6) printf(" ");
	                        	x++;
							}
	                        break;
	                    case 's':
	                        if (myMaze[y+1][x-6]->symbol != (char)219) {
	                        	setCursorPosition(x, y);
	                        	if (y != startY || x != startX+6) printf(" ");
	                        	y++;
							}
	                        break;
	                    case 13:
	                    	if (count == 1) {
		                    	startY = y;
				                startX = x-6;
				                myMaze[startY][startX]->symbol = 'a';
				                myMaze[startY][startX]->symbol_2 = 219;
				                validPlace = true;
							}
							else if (count == 2) {
								if (startY == y && startX == x-6) {
									setCursorPosition(6, 22);
									printf("You can't set finish point to be the same place as starting point!");
								}
								else {
									finishY = y;
									finishX = x-6;
									myMaze[finishY][finishX]->symbol = 'a';
					                myMaze[finishY][finishX]->symbol_2 = 219;
					                validPlace = true;	
								}
							}
			            }
					} while (!validPlace);
					count++;
				}
				return initializeStartAndFinishTile(2);
			}
            else if (where == 3 && state == 2) {
                int cursor = 1;
                bool loop = true;
                system("cls");
                printMap(1);
                puts("");
                printf("      [w s Enter]\n");
                puts("");
                printf("      View Full Process\n");
                printf("      Show only best route\n");
                printf("      Go Back\n");
                do {
                	if (cursor == 1) {
			        	setCursorPosition(4, 23);
			        	printf(" ");
			        	setCursorPosition(4, 24);
			        	printf(" ");
			            setCursorPosition(4, 22);
			            printf("%c", char(16));
			        }
			        else if (cursor == 2) {
			        	setCursorPosition(4, 22);
			        	printf(" ");
			        	setCursorPosition(4, 24);
			        	printf(" ");
			            setCursorPosition(4, 23);
			            printf("%c", char(16));
			        }
			        else if (cursor == 3) {
			        	setCursorPosition(4, 22);
			        	printf(" ");
			        	setCursorPosition(4, 23);
			        	printf(" ");
			            setCursorPosition(4, 24);
			            printf("%c", char(16));
			        }
			        char c = getch();
                    switch (c) {
                    case 'w':
                        if (cursor != 1) cursor--;
                        break;
                    case 's':
                        if (cursor != 3) cursor++;
                        break;
                    case 13:
                    	if (cursor == 1) viewFullProcess = true;
                    	else if (cursor == 2) viewFullProcess = false;
                    	else if (cursor == 3) {
                    		system("cls");
            				printMenu();
            				return initializeStartAndFinishTile(2);
						}
                        loop = false;
                        break;
                    }
                    
                } while (loop);

                minMove = 0;
                startTile = myMaze[startY][startX];
                startTile->symbol = 'a';
                startTile->symbol_2 = 219;
                startTile->visited = true;
                startTile->minDistance = 0;
                addNeighborsToQueue(startTile);

                finishTile = myMaze[finishY][finishX];
                finishTile->symbol = 'a';
                finishTile->symbol_2 = 219;

                dijkstra();
                backTrack(finishTile, 0);
                while (!xStack.empty()) {
                	int xCoor = xStack.top();
                	xStack.pop();
                	int yCoor = yStack.top();
                	yStack.pop();
                	setCursorPosition(xCoor+6, yCoor);
			        green();
			        printf("%c", 219);
			        resetColor();
			        Sleep(20);
				}
                return initializeStartAndFinishTile(3);
            }
            else if (where == 4) {
            	initializeDijkstraMap();
            	startY = startX = finishY = finishX = 0;
            	return initializeStartAndFinishTile(1);
			}
            else if (where == 5) {
            	notPerfectMaze = false;
            	showGenerate = false;
            	system("cls");
            	printMenu();
                return;
            }
        default:
            break;
        }
    }
    
}

void initializeMap() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            maze[i][j] = 219;
        }
    }
}

void printMaze() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", maze[i][j]);
        }
        puts("");
    }
}

void notPerfectGenerateMaze() {
	for (int i = 1; i < H-1; i+=2) {
    	int count = 0;
    	for (int j = 1; j < W-1; j++) {
    		if (maze[i][j] == (char)219 && maze[i][j-1] == ' ' && maze[i][j+1] == ' ') {
    			maze[i][j] = ' ';
    			setCursorPosition(j + 6, i);
	        	printf(" ");
	        	Sleep(10);
	        	count++;
	        	j += 16;
    			if (count == 6) break;
			}
		}
		printf("\n");
	}
	
	for (int i = 1; i < W-1; i+=15) {
    	int count = 0;
    	for (int j = 1; j < H-1; j++) {
    		if (maze[j][i] == (char)219 && maze[j][i-1] == ' ' && maze[j][i+1] == ' ') {
    			maze[j][i] = ' ';
    			setCursorPosition(i+6, j);
	        	printf(" ");
	        	Sleep(10);
	        	count++;
	        	j += 3;
    			if (count == 5) break;
			}
		}
		printf("\n");
	}
}

void generateMaze() {
    vector<Node> deleteNode;
    bool visited[H][W] = {false};
    deleteNode.push_back(Node(W/2 + 1, H/2));

    bool first = true;
    while (deleteNode.size() > 0) {
        Node curr = deleteNode.at(0);
        deleteNode.erase(deleteNode.begin());

        if (visited[curr.y][curr.x]) continue;
        visited[curr.y][curr.x] = true;

        //delete node di titik sekarang
        maze[curr.y][curr.x] = ' ';
        
        if (showGenerate) {
	        setCursorPosition(curr.x+6, curr.y);
	        printf(" ");
	        Sleep(10);	
		}

        int randNeighbor;
        bool valid = true;
        
        if (!first) {
            do {
                randNeighbor = rand() % 4;
                valid = curr.x - directionX[randNeighbor] >= 0 &&
                        curr.x - directionX[randNeighbor] < W &&
                        curr.y - directionY[randNeighbor] >= 0 &&
                        curr.y - directionY[randNeighbor] < H &&
                        maze[curr.y - directionY[randNeighbor]][curr.x - directionX[randNeighbor]] == ' ';
            } while (!valid);
            maze[curr.y - (directionY[randNeighbor] / 2)][curr.x - (directionX[randNeighbor] / 2)] = ' ';
            
            if (showGenerate) {
	            setCursorPosition(curr.x - (directionX[randNeighbor] / 2) + 6, curr.y - (directionY[randNeighbor] / 2));
		        printf(" ");
		        Sleep(10);	
			}
        }

        //masukkan node2 sekitar ke list
        for (int i = 0; i < 6; i++) {
        	randNeighbor = rand() % 4;
            if  (curr.x - directionX[randNeighbor] >= 0 && curr.x - directionX[randNeighbor] < W && curr.y - directionY[randNeighbor] >= 0 && curr.y - directionY[randNeighbor] < H) {
                deleteNode.push_back(Node(curr.x - directionX[randNeighbor], curr.y - directionY[randNeighbor]));
            }
        }
        first = false;
    }
}

void printMazeMap() {
	for (int i = 0; i < H; i++) {
    	printf("      ");
    	for (int j = 0; j < W; j++) {
    		printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

void menuDijkstra() {
    system("cls");

    srand(time(0));
    initializeMap();
    if (showGenerate) printMazeMap();
    generateMaze();
    if (notPerfectMaze) notPerfectGenerateMaze();

    initializeDijkstraMap();

    initializeStartAndFinishTile(1);
}
