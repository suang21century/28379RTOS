/*
 * isr.c
 *
 *  Created on: 2018��6��21��
 *      Author: SuAng
 */


#include "F28x_Project.h"


interrupt void timer0_isr(void)
{
  Swi_post(swi1);
  CpuTimer0Regs.TCR.bit.TIF=1;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void adc1_isr(void)//10khz
{
  Swi_post(swi);
  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;                        //��ADC�ж�
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void sciarx_isr(void)                   //
{
    Uint16 i;
    while(SciaRegs.SCIFFRX.bit.RXFFST>0)   // Rx��buffer��������δ��
    {
      i =SciaRegs.SCIRXBUF.all&0x00ff;     // �ӽ���buffer���ȡ����

    }
  SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

  PieCtrlRegs.PIEACK.all =PIEACK_GROUP9;       // Issue PIE ack
}
