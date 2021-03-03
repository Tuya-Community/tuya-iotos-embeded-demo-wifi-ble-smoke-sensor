# Tuya IoTOS Embeded Demo WiFi & BLE Smart Smoke Sensor 

[English](./README.md) | [中文](./README_zh.md) 

## Introduction 

This Demo implements a smart smoke detection through Tuya Smart Cloud Platform, Tuya Smart APP, IoTOS Embeded WiFi &Ble SDK, using Tuya WiFi/WiFi+BLE series modules to achieve remote data monitoring.

Implemented features include.

+ Real-time detection of smoke values in the environment and alarm alerts when a certain threshold is reached.




## Quick start 

### Compile & Burn
+ Download [Tuya IoTOS Embeded WiFi & BLE sdk](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231t) 

+ Download the demo to the apps directory of the SDK 

  ```bash
  $ cd apps
  $ git clone https://github.com/Tuya-Community/tuya-iotos-embeded-demo-wifi-ble-smoke-sensor
  ```
  
+ Execute the following command in the SDK root directory to start compilation.

  ```bash
  sh build_app.sh apps/tuya-iotos-embeded-demo-wifi-ble-smoke-sensor tuya-iotos-embeded-demo-wifi-ble-smoke-sensorr 1.0.0 
  ```

+ Firmware burn-in license information please refer to: [Wi-Fi + BLE series module burn-in license](https://developer.tuya.com/cn/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd) 

 

### Demo information 

|      Product ID      |                       ybvv6byxhmn4n8fv                       |
| :------------------: | :----------------------------------------------------------: |
|    chip platform     |                           BK7231S                            |
| Compiler Environment | ty_iot_wf_bt_sdk_bk_bk7231t_1.0.2 (Tuya IOT Platform SDK 1.0.2) |

 

### File introduction 

```
├── include
│ ├── common
│ │ ├── device_config_load.h
│ │ ├── light_printf.h
│ │ ├── light_types.h
│ ├── soc
│ │ ├── soc_adc.h
│ │ └── soc_pwm.h
│ ├── tuya_device.h
│ ├── tuya_dp_process.h
│ └── tuya_smoke_sensor.h
└── src
    ├─ soc
    │ ├── soc_adc.c
    │ └── soc_pwm.c
    ├── tuya_device.c 		// application entry file
    ├── tuya_dp_process.c 	//DataPoint processing file
    └── tuya_smoke_sensor.c //smoke sensor data processing file
```





### Demo entry

Entry file: tuya_device.c

Important function: device_init()

+ Call tuya_iot_wf_soc_dev_init_param() interface to initialize the SDK, configure the operating mode, the wiring mode, and register various callback functions and store the firmware key and PID.

+ Calling the tuya_iot_reg_get_wf_nw_stat_cb() interface to register the device network status callback functions.

+ Call the application layer initialization function air_box_device_init()



### DataPoint related

+ Report dp point interface: dev_report_dp_json_async()

| function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt) |
| ------------- | ------------------------------------------------------------ |
| devid         | device id (if gateway, MCU, SOC class device then devid = NULL; if sub-device, then devid = sub-device_id) |
| dp_data       | dp structure array name                                      |
| cnt           | Number of elements of the dp structure array                 |
| return        | OPRT_OK: Success Other: Failure                              |



### I/O List 

| Flame sensor pins | Corresponding connected wb3s pins |
| :---------------: | :-------------------------------: |
|        VCC        |               3.3V                |
|        GND        |                GND                |
|        AO         |           ADC/GPIOA_23            |



## Related Documents

Tuya Demo Center: https://developer.tuya.com/cn/demo/



## Technical Support

You can get support for Tuya by using the following methods:

- Developer Center: https://developer.tuya.com/cn/
- Help Center: https://support.tuya.com/en/help
- Technical Support Work Order Center: [https://service.console.tuya.com](https://service.console.tuya.com/) 