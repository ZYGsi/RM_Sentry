/**
  ****************************(C) COPYRIGHT 2024 FJUT RobotLab****************************
  * @file       main.c/h
  * @brief      stm32��ʼ���Լ���ʼ����freeRTOS.h�ļ��������ȫ�ֺ궨���Լ�
  *             typedef һЩ������������
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Oct-30-2024     Zard        1. δ���
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
	configHi219m_ParaInit();//���������ʼ��
	//configSignal_ParaInit();//�źŲ�����ʼ��
}
void Task_Init(void)
{
	    taskENTER_CRITICAL();//�����ٽ���
	P_shH219DataDecode_Binary = xSemaphoreCreateBinary();//���������ݽ���
//	P_stPCDataDecode_Binary = xSemaphoreCreateBinary();   
	//������
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
	//��ʱ����
	xTaskCreate(Task_TimeCount,
				"Task_TimeCount",
				300,
				NULL,
				4,
				NULL);
	
//	//���߼������
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

    taskEXIT_CRITICAL();//�˳��ٽ���
}

	


