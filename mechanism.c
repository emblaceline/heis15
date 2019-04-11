/**
* @file
* @brief Implementation file for most of the mechanisms of the elevator
*/

#include "mechanism.h"
#include "elev.h"
#include "queue.h"
#include <stdio.h>
#include "door.h"

int motorDir = 0;
int emergencyWasPressed=0;
int emergencyDir=0;

void mechanism_check_all_button(int lastFloor){
	for (int floor=0; floor<N_FLOORS; floor++) {
		if (elev_get_button_signal(BUTTON_COMMAND,floor)) {
			queue_set(floor, lastFloor, motorDir);
		}

		if (floor!=N_FLOORS-1) {

			if (elev_get_button_signal(BUTTON_CALL_UP, floor)==1){
				queue_set_up_queue(floor,lastFloor);
				elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
			}
		}
		if (floor != 0) {
			if (elev_get_button_signal(BUTTON_CALL_DOWN, floor)==1){
				queue_set_down_queue(floor,lastFloor);
				elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
			}
		}
	}
}

void mechanism_emergency(){ 
	emergencyWasPressed=1; 
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	mechanism_turn_off_all_lights();

	if(elev_get_floor_sensor_signal()>=0){
		while(elev_get_stop_signal()){
			door_open_door();
		}
	}
	elev_set_stop_lamp(0);
	

}



void mechanism_turn_off_all_lights(){
	for(int floor = 0; floor < N_FLOORS; floor ++){
		elev_set_button_lamp(BUTTON_COMMAND,floor,0);
	}
	for(int floor = 0; floor < N_FLOORS-1; floor++){
		elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor+1,0);
	}

}

void mechanism_turn_off_light(int order){
	elev_set_button_lamp(BUTTON_COMMAND, order, 0);
	if (order<3){
		elev_set_button_lamp(BUTTON_CALL_UP, order, 0);
	}
	if (order>0){
		elev_set_button_lamp(BUTTON_CALL_DOWN, order, 0);
	}
}


_Bool mechanism_correct_floor(int order){
    if(elev_get_floor_sensor_signal() == order) {
        return true;
    }
    return false;
}

int mechanism_compare(int order, int lastFloor){
	if(lastFloor<order){
		return 1;
	}
	else if (lastFloor>order){
		return -1;
	}
	else{
		return 0;
	}
}


void mechanism_drive(int lastFloor){ 
	int order = -2;

	//print_queue();
	if(motorDir==0){
		order=queue_get_next_order_up(lastFloor);
		if(order==-2){
			order=queue_get_next_order_down(lastFloor);
		}
	}
	else if(motorDir==1){ 
		order=queue_get_next_order_up(lastFloor);
		if(order==-2){
			order=queue_get_next_order_down(lastFloor);	
		}

		else if(order < lastFloor && queue_get_next_order_down(lastFloor)!=-2){
			order=queue_get_next_order_down(lastFloor);
		}


		/*if(order==lastFloor && elev_get_floor_sensor_signal()==-1 && emergencyWasPressed == 0){
			order=queue_get_next_order_over(lastFloor);
		}*/
	}
	else{ 
		order=queue_get_next_order_down(lastFloor);
		if(order==-2){
			order=queue_get_next_order_up(lastFloor);
		}

		else if(order > lastFloor && queue_get_next_order_up(lastFloor)!=-2){
			order=queue_get_next_order_up(lastFloor);
		}

		/*
		if(order==lastFloor && elev_get_floor_sensor_signal()==-1 && emergencyWasPressed==0){
			order=queue_get_next_order_under(lastFloor);
		}*/
	}
	//order=mechanism_get_order(motorDir, lastFloor);

	if(emergencyWasPressed==1){
		if(order!=-2){
			emergencyWasPressed=0;
			if(order==lastFloor){
				emergencyDir=motorDir;
			}
		}
	}
	
	if(order!=-2 && door_get_door_open()==0){
       	if(emergencyDir!=0){
       		elev_set_motor_direction(-(emergencyDir));
       		if(elev_get_floor_sensor_signal()==order){
       			emergencyDir=0;
       		}
       	}
       	else{
       		motorDir = mechanism_compare(order,lastFloor);
       		elev_set_motor_direction(motorDir);
  
       		if(order==lastFloor && elev_get_floor_sensor_signal()!=-1){  
        		door_open_door();
        		queue_remove_element(order);
        		mechanism_turn_off_light(order);
        	}
       	}
    }
}

