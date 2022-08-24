/**
 * @file piccolo_os_lock_core_v1.c
 * @author Keith Standiford
 * @brief Piccolo OS v1 overrides for Pi Pico SDK lock_core defaults
 * @version 0.1
 * @date 2022-08-21
 * 
 * @copyright Copyright (c) 2022 Keith Standiford
 * 
 * 
 */
#include "pico/stdlib.h"
#include "piccolo_os.h"

extern piccolo_os_internals_t piccolo_ctx;

/**
 * @brief Get the ID (task struct address) of the running task
 * 
 * @return lock_owner_id_t Task ID to use as lock owner
 * 
 * If piccolo_os is NOT started (start hasn't yet been called), return the
 * core number. Otherwise, return the task ID of the running task. Piccolo_init
 * sets these to the core number as well, since even if the schedular is running
 * it MAY NOT have yet selected a task to run.
 */
lock_owner_id_t piccolo_get_task_id(){
    lock_owner_id_t task;
    return (lock_owner_id_t) piccolo_ctx.current_task;
}

/**
 * @brief yield if piccolo OS has started it's scheduler
 * 
 * Remember the caller checks anyway, so if we don't have a valid task running
 * we will just return.
 * 
 */
void piccolo_lock_wait(void) {
    if(piccolo_ctx.started) piccolo_yield();
    return;
}

/**
 * @brief if a valid task is running, sleep until the timeout expires. Then return the timeout status.
 * 
 * @param timeout_timestamp 
 * @return true if the timeout has expired
 * @return false if the timeout has not expired
 * 
 * The caller will keep trying until the timeout expires. Piccolo_OS will yield
 * until then, but if things aren't running yet, we will just return the timeout status
 * and let the loop run.
 */
bool piccolo_lock_wait_until(absolute_time_t timeout_timestamp){
    if(piccolo_ctx.started) piccolo_yield();
    return time_reached(timeout_timestamp);
}

/**
 * @brief Default idle routine for the lock system. We will yield if we can.
 * 
 */
void piccolo_lock_yield(void) {
    if(piccolo_ctx.started) piccolo_yield();
    return;
}