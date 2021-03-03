/**
 * @File: tuya_smoke_sensor.h 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-13 
 * @Description: smoke detection demo 
 */
#ifndef __TUYA_SMOKE_SENSOR_H__
#define __TUYA_SMOKE_SENSOR_H__

#include "tuya_cloud_types.h"
#include "tuya_gpio.h"

#define SMOKE_SENSOR_PIN    TY_GPIOA_8

VOID smoke_sensor_init(VOID);

#endif

