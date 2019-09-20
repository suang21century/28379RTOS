//###########################################################################
//
// FILE:   F28x_Project.h
//
// TITLE:  F28x Project Headerfile and Examples Include File
//
//###########################################################################
// $TI Release: F2837xD Support Library v200 $
// $Release Date: Tue Jun 21 13:00:02 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F28X_PROJECT_H
#define F28X_PROJECT_H

//----------------------------------�����ļ�-----------------------------//

#include "F2837xD_Cla_typedefs.h"  // F2837xD CLA Type definitions
#include "F2837xD_device.h"        // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"      // F2837xD Examples Include File
#include "math.h"

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/hal/Timer.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>

//--------------------------��������----------------------------//
extern void InitCpu(void);
extern void InitCtrl(void);

extern interrupt void timer0_isr(void);
extern interrupt void adc1_isr(void);
extern interrupt void sciarx_isr(void);

extern Queue_Handle myQ;//��������
extern Semaphore_Handle sem;//�����ź���
extern Task_Handle task;//��������
extern Task_Handle task1;
extern Task_Handle task2;
extern Swi_Handle swi;
extern Swi_Handle swi1;
extern Void taskFxn(UArg a0, UArg a1);
extern Void task1Fxn(UArg a0, UArg a1);
extern Void task2Fxn(UArg a0, UArg a1);
extern Void swiFxn(UArg arg0, UArg arg1);
extern Void swi1Fxn(UArg arg0, UArg arg1);
extern Void clk0Fxn(UArg arg0);

//-------------------------------�궨��--------------------------//
#define BLINKY_LED_GPIO 31
#define BLINKY_LED_GPIO2 34

//-------------------------------�ṹ�����-------------------------//
typedef struct Rec {
Queue_Elem elem;
Int data;
} Rec;

typedef struct
{
Uint16     En;
Uint16     RxFlag;      //���ձ�־��Ϊ1���޸ģ��޸ĺ�λ0
Uint16     ZeroFlag;
Uint16     WriteFlag;   //д���־��Ϊ1��д��FLASH��H������ɺ�λ0
Uint16     RxType;        //���ڽ��յ�����
Uint16     Read1;
Uint16     Read2;
int32      RxTmp;
Uint16     RxSum;        // ����ָ����ۼ�
Uint16     RxCnt;        // �Ѿ����ܵ����ֽ���
Uint16     TxType;       //�������ͣ��ɽ��յ�֡����0�ķ���ָ�����
Uint16     TxData[2];    // ���͵����������ֽ�
int16      TxTemp;       //�������ݴ�
Uint16     TxTemp1;       //�������ݴ�
Uint16     TxCnt;        // �Ѿ����͵����ݳ���
Uint16     TxSum;        //�ѷ��͵����ݵļӺͣ�
Uint16     Ver;
Uint16     Buffer[256];   //�洢��������д��flash
}Uart_REG;
extern Uart_REG Uart;

#endif  // end of F28X_PROJECT_H definition

//
// End of file
//
