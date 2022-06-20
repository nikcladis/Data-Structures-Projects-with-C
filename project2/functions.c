//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#include "functions.h"

void printlist(node *head){
	
	node *tmp = head;
	while(tmp != NULL){
		printf("%d", tmp->bit);
		tmp = tmp->next;
	}
}

node *create_new_node(int bit){
	
	node *result = malloc(sizeof(node));
	result->bit = bit;
	result->next = NULL;
	return result;
}

node *insert_at_head(node **head, node *node_to_insert){
	
	node_to_insert->next = *head;
	*head = node_to_insert;
	return node_to_insert;
}

void reverselist(node **head){
	
	node *t;
	node *y = *head;
	node *r = NULL;
	
	while (y != NULL){
		t = y->next; 
		y->next = r;
		r = y;
		y = t;
	}
	*head = r;
}

int *getIP(int use, char *ipf){
	
	int IP_SIZE = 50;
	int X = 5;
	int Y = 4;
	
	while(1){
		int i;
		
		char *ipm;
		ipm = calloc(IP_SIZE, sizeof(char));
		if(ipf == NULL){
			if(use == 2) printf("Search IP Adress...\n$> ");
			fgets(ipm, 100, stdin);
		}
		
		char **string_array;
		
		string_array = malloc(sizeof(char*)*X);
		
		for(i = 0; i < 5; i++)	
			string_array[i] = malloc(sizeof(int)*Y);
		
		i = 0;
		if(ipf == NULL) string_array[i] = strtok(ipm, ".");
		else string_array[i] = strtok(ipf, ".");
		while(string_array[i] != NULL){
			i++;
			string_array[i] = strtok(NULL, ".");
		}
		
		string_array[3] = strtok(string_array[3], "/");
		string_array[4] = strtok(NULL, "/");
			
		int *int_array = (int*)calloc(4, sizeof(int));
		
		for(i = 0; i < 5; i++){
			int_array[i] = atoi(string_array[i]);
		}
		
		int error = 0;
		
		for(i = 0; i < 4; i++){
			if(int_array[i] < 0 || int_array[i] > 255){
				error++;
			}
		}
		
		if(int_array[4] < 0 || int_array[4] > 32)	error++;
		
		if(use == 2){
			if(error == 0)printf("\nLongest IP Prefix Found: %d.%d.%d.%d/", int_array[0], int_array[1], int_array[2], int_array[3]);
			else printf("Faulty IP!\n");
		}
			
		if(error == 0) return int_array;
		else printf("\n");
	}
}

void decimalToBinary(int *array, node **head){
	
	int N = 4;
	int M = 8;
	
	node *tmp;
	int i, j, k = 0;
	int decimal[N];
	int binary[N][M];
	int sizeIP = array[4];
	int finalArray[N*M+1];
	
	sizeIP++;
	
	for(i = 0; i < N; i++)	decimal[i] = array[i];	
	
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			binary[i][j] = 0;
		}
	}

	for(i = 0; i < N; i++){
		j = 0;
		while(decimal[i] > 0){
			binary[i][j] = decimal[i]%2;
			decimal[i] = decimal[i]/2;
			j++;
		}
	}

	for(i = 0; i < N; i++){
		for(j = M - 1; j >= 0; j--){
			finalArray[k] = binary[i][j];
			k++;
		}
	}
	
	for(i = 0; i < sizeIP; i++){
		tmp = create_new_node(finalArray[i]);
		insert_at_head(head, tmp);
	}
	
	reverselist(&(*head));
}

void insertIP(tree_node **link, node *list){
	if(list == NULL) return;

	if(list->bit == 0){
		if(*link != NULL){
			insertIP(&(*link)->left, list->next);
		}
		else{
			tree_node *temp = (tree_node*)malloc(sizeof(tree_node));
			temp->right = NULL;
			temp->left = NULL;
			*link = temp;
			insertIP(&(*link)->left, list->next);
		}
	}
	else{
		if(*link != NULL){
			insertIP(&(*link)->right, list->next);
		}
		else{
			tree_node *temp = (tree_node*)malloc(sizeof(tree_node));
			temp->right = NULL;
			temp->left = NULL;
			*link = temp;
			insertIP(&(*link)->right, list->next);
		}
	}
}

int searchIP(tree_node *link, node *list){
	tree_node *tmp_link = link;
	int prefix = 0;
	while(1){
		if(list->next == NULL) break;
		else{
			if(list->bit == 0){
				if(tmp_link->left != NULL){
					prefix++;
					tmp_link = tmp_link->left;
					list = list->next;
				}
				else{
					return prefix;
				}
			}
			else{
				if(tmp_link->right != NULL){
					prefix++;
					tmp_link = tmp_link->right;
					list = list->next;	
				}
				else{
					return prefix;
				}
			}
		}
	}
	return prefix;	
}
