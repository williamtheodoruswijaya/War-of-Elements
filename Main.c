#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TABLE_SIZE 26 // based on alpabet

struct userData{
	char username[51];
	char password[21];
	int score;
	struct userData* prev;
	struct userData* next;
}*head[TABLE_SIZE], *tail[TABLE_SIZE];

void mainMenu(char username[], int score){
	clearScreen();
	printf("Welcome, %s...\n\n", username);
	puts("1. Play");
	puts("2. View Score");
	puts("3. Exit");
}

int main(){
	int loop = 1, i;
	while(loop == 1){
		clearScreen();
    	puts(" W                  .__. .__.      ");
    	puts("[ ]                 |::| |::|           ");
    	puts(" E          ._.     |::| |::|   ._.     ");
    	puts(" |\\         |:| ._. |::| |::|   |/|     ");
    	puts("  \\ \\|/     |:|_|/| |::| |::|_  |/|     ");
    	puts("  |-( )-    |:|\"|/|_|::| |::|\\|_|/| _   ");
    	puts("  | V L     |:|\"|/|||::| |::|\\|||/||:|  ");
    	puts("  \\    `  ___   ~~~~~~~~~~~~~~~~~~~~~~~");
    	puts("  \\    `  ___   ~~~~~~~~~~~~~~~~~~~~~~~");
    	puts("========================================");
    	puts("\n");
    	puts("Battle of New York\n");
    	puts("1. Login");
    	puts("2. Sign up");
    	puts("3. Exit");
    	printf(">> ");
    	int operation;
    	scanf("%d", &operation);
    	switch(operation){
        	case 1:
				loginMenu();
				getchar();
				getchar();
            	break;
        	case 2:
				signUpMenu();
				getchar();
				getchar();
            	break;
        	case 3:
            	clearScreen();
            	char thankYou[] = "Thank you for playing!";
            	for(i = 0; thankYou[i] != '\0'; i++){
                	printf("%c", thankYou[i]);
                	usleep(100000);
            	}
				printf("\n");
            	loop = 0;
            	break;
        	default:
            	break;
   		}
	}
    return 0;
}

void loginMenu(){
	clearScreen();
	char username[51];
	char password[21];
	char userPassword[21];
	int valid, score;

	do{
		printf("Username: ");
		scanf(" %[^\n]", username);
		readFile(); // mindahin isi file ke hashTable
		// Accessing hash table based on the first letter
		int index = username[0] - 'a';
		struct userData* curr = head[index];
		valid = 0;
		while(curr != NULL){
			if(strcmp(curr->username, username) == 0){
				score = curr->score;
				strcpy(userPassword, curr->password); 
				valid = 1;
				break;
			}
			curr = curr->next;
		}
		if(valid == 0){
			printf("\033[1;31mUsername is not available!\033[0m\ ");
			printf("\n");
		}
	}while(valid == 0);

	do{
		printf("Password: ");
		scanf(" %[^\n]", password);
		if(strcmp(password, userPassword) != 0){
			printf("\033[1;31mWrong password!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		else{
			valid = 1;
		}
	}while(valid == 0);
	mainMenu(username, score);
}

void signUpMenu(){
	clearScreen();
	char username[51];
	char password[21];
	int valid, i, length;

	do{
		valid = 1;
		length = 0;
		printf("Username: ");
		scanf(" %[^\n]", username);
		if(strcmp(username, "") == 0){
			printf("\033[1;31mUsername can't be empty!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		if(username[0] >= '0' && username[0] <= '9'){
			printf("\033[1;31mUsername first character can't be a number!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		for(i = 0; username[i] != '\0'; i++){
			if(username[i] == ' '){
				printf("\033[1;31mUsername must not contain space!\033[0m\ ");
				printf("\n");
				valid = 0;
				break;
			}
			if(username[i] >= 'A' && username[i] <= 'Z'){
				printf("\033[1;31mUsername must not contain any CAPITAL letter!\033[0m\ ");
				printf("\n");
				valid = 0;
				break;
			}
		}
		for(i = 0; username[i] != '\0'; i++){
			length++;
		}
		if(length < 8 || length > 50){
			printf("\033[1;31musername length must be between 8-50 characters!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		printf("\n");
	}while(valid == 0);

	do{
		valid = 1;
		length = 0;
		printf("Password: ");
		scanf(" %[^\n]", password);
		if(strcmp(password, "") == 0){
			printf("\033[1;31mPassword can't be empty!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		for(i = 0; password[i] != '\0'; i++){
			if(password[i] == ' '){
				printf("\033[1;31mPassword must not contains space!\033[0m\ ");
				printf("\n");
				valid = 0;
				break;
			}
		}
		for(i = 0; password[i] != '\0'; i++){
			length++;
		}
		if(length < 5 || length > 20){
			printf("\033[1;31mPassword length must be between 5-20 characters!\033[0m\ ");
			printf("\n");
			valid = 0;
		}
		printf("\n");
	}while(valid == 0);

	clearScreen();
	printf("Are you sure? [Y/N] - Case sensitive!\n");
	printf(">> ");
	char operation;
	scanf(" %c", &operation);
	if(operation == 'Y'){
		writeFile(username, password, 0);
		char messages[] = "\033[1;32mAccount Successfully being made!\nRedirecting back to Main Menu!...\033[0m ";
		for(i = 0; messages[i] != '\0'; i++){
			printf("%c", messages[i]);
			usleep(50000);
		}
	}
	else if(operation == 'N'){
		char messages[] = "Account deleted!...\nRedirecting back to Main Menu!...";
		for(i = 0; messages[i] != '\0'; i++){
			printf("%c", messages[i]);
			usleep(50000);
		}
	}
	else{
		char messages[] = "\033[1;31mError! Operation Canceled!...\033[0m\ ";
		for(i = 0; messages[i] != '\0'; i++){
			printf("%c", messages[i]);
			usleep(50000);
		}
	}
	return;
}

void insertData(char username[], char password[], int score){
	struct userData* node = (struct userData*)malloc(sizeof(struct userData));
	strcpy(node->username, username);
	strcpy(node->password, password);
	node->score = score;
	node->prev = NULL;
	node->next = NULL;

	int index = username[0] - 'a';
	//pushTail
	if(head[index] == NULL){
		head[index] = node;
		tail[index] = node;
	}
	else{
		node->prev = tail[index];
		tail[index]->next = node;
		tail[index] = node;
	}
}

void clearScreen(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void writeFile(char username[], char password[], int score){
	// storing data into File
	FILE* inputFile = fopen("playerData.txt", "a");
	if(inputFile == NULL){
		printf("\033[1;31mWARNING! ERROR IN FILE!\033[0m\ ");
		printf("\n");
		exit(1);
	}
	fprintf(inputFile, "%s#%s#%d\n", username, password, score);
	fclose(inputFile);
	return;
} 

void readFile(){
	// ini masukin data dari file ke hash table
	FILE* outputFile = fopen("playerData.txt", "r");
	if(outputFile == NULL){
		printf("\033[1;31mWARNING! ERROR IN FILE!\033[0m\ ");
		printf("\n");
		exit(1);
	}

	char username[51];
	char password[21];
	int score;
	while(fscanf(outputFile, "%[^#]#%[^#]#%d\n", username, password, &score) == 3){
		insertData(username, password, score);
	}
	fclose(outputFile);
}