#include "fd_can_rs01.h"

#define hfdcanx hfdcan2

void rs01_CAN_Filter_Config(void)
{
    FDCAN_FilterTypeDef sFilterConfig;

    sFilterConfig.IdType = FDCAN_EXTENDED_ID;             // 灵足电机使用扩展帧
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;         // 掩码模式
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // 存入 FIFO0
    sFilterConfig.FilterID1 = 0x00000000;                 // 接收所有 ID
    sFilterConfig.FilterID2 = 0x00000000;
    
    if (HAL_FDCAN_ConfigFilter(&hfdcanx, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void rs01_CAN_Init(void)
{
    rs01_CAN_Filter_Config();
    if (HAL_FDCAN_Start(&hfdcanx) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(&hfdcanx, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        Error_Handler();
    }
}
