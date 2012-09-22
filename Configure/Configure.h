/****************************************Copyright (c)**************************************************

********************************************************************************************************/
#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif


#define TASK_STK_SIZE ((INT8U)64)

/********************************/
/*      uC/OS-II���������      */
/********************************/
#include "Includes.h"

/********************************/
/*      ARM���������           */
/********************************/
#include "LPC2124.h"

/********************************/
/*      	LCD1602����         */
/********************************/
#include "LCD1602.h"

/********************************/
/*      	LCD12864����        */
/********************************/
#include "LCD12864.h"

/********************************/
/*     Ӧ�ó�������             */
/********************************/

#include    <stdio.h>
#include 	<stdlib.h>
#include    <stdarg.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h> 

/********************************/
/*     �����ӵ�����             */
/********************************/
/* ϵͳ���� */
#define Fosc            10000000                    //����Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 4)                  //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 1             //VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1��2��4��


#include    "target.h"

// LPC21000 misc uart0 definitions
#define UART0_PCB_PINSEL_CFG     ((INT32U)0x00000005)
#define UART0_INT_BIT            ((INT32U)0x0040)
#define LCR_DISABLE_LATCH_ACCESS ((INT32U)0x00000000)
#define LCR_ENABLE_LATCH_ACCESS  ((INT32U)0x00000080)
#define LCR_DISABLE_BREAK_TRANS  ((INT32U)0x00000000)
#define LCR_ODD_PARITY           ((INT32U)0x00000000)
#define LCR_ENABLE_PARITY        ((INT32U)0x00000008)
#define LCR_1_STOP_BIT           ((INT32U)0x00000000)
#define LCR_CHAR_LENGTH_8        ((INT32U)0x00000003) 
#define LSR_THR_EMPTY            ((INT32U)0x00000020)
#define KEY_SEL PINSEL1  
#define KEY_DIR IO0DIR   
#define KEY_SET IO0SET   
#define KEY_CLR IO0CLR   
#define KEY_PIN IO0PIN   
//#define KEY_BEG 24

// ��/�ر�debug���
#define DEBUG FALSE

//�����
#define LEFT       ((INT8U)0x01)		    // �������������ĸ�����
#define UP         ((INT8U)0x02)
#define RIGHT      ((INT8U)0x03)
#define DOWN       ((INT8U)0x04)
#define START      ((INT8U)0x05)	    	// ���忪�ؼ���ֵ

// ȫ�ֺ궨��

#define GAME_STAT_WELCOME	     ((INT8U)0x2)   	//��Ϸ״̬����ӭ״̬��	
#define GAME_STAT_CHANGEMAP	   ((INT8U)0x3)   	//��Ϸ״̬��ѡ��ͼ״̬��	
#define GAME_STAT_DEAD	       ((INT8U)0x4)   	//��Ϸ״̬������״̬��	
#define GAME_STAT_DONE	       ((INT8U)0x5)   	//��Ϸ״̬��ͨ��״̬��	
#define GAME_STAT_INPUTNAME	   ((INT8U)0x6)   	//��Ϸ״̬����������״̬��	
#define GAME_STAT_DISPLAYHERO	 ((INT8U)0x7)   	//��Ϸ״̬����ʾӢ�۰�״̬��	
#define GAME_STAT_GAMING	     ((INT8U)0x8)   	//��Ϸ״̬����Ϸ�С�
#define GAME_STAT_PAUSE	       ((INT8U)0x9)     //��Ϸ״̬��ͣ

#define MAX_BEANS		           ((INT8U)30)      //��Ϸ�����еĶ�����Ŀ
#define BEAN_SCORE	      	   ((INT8U)0x1)     //һ�����Ӷ�Ӧ�ķ���
#define MAX_MAPS               ((INT8U)4)       //ͼ����Ŀ
#define SNAKE_MAX_LENGTH	     ((INT8U)60)      //�ߵ���󳤶�

#define LEVEL_BEANS	           ((INT8U)3)       //������Ҫ�Ķ�����Ŀ
#define DECREASE_DELAY_TIME	   ((INT32U)15)     //ÿ���������ٵ��ӳ�ʱ��
#define INITIAL_DELAY_TIME	   ((INT32U)200)    //Ĭ�ϼ�����ӳ�ʱ��
#define INITIAL_LEVEL	         ((INT8U)0)       //��ʼ����
#define TIME_DELAY             ((INT32U)20)     //��Ϸʱ�Ӹ�����ʱ

#define OPEN_TIME_PRIO         ((INT8U)0x1)     //��ʱ���жϳ����������ȼ�
#define KEY_PRIO               ((INT8U)0x2)     //�������ȼ�
#define SNAKE_MOVE_PRIO	       ((INT8U)0x3)     //���ƶ��������ȼ�
#define DEL_SNAKE_MOVE_PRIO    ((INT8U)0x4)     //ɾ�����ƶ��������ʱtask���ȼ�
#define GAME_TIME_PRIO         ((INT8U)0x5)     //��Ϸʱ���������
#define TWINK_PIC_PRIO         ((INT8U)0x6)     //��˸����
#define DEL_TWINK_PRIO         ((INT8U)0x7)     //ɾ����˸����

typedef struct tagNode_t{
  INT8U ucX,
        ucY;
}Node_t;

typedef struct tagSnake_t{
  INT8U ucDir;//�ߵ��˶�����
  INT8U ucHead;//ָ��ͷ
  INT8U ucTail;//ָ��β
  Node_t aSnakeBody[SNAKE_MAX_LENGTH];//��¼�ߵ����нڵ��״̬
}Snake_t;

//��ʾһ��ͼ�ĳߴ磬������ͼ�ĳ��͸�
typedef struct tagSize_t
{
     INT8U ucLength;
     INT8U ucHight;
}Size_t;

//�ض���һ��Ӣ�۵Ľṹ��
typedef struct tagHero_Score_t
{
	INT8U cName[3];
	INT8U ucScore;
}Hero_Score_t; 

/*******
 * ���볣����
 */
#include "Data.h"
#include "Letter.h"
#include "Map.h"
#include "MiniMap.h"
#include "number.h"
#include "StaticPic.h"
#include "TwinklePic.h"
#include "bitmap.h"

/********************************/
/*        ��Ϸ��Ϣ         	*/
/********************************/
#include "environment.h"

/********************************/
/*          ��������         	*/
/********************************/
#include "key_press.h"

/********************************/
/*          ��Ϸ����         	*/
/********************************/
#include "game_control.h"

/********************************/
/*          ��ӡ����            */
/********************************/
#include "print.h"

/********************************/
/*      	ͼ�κ���         */
/********************************/
#include "Graphic.h"

#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/

