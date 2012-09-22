#include "Configure.h"

#ifndef __GRAPHIC__
#define __GRAPHIC__



/*
 * �궨��
*/
#define TWINK_PIC_X     ((INT8U)4) //��˸��Ŀ��xλ��
#define TWINK_PIC_Y     ((INT8U)48) //��˸��Ŀ��xλ��
#define TWINK_DELAY_TIME      ((INT32U)150)//��˸��ʱ


/*
* ���ƣ�GUI_Init()
* ���ܣ�����Һ�����ĳ�ʼ��
*/
void GUI_Init(void);

/*
 * ���ƣ�GUI_TwinklePic()
 * ���ܣ�ͼ����˸
*/
void GUI_TwinklePic(void);

/*
 * ����: GUI_KeyProcess()
 * ���ܣ���Ӧ������������˸����״̬�л�ʱɱ������
 */
void GUI_KeyPress(INT8U ucKeyValue);

/*
 * ����: GUI_DrawSnake()
 * ����: ��ͣ�ָ�ʱ���ָ�����
 */ 
//void GUI_DrawSnake(Snake_t *pSnake_tSnake);

/*
* ����: GUI_DisplayTime()
* ����: ��ʾ��Ϸʹ�õ�ʱ�� 
* ������INT32U ucSeconds 
*/
void GUI_DisplayTime(INT32U ucSeconds);

/*
* ����: GUI_DisplayScore()
* ����: ��ʾ��ҵ÷� 
* ������INT32U ucScore
*/
void GUI_DisplayScore(INT32U ucScore);

/*
* ����: GUI_DisplayLevel()
* ����: ��ʾ��ҵȼ� 
* ������INT8U ucLevel 	
*/
void GUI_DisplayLevel(INT8U ucLevel);

/*
* ����: GUI_DrawNode()
* ����: ���ߵ�ÿ���ڵ� 
* �������ڵ�ĺ����꣺INT8U x,INT8U y	
*/
void GUI_DrawNode(INT8U ucX,INT8U ucY,BOOLEAN DrawORClear);

/*
 * ���ƣ�GUI_DrawSnake
 * ���ܣ�������
 */
void GUI_DrawSnake(Snake_t *pSnake_tSnake);

/*
* ����: GUI_DisplayMiniMap()
* ����: ѡ��ͼʱ����ʾ��ͼ������ͼ 
* ��������ͼ���	
*/
void GUI_DisplayMiniMap(INT8U ucMiniMapNumber);

/* 
* ���ƣ�GUI_DisplayMap()
* ���ܣ���ʾ��ѡ�Ĺؿ���ͼ
* ��������ͼ�ı��
*/
void GUI_DisplayMap(INT8U ucMapNumber);

/*
* ����: GUI_DisplayPicture()
* ����: ��ָ�������ӡָ����ͼƬ
* ������������: INT8U uxX,�����꣺INT8U ucY ,ͼƬ��pucPicture	
*/
void GUI_DisplayPicture(INT8U ucX,INT8U ucY,const INT8U *pucPicture,const Size_t *Size_tPictureSize);

/*
*  ���ƣ�GUI_DisplayHeroName()�� 
*  ���ܣ���ʾ�����Ӣ����
*  ������
*/
void GUI_DisplayHeroName(INT8U Heros[],INT8U CurPosition) ;

/*
* ����: GUI_DisplayHero()
* ����: ��ʾӢ�۰� 
* ������Ӣ�۰����� 	
*/
void GUI_DisplayHero(Hero_Score_t aHero_tHeroes[]);

/*
* ����: GUI_DisplayHero()
* ����: ��ʾ��ͣ״̬
* ������ 	
*/
void GUI_DisplayPause(void);

#endif

