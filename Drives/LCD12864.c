#include"Configure.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//****************************************************************************
//* ���ƣ�LCD12864Driver_WriteCMD
//* ���ܣ�д����
//****************************************************************************
void LCD12864Driver_WriteCMD(INT8U ucCMD)
{
	LCD12864Driver_CLR=LCD12864Driver_RS;
	LCD12864Driver_CLR=LCD12864Driver_RW;

	LCD12864Driver_CLR=0xFF <<LCD12864Driver_DAT_NO;
	LCD12864Driver_SET=ucCMD<<LCD12864Driver_DAT_NO;
	LCD12864Driver_SET=LCD12864Driver_EN;
	LCD12864Driver_CLR=LCD12864Driver_EN;
}

//****************************************************************************
//* ���ƣ�LCD12864Driver_WriteData
//* ���ܣ�д����
//****************************************************************************
void LCD12864Driver_WriteData(INT8U ucData)
{
	LCD12864Driver_SET=LCD12864Driver_RS;
	LCD12864Driver_CLR=LCD12864Driver_RW;

	LCD12864Driver_CLR=0xFF <<LCD12864Driver_DAT_NO;
	LCD12864Driver_SET=ucData<<LCD12864Driver_DAT_NO;
	
	LCD12864Driver_SET=LCD12864Driver_EN;
	LCD12864Driver_CLR=LCD12864Driver_EN;

}

//****************************************************************************
//* ���ƣ�LCD12864Driver_CleanAll
//* ���ܣ�����

//****************************************************************************
void LCD12864Driver_CleanAll(void)
{
	INT8U ucPage,ucCol;
	LCD12864Driver_SET=LCD12864Driver_CSA;	//����������ѡ��
	LCD12864Driver_SET=LCD12864Driver_CSB;
	for(ucPage=0;ucPage<8;ucPage++)
	{
	
		LCD12864Driver_WriteCMD(LCD_PAGE+ucPage);	  //ҳ
		LCD12864Driver_WriteCMD(LCD_COL);		 //��
		for(ucCol=0;ucCol<64;ucCol++)
			LCD12864Driver_WriteData(0x00);
	}
}

//****************************************************************************
//* ���ƣ�LCD12864Driver_Init
//* ���ܣ���ʼ��
//****************************************************************************
void LCD12864Driver_Init(void)
{

	LCD12864Driver_SEL0 &=0x003FFFFF;
	LCD12864Driver_DIR &= 0x000FF801;     //����
	LCD12864Driver_DIR |= 0x00FFF800;
	LCD12864Driver_CLR |= 0x00FFF800;
		
	LCD12864Driver_WriteCMD(LCD_DispOn);  //����ʾ
	LCD12864Driver_WriteCMD(LCD_STARTROW);  //������ʼ�е�ַ���е�ַ��ҳ��ַ�Ǳ仯��
	
	LCD12864Driver_CleanAll();
}

 /* *************************************************************************************************
* Function Name : LCD12864Driver_DisplayByte                                                             *
* Description	: ��ʾһ���ֽ�,������8������    							             	       *
* Date		    :                                                             	           		   *
* Parameter     : ucPage         ��ʾ��ҳ (��Ļһ��8ҳ)                                            *
*                 ucCol          Ҫ��ʾ���� (��Ļһ��128��)                                        *
*                 ucData         Ҫ��ʾ������                                                      *
* Return Code   : ��                                                                               *
* Author	    :                                                                 	               *
************************************************************************************************* */
void LCD12864Driver_DisplayByte(INT8U ucPage,INT8U ucCol,INT8U ucData)
{	
	
	if(ucCol/SINGLE_SCREEN_COL==0)
	{
		LCD12864Driver_SET=LCD12864Driver_CSA;
		LCD12864Driver_CLR=LCD12864Driver_CSB;
	}
	else{
		LCD12864Driver_CLR=LCD12864Driver_CSA;
		LCD12864Driver_SET=LCD12864Driver_CSB;
	}

	//���ÿ�ʼ��ҳ����

	LCD12864Driver_WriteCMD(LCD_PAGE+ucPage);
	LCD12864Driver_WriteCMD(LCD_COL+ucCol%SINGLE_SCREEN_COL);
	LCD12864Driver_WriteData(ucData);
	
}

//****************************************************************************
//* ���ƣ�LCD12864Driver_DispOneChinese
//* ���ܣ���ʾһ������
//һ��������Ҫ��ҳ*16��
//*ע�⣺ҳ,���иı�
//****************************************************************************

void LCD12864Driver_DispOneChinese(INT8U ucPage,INT8U ucCol,INT8U *pDisTable)
{
	INT8U i=0;
	for(i= 0;i<16;i++)	//�����ϰ벿��
	{
	LCD12864Driver_DisplayByte(ucPage,ucCol+i,*(pDisTable+i));

	}
	for(i= 0;i<16;i++)	 //�����°벿��
	{
	LCD12864Driver_DisplayByte(ucPage+1,ucCol+i,*(pDisTable+16+i));

	}
}

 //****************************************************************************
//* ���ƣ�LCD12864Driver_DispChinese
//* ���ܣ���ʾn������
//һ��������Ҫ��ҳ*16��
//*ע�⣺  ��������д��Ҫÿ�����ֵ���ȡģ
//**************************************************
void LCD12864Driver_DispChinese(INT8U ucPage,INT8U ucCol,INT8U pDisTable[][32],INT8U Num)
{
	INT8U i=0;
	for(i= 0;i<Num;i++)
	LCD12864Driver_DispOneChinese (ucPage,ucCol+16*i,*(pDisTable+i));
}
  //****************************************************************************
//* ���ƣ�LCD12864Driver_DisPicture
//* ���ܣ���ʾһ��ͼ
//
//*ע�⣺���128*64���� ��Ҫ�ṩͼ�εĸ߶ȺͿ��
//**************************************************
void LCD12864Driver_DisPicture(INT8U ucPage,INT8U ucCol,INT8U *pDisTable,INT8U width,INT8U hight)
{
	INT8U i,j;
	for(i = ucPage;i<ucPage+hight/8;i++)
		for(j = ucCol;j<ucCol+ width;j++)	
			LCD12864Driver_DisplayByte(i,j,*(pDisTable+i*128+j));

}


