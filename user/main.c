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



Queue_Handle myQ;//定义队列


/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
  while(1)
  {
    GPIO_WritePin(BLINKY_LED_GPIO, 0);
    Task_sleep(1000);
    GPIO_WritePin(BLINKY_LED_GPIO, 1);
    Task_sleep(1000);
    GPIO_WritePin(BLINKY_LED_GPIO2, 0);
    Task_sleep(500);
    GPIO_WritePin(BLINKY_LED_GPIO2, 1);
    Task_sleep(500);
  }
}

/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;//初始化任务
    Error_Block eb;


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

    BIOS_start();    /* does not return */
    return(0);
}
