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
//static int command_queue[4]={0};
int lastDir=1;


void queue_set(int order, int lastFloor, int motorDir){
	elev_set_button_lamp(BUTTON_COMMAND, order,1);
	if (order==lastFloor) {
		if (elev_get_floor_sensor_signal()==order && motorDir==0){ 
			door_open_door();
			elev_set_button_lamp(BUTTON_COMMAND,order,0);
		}
	}
	else{
		command_queue[order]=1;
	}
}

void queue_set_up_queue(int order, int lastFloor){
	up_queue[order]=1;
}

void queue_set_down_queue(int order, int lastFloor){
	down_queue[order]=1;
}

/*int queue_get_next_order(int lastFloor, int motorDir){
	if(motorDir==0){
		for (int i = 0; i < N_FLOORS; ++i){
			if (command_queue[i]==1){
				return i;
			}
		}
		for (int i = 0; i < N_FLOORS; ++i){
			if (up_queue[i]==1){
				return i;
			}
		}
		for (int i = 0; i < N_FLOORS; ++i){
			if (up_queue[i]==1){
				return i;
			}
		}
	}

}*/



int queue_nr_of_order(){
	int temp=0;
	for (int i = 0; i < N_FLOORS; i++){
		if(up_queue[i]==1){
			temp++;
		}
		if(down_queue[i]==1){
			temp++;
		}
	}
	return temp;
}

int queue_get_next_order(int lastFloor, int motorDir){
	if (motorDir==0){
		if (lastDir==1){ 
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
		if (lastDir==-1){ 
			for (int i = N_FLOORS-1; i >= 0; i--){
				if (down_queue[i]==1){
					return i;
				}
			}
			for (int i = 0; i < N_FLOORS; i++){
				if (up_queue[i]==1){
					return i;
				}
			}
		}
	}
	else if (motorDir==1){
		lastDir=1;
		for (int i = lastFloor+1; i < N_FLOORS; i++){
			if (up_queue[i]==1 && up_queue[lastFloor]==0){
				return i;
			}
		}
		for (int i = lastFloor+1; i< N_FLOORS; i++){
			if (down_queue[i]==1 && up_queue[lastFloor]==0){
				return i;
			}
		}
		if(up_queue[lastFloor]==1 && queue_nr_of_order()==2){
			for(int i=lastFloor+1; i<N_FLOORS; i++){
				if(down_queue[i]==1){
					return i;
				}
			}
		}
		if(up_queue[lastFloor]==1 && queue_nr_of_order()>=2){
			for(int i=lastFloor+1; i<N_FLOORS; i++){
				if(up_queue[i]==1){
					return i;
				}
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
		lastDir=-1; 
		for (int i = lastFloor-1; i >= 0; i--){
			if (down_queue[i]==1 && down_queue[lastFloor]==0){
				return i;
			}
		}
		
		for (int i = lastFloor-1; i >= 0; i--){
			if (up_queue[i]==1 && down_queue[lastFloor]==0){
				return i;
			}
		}

		if(down_queue[lastFloor]==1 && queue_nr_of_order()==2){
			for(int i=lastFloor-1; i>=0; i--){
				if(up_queue[i]==1){
					return i;
				}
			}
		}
		if(down_queue[lastFloor]==1 && queue_nr_of_order()=2){
			for(int i=lastFloor-1; i>=0; i--){
				if(down_queue[i]==1){
					return i;
				}
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
}