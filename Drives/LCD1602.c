/******************************************************************************************/
#include "Configure.h"
/****************************************************************************
* File: LCD1602Driver.c
* ���ܣ�LCD1602Driver����
****************************************************************************/

/****************************************************************************
* ���ƣ�LCD1602Driver_CheckBusy()
* ���ܣ���������Ƿ�æ
ע���ڷ��滷���в�ѯ��Ч�����ú�����ʡ��
****************************************************************************/

void LCD1602Driver_CheckBusy(void)
{
	LCD1602Driver_DIR &= 0xfffff800;           //����
	LCD1602Driver_DIR |= LCD1602Driver_PINCTR;//0111 0000 0000 p0.8-p0.10�������
	while(1)
	{	
		//��״̬ RS = L,RW = H, EN = H
		LCD1602Driver_CLR = LCD1602Driver_RS;	 
		IO0SET = LCD1602Driver_RW;
		IO0SET = LCD1602Driver_EN;
	
		if (!(IO0PIN & LCD1602Driver_BUSY) )
		{
			break;
		}
		
	
		LCD1602Driver_CLR=LCD1602Driver_EN;
	}
	

	LCD1602Driver_DIR |= LCD1602Driver_PINALL;  //LCD����Ӧ��IO��������Ϊ�������
}


/****************************************************************************
* ���ƣ�LCD1602Driver_WriteCMD()
* ���ܣ�д����
 RS = L; RW = L;D0-D7 = ָ���� E = ������
****************************************************************************/
void LCD1602Driver_WriteCMD(unsigned char dat)
{

	LCD1602Driver_CheckBusy();

	LCD1602Driver_CLR=LCD1602Driver_RS;		//ȫ������
	LCD1602Driver_CLR=LCD1602Driver_RW;
	LCD1602Driver_CLR=0xff;	//������ָ��λ �ز�����
	IO0SET=dat;		//����ָ��
	IO0SET=LCD1602Driver_EN;		//ns������Чָ���뱻ʶ��ARMʱ����1/M ��us�����
//	DelayMS(1);
	LCD1602Driver_CLR=LCD1602Driver_EN;	  //�ָ���̬ ��Ϊ���´��и�����
}
/****************************************************************************
* ����  LCD1602Driver_WriteData()
* ���ܣ�д����
  RS = H; RW = L;D0-D7 = ���� E = ������
****************************************************************************/
void LCD1602Driver_WriteData(unsigned char dat)	
{

	LCD1602Driver_CheckBusy();

	IO0SET=LCD1602Driver_RS;
	LCD1602Driver_CLR=LCD1602Driver_RW;

	LCD1602Driver_CLR=0xff;	//������
	IO0SET=dat;	   //������

	IO0SET=LCD1602Driver_EN;
	//	DelayMS(1);
	LCD1602Driver_CLR=LCD1602Driver_EN;
}
/****************************************************************************
* ���ƣ�LCD1602Driver_Init()
* ���ܣ�lcd��ʼ������
****************************************************************************/
void LCD1602Driver_Init(void)
{

	 LCD1602Driver_SEL0 &= LCD1602Driver_PINSEL0;
	 LCD1602Driver_SEL1 &= LCD1602Driver_PINSEL1;
	 LCD1602Driver_DIR  |= LCD1602Driver_PINALL;		//����Ϊ���
	 LCD1602Driver_CLR   = LCD1602Driver_PINALL; 
	 LCD1602Driver_WriteCMD(0x01); //��ʾ����
	 LCD1602Driver_WriteCMD(0x38); //��ʾ����ƶ�����8λ2��5x7����
	 LCD1602Driver_WriteCMD(0x0C); //��ʾ�������������ʾ��������꿪����˸��
	 
}

/********************************************************************************
* ���ƣ� LCD1602Driver_Set_xy()
* ���ܣ��趨�ַ�λ�ã�
ע��x:0~1�У�y��0~15��
*********************************************************************************/
void  LCD1602Driver_Set_xy(unsigned  char x,unsigned  char y)
{ 
  switch (x)
   {
   	 case 0: y+=LCD1602Driver_FIRSTLINE;break;
	 case 1: y+=LCD1602Driver_SECONDLINE;break;
	// case 2: y+=0x90; break;   //���������ַ���LCD
	// case 3: y+=0xd0; break;
   }  
  LCD1602Driver_WriteCMD(y);	//��ʾ������� ��������ָ��
}
/********************************************************************************
* ���ƣ� display_onechar����
* ���ܣ���ָ��λ����ʾһ���ַ�
*********************************************************************************/
void  LCD1602Driver_DisplayChar(unsigned  char x,unsigned  char y,unsigned  char wdate)
{
 	LCD1602Driver_Set_xy(x,y);
 	LCD1602Driver_WriteData(wdate);
}
/********************************************************************************
* ���ƣ�display_string����
* ���ܣ���ָ��λ����ʾһ���ַ���
*********************************************************************************/
void  LCD1602Driver_DisplayString(unsigned  char x,unsigned  char y,unsigned  char *s)
{
  LCD1602Driver_Set_xy(x,y);
  while(*s)
  {
   LCD1602Driver_WriteData(*s);
   s++;
  }
}



