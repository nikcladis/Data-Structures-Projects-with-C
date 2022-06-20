//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_struct{
	int bit;
	int size;
	struct node_struct *next;
}node_struct;

typedef struct node_struct node;

struct Node{
	struct Node *left, *right;
};

typedef struct Node tree_node;
tree_node *root;

void printlist(node *head);
node *create_new_node(int bit);
node *insert_at_head(node **head, node *node_to_insert);
void reverselist(node **head);
int *getIP(int use, char *ipf);
void decimalToBinary(int *array, node **head);
void insertIP(tree_node **link, node *list);
int searchIP(tree_node *link, node *list);

#endif
