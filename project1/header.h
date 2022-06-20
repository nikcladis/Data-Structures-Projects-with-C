//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct node
{
	double arrive;
	double finish;
	double wait;
	double service;
	struct node *next;
} node;

typedef struct
{
	node *head;
	node *tail;
} queue;

double genrand(double rate);
void initqueue(queue *q);
void putqueue(queue *q, int type, double service_rate, double arrival_rate);
node *getqueue(queue *q);

#endif
