/*
 * isr.c
 *
 *  Created on: 2018年6月21日
 *      Author: SuAng
 */


#include "F28x_Project.h"

Rec r1;//队列待传量按此定义

interrupt void timer0_isr(void)
{
  Swi_post(swi);//触发软件中断
  //Swi_post(swi1);//触发软件中断
  StartDMACH5();
  CpuTimer0Regs.TCR.bit.TIF=1;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void adc1_isr(void)//10khz
{
  //Swi_post(swi);
  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;                        //清ADC中断
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void scirx_isr(void)                   //
{
    while(ScicRegs.SCIFFRX.bit.RXFFST>0)   // Rx的buffer中有数据未读
    {
      r1.data =ScicRegs.SCIRXBUF.all&0x00ff;     // 从接收buffer里读取数据
      Queue_enqueue(myQ, &(r1.elem));//队列添加
    }
    //Swi_post(swi1);//触发软件中断
  ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

  PieCtrlRegs.PIEACK.all =PIEACK_GROUP8;       // Issue PIE ack
}
