﻿/**
 * @File: tuya_dp_process.h 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-05 
 * @Description: flame detection demo 
 */
#ifndef __TUYA_DP_PROCESS_H_
#define __TUYA_DP_PROCESS_H_

#include "tuya_cloud_com_defs.h"
#include "tuya_cloud_types.h"

typedef enum {
    alarm = 0,
    normal
}FLAME_STA_E;

//设备状态结构体
typedef struct {
    FLAME_STA_E smoke_sta; 
}SMOKE_SENSOR_S;

extern SMOKE_SENSOR_S  smoke_sensor_status;

VOID updata_dp_all(VOID);
VOID dp_process(IN CONST TY_OBJ_DP_S *root);

#endif

