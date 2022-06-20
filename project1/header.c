//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#include "header.h"

void initqueue(queue *q)
{
	//queue initialition
	q->head = NULL;
	q->tail = NULL;
}

double genrand(double rate)
{
	// generate l
	int y;
	double p;
	while((y = rand()) == RAND_MAX);
	p = (double) y / RAND_MAX;
	return (-log(1-p)) / rate;
}

node *getqueue(queue *q)
{
	// check if the queue is empty
	if (q->head == NULL) return NULL;
	
	// save the head of the queue
	node *save = q->head;
	
	// take off the head
	q->head = q->head->next;
	
	if (q->head == NULL)
	{
		q->tail = NULL;
	}
	
	// return the saved node
	return save;
}

void putqueue(queue *q, int type, double service_rate, double arrival_rate)
{
	// create new node
	node *newnode = malloc(sizeof(node));
	if(q->head == NULL)
	{
		// if list is empty
		newnode->arrive = genrand(arrival_rate);
		if(type == 1)	newnode->service = 1.0;
		else if(type == 2)	newnode->service = genrand(service_rate);
		newnode->finish = newnode->arrive + newnode->service;
		newnode->wait = newnode->service;
		newnode->next = NULL;
	}
	else if(q->head == q->tail)
	{
		// if list has one node
		newnode->arrive = q->tail->arrive + genrand(arrival_rate);
		if(type == 1)	newnode->service = 1.0;
		else if(type == 2)	newnode->service = genrand(service_rate);
		if(newnode->arrive < q->tail->finish)
		{
			newnode->finish = q->tail->finish + newnode->service;
			newnode->wait = newnode->finish - newnode->arrive + newnode->service;
		}
		else
		{
			newnode->finish = newnode->arrive + newnode->service;
			newnode->wait =	newnode->service;
		}
		newnode->next = NULL;
	}
	else 
	{
		// list has more than one nodes
		newnode->arrive = q->tail->arrive + genrand(arrival_rate);
		if(type == 1)	newnode->service = 1.0;
		else if(type == 2)	newnode->service = genrand(service_rate);
		if(newnode->arrive < q->tail->finish)
		{
			newnode->finish = q->tail->finish + newnode->service;
			newnode->wait = newnode->finish - newnode->arrive + newnode->service;
		}
		else
		{
			newnode->finish = newnode->arrive + newnode->service;
			newnode->wait =	newnode->service;
		} 
		newnode->next = NULL;
	}
	
	
	// if there is a tail, connect that tail to this new node
	if (q->tail != NULL)
	{
		q->tail->next = newnode;
	}
	q->tail = newnode;
	
	// make sure the head makes sence
	if (q->head == NULL)
	{
		q->head = newnode;
	}
}
