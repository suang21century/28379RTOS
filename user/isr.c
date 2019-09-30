/*
 * isr.c
 *
 *  Created on: 2018��6��21��
 *      Author: SuAng
 */


#include "F28x_Project.h"

Rec r1;//���д��������˶���

interrupt void timer0_isr(void)
{
  Swi_post(swi);//��������ж�
  //Swi_post(swi1);//��������ж�
  StartDMACH5();
  CpuTimer0Regs.TCR.bit.TIF=1;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void adc1_isr(void)//10khz
{
  //Swi_post(swi);
  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;                        //��ADC�ж�
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
interrupt void scirx_isr(void)                   //
{
    while(ScicRegs.SCIFFRX.bit.RXFFST>0)   // Rx��buffer��������δ��
    {
      r1.data =ScicRegs.SCIRXBUF.all&0x00ff;     // �ӽ���buffer���ȡ����
      Queue_enqueue(myQ, &(r1.elem));//�������
    }
    //Swi_post(swi1);//��������ж�
  ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
  ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

  PieCtrlRegs.PIEACK.all =PIEACK_GROUP8;       // Issue PIE ack
}
