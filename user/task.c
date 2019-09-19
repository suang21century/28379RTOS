/*
 * task.c
 *
 *  Created on: 2019年9月19日
 *      Author: suang
 */
#include <F28x_Project.h>



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

Void clk0Fxn(UArg arg0)  //定时任务，与软中断同级，1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;

}
