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
static int command_queue[4]={0};
int lastDir=1;
int problemUp, problemDown =0;

void queue_set(int order, int lastFloor, int motorDir){
	elev_set_button_lamp(BUTTON_COMMAND, order,1);
	if (order==lastFloor && elev_get_floor_sensor_signal()==order && motorDir==0) {
		door_open_door();
		elev_set_button_lamp(BUTTON_COMMAND,order,0);
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

int queue_get_next_order(int lastFloor, int motorDir){
	if(motorDir==0){
		return queue_get_next_order_stop(lastFloor);
	}
	else if(motorDir==1){
		return queue_get_next_order_moving_up(lastFloor);
	}
	else{
		return queue_get_next_order_moving_down(lastFloor);
	}
	return -2;

}


int queue_get_next_order_stop(int lastFloor){
	if(lastDir==1){
			for(int i=lastFloor; i<N_FLOORS; i++){
				if (command_queue[i]==1){
					return i;
				}
				if (up_queue[i]==1){
					return i;
				}
			}
			for (int i = N_FLOORS-1; i>=lastFloor; i--){
				if (down_queue[i]==1){
					return i;
				}
			}
			for (int i = 0; i<lastFloor; i++){
				if (command_queue[i]==1){
					return i;
				}
				if (up_queue[i]==1){
					return i;
				}
			}
			for (int i = lastFloor-1; i>=0; i--){
				if (down_queue[i]==1){
					return i;
				}
			}
		}
		else{
			for(int i = 0; i <= lastFloor; i++){
				if (command_queue[i]==1){
					return i;
				}
				if (down_queue[i]==1){
					return i;
				}

			}
			for (int i = lastFloor; i>=0; i--){
				if (up_queue[i]==1){
					return i;
				}
			}
			for(int i=lastFloor+1; i<N_FLOORS-1; i++){
				if (command_queue[i]==1){
					return i;
				}
				if (down_queue[i]==1){
					return i;
				}
			}
			for (int i = N_FLOORS-1; i > lastFloor; i--){
				if (up_queue[i]==1){
					return i;
				}
			}
		}
	return -2;
}
int queue_get_next_order_moving_up(int lastFloor){
	lastDir=1;
		if(elev_get_floor_sensor_signal()>=0){
			if(problemUp<5){  // Dette fikser problemet adressert under, men er kanskje ikke fineste løsningen? 
				problemUp++;
			}
			else{
				if(up_queue[lastFloor]==1){  //noen ganger leser den av signal fra sensor før lastFloor har blitt byttet, da kan den slette feil
					return lastFloor;		// sånn som skjer i kryssfeil
				}
				if(command_queue[lastFloor]==1){
					return lastFloor;
				}
				if(down_queue[lastFloor]==1 && queue_empty_in_dir(1,lastFloor)==lastFloor){
					return lastFloor;
				}
				problemUp=0;
			}
		}

		for(int i=lastFloor+1; i<N_FLOORS;i++){
			if(command_queue[i]==1){
				return i;
			}
		}
		for(int i=lastFloor+1; i<N_FLOORS;i++){
			if(up_queue[i]==1){
				return i;
			}
		}
		if (queue_empty_in_dir(1,lastFloor)>=0){
			for(int i=N_FLOORS-1; i>lastFloor;i--){
				if(down_queue[i]==1){
					return i;
				}
			}
		}
	return -2;
}

int queue_get_next_order_moving_down(int lastFloor){
	lastDir=-1;
		if(elev_get_floor_sensor_signal()>=0){
			if(elev_get_floor_sensor_signal()>=0){
				if(problemDown<5){
					problemDown++;
				}
				else{
					if(down_queue[lastFloor]==1){
						return lastFloor;
					}
					if(command_queue[lastFloor]==1){
					return lastFloor;
					}
					if(up_queue[lastFloor]==1 && queue_empty_in_dir(-1,lastFloor)==lastFloor){
						return lastFloor;
					}
					problemDown=0;
				}
			}
		}

		for(int i=lastFloor-1; i>=0 ;i--){
			if(command_queue[i]==1){
				return i;
			}
		}
		for(int i=lastFloor-1; i>=0 ;i--){
			if(down_queue[i]==1){
				return i;
			}
		}
		if (queue_empty_in_dir(-1,lastFloor)>=0){
			for(int i=0; i<lastFloor;i++){
				if(up_queue[i]==1){
					return i;
				}
			}
		}
	return -2;
}


void queue_remove_element(int order){
	up_queue[order]=down_queue[order]=0;
	command_queue[order]=0;
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

int queue_empty_in_dir(int upOrDown, int lastFloor){
	if(upOrDown==1){
		for(int i = lastFloor; i<N_FLOORS; i++){
			if((up_queue[i]||command_queue[i])==1){
				return -2;
			}
		}
		for(int i = N_FLOORS-1; i>=lastFloor;i--){
			if(down_queue[i]==1){
				return i;
			}
		}
	}
	else{
		for(int i = lastFloor; i>=0; i--){
			if((down_queue[i]||command_queue[i])==1){
				return -2;
			}
		}
		for(int i = 0; i<=lastFloor;i++){
			if(up_queue[i]==1){
				return i;
			}
		}
	}
	return -2;
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
	printf("COMMAND: ");
	for (int i = 0; i < 4; ++i)
	{
		printf("%i", command_queue[i]);
		if(i==3){
			printf(" \n");
		}
	}
}