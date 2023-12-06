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
	int loop = 1;
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
				newMain();
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

	for(i = 0; i < Arraysize; i++){
		for(j = 0; j < Arraysize-1-i; j++){
			if(arr[j]->score < arr[j+1]->score){
				struct userData* temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	} // Ini BubbleSort buat sorting array berdasarkan score

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
void newMain(){

//Function untuk attack
int performAttack(int attacker_atk, int defender_def) {
    int damage = attacker_atk - defender_def;
    if (damage < 0) {
        damage = 0;
    }
    return damage;
}

//Function untuk giliran player
void playerTurn(struct ClassPlayer *player, struct ClassEnemy *enemy) {
    printf("%s's turn!\n", player->name);
    int choice;
    printf("Choose your action:\n");
    printf("1. Attack\n2. Defend\n");
    scanf("%d", &choice);

    if (choice == 1) { // Attack
        int mpGain = rand() % 11 + 5;
        player->mp += mpGain;
        printf("%s gains %d magic points!\n", player->name, mpGain);
	//magic attack
        if (player->mp >= 100) { // Use magic points if >= 100
            int damage = performAttack(player->atk + 10, enemy->def);
            printf("%s uses magic attack on %s and deals %d damage!\n", player->name, enemy->name, damage);
            enemy->hp -= damage;
            player->mp = 0;
        } else {
            // regular attack
            int damage = performAttack(player->atk, enemy->def);
            printf("%s attacks %s and deals %d damage!\n", player->name, enemy->name, damage);
            enemy->hp -= damage;
        }
    } else if (choice == 2) { // Defend
        int mpGain = rand() % 11 + 5;
        player->mp += mpGain;
        printf("%s gains %d magic points while defending!\n", player->name, mpGain);

        printf("%s defends!\n", player->name);
        // Increase player's defense temporarily
        player->def += 5;
    }
}

//Function untuk giliran enemy
void enemyTurn(struct ClassEnemy *enemy, struct ClassPlayer players[], int numPlayers) {
    printf("%s's turn!\n", enemy->name);

    // Enemy randomly chooses to attack or defend
    int choice = rand() % 2;

    if (choice == 0) { // Attack
        int targetPlayer = rand() % numPlayers;
        int mpGain = rand() % 11 + 5;
        enemy->mp += mpGain;
        printf("%s gains %d magic points!\n", enemy->name, mpGain);

        if (enemy->mp >= 100) { // Use magic points if >= 100
            // Perform strong attack
            int damage = performAttack(enemy->atk + 10, players[targetPlayer].def);
            printf("%s uses magic attack on %s and deals %d damage!\n", enemy->name, players[targetPlayer].name, damage);
            players[targetPlayer].hp -= damage;

            // Reset enemy's MP
            enemy->mp = 0;
        } else {
            // Perform regular attack
            int damage = performAttack(enemy->atk, players[targetPlayer].def);
            printf("%s attacks %s and deals %d damage!\n", enemy->name, players[targetPlayer].name, damage);
            players[targetPlayer].hp -= damage;
        }
    } else if (choice == 1) { // Defend
        // Increment enemy's MP by a random amount between 5 to 15
        int mpGain = rand() % 11 + 5;
        enemy->mp += mpGain;
        printf("%s defends and gains %d magic points!\n", enemy->name, mpGain);

        printf("%s defends!\n", enemy->name);
        // Increase enemy's defense temporarily
        enemy->def += 5;
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Initialize players
    struct ClassPlayer players[7] = {
        {1, "Player 1", "Fire", 100, 0, 20, 10},
        {2, "Player 2", "Water", 120, 0, 18, 12},
        {3, "Player 3", "Earth", 90, 0, 22, 8},
        {4, "Player 4", "Fire", 110, 0, 21, 11},
        {5, "Player 5", "Water", 105, 0, 19, 13},
        {6, "Player 6", "Earth", 95, 0, 23, 9},
        {7, "Player 7", "Fire", 115, 0, 20, 10}
    };

    // Initialize enemy
    struct ClassEnemy enemy = {1, "Enemy", "Water", 150, 0, 25, 15};

    printf("Welcome to the Turn-Based Battle Game!\n");

    int currentPlayer = 0;
    int turn = 1;
    int numPlayers = 7;

    while (numPlayers > 0 && enemy.hp > 0) {
        printf("\nTurn %d\n", turn);

        // Player's turn
        if (players[currentPlayer].hp > 0) {
            playerTurn(&players[currentPlayer], &enemy);
        }

        // Enemy's turn
        if (enemy.hp > 0) {
            enemyTurn(&enemy, players, numPlayers);
        }

        // Display current health of players and enemy
        printf("Enemy's Health: %d\n", enemy.hp);
        printf("Players' Health: ");
        int activePlayers = 0;
        for (int i = 0; i < 7; ++i) {
            if (players[i].hp > 0) {
                printf("%s: %d | ", players[i].name, players[i].hp);
                activePlayers++;
            }
        }
        printf("\n");

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % 7;

        turn++;
    }

    // Determine the winner
    if (enemy.hp <= 0) {
        printf("\nPlayers win!\n");
    } else {
        printf("\nEnemy wins!\n");
    }

    return 0;
}
}
