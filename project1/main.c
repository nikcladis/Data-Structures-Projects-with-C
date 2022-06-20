//Basilis Xristogiannis AM: 2022201800230
//Nikolaos Kladis-Kountouris AM: 2022201800086

#include "header.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	queue q;
	initqueue(&q);
	
	int type; 
	double arrival_rate = 1;
	double service_rate = 1;
	
	do{
		printf("Type number 1 for Determenistic(M/D/1) or number 2 for Random(M/M/1): ");
		scanf("%d", &type);
		printf("\n");
	}while(type != 1 && type != 2);
	
	if(type == 1)
	{
		do{
			printf("Warning: Arrival Rate must be less than 1!\n");
			printf("Type Arrival Rate: ");
			scanf("%lf", &arrival_rate);
			printf("\n");
		}while(arrival_rate > service_rate);
	}
	else if(type == 2)
	{
		printf("Type Arrival Rate: ");
		scanf("%lf", &arrival_rate);
		printf("\n");
		do{
			printf("Warning: Service Rate must be greater than Arrival Rate!\n");
			printf("Type Service Rate: ");
			scanf("%lf", &service_rate);
			printf("\n");
		}while(arrival_rate > service_rate);
	}

	int i, customers = 0;
	double sum_time_wait = 0;
	
	for(i = 0; i < 1000000; i++)
	{
		putqueue(&q, type, service_rate, arrival_rate);
		customers++;
		while(q.tail->arrive > q.head->finish)
		{
			node *tmp = getqueue(&q);
			sum_time_wait += tmp->wait;
			free(tmp);
		}
	}
	double average_time_wait = sum_time_wait/customers; 
	printf("\nAVERAGE_TIME: %lf\n", average_time_wait);
	
	return 0;
}
