/**
 * @File: tuya_app_smoke_sensor_drive.c 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-13 
 * @Description: smoke detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_smoke_sensor.h"
#include "tuya_iot_com_api.h"
#include "uni_log.h"
#include "soc_adc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "uni_thread.h"

#define ADC_DATA_LEN 4

#define SMOKE_ALARM 1.3 //电压超过 1.3v 报警 

static tuya_adc_dev_t tuya_adc;

VOID check_smoke_task(VOID);

VOID smoke_sensor_init(VOID)
{
    tuya_gpio_inout_set(SMOKE_SENSOR_PIN, TRUE);

    tuya_adc.priv.pData = Malloc(ADC_DATA_LEN * sizeof(USHORT_T));
    memset(tuya_adc.priv.pData, 0, ADC_DATA_LEN*sizeof(USHORT_T));
    tuya_adc.priv.data_buff_size = ADC_DATA_LEN; //设置数据缓存个数

    tuya_hal_thread_create(NULL, "check_flame", 512, TRD_PRIO_2, check_smoke_task, NULL);
}

VOID get_smock_adc_value(OUT USHORT_T* adc_value) 
{
    INT_T ret;

    if (adc_value == NULL) {
        PR_ERR("pm25_adc_value is NULL");
        return;
    }
    memset(tuya_adc.priv.pData, 0, ADC_DATA_LEN*sizeof(USHORT_T));
    ret = tuya_hal_adc_init(&tuya_adc);
    if (ret != OPRT_OK) {
        PR_ERR("ADC init error : %d ", ret);
        return;
    }

    ret = ret = tuya_hal_adc_value_get(ADC_DATA_LEN, adc_value); 
    if (ret != OPRT_OK) {
        tuya_hal_adc_finalize(&tuya_adc);
        PR_ERR("ADC get value error : %d ", ret);
        return;
    }

    tuya_hal_adc_finalize(&tuya_adc);
    return;
}


VOID check_smoke_task(VOID)
{
    USHORT_T smoke_adc_value = 0;
    FLOAT_T vol_value = 0;
    
    while (1) {
        //得到adc值
        get_smock_adc_value(&smoke_adc_value);
        //PR_NOTICE("adc get value is %d", smoke_adc_value);
        vol_value = (smoke_adc_value * 1.0 / 4095) * 3.3;
        PR_NOTICE("vol value is %lf", vol_value);

        if(SMOKE_ALARM < vol_value) {
            smoke_sensor_status.smoke_sta = alarm;
        } else {
            smoke_sensor_status.smoke_sta = normal;
        }

        updata_dp_all();
        tuya_hal_system_sleep(6000);
    }
}

