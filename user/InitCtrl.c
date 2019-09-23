
#include "F28x_Project.h"


void InitCtrl()
{
  EALLOW;
    PieVectTable.ADCA1_INT = &adc1_isr; //function for ADCA interrupt 1
    PieVectTable.SCIC_RX_INT = &scirx_isr;
    PieVectTable.TIMER0_INT = &timer0_isr;
  EDIS;
  PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
  IER |= M_INT1;
  IER |= M_INT8;
  PieCtrlRegs.PIEIER1.bit.INTx1 = 1; //adc1
  PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //timer0
  PieCtrlRegs.PIEIER8.bit.INTx5 = 1; //scirx
  EINT;
  ERTM;

//  r1.data=0;
}

