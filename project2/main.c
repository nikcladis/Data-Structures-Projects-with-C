//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#include "functions.h"

int main()
{
	//initialize root
	root = (tree_node*)malloc(sizeof(tree_node));
	root->left = NULL;
	root->right = NULL;
	
	FILE *fptr = fopen("routingtable.txt", "r");
	if(fptr == NULL) {
		printf("\nUnable to open the file!\n\n");
		return 0;
	}
	char line[100];
	while(fgets(line, sizeof(line), fptr))
	{
		printf("%s", line);
		node *list = NULL;
		decimalToBinary(getIP(0, line), &list);
		if(list->bit == 0) insertIP(&(root->left), list);
		else if(list->bit == 1) insertIP(&(root->right), list);
	}
	
	while(1)
	{
		//search ip in tree
		printf("\n");
		node *list = NULL;
		decimalToBinary(getIP(2, NULL), &list);
		int prefix;
		if(list->bit == 0) prefix = searchIP(root->left, list);
		else if(list->bit == 1) prefix = searchIP(root->right, list);
		printf("%d\n", prefix);
	}
	
	return 0;
}
