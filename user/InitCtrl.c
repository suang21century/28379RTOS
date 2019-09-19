
#include "F28x_Project.h"


void InitCtrl()
{
  EALLOW;
    PieVectTable.ADCA1_INT = &adc1_isr; //function for ADCA interrupt 1
    PieVectTable.SCIA_RX_INT = &sciarx_isr;
  EDIS;

  IER |= M_INT1;
  IER |= M_INT9;
  PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
  PieCtrlRegs.PIEIER9.bit.INTx1 = 1;  //scirx
  EINT;
  ERTM;

}

