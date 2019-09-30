
#include "F28x_Project.h"
#pragma DATA_SECTION(sdata, "ramgs0");  // ����cmd��������ڴ�
#pragma DATA_SECTION(rdata, "ramgs1");
#define BURST       7       //���32���ڴ浥Ԫ��ÿ��Ԫ16bit��ÿ��    ����Ԫ
#define TRANSFER    15        //   ������128����Ԫ
Uint16 *DMADest;
Uint16 *DMASource;
Uint16 sdata[128];   // Send data buffer
Uint16 rdata[128];   // Receive data buffer

void InitCpu()
{

//###########################################################################
// ����ʱ�Ӻ��ж��������ʼ��
//###########################################################################
  InitSysCtrl();
  //InitPeripheralClocks();
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


  EALLOW;
  CpuTimer0Regs.PRD.all  = 200000000;    //�������� 10k
  CpuTimer0Regs.TPR.all  = 0;           // ��ʱ������Ƶ
  CpuTimer0Regs.TPRH.all = 0;
  CpuTimer0Regs.TIM.all = 0xffffffff;            // ������0��ʼ
  CpuTimer0Regs.TCR.all = 0xC020;       // �ж�ʹ��,��ʱ������   0xC020
  CpuTimer0Regs.TCR.bit.TSS = 0;    //start timer

  ClkCfgRegs.LOSPCP.all = 0;// ==sysclk,Ĭ��ֵ2��Ϊsysclk/4
  //---------------------------gpio-------------------------//

  //scic
  GpioCtrlRegs.GPBGMUX2.bit.GPIO56 = 1;
  GpioCtrlRegs.GPEGMUX1.bit.GPIO139 = 1;
  GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 2; //rx
  GpioCtrlRegs.GPEMUX1.bit.GPIO139 = 2; //tx
  //led
  GPIO_SetupPinMux(BLINKY_LED_GPIO, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(BLINKY_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_WritePin(BLINKY_LED_GPIO, 1);
  GPIO_SetupPinMux(BLINKY_LED_GPIO2, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(BLINKY_LED_GPIO2, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_WritePin(BLINKY_LED_GPIO2, 1);

  //pwm
  GPIO_SetupPinMux(0, GPIO_MUX_CPU1, 1);
  GPIO_SetupPinMux(1, GPIO_MUX_CPU1, 1);
  GPIO_SetupPinOptions(0, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_SetupPinOptions(1, GPIO_OUTPUT, GPIO_PUSHPULL);
  EDIS;

  //spiC
  EALLOW;
  GpioCtrlRegs.GPDPUD.all &= 0xC3FFFFFF;

  GpioCtrlRegs.GPDGMUX2.bit.GPIO122 = 0x1;
  GpioCtrlRegs.GPDGMUX2.bit.GPIO123 = 0x1;
  GpioCtrlRegs.GPDGMUX2.bit.GPIO124 = 0x1;
  GpioCtrlRegs.GPDGMUX2.bit.GPIO125 = 0x1;

  GpioCtrlRegs.GPDMUX2.bit.GPIO122 = 0x2;
  GpioCtrlRegs.GPDMUX2.bit.GPIO123 = 0x2;
  GpioCtrlRegs.GPDMUX2.bit.GPIO124 = 0x2;
  GpioCtrlRegs.GPDMUX2.bit.GPIO125 = 0x2;

  GpioCtrlRegs.GPDQSEL2.all |= 0x03F00000;
  EDIS;
//-----------------------------------epwm---------------------------------------//
  EALLOW;
  ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=0x1;    //pwmģ������ʱ�ӷ�Ƶ��Ĭ��Ϊ2��Ƶ
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;// ��ֹePMWʱ��
  EDIS;
           EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
           EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
           EPwm5Regs.TBCTL.bit.SYNCOSEL = 0;
           EPwm1Regs.TBCTL.bit.PHSEN = 1;
           EPwm2Regs.TBCTL.bit.PHSEN = 1;
           EPwm5Regs.TBCTL.bit.PHSEN = 1;
           EPwm1Regs.CMPA.bit.CMPA=2500;
           EPwm2Regs.CMPA.bit.CMPA=2500;
           EPwm5Regs.CMPA.bit.CMPA=2500;
           EPwm1Regs.TBCTL.all=0xA00A;
           EPwm2Regs.TBCTL.all=0xA00A;          // run free;û��Ƶ��ͬ����Ӱ�ӼĴ�������������
           EPwm5Regs.TBCTL.all=0xA00A;
           EPwm1Regs.TBPHS.all=0;
           EPwm2Regs.TBPHS.all=0;
           EPwm5Regs.TBPHS.all=0;
           EPwm1Regs.TBPRD=5000;                //5000=10khz��100Mhz
           EPwm2Regs.TBPRD=5000;
           EPwm5Regs.TBPRD=5000;
           EPwm1Regs.TBCTR=0;
           EPwm2Regs.TBCTR=0;
           EPwm5Regs.TBCTR=0;
           EPwm1Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��0x0050
           EPwm2Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��
           EPwm5Regs.CMPCTL.all  = 0x0000;       // ����Ϊ0ʱCMPA/Bֱ��װ��
           EPwm1Regs.DBCTL.all=0x000B;
           EPwm2Regs.DBCTL.all=0x000B;           //����
           EPwm5Regs.DBCTL.all=0x000B;
           EPwm1Regs.DBRED.all=100;              //1us
           EPwm2Regs.DBRED.all=100;
           EPwm5Regs.DBRED.all=100;
           EPwm1Regs.DBFED.all=100;
           EPwm2Regs.DBFED.all=100;
           EPwm5Regs.DBFED.all=100;
           EPwm1Regs.PCCTL.all=0;
           EPwm2Regs.PCCTL.all=0;
           EPwm5Regs.PCCTL.all=0;
           EPwm1Regs.AQCTLA.all=0x0060;   //����ƥ��ʱ�ߣ��½�ƥ��ʱ��
           EPwm2Regs.AQCTLA.all=0x0060;
           EPwm5Regs.AQCTLA.all=0x0060;   //
           EPwm1Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
           EPwm2Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
           EPwm5Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
  EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;// ������ɺ�����EPWMģ��ʱ��
  EDIS;
//###########################################################################
// ADC
//###########################################################################
  EALLOW;
  AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /1
  AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12λ�����˲���
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
  DELAY_US(1000);

  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
  AdcaRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //pwm1SOCAͨ������
  AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
  AdcaRegs.ADCSOC1CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC2CTL.bit.CHSEL = 1;  //SOC0 will convert pin A1  IV  B�����
  AdcaRegs.ADCSOC2CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC3CTL.bit.CHSEL = 2;  //SOC0 will convert pin A2  IW  A�����
  AdcaRegs.ADCSOC3CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC4CTL.bit.CHSEL = 3;  //SOC0 will convert pin A3
  AdcaRegs.ADCSOC4CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC5CTL.bit.CHSEL = 4;  //SOC0 will convert pin A4  IU  C�����
  AdcaRegs.ADCSOC5CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC6CTL.bit.CHSEL = 5;  //SOC0 will convert pin A5
  AdcaRegs.ADCSOC6CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 5;

  AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 4; //SOC4�����ж�
  AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag

  EPwm1Regs.ETSEL.bit.SOCAEN    = 0;            // Disable SOC on A group
   EPwm1Regs.ETSEL.bit.SOCASEL = 1;            // count=0
  EPwm1Regs.ETPS.bit.SOCAPRD = 1;

  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
  EDIS;
  EPwm1Regs.ETSEL.bit.SOCAEN = 1;  //enable SOCA

  //ADCB
  EALLOW;
  AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /1
  AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12λ�����˲���
  AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
  AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
  DELAY_US(1000);

  AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin B0
  AdcbRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  //pwm1SOCAͨ������
  EDIS;
//-------------------------------------SCIB------------------------------//
  ScicRegs.SCICCR.all  = 0x0007; // 8bit ��У�� �޵�ַ
  ScicRegs.SCICTL1.all = 0x0023; //
  ScicRegs.SCICTL2.all = 0x0002;
  ScicRegs.SCIHBAUD.all    = 0;
  ScicRegs.SCILBAUD.all    = 0x00D8; //  D8=115200  26;//26=921600;
  ScicRegs.SCIFFTX.all = 0xe010;//16�ֽ�fifo
  ScicRegs.SCIFFRX.all = 0x2021;//8���ֽڴ����ж�
  ScicRegs.SCIFFCT.all = 0x0000;


//-----------------------------DMA--------------------------//

  DMAInitialize();

  DMASource =( Uint16 * )sdata;
  DMADest = ( Uint16 * )rdata;
  DMACH5AddrConfig(&SpicRegs.SPITXBUF,DMASource);
  DMACH5BurstConfig(BURST,1,0);    //ÿ�����ٸ���Ԫ����ַ������
  DMACH5TransferConfig(TRANSFER,1,0);  //���ٲ����ݣ���ַ������
  DMACH5ModeConfig(DMA_SPICTX,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                       SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                       CHINT_END,CHINT_ENABLE);

  EALLOW;
  CpuSysRegs.SECMSEL.bit.PF2SEL = 1;
  EDIS;
  Uint16 i;
  for(i = 0; i < 128; i++)
  {
      sdata[i] = i;
      rdata[i] = 0;
  }



//--------------------------SPIC-----------------------------//
  /// <li> SPI��ʼ��: �����10MHz,ʱ���������������
  SpicRegs.SPICCR.bit.SPISWRESET = 1;
  SpicRegs.SPICCR.all = 0x008F;         // SCK��������������½��ؽ�������,16bit����,���ûػ�
  SpicRegs.SPICTL.all = 0x000E;         // ����ģʽ,ʹ��ste,�����ж�
  //SpicRegs.SPISTS.all = 0x00e0;
  SpicRegs.SPIBRR.all     = 19;              // ��߲�����90MHz/9=10MHz
  SpicRegs.SPIFFRX.all = 0x4444;        // ��־����,��λ,ʹ�ܽ���4�����ж�
  SpicRegs.SPIFFTX.all = 0xe048;        // ��λ,���ж�,��������λ�жϱ�־,fifo8
  SpicRegs.SPIFFCT.all = 0;
  SpicRegs.SPIPRI.all = 0x0020;
  SpicRegs.SPIFFRX.bit.RXFIFORESET = 1; // ��������FIFO

  StartDMACH5();
}
