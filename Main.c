#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void mainMenu(char username[], int score);
void tutorialMenu();
void loginMenu();
void signUpMenu();
void insertData(char username[], char password[], int score, int character);
void clearScreen();
void writeFile(char username[], char password[], int score, int character);
void readFile();
void popAll();
void searchUsername(char username[]);
void merge(struct userData* arr[], int left, int mid, int right);
void mergeSort(struct userData* arr[], int left, int right);
void viewScore();
void updateScore();
void newMain(char username[], int score);
void chooseCharacter(char username[], int score);
void updateCharacter(int ID, char username[], int score);
void startGame(char username[], int score);

#define TABLE_SIZE 26 // based on alpabet

struct userData{
	char username[51];
	char password[21];
	int score;
	int character;
	struct userData* prev;
	struct userData* next;
}*head[TABLE_SIZE], *tail[TABLE_SIZE];

struct ClassPlayer{
	int ID;
	char name[51];
	char elements[51];
	int hp;
	int mp;
	int atk;
	int def;
};

struct ClassEnemy{
	int ID;
	char name[51];
	char elements[51];
	int hp;
	int mp;
	int atk;
	int def;
};

void mainMenu(char username[], int score){
	int loop = 1, i;
	while(loop == 1){
		clearScreen();
		printf("Welcome, %s...\n\n", username);
		puts("1. Play");
		puts("2. Tutorial");
		puts("3. View Score");
		puts("4. Exit");
		printf(">> ");
		int operation;
		scanf("%d", &operation);
		switch(operation){
			case 1:
				newMain(username, score);
				getchar();
				break;
			case 2:
				tutorialMenu();
				getchar();
				break;
			case 3:
				viewScore();
				getchar();
				break;
			case 4:
				updateScore(); // update score terbaru dari hashTable ke file
				popAll(); // hapus semua isi dari hashMap biar ga nimpa
				clearScreen();
            	char messages[] = "\033[1;31mExitting...\033[0m\ ";
            	for(i = 0; messages[i] != '\0'; i++){
                	printf("%c", messages[i]);
                	usleep(100000);
            	}
				printf("\n");
            	loop = 0;
				break;
			default:
				break;
		}
	}
}

void tutorialMenu(){
	clearScreen();
	int i;
	char messages[] = "Welcome to the tutorial!\nI'm Rydia, the tutorial bot!\nToday, I will teach you how to play this game!\n\n";
	for(i = 0; messages[i] != '\0'; i++){
		printf("%c", messages[i]);
		usleep(75000);
	}
	printf("\nPress Enter to continue!\n");
	getchar();
}

void loginMenu(){
	clearScreen();
	char username[51];
	char password[21];
	char userPassword[21];
	int valid, score, character;
	printf("Enter 0 to return to cancel!\n\n");
	
	do{
		printf("Username: ");
		scanf(" %[^\n]", username);
		if(strcmp(username, "0") == 0){
			return;
		}
		readFile(); // mindahin isi file ke hashTable
		// Accessing hash table based on the first letter
		int index = username[0] - 'a';
		struct userData* curr = head[index];
		valid = 0;
		while(curr != NULL){
			if(strcmp(curr->username, username) == 0){
				score = curr->score;
				character = curr->character;
				strcpy(userPassword, curr->password); 
				valid = 1;
				break;
			}
			curr = curr->next;
		}
		if(valid == 0){
			popAll();
			printf("\033[1;31mUsername is not available!\033[0m\ ");
			printf("\n");
		}
	}while(valid == 0);

	do{
		printf("Password: ");
		scanf(" %[^\n]", password);
		if(strcmp(password, "0") == 0){
			return;
		}
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
	printf("Enter 0 to return to cancel!\n\n");
	do{
		valid = 1;
		length = 0;
		printf("Username: ");
		scanf(" %[^\n]", username);
		if(strcmp(username, "0") == 0){
			return;
		}
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
		if(strcmp(password, "0") == 0){
			return;
		}
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
		writeFile(username, password, 0, 0);
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

void insertData(char username[], char password[], int score, int character){
	struct userData* node = (struct userData*)malloc(sizeof(struct userData));
	strcpy(node->username, username);
	strcpy(node->password, password);
	node->score = score;
	node->character = character;
	node->prev = NULL;
	node->next = NULL;

	int index = username[0] - 'a';
	// ini pushTail
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

void writeFile(char username[], char password[], int score, int character){
	// storing data into File
	FILE* inputFile = fopen("playerData.txt", "a");
	if(inputFile == NULL){
		printf("\033[1;31mWARNING! ERROR IN FILE!\033[0m\ ");
		printf("\n");
		exit(1);
	}
	fprintf(inputFile, "%s#%s#%d#%d\n", username, password, score, character);
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
	int character;
	while(fscanf(outputFile, "%[^#]#%[^#]#%d#%d\n", username, password, &score, &character) == 4){
		insertData(username, password, score, character);
	}
	fclose(outputFile);
	return;
}

void popAll(){
	int i;
	for(i = 0; i < TABLE_SIZE; i++){
		while(head[i] != NULL){
			if(head[i] == tail[i]){
				struct userData* temp = head[i];
				head[i] = NULL;
				tail[i] = NULL;
				free(temp);
			}
			else{
				struct userData* temp = head[i];
				head[i] = head[i]->next;
				temp->next = NULL;
				head[i]->prev = NULL;
				free(temp);
			}
		}
	}
	return;
}

void searchUsername(char username[]){
	clearScreen();
	int index = username[0] - 'a';
	struct userData* curr = head[index];

	int found = 0;
	while(curr != NULL){
		if(strcmp(username, curr->username) == 0){
			printf("Username: %s\n", curr->username);
			printf("Score: %d\n", curr->score);
			found = 1;
			break;
		}
		curr = curr->next;
	}
	if(found == 0){
		printf("There is no username with that name!\n");
	}
	printf("\nPress ENTER to continue!\n");
	getch();
	return;
}

void merge(struct userData* arr[], int left, int mid, int right){
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	struct userData *L[n1], *R[n2];

	for(i = 0; i < n1; i++){
		L[i] = arr[left + i];
	}
	for(j = 0; j < n2; j++){
		R[j] = arr[mid + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	while(i < n1 && j < n2){
		if(L[i]->score >= R[j]->score){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(struct userData* arr[], int left, int right){
	if(left < right){
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void viewScore(){
	int i = 0, j = 0;
	clearScreen();

	int Arraysize = 0;
	for(i = 0; i < TABLE_SIZE; i++){
		struct userData* curr = head[i];
		if(head[i] != NULL){
			while(curr != NULL){
				Arraysize++;
				curr = curr->next;
			}
		}
	} // Ini buat dapet size array

	struct userData* arr[Arraysize];
	for(i = 0; i < TABLE_SIZE; i++){
		struct userData* curr = head[i];
		if(head[i] != NULL){
			while(curr != NULL){
				arr[j] = curr;
				j++;
				curr = curr->next;
			}
		}
	} // Ini buat mindahin semua hash table ke dalam satu array

	mergeSort(arr, 0, Arraysize - 1); // Ini buat sort array berdasarkan score

	int loop = 1;
	do{
		clearScreen();
		printf("==========================================\n");
		printf("|| Score   || Username                  ||\n");
		printf("==========================================\n");
		for(i = 0; i < Arraysize; i++){
			printf("|| %-8d||%-27s||\n", arr[i]->score, arr[i]->username);
			printf("==========================================\n");
		}
		printf("\nEnter the username you want to search: [enter 0 to exit!]\n");
		printf(">> ");
		char username[51];
		scanf(" %[^\n]", username);
		if(strcmp(username, "0") == 0){
			loop = 0;
		}
		else{
			searchUsername(username);
			getchar();
		}
	} while(loop == 1);
	// Ini buat liat score leaderboard
	return;
}

// Update score terbaru dari hashTable ke file
// Jadi hashTablenya harus udah di update juga
void updateScore(){
	// ini buat update score dengan rewrite ulang file
	int i;
	FILE* inputFile = fopen("playerData.txt", "w");
	if(inputFile == NULL){
		printf("\033[1;31mWARNING! ERROR IN FILE!\033[0m\ ");
		printf("\n");
		exit(1);
	}
	for(i = 0; i < TABLE_SIZE; i++){
		struct userData* curr = head[i];
		while(curr != NULL){
			fprintf(inputFile, "%s#%s#%d#%d\n", curr->username, curr->password, curr->score, curr->character);
			curr = curr->next;
		}
	}
	fclose(inputFile);
}

/* New Main buat fungsi utama game
Anggep aja int main kosong (~Will) */
void newMain(char username[], int score){
	int i;
	if(score == 0){
		chooseCharacter(username, score);
	}
	clearScreen();
	char messages[] = "Are you ready for the battle? [Y/N]\n";
	for(i = 0; messages[i] != '\0'; i++){
		printf("%c", messages[i]);
		usleep(50000);
	}
	printf(">> ");
	char operation;
	scanf(" %c", &operation);
	if(operation == 'Y'){
		startGame(username, score);
	}
	else if(operation == 'N'){
		char messages[] = "Redirecting back to Main Menu!...\n";
		for(i = 0; messages[i] != '\0'; i++){
			printf("%c", messages[i]);
			usleep(50000);
		}
	}
	else{
		char messages[] = "Error! Operation Canceled!...\n";
		for(i = 0; messages[i] != '\0'; i++){
			printf("%c", messages[i]);
			usleep(50000);
		}
	}
}

void chooseCharacter(char username[], int score){
	int valid, i, j;
	int id;
	do{
		valid = 1;
		clearScreen();
		printf("Choose your character!\n");
		printf("======================\n");
		printf("1. Chocobo (Pyshical)\n");
		printf("2. Shiva (Ice)\n");
		printf("3. Ramuh (Thunder)\n");
		printf("4. Ifrit (Fire)\n");
		printf("5. Leviathan (Water)\n");
		printf("6. Titan (Earth)\n");
		printf("7. Bahamut (Dark)\n\n");
		printf(">> ");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
            case 1:
                // Chocobo
				clearScreen();
                id = 1;
                updateCharacter(id, username, score);
				char messages1[] = "\033[33;1mChocobo is now your main character\033[0m ";
                for(i = 0; messages1[i] != '\0'; i++){
					printf("%c", messages1[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 2:
                // Shiva
				clearScreen();
                id = 2;
                updateCharacter(id, username, score);
				char messages2[] = "\033[36;1mShiva is now your main character\033[0m ";
                for(i = 0; messages2[i] != '\0'; i++){
					printf("%c", messages2[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 3:
                // Ramuh
				clearScreen();
                id = 3;
                updateCharacter(id, username, score);
				char messages3[] = "\033[35;1mRamuh is now your main character\033[0m ";
                for(i = 0; messages3[i] != '\0'; i++){
					printf("%c", messages3[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 4:
                // Ifrit
				clearScreen();
                id = 4;
                updateCharacter(id, username, score);
				char messages4[] = "\033[41;1mIfrit is now your main character\033[0m ";
				for(i = 0; messages4[i] != '\0'; i++){
					printf("%c", messages4[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 5:
                // Leviathan
				clearScreen();
                id = 5;
                updateCharacter(id, username, score);
				char messages5[] = "\033[34;1mLeviathan is now your main character\033[0m ";
				for(i = 0; messages5[i] != '\0'; i++){
					printf("%c", messages5[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 6:
                // Titan
				clearScreen();
                id = 6;
                updateCharacter(id, username, score);
				char messages6[] = "\033[32;1mTitan is now your main character\033[0m ";
				for(i = 0; messages6[i] != '\0'; i++){
					printf("%c", messages6[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            case 7:
                // Bahamut
				clearScreen();
                id = 7;
                updateCharacter(id, username, score);
				char messages7[] = "\033[30;47;1mBahamut is now your main character\033[0m ";
				for(i = 0; messages7[i] != '\0'; i++){
					printf("%c", messages7[i]);
					usleep(50000);
				}
				printf("\n");
                break;
            default:
                valid = 0;
                break;
        }
	}while(valid == 0);
}

void updateCharacter(int ID, char username[], int score){
	int index = username[0] - 'a';
	struct userData* curr = head[index];
	while(curr != NULL){
		if(strcmp(username, curr->username) == 0){
			curr->character = ID;
			curr->score = score;
			break;
		}
		curr = curr->next;
	}
}

void startGame(char username[], int score){
	clearScreen();
	char messages[] = "Commencing battle unit!...\n";
	srand(time(NULL));
	int randomNum = 1 + rand() % (7 - 1 + 1);
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
    	puts("\x1b[36mWar of Elements: Eclipsia Wars\x1b[0m\n");
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
            	break;
        	case 2:
				signUpMenu();
				getchar();
            	break;
        	case 3:
            	clearScreen();
            	char thankYou[] = "\x1b[33mThank you for playing!\x1b[0m";
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
