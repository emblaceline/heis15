/**
* @file
* @brief Library to check for orders, 
* handle stop-button functions and driving the elevator
*/
#ifndef __INCLUDE_MECHANISM_H__
#define __INCLUDE_MECHANISM_H__

/**
* @brief Checks if any order buttons are pressed, and turns on light and adds them to the order queue
* if they are.
*
* @param lastFloor The last floor the elevator was registered at.
*/
void mechanism_check_all_button(int lastFoor);


/**
* @brief Stops the elevator, stop button is on while pressed. If elevator is on a floor the door is opened while 
* stop button is pressed and three sec after it is released. Turns off all order buttons.
*/
void mechanism_emergency();


/**
* @brief Turns off all order buttons.
*/
void mechanism_turn_off_all_lights();

/**
* @brief Turns off all call-buttons on a given floor.
*
* @param order The order.
*/
void mechanism_turn_off_light(int order);

/**
* @brief Checks if elevator floor signal is the same as the order.
*
* @param order The order.
*
* @return true if elevator is on correct floor, if not false.
*/
_Bool mechanism_correct_floor(int order);


/**
* @brief Compares the order and the last floor the elevator was registered at to figure
* out wanted direction on the motor.
*
* @param order The order.
*
* @param lastFloor The last floor the elevator was registered at.
*
* @return -1 if @p order is under @p lastFloor, 0 if they are the same, 1 if @p order is over @p lastFloor.
*/
int mechanism_compare(int order, int lastFloor);

/**
* @brief Checks what the next order is and drives there. Calls @p door_open_door(), @p queue_remove_element(int order)
* and @p mechanism_turn_off_light(int order) when the elevator reaches the correct floor.
*
* @param lastFloor The last floor the elevator was registered at.
*/
void mechanism_drive(int lastFloor);

#endif // #ifndef __INCLUDE_MECHANISM_H__
