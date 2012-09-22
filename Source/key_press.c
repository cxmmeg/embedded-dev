#include "Configure.h"

/**************************************************************************************************
* ������:    Key_Init                                                                             *
* ��������:  ��ʼ������                                                                           *
* ����:      2009-7-17                                                                       	  *
* ����:      -                                                      				              *
* ����ֵ:    -                                                                             	      *
* ����:      ����                                                                                 *
**************************************************************************************************/
void Key_Init(void)			        // ��ʼ��������Ӧ���ŵ�״̬
{
    DIR_KEY_SEL    &= DIR_KEY_PIN;       //��P0.24��P0.25��P0.27��P0.28 ��ΪGPIO��
	DIR_KEY_DIR    |= DIR_KEY_PIN_OUT;   //������Щ����Ϊ������� 
	DIR_KEY_SET     = DIR_KEY_PIN_OUT;   //����Щ����״̬��Ϊ���
	START_KEY_SEL  &= START_PIN;		 //��P1.16 ��ΪGPIO��
	START_KEY_DIR  &= START_PIN_IN;		 //����P1.16Ϊ��������
	START_KEY_SET   = START_PIN_IN;

#if DEBUG==TRUE
  debug("Initial the keys.");
#endif
}



/**************************************************************************************************
* ������:    Key_GetKey                                                                           *
* ��������:  �԰�����ֵ�����жϣ���ȡ������ֵ                                                     *
* ����:      2009-7-17                                                                       	  *
* ����:      -                                                      				              *
* ����ֵ:    ucKeyValue                                                                           *
* ����:      ����                                                                                 *
**************************************************************************************************/ 
INT8U Key_GetKey(void)		       //��ȡ����������ļ�ֵ
{ 
	if (!(IO0PIN & KEY_LEFT))	  // �������
	{
		ucKeyValue = LEFT;
		return ucKeyValue;
	}
	if (!(IO0PIN & KEY_UP))	      // �����ϼ�
	{
		ucKeyValue = UP;
		return ucKeyValue;
	}
	if (!(IO0PIN & KEY_RIGHT))	  // �����Ҽ�
	{
		ucKeyValue = RIGHT;
		return ucKeyValue;
	}
	if (!(IO0PIN & KEY_DOWN)) 	  // �����¼�
	{
		ucKeyValue = DOWN;
		return ucKeyValue;
	}
	if (!(IO1PIN & KEY_START)) 	  // ���¿�ʼ��
	{
		ucKeyValue = START;
		return ucKeyValue;
	}
	else					      //û�а�������
	{
		ucKeyValue = EMPTY;
		return ucKeyValue;
	}
}



/**************************************************************************************************
* ������:    Key_ProcessKey                                                                       *
* ��������:  ���ض���ֵ���д���������ֵ���ݸ��ӿں���                                           *
* ����:      2009-7-17                                                                       	  *
* ����:      ucKeyValue                                                      				      *
* ����ֵ:    -                                                                             	      *
* ����:      ����                                                                                 *
**************************************************************************************************/ 
void Key_ProcessKey(INT8U ucKeyValue)
{
	if(ucKeyValue != EMPTY)					  //���������Ϊ��
	{
		GUI_KeyPress(ucKeyValue);			  //����ֵ���ݸ�GUI�Ľӿں���
		GameControl_KeyPress(ucKeyValue);	  //����ֵ���ݸ�GameControl�Ľӿں���
		Environment_KeyPress(ucKeyValue);	  //����ֵ���ݸ�Environment�Ľӿں���
	}
	else
	{}
}



/**************************************************************************************************
* ������:    Key_Main                                                                             *
* ��������:  Key���������򣬷�ֹ������������ֹ��������                                            *
* ����:      2009-7-17                                                                       	  *
* ����:      -                                                      				              *
* ����ֵ:    -                                                                             	      *
* ����:      ����                                                                                 *
**************************************************************************************************/ 
void Key_Main(void*arg)
{ 
	  if(((IO0PIN & DIR_KEY_PRESSED)!= DIR_KEY_PRESSED)||(IO1PIN & START_KEY_PRESSED)!=START_KEY_PRESSED)
	  {
		OSTimeDlyHMSM(0,0,0,3);
	 	if(((IO0PIN & DIR_KEY_PRESSED)!= DIR_KEY_PRESSED)||(IO1PIN & START_KEY_PRESSED)!=START_KEY_PRESSED)
		Key_ProcessKey(Key_GetKey());
	  }
	
	  if((IO0PIN & DIR_KEY_PRESSED)!= DIR_KEY_PRESSED)
	  {
	 	 if(ucGameState != GAME_STAT_GAMING)
	  	 {
			while ((IO0PIN & DIR_KEY_PRESSED)!= DIR_KEY_PRESSED);
	     }
	  }

      if((IO1PIN & START_KEY_PRESSED)!=START_KEY_PRESSED)
   	  {
		 while ((IO1PIN & START_KEY_PRESSED)!=START_KEY_PRESSED);
      }
   	  OSTimeDlyHMSM(0,0,0,30);
}

