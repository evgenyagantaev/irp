/*
 * ctc_controller_obj.h
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#ifndef INC_CTC_CONTROLLER_OBJ_H_
#define INC_CTC_CONTROLLER_OBJ_H_

#define CTC_INACTIVE 0
#define CTC_JUST_ACTIVATED 1
#define CTC_CHARGING 2
#define CTC_CHARGED 3
#define CTC_DISCHARGING 4
#define CTC_DISCHARGED 5
#define CTC_RECHARGING 6
#define CTC_RECHARGED 7
#define CTC_JUST_INACTIVATED 8


#define CTC_CONTROL_PERIOD 3


void ctc_set_stage(int stage);

void ctc_controller_task();

#endif /* INC_CTC_CONTROLLER_OBJ_H_ */
