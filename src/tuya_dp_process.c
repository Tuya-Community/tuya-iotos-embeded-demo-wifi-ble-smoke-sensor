/**
 * @File: tuya_dp_process.c 
 * @Author: shiliu.yang@tuya.com 
 * @Last Modified time: 2021-01-13 
 * @Description: smoke detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_iot_com_api.h"
#include "gw_intf.h"
#include "uni_log.h"

#define dpid_smoke_state    1

SMOKE_SENSOR_S  smoke_sensor_status = {
    .smoke_sta = normal,
};

 /***********************************************************
 *   Function:  dp_process
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    处理 dp 数据 
 ***********************************************************/
VOID dp_process(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);

    return;
}

 /***********************************************************
 *   Function:  updata_dp_all
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    上报所有 dp 
 ***********************************************************/
VOID updata_dp_all(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 1;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = dpid_smoke_state;
    dp_arr[0].type = PROP_ENUM;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_enum = smoke_sensor_status.smoke_sta;

    op_ret = dev_report_dp_json_async(NULL , dp_arr, dp_cnt);
    //op_ret = sf_obj_dp_report_async(get_gw_cntl()->gw_if.id, dp_arr, FALSE);
    Free(dp_arr);
    dp_arr = NULL;
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    
    return;
}



