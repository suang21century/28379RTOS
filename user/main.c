/*
 *  ======== main.c ========
 */
#include <F28x_Project.h>
#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/hal/Timer.h>


Queue_Handle myQ;//定义队列
Void clk0Fxn(UArg arg0);
Void clk1Fxn(UArg arg0);

Clock_Struct clk0Struct;
Clock_Handle clk2Handle;

/*
 *  ======== taskFxn ========
 */
Uint16 t=0;
Void taskFxn(UArg a0, UArg a1)
{
  while(1)
  {
//    GPIO_WritePin(BLINKY_LED_GPIO, 0);
//    Task_sleep(1000);
//    GPIO_WritePin(BLINKY_LED_GPIO, 1);
    t++;
    Task_sleep(1000);
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
/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;//初始化任务
    Task_Handle task1;//初始化任务
    Error_Block eb;
    Clock_Params clkParams;

    System_printf("enter main()\n");

    //InitCpu();
    //InitCtrl();
    GPIO_SetupPinMux(BLINKY_LED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(BLINKY_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(BLINKY_LED_GPIO, 1);
    GPIO_SetupPinMux(BLINKY_LED_GPIO2, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(BLINKY_LED_GPIO2, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(BLINKY_LED_GPIO2, 1);
    //创建队列
    myQ = Queue_create(NULL, NULL);

    //创建任务
    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
        task1 = Task_create(task1Fxn, NULL, &eb);
        if (task1 == NULL) {
            System_printf("Task1_create() failed!\n");
            BIOS_exit(0);
        }

        //创建clock任务
        Clock_Params_init(&clkParams);
        clkParams.period = 1000;  //1000*tickperiod(1000us)
        clkParams.startFlag = TRUE;

        Clock_construct(&clk0Struct, (Clock_FuncPtr)clk0Fxn,
                        1000, &clkParams);
    BIOS_start();    /* does not return */
    return(0);
}

Void clk0Fxn(UArg arg0)  //定时任务，与软中断同级，1s
{
 GpioDataRegs.GPATOGGLE.bit.GPIO31=1;
}
