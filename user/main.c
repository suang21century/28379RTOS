/*
 *  ======== main.c ========
 */
#include <F28x_Project.h>

Queue_Handle myQ;//定义队列

Task_Handle task;//初始化任务
Task_Handle task1;//初始化任务

Swi_Handle swi;

//Timer_Handle timer;

Clock_Struct clk0Struct;

/*
 *  ======== main ========
 */
Int main()
{ 
//    Timer_Params timerParams;
    Error_Block eb;
    Clock_Params clkParams;

    System_printf("enter main()\n");

    InitCpu();
    InitCtrl();

    //创建队列
    myQ = Queue_create(NULL, NULL);

    //创建swi
    Error_init(&eb);
    swi = Swi_create(swiFxn, NULL, &eb);
    if (swi == NULL) {
        System_printf("Swi create failed");
    }
    //创建task任务
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

//    //创建timer定时hwi
//    timerParams.period = 1000;
//    timer = Timer_create(Timer_ANY, hwiFxn, &timerParams, &eb);
//    if (timer == NULL) {
//        System_printf("Timer create failed");
//    }
    //创建clock任务
    Clock_Params_init(&clkParams);
    clkParams.period = 1000;  //1000*tickperiod(1000us)
    clkParams.startFlag = TRUE;

    Clock_construct(&clk0Struct, (Clock_FuncPtr)clk0Fxn,
                        1000, &clkParams);

    BIOS_start();    /* does not return */
    return(0);
}

