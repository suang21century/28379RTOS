/*
 *  ======== main.c ========
 */
#include <F28x_Project.h>

Uart_REG Uart;

Queue_Handle myQ;//�������
Task_Handle task;//��������
Task_Handle task1;//��������
Task_Handle task2;
Swi_Handle swi;  //��������ж�
Swi_Handle swi1;
Clock_Struct clk0Struct;//����ʱ������
Semaphore_Handle sem;  //�����ź���
Semaphore_Handle sem1;
Event_Handle myEvent; //�����¼���ͬswitch
//Timer_Handle timer;

/*
 *  ======== main ========
 */
Int main()
{ 
//    Timer_Params timerParams;
    Error_Block eb;
    Clock_Params clkParams;
    Task_Params taskParams;
    Task_Params_init(&taskParams);

    System_printf("enter main()\n");

    InitCpu();
    InitCtrl();

    //��������
    myQ = Queue_create(NULL, NULL);
    //�����ź���
    sem = Semaphore_create(0, NULL, &eb);
    sem1 = Semaphore_create(0, NULL, &eb);
    //�����¼�
    myEvent = Event_create(NULL, &eb);
    //����swi
    Error_init(&eb);
    swi = Swi_create(swiFxn, NULL, &eb);
    if (swi == NULL) {
        System_printf("Swi create failed");
    }
    swi1 = Swi_create(swi1Fxn, NULL, &eb);
    if (swi1 == NULL) {
        System_printf("Swi1 create failed");
    }
    //����task����
    Error_init(&eb);
    taskParams.instance->name = "task";
    taskParams.priority = 3;
//    taskParams.stackSize = 512;
    task = Task_create(taskFxn, &taskParams, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }
    taskParams.instance->name = "task1";
    taskParams.priority = 4;
//    taskParams.stackSize = 512;
    task1 = Task_create(task1Fxn, &taskParams, &eb);
    if (task1 == NULL) {
        System_printf("Task1_create() failed!\n");
        BIOS_exit(0);
    }
    taskParams.instance->name = "task2";
    taskParams.priority = 5;
//    taskParams.stackSize = 512;
    task2 = Task_create(task2Fxn, &taskParams, &eb);
    if (task2 == NULL) {
        System_printf("Task2_create() failed!\n");
        BIOS_exit(0);
    }
//    //����timer��ʱhwi
//    timerParams.period = 1000;
//    timer = Timer_create(Timer_ANY, hwiFxn, &timerParams, &eb);
//    if (timer == NULL) {
//        System_printf("Timer create failed");
//    }
    //����clock����
    Clock_Params_init(&clkParams);
    clkParams.period = 1000;  //1000*tickperiod(1000us)
    clkParams.startFlag = TRUE;

    Clock_construct(&clk0Struct, (Clock_FuncPtr)clk0Fxn,
                        1000, &clkParams);

    BIOS_start();    /* does not return */
    return(0);
}

