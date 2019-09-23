
#include "F28x_Project.h"
#pragma DATA_SECTION(sdata, "ramgs0");  // 需在cmd定义相关内存
#pragma DATA_SECTION(rdata, "ramgs1");
#define BURST       31       //最大32个内存单元，每单元16bit
#define TRANSFER    4        //4波发完128个单元
Uint16 *DMADest;
Uint16 *DMASource;
Uint16 sdata[128];   // Send data buffer
Uint16 rdata[128];   // Receive data buffer
void dma_init()
{

    DMAInitialize();

    DMASource = ( Uint16 *)sdata;
    DMADest = (  Uint16 *)rdata;

    DMACH6AddrConfig(DMADest,DMASource);
    DMACH6BurstConfig(BURST,1,1);
    DMACH6TransferConfig(TRANSFER,1,1);
    DMACH6ModeConfig(68,PERINT_ENABLE,ONESHOT_ENABLE,CONT_ENABLE,        //触发源T0，中断使能，一次触发发送全部数据，连续使能
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
}
void InitCpu()
{

//###########################################################################
// 外设时钟和中断向量表初始化
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
//  // 初始化Timer
//  InitCpuTimers();

  CpuTimer0Regs.PRD.all  = 200000000;    //周期设置 10k
  CpuTimer0Regs.TPR.all  = 0;           // 定时器不分频
  CpuTimer0Regs.TPRH.all = 0;
  CpuTimer0Regs.TIM.all = 0xffffffff;            // 计数从0开始
  CpuTimer0Regs.TCR.all = 0xC020;       // 中断使能,定时器启动   0xC020
  CpuTimer0Regs.TCR.bit.TSS = 0;    //start timer


  //---------------------------gpio-------------------------//

  GPIO_SetupPinMux(BLINKY_LED_GPIO, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(BLINKY_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_WritePin(BLINKY_LED_GPIO, 1);
  GPIO_SetupPinMux(BLINKY_LED_GPIO2, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(BLINKY_LED_GPIO2, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_WritePin(BLINKY_LED_GPIO2, 1);


  GPIO_SetupPinMux(0, GPIO_MUX_CPU1, 1);
  GPIO_SetupPinMux(1, GPIO_MUX_CPU1, 1);
  GPIO_SetupPinOptions(0, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_SetupPinOptions(1, GPIO_OUTPUT, GPIO_PUSHPULL);
//###########################################################################
// pwm
//###########################################################################
  EALLOW;
  ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV=0x1;    //pwm模块外设时钟分频，默认为2分频
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;// 禁止ePMW时钟
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
           EPwm2Regs.TBCTL.all=0xA00A;          // run free;没分频；同步；影子寄存器；增减记数
           EPwm5Regs.TBCTL.all=0xA00A;
           EPwm1Regs.TBPHS.all=0;
           EPwm2Regs.TBPHS.all=0;
           EPwm5Regs.TBPHS.all=0;
           EPwm1Regs.TBPRD=5000;                //5000=10khz，100Mhz
           EPwm2Regs.TBPRD=5000;
           EPwm5Regs.TBPRD=5000;
           EPwm1Regs.TBCTR=0;
           EPwm2Regs.TBCTR=0;
           EPwm5Regs.TBCTR=0;
           EPwm1Regs.CMPCTL.all  = 0x0000;       // 计数为0时CMPA/B直接装载0x0050
           EPwm2Regs.CMPCTL.all  = 0x0000;       // 计数为0时CMPA/B直接装载
           EPwm5Regs.CMPCTL.all  = 0x0000;       // 计数为0时CMPA/B直接装载
           EPwm1Regs.DBCTL.all=0x000B;
           EPwm2Regs.DBCTL.all=0x000B;           //死区
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
           EPwm1Regs.AQCTLA.all=0x0060;   //上升匹配时高，下降匹配时低
           EPwm2Regs.AQCTLA.all=0x0060;
           EPwm5Regs.AQCTLA.all=0x0060;   //
           EPwm1Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
           EPwm2Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
           EPwm5Regs.AQCSFRC.all=0x0000;  //a PWM b PWM
  EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;// 设置完成后启动EPWM模块时钟
  EDIS;
//###########################################################################
// ADC
//###########################################################################
  EALLOW;
  AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /1
  AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12位，单端采样
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
  DELAY_US(1000);

  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
  AdcaRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5; //pwm1SOCA通道触发
  AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0;  //SOC0 will convert pin A0
  AdcaRegs.ADCSOC1CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC2CTL.bit.CHSEL = 1;  //SOC0 will convert pin A1  IV  B相电流
  AdcaRegs.ADCSOC2CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC3CTL.bit.CHSEL = 2;  //SOC0 will convert pin A2  IW  A相电流
  AdcaRegs.ADCSOC3CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC4CTL.bit.CHSEL = 3;  //SOC0 will convert pin A3
  AdcaRegs.ADCSOC4CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC5CTL.bit.CHSEL = 4;  //SOC0 will convert pin A4  IU  C相电流
  AdcaRegs.ADCSOC5CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 5;
  AdcaRegs.ADCSOC6CTL.bit.CHSEL = 5;  //SOC0 will convert pin A5
  AdcaRegs.ADCSOC6CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 5;

  AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 4; //SOC4触发中断
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
  AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  //12位，单端采样
  AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
  AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
  DELAY_US(1000);

  AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;  //SOC0 will convert pin B0
  AdcbRegs.ADCSOC0CTL.bit.ACQPS = 6; //sample window is 6 SYSCLK cycles
  AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  //pwm1SOCA通道触发
  EDIS;
  //******SCI初始化*****************************************
  // 串口设置:8位,无校验,1位停止位,接收中断,中断在初始化完成后统一打开
  //********************************************************
  SciaRegs.SCICCR.all  = 0x0007; // 8bit 无校验 无地址
  SciaRegs.SCICTL1.all = 0x0023; //
  SciaRegs.SCICTL2.all = 0x0002;
  SciaRegs.SCIHBAUD.all    = 0x0000;
  SciaRegs.SCILBAUD.all    = 0x00D8; //  D8=11520026;//26=921600;
  SciaRegs.SCIFFTX.all = 0xe010;//16字节fifo
  SciaRegs.SCIFFRX.all = 0x2028;//8个字节触发中断
  SciaRegs.SCIFFCT.all = 0x0000;
//-----------------------------DMA--------------------------//

//  DmaRegs.DMACTRL.bit.HARDRESET = 1;
//  __asm (" nop");
//  DmaRegs.DEBUGCTRL.bit.FREE = 1;
//
//
//
//  DmaRegs.CH6.SRC_BEG_ADDR_SHADOW =  (Uint32)(volatile Uint16 *)sdata;
//  DmaRegs.CH6.SRC_ADDR_SHADOW =      (Uint32)(volatile Uint16 *)sdata;
//  DmaRegs.CH6.DST_BEG_ADDR_SHADOW =  (Uint32)(volatile Uint16 *)rdata;
//  DmaRegs.CH6.DST_ADDR_SHADOW =      (Uint32)(volatile Uint16 *)rdata;
//  DmaRegs.DEBUGCTRL.bit.FREE = 1;

  dma_init();
  EALLOW;
  CpuSysRegs.SECMSEL.bit.PF2SEL = 1;
  EDIS;
  Uint16 i;
  for(i = 0; i < 128; i++)
  {
      sdata[i] = i;
      rdata[i] = 0;
  }
  StartDMACH6();
}
