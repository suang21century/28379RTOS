
#include "F28x_Project.h"

void InitCpu()
{

//###########################################################################
// ����ʱ�Ӻ��ж��������ʼ��
//###########################################################################
  InitSysCtrl();
//  SeizeFlashPump();
//  DINT;
//  InitPieCtrl();
//
//  IER = 0x0000;
//  IFR = 0x0000;
//
//  InitPieVectTable();
//
//  EINT;
//  ERTM;
//
//  // ��ʼ��Timer
//  InitCpuTimers();

//  CpuTimer0Regs.PRD.all  = 200000000;    //�������� 10k
//  CpuTimer0Regs.TPR.all  = 0;           // ��ʱ������Ƶ
//  CpuTimer0Regs.TPRH.all = 0;
//  CpuTimer0Regs.TIM.all = 0xffffffff;            // ������0��ʼ
//  CpuTimer0Regs.TCR.all = 0xC020;       // �ж�ʹ��,��ʱ������   0xC020
//  CpuTimer0Regs.TCR.bit.TSS = 0;    //start timer
////###########################################################################
//// pwm
////###########################################################################
//  EALLOW;
//  GPIO_SetupPinMux(BLINKY_LED_GPIO, GPIO_MUX_CPU1, 0);
//  GPIO_SetupPinOptions(BLINKY_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);
//
//  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;// ��ֹePMWʱ��
//  EDIS;
//           EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
//           EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
//           EPwm5Regs.TBCTL.bit.SYNCOSEL = 0;
//           EPwm1Regs.TBCTL.bit.PHSEN = 1;
//           EPwm2Regs.TBCTL.bit.PHSEN = 1;
//           EPwm5Regs.TBCTL.bit.PHSEN = 1;
//           EPwm1Regs.CMPA.bit.CMPA=2500;
//           EPwm2Regs.CMPA.bit.CMPA=2500;
//           EPwm5Regs.CMPA.bit.CMPA=2500;
//           EPwm1Regs.TBCTL.all=0xA00A;
//           EPwm2Regs.TBCTL.all=0xA00A;          // run free;û��Ƶ��ͬ����Ӱ�ӼĴ�������������
//           EPwm5Regs.TBCTL.all=0xA00A;
//           EPwm1Regs.TBPHS.all=0;
//           EPwm2Regs.TBPHS.all=0;
//           EPwm5Regs.TBPHS.all=0;
//           EPwm1Regs.TBPRD=5000;                //5000=10khz��100Mhz
//           EPwm2Regs.TBPRD=5000;
//           EPwm5Regs.TBPRD=5000;
//           EPwm1Regs.TBCTR=0;
//           EPwm2Regs.TBCTR=0;
//           EPwm5Regs.TBCTR=0;
//           EPwm1Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��0x0050
//           EPwm2Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��
//           EPwm5Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��
//           EPwm1Regs.DBCTL.all=0x000B;
//           EPwm2Regs.DBCTL.all=0x000B;           //����
//           EPwm5Regs.DBCTL.all=0x000B;
//           EPwm1Regs.DBRED.all=100;              //1us
//           EPwm2Regs.DBRED.all=100;
//           EPwm5Regs.DBRED.all=100;
//           EPwm1Regs.DBFED.all=100;
//           EPwm2Regs.DBFED.all=100;
//           EPwm5Regs.DBFED.all=100;
//           EPwm1Regs.PCCTL.all=0;
//           EPwm2Regs.PCCTL.all=0;
//           EPwm5Regs.PCCTL.all=0;
//           EPwm1Regs.AQCTLA.all=0x0060;   //����ƥ��ʱ�ߣ��½�ƥ��ʱ��
//           EPwm2Regs.AQCTLA.all=0x0060;
//           EPwm5Regs.AQCTLA.all=0x0060;   //
//           EPwm1Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
//           EPwm2Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
//           EPwm5Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
//  EALLOW;
//    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;// ������ɺ�����EPWMģ��ʱ��
//  EDIS;
////###########################################################################
//// ADC
////###########################################################################
//  EALLOW;
//  AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /1
//  AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12λ�����˲���
//  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
//  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
//  DELAY_US(1000);
//
//  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
//  AdcaRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //pwm1SOCAͨ������
//  AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
//  AdcaRegs.ADCSOC1CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
//  AdcaRegs.ADCSOC2CTL.bit.CHSEL = 1;  //SOC0 will convert pin A1  IV  B�����
//  AdcaRegs.ADCSOC2CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
//  AdcaRegs.ADCSOC3CTL.bit.CHSEL = 2;  //SOC0 will convert pin A2  IW  A�����
//  AdcaRegs.ADCSOC3CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
//  AdcaRegs.ADCSOC4CTL.bit.CHSEL = 3;  //SOC0 will convert pin A3
//  AdcaRegs.ADCSOC4CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
//  AdcaRegs.ADCSOC5CTL.bit.CHSEL = 4;  //SOC0 will convert pin A4  IU  C�����
//  AdcaRegs.ADCSOC5CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 5;
//  AdcaRegs.ADCSOC6CTL.bit.CHSEL = 5;  //SOC0 will convert pin A5
//  AdcaRegs.ADCSOC6CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 5;
//
//  AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 4; //SOC4�����ж�
//  AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
//
//  EPwm1Regs.ETSEL.bit.SOCAEN    = 0;            // Disable SOC on A group
//   EPwm1Regs.ETSEL.bit.SOCASEL = 1;            // count=0
//  EPwm1Regs.ETPS.bit.SOCAPRD = 1;
//
//  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
//  EDIS;
//  EPwm1Regs.ETSEL.bit.SOCAEN = 1;  //enable SOCA
//
//  //ADCB
//  EALLOW;
//  AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /1
//  AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12λ�����˲���
//  AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
//  AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
//  DELAY_US(1000);
//
//  AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin B0
//  AdcbRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
//  AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  //pwm1SOCAͨ������
//  EDIS;
  //******SCI��ʼ��*****************************************
  // ��������:8λ,��У��,1λֹͣλ,�����ж�,�ж��ڳ�ʼ����ɺ�ͳһ��
  //********************************************************
  SciaRegs.SCICCR.all  = 0x0007; // 8bit ��У�� �޵�ַ
  SciaRegs.SCICTL1.all = 0x0023; //
  SciaRegs.SCICTL2.all = 0x0002;
  SciaRegs.SCIHBAUD.all    = 0x0000;
  SciaRegs.SCILBAUD.all    = 0x00D8; //  D8=11520026;//26=921600;
  SciaRegs.SCIFFTX.all = 0xe010;//16�ֽ�fifo
  SciaRegs.SCIFFRX.all = 0x2028;//8���ֽڴ����ж�
  SciaRegs.SCIFFCT.all = 0x0000;



}
