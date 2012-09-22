#include "Configure.h"


//����Key_press task �������ջ
OS_STK keyMainStk[TASK_STK_SIZE];

OS_STK timeStk[TASK_STK_SIZE];

//��ʼʱ���жϳ���
void startTimer(void* arg){
  arg=arg;
	T0TCR = 1;//�ؼ�
#if DEBUG==TRUE
  debug("Start Timer Service.");
#endif
  OSTaskDel(OS_PRIO_SELF);
}

void init(){
  TargetInit();
  OSInit();
  Environment_Initial();
  srand(OSTimeGet());
#if DEBUG==TRUE
  debug("Initialize: Target, OS, LCDs, Key, Environment.");
#endif
}

int main()
{
  init();
  OSTaskCreate(startTimer, NULL, &timeStk[TASK_STK_SIZE-1],OPEN_TIME_PRIO);
  OSTaskCreate(Key_Main, NULL, &keyMainStk[TASK_STK_SIZE-1], KEY_PRIO);
  OSStart();
}

