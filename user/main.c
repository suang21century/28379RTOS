/*
 *  ======== main.c ========
 */
#include <F28x_Project.h>
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

Queue_Handle myQ;//�������

Task_Handle task;//��ʼ������
Task_Handle task1;//��ʼ������

Swi_Handle swi;

Timer_Handle timer;

Void clk0Fxn(UArg arg0);
Void clk1Fxn(UArg arg0);

Clock_Struct clk0Struct;
Clock_Handle clk2Handle;
/*
 *  ======== taskFxn ========
 */
Uint16 t=0,j=0;
Void taskFxn(UArg a0, UArg a1)
{
  while(1)
  {
//    GPIO_WritePin(BLINKY_LED_GPIO, 0);
//    Task_sleep(1000);
//    GPIO_WritePin(BLINKY_LED_GPIO, 1);
//    if(CpuTimer0Regs.TCR.bit.TIF==1)
//    {
//        CpuTimer0Regs.TCR.bit.TIF=1;
        t++;
//    }

    Task_sleep(1000);
  }
}
Void task1Fxn(UArg a0, UArg a1)
{
  while(1)
  {
    GPIO_WritePin(BLINKY_LED_GPIO2, 0);
    Task_sleep(1000);
    GPIO_WritePin(BLINKY_LED_GPIO2, 1);
    Task_sleep(1000);
  }
}

//Void hwiFxn(UArg arg)
//{
//  Swi_post(swi);
//}

/* ======== mySwiFunc ======== */
Void swiFxn(UArg arg0, UArg arg1)
{
//  while(1)
//  {
    j++;
//    DELAY_US(10000);
//  }
}
/*
 *  ======== main ========
 */
Int main()
{ 
    Timer_Params timerParams;
    Error_Block eb;
    Clock_Params clkParams;

    System_printf("enter main()\n");

    InitCpu();
    //InitCtrl();

    //��������
    myQ = Queue_create(NULL, NULL);

    //����swi
    Error_init(&eb);
    swi = Swi_create(swiFxn, NULL, &eb);
    if (swi == NULL) {
        System_printf("Swi create failed");
    }
    //����task����
    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
    task1 = Task_create(task1Fxn, NULL, &eb);
    if (task1 == NULL) {
        System_printf("Task1_create() failed!\n");
        BIOS_exit(0);
    }

//    //����timer��ʱhwi
//    timerParams.period = 1000;
//    timer = Timer_create(Timer_ANY, hwiFxn, &timerParams, &eb);
//    if (timer == NULL) {
//        System_printf("Timer create failed");
//    }
    //����clock����
    Clock_Params_init(&clkParams);
    clkParams.period = 1000;  //1000*tickperiod(1000us)
    clkParams.startFlag = TRUE;

    Clock_construct(&clk0Struct, (Clock_FuncPtr)clk0Fxn,
                        1000, &clkParams);
    BIOS_start();    /* does not return */
    return(0);
}

Void clk0Fxn(UArg arg0)  //��ʱ���������ж�ͬ����1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;
 Swi_post(swi);
}
