#include "Configure.h"

#ifndef __ENVIRONMENT__
#define __ENVIRONMENT__

#define WIN_SCORE  ((MAX_BEANS)*(BEAN_SCORE))  //��Ϸͨ����Ҫ�ķ���
#define TOP_NUMBER ((INT8U)3) //Ӣ�۰����Ŀ

//������ģ����ã����밴��ֵ
INT8U Environment_KeyPress (INT8U ucKeyValue );	  

//����Ϸ����ģ����ã��õ���Ϸ���н���ʱ�ķ���
INT8U Environment_PassScore (INT8U ucScore );	 

//��ʼ��һЩ�ڲ�������GUIģ�飨��Ҫ����LCD1��LCD2��
void Environment_Initial(void);

#endif

