#define TABLE_SIZE 20
#define CHUNK_SIZE 1000
#define STRING_SIZE 100
#define QUERYAND_SIZE 9
#define QUERYOR_SIZE 8
#define QUERY_SIZE 6
#define STATS_SIZE 6
#define LOAD_SIZE 5
#define EMPTY_KEY 0
#define WRONG_FORMAT -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
	int num; 
	struct node *next;
}node;

typedef struct node number;

struct inverse {
	char *word;
	int df;
	number *list;
	struct inverse *next;
}inverse;

typedef struct inverse index;

char* removeSpace(int num, char *input);
char editChar(char c);
char *toLowerString(char *string);
int format(char chunk[]);
int getCommand(char *input);
unsigned int h(char *string);
index *insertToTable(index *table, char chunk[]);
index *initTable(index *table);
char *getNextString(char *input);
void printTable(index *table);
void query(index *table, char *word);
void stats(index *table, char *word);

int main() {
	
	FILE *fptr;
	index *table = initTable(table);
	char chunk[CHUNK_SIZE];
	char* input = malloc (sizeof(char) * STRING_SIZE);
	char* string = malloc (sizeof(char) * STRING_SIZE);
	
	do {
		printf("$> ");
		fgets(input, STRING_SIZE, stdin);
		switch(getCommand(input)) {
			case 1:
				fptr = fopen(getNextString(input), "r");
				if(fptr == NULL) {
	        		printf("\nFile not found!\n");
	        		break;
	    		}
	    		else {
					char chunk[CHUNK_SIZE];
					while(fgets(chunk, sizeof(chunk), fptr) != NULL) {
						table = insertToTable(table, chunk);
					}
					fclose(fptr);
					printTable(table);
					printf("\nFile loaded and indexed!\n");
				}
				break;
			case 2:
				query(table, toLowerString(getNextString(input)));
				break;
			case 3:
				stats(table, toLowerString(getNextString(input)));
				break;
			case 4:
				string = toLowerString(getNextString(input));
				printf("%s\n", string);
				string = toLowerString(getNextString(input));
				printf("%s\n", string);
				break;
			case 5:
				break;
			default:
				printf("\nWrong Input!\n");
				break;
		}
		printf("\n");
	} while(1);
	return 0;
}

char *getNextString(char *input) {
	int i, k = 0, size = 0;
	char* string = malloc (sizeof(char) * STRING_SIZE);
	for(i = 0; input[i] != '\0'; i++) {
		if(input[i] == 32) {
			break;
		}
		size++;
	}
	input = removeSpace(size - 1, input); 
	for(i = 0; i < STRING_SIZE; i++) string[i] = '\0';
	for(i = 0; i < STRING_SIZE; i++) {
		if(input[i] == '\n') break;
			string[i] = input[i];
		}
	return string;
}

int getCommand(char *input) {
	int compare = 0;
	char *string = malloc (sizeof(char) * STRING_SIZE);
	string = "load ";
	compare = strncmp(input, string, LOAD_SIZE);
	if(compare == 0) return 1;
	string = "query ";
	compare = strncmp(input, string, QUERY_SIZE);
	if(compare == 0) return 2;
	string = "stats ";
	compare = strncmp(input, string, STATS_SIZE);
	if(compare == 0) return 3;
	string = "queryAND ";
	compare = strncmp(input, string, QUERYAND_SIZE);
	if(compare == 0) return 4;
	string = "queryOR ";
	compare = strncmp(input, string, QUERYOR_SIZE);
	if(compare == 0) return 5;
	return 0;
}

char* removeSpace(int num, char *input) {
	do {
		num++;
		if( input[num] != 32 ) break;		
	} while(num < STRING_SIZE - 1);		
	return (input + num);
}

char editChar(char c) {
	if(c >= 65 && c <= 90) return tolower(c);
	if(c >= 97 && c <= 122) return c;
	if(c == 32) return c;
	if(c == '\0') return c;
	return 32;
}

int format(char chunk[CHUNK_SIZE]) {
	int i, j, k, find, number, correct;
	for(i = 0; i < chunk[i] != '\0'; i++) {
		if(chunk[i] == 58) {
			find = i;
			char *charNum = malloc (sizeof(char) * STRING_SIZE);
			for(j = 0; j < find; j++) {
				charNum[j] = chunk[j];
			}
			charNum[find] = '\0';
			number = atoi(charNum);
			if(number == 0 && charNum[0] == '0') correct = 1;
			if(number > 0) correct = 1;
			for(k = 0; k < 3; k++) {
				if(chunk[find + 1 + k] != 32) {
					correct = 0;
				}
			}
			break;
		}
	}
	if(correct == 1) return number;
	else return WRONG_FORMAT;
}

char *toLowerString(char *string) {
	int i;
	for(i = 0; string[i] != '\0'; i++) {
		string[i] = editChar(string[i]);
	}
	for(i = 0; string[i] != 32; i++) {}
	string[i] = '\0';
	return string;
}

index *insertToTable(index *table, char chunk[CHUNK_SIZE]) {
	int i, j, n, k;
	int position = format(chunk);
	for(i = 0; chunk[i] != '\0'; i++) chunk[i] = editChar(chunk[i]);
	if(format(chunk) != WRONG_FORMAT) {		
		for(i = 0; chunk[i] != '\0'; i++) {
			char *string = (char*) malloc (sizeof(char) * STRING_SIZE);
			if(chunk[i] != 32 && chunk[i-1] == 32) {
				j = i;
				k = 0;
				while(chunk[j] != 32) {
					string[k] = chunk[j];
					k++;
					j++;
				}
			}
			if(table[h(string)].df == EMPTY_KEY) {
				table[h(string)].word = string;
				table[h(string)].df = 1;
			}
			else {
				if(strcmp(table[h(string)].word, string) != 0) {
					index *tmp = malloc (sizeof(index));
					if(table[h(string)].next == NULL) {
						table[h(string)].next = tmp;
						tmp->df = 1;
						tmp->word = string;
						tmp->next = NULL;
					}
					else {
						int find = 0;
						tmp = table[h(string)].next;
						while(tmp != NULL) {
							if(strcmp(tmp->word, string) == 0) {
								tmp->df++;
								printf("\nfind 1");
								find = 1;
								break;
							}
							tmp = tmp->next;
						}
						if(find == 0) {
							printf("\nfind 0");
							tmp->df = 1;
							tmp->word = string;
							tmp->next = NULL;
						}
					}
				}
				else {
					table[h(string)].df++;
				}
			}
		}
	}
	return table;
}

unsigned int h(char *string) {
	int i;
	int length = strnlen(string, STRING_SIZE);
	unsigned int hash_value = 0;
	for(i = 0; i < length; i++) {
		hash_value += string[i];
		hash_value = (hash_value * string[i]) % TABLE_SIZE;
	}
	return hash_value;
}

index *initTable(index *table) {
	int i;
	table = malloc (sizeof(index) * TABLE_SIZE);
	for(i = 0; i < TABLE_SIZE; i++) {
		table[i].df = EMPTY_KEY;
		table[i].word = (char*) malloc (sizeof(char) * STRING_SIZE);
		table[i].next = NULL;
	}
	return table;
}

void printTable(index *table) {
	int i, count1 = 0, count2 = 0;
	for(i = 0; i < TABLE_SIZE; i++) {
		if(table[i].df != EMPTY_KEY) {
			count1++;
			printf("%d %s\n", table[i].df, table[i].word);
			if(table[i].next != NULL) {
				index *tmp = table[i].next;
				do{
					count2++;
					printf(" -> %d %s\n", tmp->df, tmp->word);
					tmp = tmp->next;
				}while(tmp == NULL);
			}
		}
	}
	printf("\ncount1 = %d\n", count1);
	printf("\ncount2 = %d\n", count2);
}

void stats(index *table, char *word) {
	
}

void query(index *table, char *word) {
	
}
