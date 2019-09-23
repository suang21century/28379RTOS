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
//    Uint16 done = 0;           // Test is not done yet
//
//       while(!done)        // wait until the DMA transfer is complete
//       {
//           EALLOW;
//           DmaRegs.CH6.CONTROL.bit.PERINTFRC = 1;
//           EDIS;
//
//           Task_sleep(1000);
//       }
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

Uint16 s=1000,cnt=0;
Void task2Fxn(UArg a0, UArg a1)
{
  UInt events;
  while(1)
  {
      events = Event_pend(myEvent, Event_Id_NONE,
      Event_Id_00 + Event_Id_01 + Event_Id_02,
      BIOS_WAIT_FOREVER);                       //接收事件，否则堵塞
    if (events & Event_Id_00)  //根据事件id进入对应函数
    {
      s--;
    }
    if (events & Event_Id_01)
    {
      s++;
    }
    if (events & Event_Id_02)
    {
      s=s+10;
    }
  }
}
//-------------------------swifunc-------------------------//
Void swiFxn(UArg arg0, UArg arg1)//由timer硬件中断触发
{
    ScicRegs.SCITXBUF.all=0x0088;
      ScicRegs.SCITXBUF.all=0x0055;
      ScicRegs.SCITXBUF.all=0x0055;
      ScicRegs.SCITXBUF.all=0x00AA;
      ScicRegs.SCITXBUF.all=0x00AA;
      ScicRegs.SCITXBUF.all=0x0066;
      ScicRegs.SCITXBUF.all=0x0066;
    //  EALLOW;
    //  DmaRegs.CH6.CONTROL.bit.PERINTFRC = 1;//用于手动软件触发
      //DmaRegs.CH6.CONTROL.bit.HALT = 1;//dma挂起
      //DmaRegs.CH6.CONTROL.bit.RUN = 1; //dma运行
    //  EDIS;

      k++;
      if(k>9)
      {
        k=0;

        Semaphore_post((Semaphore_Object *)sem);//发送信号量
      }
}

Rec* rp;
Void swi1Fxn(UArg arg0, UArg arg1)//由sci硬件中断触发
{

        while(!Queue_empty(myQ))//队列非空
        {
          rp = Queue_dequeue(myQ);//出队列
          switch(cnt)
          {
            case 0 :
              if(rp->data==0x55) cnt=1;
              else cnt=0;
            break;
            case 1:
              if(rp->data==0x01) cnt=2;
              else cnt=0;
            break;
            case 2:
              if(rp->data==0x02)
              {
                Event_post(myEvent, Event_Id_00);//发送id0事件，单次触发
              }
              if(rp->data==0x03)
              {
                Event_post(myEvent, Event_Id_01);//发送id1事件
              }
              if(rp->data==0x04)
              {
                Event_post(myEvent, Event_Id_02);//发送id2事件
              }
              cnt=0;
            break;
          }

        }

}
//---------------------clock task---------------------//
Void clk0Fxn(UArg arg0)  //clock定时任务，与软中断同级，1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;

}
