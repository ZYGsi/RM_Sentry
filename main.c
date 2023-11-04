/**
  ****************************(C) COPYRIGHT 2024 FJUT RobotLab****************************
  * @file       main.c/h
  * @brief      stm32初始化以及开始任务freeRTOS.h文件定义相关全局宏定义以及
  *             typedef 一些常用数据类型
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Oct-30-2024     Zard        1. 未完成
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 FJUT RobotLab****************************
  */

#include "main.h"
void Task_Init(void);
void BSP(void);
void EDH(void);

int main(void)
{ 
	BSP();
	EDH();
	Task_Init();

	
	vTaskStartScheduler();
	
	while(1);
}
void BSP(void)
{
	configCAN_Init();
	configDMA_Init();
	configIO_Init();
	configNVIC_Init();
	configTIM_Init();
	configUART_Init();
	RNG_Init();
}
void EDH(void)
{
	configHi219m_ParaInit();//电机参数初始化
	//configSignal_ParaInit();//信号参数初始化
}
void Task_Init(void)
{
	    taskENTER_CRITICAL();//进入临界区
	P_shH219DataDecode_Binary = xSemaphoreCreateBinary();//陀螺仪数据解析
//	P_stPCDataDecode_Binary = xSemaphoreCreateBinary();   
	//主任务
	xTaskCreate(Task_Main,
				"Task_Main",
				300,
				NULL,
				5,
				NULL);
	xTaskCreate(Task_DataSend,
				"Task_DataSend",
				300,
				NULL,
				5,
				NULL);
	//计时任务
	xTaskCreate(Task_TimeCount,
				"Task_TimeCount",
				300,
				NULL,
				4,
				NULL);
	
//	//离线检测任务
//	xTaskCreate(Task_OfflineDete,
//				"Task_OfflineDete",
//				300,
//				NULL,
//				5,
//				NULL);
		
	xTaskCreate(Task_Hi219mDataDecode,
				"Task_Hi219mDataDecode",
				300,
				NULL,
				4,
				NULL);

    taskEXIT_CRITICAL();//退出临界区
}

	


