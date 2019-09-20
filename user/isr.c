/*
 * isr.c
 *
 *  Created on: 2018年6月21日
 *      Author: SuAng
 */


#include "F28x_Project.h"

//Rec r1;

interrupt void timer0_isr(void)
{
  Swi_post(swi1);

//  if(r1.data++>2)r1.data=0;
//  Queue_enqueue(myQ, &(r1.elem));

  CpuTimer0Regs.TCR.bit.TIF=1;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void adc1_isr(void)//10khz
{
  Swi_post(swi);
  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;                        //清ADC中断
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void sciarx_isr(void)                   //
{
    Uint16 i;
    while(SciaRegs.SCIFFRX.bit.RXFFST>0)   // Rx的buffer中有数据未读
    {
      i =SciaRegs.SCIRXBUF.all&0x00ff;     // 从接收buffer里读取数据

    }
  SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

  PieCtrlRegs.PIEACK.all =PIEACK_GROUP9;       // Issue PIE ack
}
