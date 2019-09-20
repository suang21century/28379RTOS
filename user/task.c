/*
 * task.c
 *
 *  Created on: 2019年9月19日
 *      Author: suang
 */
#include <F28x_Project.h>



//-------------------------------taskfunc-----------------------//
Uint16 t=0,j=0,k=0;
Void taskFxn(UArg a0, UArg a1)
{

  while(1)
  {
    Semaphore_pend(sem, BIOS_WAIT_FOREVER);//接收信号量，未收到时堵塞在此
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

Uint16 s=1000,cnt=0,n=0;
Void task2Fxn(UArg a0, UArg a1)
{
  while(1)
  {
    s--;
    Task_sleep(1000);
  }
}
//-------------------------swifunc-------------------------//
Void swiFxn(UArg arg0, UArg arg1)//由adc硬件中断触发
{
    j++;
}

Rec* rp;
Void swi1Fxn(UArg arg0, UArg arg1)//由timer0硬件中断触发
{
        if(!Queue_empty(myQ))
        {
          rp = Queue_dequeue(myQ);
          switch(cnt)
          {
          case 0 :
            if(rp->data==0) cnt=1;
            else cnt=0;
          case 1:
            if(rp->data==1) cnt=2;
            else cnt=0;
          case 2:
            if(rp->data==2)
            {
              n--;
            }
            cnt=0;
          }
        }
  k++;
  if(k>9)
  {
    k=0;
    Semaphore_post((Semaphore_Object *)sem);//发送信号量
  }
}
//---------------------clock task---------------------//
Void clk0Fxn(UArg arg0)  //clock定时任务，与软中断同级，1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;

}
