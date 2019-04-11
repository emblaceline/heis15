/**
* @file
* @brief Implementation file for controlling the door
*/

#include "elev.h"
#include "door.h"
#include <time.h>
#include <stdio.h>

bool doorIsOpen;
int doorStatus = 0; 

_Bool door_get_door_open(){
	return doorIsOpen;
}

void door_open_door() {
	doorStatus = door_set_timer(WAIT_TIME);
	elev_set_door_open_lamp(1);
	doorIsOpen=true;
}


void door_close_door() {
	if (door_check_time(doorStatus)) {
		elev_set_door_open_lamp(0);
		doorStatus = 0;
		doorIsOpen=false;
	}
}

int door_set_timer(int waitTime) {
	return time(NULL) + waitTime;

}

int door_check_time(int doorStatus) {
	if (doorStatus <= time(NULL)) {
		return 1;
	}
	return 0;
}

