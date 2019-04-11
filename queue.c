/**
* @file
* @brief Implementation file for handeling the queues of orders
*/

#include "queue.h"
#include <stdio.h>
#include "elev.h"
#include "door.h"

static int up_queue[4]={0};
static int down_queue[4]={0}; 
//static int not_pressed_on_floor_up[4]={0};
//static int not_pressed_on_floor_down[4]={0};

void queue_set(int order, int lastFloor, int motorDir){
	elev_set_button_lamp(BUTTON_COMMAND, order,1);
	if (order==lastFloor) {
		if (elev_get_floor_sensor_signal()==order && motorDir==0){ 
			door_open_door();
			elev_set_button_lamp(BUTTON_COMMAND,order,0);
		}
		else{
			queue_choose(order,motorDir);
		}

	}
	else if (order>=lastFloor){
		up_queue[order]=1;
	}
	else if (order<=lastFloor){
		down_queue[order]=1;
	}
}

void queue_set_up_queue(int order, int lastFloor){
	up_queue[order]=1;

	/*if(lastFloor==order){
		down_queue[order]=1;
	}
	else{
		up_queue[order]=1;
	}*/
	/*up_queue[order]=1;
	if(lastFloor!=order){
		not_pressed_on_floor_up[order]=1;
	}*/
}

void queue_set_down_queue(int order, int lastFloor){
	down_queue[order]=1;
	/*if(lastFloor==order){
		up_queue[order]=1;
	}
	else{
		down_queue[order]=1;
	}*/
	/*down_queue[order]=1;
	if(lastFloor!=order){
	 	not_pressed_on_floor_down[order]=1;
	}*/

}


int queue_get_next_order(int lastFloor, int motorDir){
	if (motorDir==0){
		for (int i = 0; i < N_FLOORS; i++){
			if (up_queue[i]==1){
				return i;
			}
		}
		for (int i = N_FLOORS-1; i >= 0; i--){
			if (down_queue[i]==1){
				return i;
			}
		}
	}
	else if (motorDir==1){
		for (int i = lastFloor+1; i < N_FLOORS; i++){
			if (up_queue[i]==1){
				return i;
			}
		}
		for (int i = lastFloor+1; i< N_FLOORS; i++){
			if (down_queue[i]==1){
				return i;
			}
		}
		if (up_queue[lastFloor]==1){
			return lastFloor;
		}
		if (down_queue[lastFloor]==1){
			return lastFloor;
		}
	}
	else if (motorDir==-1){ 
		for (int i = lastFloor-1; i >= 0; i--){
			if (down_queue[i]==1){
				printf("%i\n", i);
				return i;
			}
		}
		
		for (int i = lastFloor-1; i >= 0; i--){
			if (up_queue[i]==1){
				return i;
			}
		}
		if (down_queue[lastFloor]==1){
			return lastFloor;
		}
		if (up_queue[lastFloor]==1){
			return lastFloor;
		}
	}
	return -2;
}

void queue_choose(int order, int motorDir){
	if (motorDir==1){
		down_queue[order]=1;
	}
	else {
		up_queue[order]=1;
	}
}


void queue_remove_element(int order){
	up_queue[order]=down_queue[order]=0;
	//not_pressed_on_floor_down[order]=not_pressed_on_floor_up[order]=0;
}

void queue_remove_all_orders(){
	for(int floor = 0; floor<N_FLOORS; floor++){  
		queue_remove_element(floor);
	}
}

int queue_empty(){
	for(int i = 0; i<N_FLOORS; i++){
		if((up_queue[i]||down_queue[i])==1){
			return 0;
		}
	}
	return 1;
}


/*int queue_get_next_order_up(int lastFloor){
	if(queue_empty()==1){
		return -2;
	}
	
	else{
		for (int i = lastFloor; i < N_FLOORS; i++){
			if(up_queue[i]==1){
				return i;
			}
		}
		for (int i = lastFloor; i >= 0; i--)
		{
			if(up_queue[i]==1){
				return i;
			}
		}
		
		for (int i=0; i<N_FLOORS; i++)
		{                              
			if(up_queue[i]==1){          
				if(i==lastFloor){                           
					for (int i=0; i<N_FLOORS; i++){
						if(not_pressed_on_floor_up[i]==1){
							return i;
						}
					}
				}
			not_pressed_on_floor_up[i]=1;
			return i;
				
			}
		}
	}
	return -2;
}

int queue_get_next_order_down(int lastFloor){

	if(queue_empty()==1){
		return -2;
	}
	else{
		
		for (int i = lastFloor; i >= 0; i--){
			if(down_queue[i]==1){
				return i;
			}
		}
		for (int i = lastFloor; i < N_FLOORS; i++)
		{
			if(down_queue[i]==1){
				return i;
			}
		}
		for (int i=N_FLOORS-1; i>=0; i--)
		{
			if(down_queue[i]==1){ 
				if(i==lastFloor){
					for (int i=N_FLOORS-1; i>=0; i--){
						if(not_pressed_on_floor_down[i]==1){
							return i;
						}
					}
				}
				not_pressed_on_floor_down[i]=1;
				return i;
				
			}
		}
	}
	return -2;
}

int queue_get_next_order_over(int lastFloor){
	if(queue_empty()==1){
		return -2;
	}
	else{
		for(int i=N_FLOORS-1; i>lastFloor;i--){
			if(down_queue[i]==1){
			
				return i;
			}
		}
		for(int i=N_FLOORS-1; i>lastFloor;i--){
			if(up_queue[i]==1){
				return i;
			}
		}
		
	}
	return -2;
}

int queue_get_next_order_under(int lastFloor){
	if(queue_empty()==1){
		return -2;
	}
	else{
		for(int i=0; i<lastFloor;i++){
			if(down_queue[i]==1){
				return i;
			}
		}
		for(int i=0; i<lastFloor;i++){
			if(up_queue[i]==1){
				return i;
			}
		}
		
	}
	return -2;
}*/




void print_queue(){ 
	printf("UP: ");
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", up_queue[i]);
		if(i==3){
			printf(" \n");
		}
	}
	printf("DOWN: ");
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", down_queue[i]);
		if(i==3){
			printf(" \n");
		}
	}
	/*printf("UP_N: ");
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", not_pressed_on_floor_up[i]);
		if(i==3){
			printf(" \n");
		}
	}
	printf("DOWN_N: ");
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", not_pressed_on_floor_down[i]);
		if(i==3){
			printf(" \n");
		}
	}*/
}