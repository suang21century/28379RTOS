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

//----------------------------------包含文件-----------------------------//

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

//--------------------------函数声明----------------------------//
extern void InitCpu(void);
extern void InitCtrl(void);

extern interrupt void timer0_isr(void);
extern interrupt void adc1_isr(void);
extern interrupt void sciarx_isr(void);

extern Queue_Handle myQ;//声明队列
extern Semaphore_Handle sem;//声明信号量
extern Task_Handle task;//声明任务
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

//-------------------------------宏定义--------------------------//
#define BLINKY_LED_GPIO 31
#define BLINKY_LED_GPIO2 34

//-------------------------------结构体变量-------------------------//
typedef struct Rec {
Queue_Elem elem;
Int data;
} Rec;

typedef struct
{
Uint16     En;
Uint16     RxFlag;      //接收标志，为1需修改，修改后复位0
Uint16     ZeroFlag;
Uint16     WriteFlag;   //写入标志，为1需写入FLASH的H区，完成后复位0
Uint16     RxType;        //串口接收的类型
Uint16     Read1;
Uint16     Read2;
int32      RxTmp;
Uint16     RxSum;        // 接受指令的累加
Uint16     RxCnt;        // 已经接受到的字节数
Uint16     TxType;       //发送类型，由接收的帧类型0的反馈指向决定
Uint16     TxData[2];    // 发送的两个数据字节
int16      TxTemp;       //待发送暂存
Uint16     TxTemp1;       //待发送暂存
Uint16     TxCnt;        // 已经发送的数据长度
Uint16     TxSum;        //已发送的数据的加和；
Uint16     Ver;
Uint16     Buffer[256];   //存储参数，待写入flash
}Uart_REG;
extern Uart_REG Uart;

#endif  // end of F28X_PROJECT_H definition

//
// End of file
//
