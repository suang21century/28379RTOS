/*
 * task.c
 *
 *  Created on: 2019��9��19��
 *      Author: suang
 */
#include <F28x_Project.h>



//-------------------------------taskfunc-----------------------//
Uint16 t=0,j=0,k=0;
Void taskFxn(UArg a0, UArg a1)
{

  while(1)
  {
    Semaphore_pend(sem, BIOS_WAIT_FOREVER);//�����ź�����δ�յ�ʱ�����ڴ�
    t++;
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
Void task2Fxn(UArg a0, UArg a1)
{

}
//-------------------------swifunc-------------------------//
Void swiFxn(UArg arg0, UArg arg1)//��adcӲ���жϴ���
{
    j++;
}
Void swi1Fxn(UArg arg0, UArg arg1)//��timer0Ӳ���жϴ���
{
  k++;
  if(k>9)
  {
    k=0;
    Semaphore_post((Semaphore_Object *)sem);//�����ź���
  }
}
//---------------------clock task---------------------//
Void clk0Fxn(UArg arg0)  //clock��ʱ���������ж�ͬ����1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;

}
