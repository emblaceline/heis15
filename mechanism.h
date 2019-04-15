/**
* @file
* @brief Library to check for orders, 
* handle stop-button functions and driving the elevator
*/
#ifndef __INCLUDE_MECHANISM_H__
#define __INCLUDE_MECHANISM_H__


/**
* @brief Checks if any order buttons are pressed. If they are: adds them to their order queue.
*
* @param [in] lastFloor The last floor the elevator was registered at.
*/
void mechanism_check_all_buttons(int lastFoor);


/**
* @brief Stops the elevator, stop button light is turned on while pressed. If
* elevator is on a floor the door is opened while 
* stop button is pressed and for a @p WAIT_TIME after it is released. 
* Turns off all order button lights.
*/
void mechanism_emergency();


/**
* @brief Turns off all order button lights.
*/
void mechanism_turn_off_all_lights();

/**
* @brief Turns off all order button lights on a given floor.
*
* @param order The floor of the order.
*/
void mechanism_turn_off_light(int order);

/**
* @brief Checks if elevator floor signal is the same as the order.
*
* @param [in] order The order.
*
* @return true if elevator is on correct floor, if not false.
*/
_Bool mechanism_correct_floor(int order);


/**
* @brief Compares the order and the last floor the elevator was registered at to figure
* out wanted direction on the motor.
*
* @param [in] order The order.
*
* @param [in] lastFloor The last floor the elevator was registered at.
*
* @return -1 if @p order is under @p lastFloor, 0 if they are the same, 1 if @p order is over @p lastFloor.
*/
int mechanism_compare(int order, int lastFloor);

/**
* @brief Gets the next order and drives there. Calls @p door_open_door(), @p queue_remove_element(int order)
* and @p mechanism_turn_off_light(int order) when the elevator reaches the correct floor.
*
* @param [in] lastFloor The last floor the elevator was registered at.
*/
void mechanism_drive(int lastFloor);

#endif // #ifndef __INCLUDE_MECHANISM_H__
