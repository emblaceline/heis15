/**
* @file
* @brief Library for doing operations on the 
* queue of orders
*/
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

/**
* @brief Puts the orders from the command-buttons into queue
*
* @param order What floor the order is at.
*
* @param[in] lastFloor The last floor the elevator was registered at.
*
* @param[in] motorDir The direction of the elevator.
*/
void queue_set(int order, int lastFloor, int motorDir);

/**
* @brief Puts a order from a call-up-button in the call-up queue. If @p order is the same as
* @p lastFloor, puts the order in the call-down queue.
*
* @param order The floor of the order.
*
* @param lastFloor The last floor the elevator was registered at.
*/
void queue_set_up_queue(int order, int lastFloor);


/**
* @brief Puts a order from a call-down-button in the call-down queue. If @p order is the same as
* @p lastFloor, puts the order in the call-up queue.
*
* @param order The floor of the order.
*
* @param lastFloor The last floor the elevator was registered at.
*/
void queue_set_down_queue(int order, int lastFloor);


/**
* @brief Chooses which queue to put a command-button order in when @p lastFloor is the same as 
* @p order.
*
* @param order The floor of the order.
*
* @param motorDir what direction the elevator is driving.
*/
void queue_choose(int order, int motorDir);

/**
* @brief Removes an order from queue.
*
* @param order The floor of the order.
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
* @brief Gets the floor of the next order from call-up queue.
*
* @return Returns the floor of the next order. Returns -2 if there are no orders.
*/

int queue_get_next_order_up(int lastFloor);

/**
* @brief Gets the floor of the next order call-down queue.
*
* @return Returns the floor of the next order. Returns -2 if there are no orders.
*/
int queue_get_next_order_down(int lastFloor);

int queue_get_next_order_over(int lastFloor);

int queue_get_next_order_under(int lastFloor);



void print_queue();



#endif // #ifndef __INCLUDE_QUEUE_H__
