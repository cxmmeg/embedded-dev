#ifndef __LCD12864_H
#define __LCD12864_H

#include "Configure.h"

#define LCD12864Driver_CTL_NO 11						//��������ʼ�˿�
#define LCD12864Driver_DAT_NO 16						//��������ʼ�˿�
 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864Driver_CSA (1<<(LCD12864Driver_CTL_NO))		//�����߶˿ڶ���
#define LCD12864Driver_CSB (1<<(LCD12864Driver_CTL_NO+1))
#define LCD12864Driver_RS	 (1<<(LCD12864Driver_CTL_NO+2))   //DI
#define LCD12864Driver_RW	 (1<<(LCD12864Driver_CTL_NO+3))
#define LCD12864Driver_EN	 (1<<(LCD12864Driver_CTL_NO+4))

//#define LCD12864Driver_BUSY (1<<LCD12864Driver_DAT_NO+7)	//æ��־λ��

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864Driver_CLR IO0CLR		//��������
#define LCD12864Driver_SET IO0SET		//������һ
#define LCD12864Driver_DIR IO0DIR		//�˿ڷ���
#define LCD12864Driver_PIN IO0PIN		//�˿�״̬

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD12864Driver_SEL0 PINSEL0
#define LCD12864Driver_SEL1 PINSEL1	//�˿ڹ���

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD_STARTROW 0xC0		//������ʼ��ָ�
#define LCD_PAGE 	 0xB8		//����ҳָ�10111000
#define LCD_COL 	 0x40		//������ָ�
#define SINGLE_SCREEN_COL  64	 //��������ÿ��64��
#define LCD_DispOn  0x3F

//****************************************************************************
//* ���ƣ�LCD12864Driver_WriteCMD
//* ���ܣ�д����
//****************************************************************************
void LCD12864Driver_WriteCMD(INT8U ucCMD);

//****************************************************************************
//* ���ƣ�LCD12864Driver_WriteData
//* ���ܣ�д����
//****************************************************************************
void LCD12864Driver_WriteData(INT8U ucData);

//****************************************************************************
//* ���ƣ�LCD12864Driver_CleanAll
//* ���ܣ�����

//****************************************************************************
void LCD12864Driver_CleanALL(void);

//****************************************************************************
//* ���ƣ�LCD12864Driver_Init
//* ���ܣ���ʼ��
//****************************************************************************
void LCD12864Driver_Init(void);

//****************************************************************************
//* ���ƣ�LCD12864Driver_DisplayByte
//* ����: ��ʾһ���ֽ�,������8������
//****************************************************************************
void LCD12864Driver_DisplayByte(INT8U ucPage,INT8U ucCol,INT8U ucData);

//****************************************************************************
//* ���ƣ�LCD12864Driver_DispOneChinese
//* ����: ��ʾһ������
//****************************************************************************
void LCD12864Driver_DispOneChinese(INT8U ucPage,INT8U ucCol,INT8U *pDisTable);

//****************************************************************************
//* ���ƣ�LCD12864Driver_DisplayByte
//* ����: ������ģ��ʾ��ʾn������
//* ע�⣺  ��������д��Ҫÿ�����ֵ���ȡģ
//****************************************************************************
void LCD12864Driver_DispChinese(INT8U ucPage,INT8U ucCol,INT8U pDisTable[][32],INT8U Num);

//****************************************************************************
//* ���ƣ�LCD12864Driver_DisPicture
//* ����: ������ģ��ʾͼƬ
//* ע�⣺���128*64���� ��Ҫ�ṩͼ�εĸ߶ȺͿ���
//****************************************************************************
void LCD12864Driver_DisPicture(INT8U ucPage,INT8U ucCol,INT8U *pDisTable,INT8U width,INT8U hight);

#endif