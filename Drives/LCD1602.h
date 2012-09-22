#ifdef  LCD1602_H
#else
#define LCD1602_H
#include "Configure.h"

#define LCD1602Driver_RS (0X1<<29)
#define LCD1602Driver_RW (0X1<<30)
#define LCD1602Driver_EN (0X1<<10)
#define LCD1602Driver_BUSY (0X1<<7)
#define LCD1602Driver_FIRSTLINE 0X80
#define LCD1602Driver_SECONDLINE 0XC0
#define LCD1602Driver_PINSEL0 0xffcf0000 //p0.0--p0.7 p0.10
#define LCD1602Driver_PINSEL1 0xc3ffffff//p0.29 p0.32
#define LCD1602Driver_PINALL 0x600004ff //LCD1602Driver��������
#define LCD1602Driver_PINCTR 0x60000400
#define LCD1602Driver_SEL0 PINSEL0
#define LCD1602Driver_SEL1 PINSEL1	//�˿ڹ���
#define LCD1602Driver_CLR IO0CLR		//��������
#define LCD1602Driver_SET IO0SET		//������һ
#define LCD1602Driver_DIR IO0DIR		//�˿ڷ���


#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/****************************************************************************
* ���ƣ�LCD1602Driver_check_busy()
* ���ܣ���������Ƿ�æ
ע���ڷ��滷���в�ѯ��Ч�����ú�����ʡ��
****************************************************************************/
void LCD1602Driver_CheckBusy(void);

/****************************************************************************
* ���ƣ�LCD1602Driver_write_command()
* ���ܣ�д����
 RS = L; RW = L;D0-D7 = ָ���� E = ������
****************************************************************************/
void LCD1602Driver_WriteCMD(INT8U dat);

/****************************************************************************
* ����  LCD1602Driver_write_data()
* ���ܣ�д����
  RS = H; RW = L;D0-D7 = ���� E = ������
****************************************************************************/
void LCD1602Driver_WriteData(INT8U dat);


/****************************************************************************
* ���ƣ�LCD1602Driver_init()
* ���ܣ�LCD��ʼ������
****************************************************************************/
void LCD1602Driver_Init(void);


/********************************************************************************
 * ���ƣ� set_xy()
 * ���ܣ��趨�ַ�λ�ã�
 ע��x:0~1�У�y��0~15��
 *********************************************************************************/
void  LCD1602Driver_Set_xy(INT8U x,INT8U y);

/********************************************************************************
 * ���ƣ� LCD1602Driver_display_onechar
 * ���ܣ���ָ��λ����ʾһ���ַ�
 *********************************************************************************/
void  LCD1602Driver_DisplayChar(INT8U x,INT8U y,INT8U wdate);


/********************************************************************************
 * ���ƣ�LCD1602Driver_display_string
 * ���ܣ���ָ��λ����ʾһ���ַ���
 *********************************************************************************/
void  LCD1602Driver_DisplayString(INT8U x,INT8U y,INT8U *s);

#endif
