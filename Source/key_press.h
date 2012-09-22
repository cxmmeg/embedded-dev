#include "Configure.h"

#ifndef __KEY_PRESS__
#define __KEY_PRESS__

#define KEY_LEFT       (1<<24)  	  //���������Ӧ����
#define KEY_UP         (1<<25)
#define KEY_RIGHT      (1<<28)
#define KEY_DOWN       (1<<27)						   
#define KEY_START      (1<<16)            // ��Ӧ���� ���ذ�ť��Ӧ����λ��

#define DIR_KEY_PIN    	  (0xFC30FFFF)	   // �����Pinѡ��ֵ
#define DIR_KEY_PIN_OUT	  (0x1B000000)	   // �������GPIO��Ϊ���
#define START_PIN     	  (0xFFFFFFFC)	   // ��ʼ����Pinֵ
#define START_PIN_IN  	  (0xFFFEFFFF)      // ��ʼ����GPIO��Ϊ����     

#define DIR_KEY_PRESSED	  (0x1B000000)
#define START_KEY_PRESSED (0x00010000)

#define DIR_KEY_SEL       PINSEL1
#define DIR_KEY_DIR       IO0DIR
#define DIR_KEY_SET       IO0SET
#define START_KEY_SEL     PINSEL2
#define START_KEY_DIR     IO1DIR
#define START_KEY_SET     IO1SET

#define EMPTY		(0x00)			// ����ռ�ֵ

static INT8U  ucKeyValue;	    // �����µİ���

void Key_Init(void);
void Key_WaitKey(void);
INT8U Key_GetKey(void);
void Key_ProcessKey(INT8U ucKeyValue);
void Key_Main(void*);
 
#endif 

