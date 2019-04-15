/**
* @file
* @brief Library for doing operations on the 
* queue of orders
*/
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__


/**
* @brief Puts the orders into queue and turns on the button light.
* If elevator is on the floor of the order it will open the door.
*
* @param[in] order What floor the order is at.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @param[in] motorDir The direction the elevator is moving.
*
* @param[in] buttonType 0 if call-up button, 1 if call-down button, 2 if command button.
*/
void queue_set_queue(int order, int lastFloor, int motorDir, int buttonType);


/**
* @brief Gets the next order.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @param [in] motorDir The direction the elevator is moving.
*
* @return The floor of the next order. -2 if there are no orders.
*/
int queue_get_next_order(int lastFloor, int motorDir);

/**
* @brief Gets the next order when the elevator is standing still.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @return The floor of the next order. -2 if there are no orders.
*/
int queue_get_next_order_stop(int lastFloor);

/**
* @brief Gets the next order when the elevator is moving up.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @return The floor of the next order. -2 if there are no orders.
*/
int queue_get_next_order_moving_up(int lastFloor);

/**
* @brief Gets the next order when the elevator is moving down.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @return The floor of the next order. -2 if there are no orders.
*/
int queue_get_next_order_moving_down(int lastFloor);

/**
* @brief Removes an order from queue.
*
* @param[in] order The floor of the order.
*/
void queue_remove_element(int order);

/**
* @brief Removes all orders in queue.
*/
void queue_remove_all_orders();

/**
* @brief Checks if there are any orders in queue.
*
* @return 1 if empty, 0 if there are any orders.
*/
int queue_empty();

/**
* @brief Checks if there are only call-up/down orders under/over the elevator in the opposite direction that the elevator is moving.
*
* @param[in] upOrDown 1 if the elevator is moving up, -1 if it is moving down
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @return If elevator is moving up: returns -2 if there are no orders over the elevator
* or if call-up or command has order(s) over the elevator.
* If neither of those: returns the floor of the call-down order over the elevator. <br>
* If elevator is moving down: returns -2 if there are no orders under the elevator
* or if call-down or command has order(s) under the elevator. 
* If neither of those: returns the floor of the call-up order under the elevator.
*/
int queue_empty_in_dir(int upOrDown, int lastFloor);

void print_queue();

#endif // #ifndef __INCLUDE_QUEUE_H__
