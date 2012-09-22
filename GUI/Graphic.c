#include "Configure.h"

OS_STK  TwinkleTaskStk[TASK_STK_SIZE];			//���������ջ��
OS_STK  DelTwinkleStk[TASK_STK_SIZE];			//ɾ�������ջ��

INT8U LCD12864_Screen[8][128] = {0};

INT8U str_Minute[] = "00";
INT8U str_Second[] = "00";
INT8U str_Level[]  = "00";
INT8U str_Score[]  = "00";

INT8U Snake_Up[] = {
  0x0F,0x0F,0x0F,0x0F
};
INT8U Snake_Down[] = {
  0xF0,0xF0,0xF0,0xF0
};

/**************************************************************************************************
* ������ : GUI_Init()                                                                             *
* �������� : GUIģ���ʼ��                                                                     	  *
* ����  :    2009-07-16                                                              		  *
* ����  :    void                                                            			  *
* ����ֵ :   void                                                                              	  *
* ����  :     ����                                                                                *
**************************************************************************************************/
void GUI_Init(void)
{
  LCD1602Driver_Init();   //LCD1602��ʼ��
  LCD12864Driver_Init();  //LCD12864��ʼ��
  LCD1602Driver_DisplayString(0, 0, "Time");  //  С����ʾʱ���ַ���
  LCD1602Driver_DisplayString(1, 0, "Score"); //  С����ʾ�����ַ���
  LCD1602Driver_DisplayString(1, 10, "Lev");  //  С����ʾ�ȼ��ַ���

 /*
  * ��ʼ��ʱ�䣬�������ȼ���Ϊ00
  */
  GUI_DisplayTime((INT32U)0);
  GUI_DisplayScore((INT8U)0);
  GUI_DisplayLevel((INT8U)0);

  GUI_DisplayPicture(0,0,ucWelcomeBmp,&ucWelcomeBmpSize);  // ��ʾ��ӭ����
  GUI_TwinklePic();                                        // ������˸����ʾ�û�����������Ϸ
}

/**************************************************************************************************
* ������ : GUI_DrawSnake                                                                          *
* �������� : ��Ϸ����ͣ�л�������ʱ��GameControl���ô˽ӿڣ����»�������                      	  *
* ����  :    2009-07-17                                                       			  *
* ����  : Snake_t *pSnake_tSnake                                                          	  *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                 	  *
**************************************************************************************************/
void GUI_DrawSnake(Snake_t *pSnake_tSnake)
{
  INT8U loop = 0;
  // �ж���ͷ�±��Ƿ������β
  if(pSnake_tSnake->ucHead>pSnake_tSnake->ucTail){
    for(loop = pSnake_tSnake -> ucTail;loop <= pSnake_tSnake -> ucHead;loop++)
    {
      GUI_DrawNode(pSnake_tSnake->aSnakeBody[loop].ucX,pSnake_tSnake->aSnakeBody[loop].ucY,DRAWNODE);
    }
  }
  // ��ͷ�±�С����β
  else{
    // ����β���꿪ʼ����������Ľ���
    for(loop = pSnake_tSnake -> ucTail;loop <SNAKE_MAX_LENGTH ;loop++)
    {
      GUI_DrawNode(pSnake_tSnake->aSnakeBody[loop].ucX,pSnake_tSnake->aSnakeBody[loop].ucY,DRAWNODE);
    }
    loop %=SNAKE_MAX_LENGTH;
    // ����ͷ��ӡ����β
    while(loop<=pSnake_tSnake->ucHead){
      GUI_DrawNode(pSnake_tSnake->aSnakeBody[loop].ucX,pSnake_tSnake->aSnakeBody[loop].ucY,DRAWNODE);
      loop++;
    }
  }
}

/**************************************************************************************************
* ������ : GUI_Mix                                                                                *
* �������� : �����ֿ�ѡ�ķ�ʽʵ�־ֲ����                                                     	  *
* ����  :  2009-07-15                                                                  		  *
* ����  :  ucX  ���ͼƬ����ʼ������                                                              *
* 	   ucY  ���ͼƬ����ʼ������                                                              *
* 	   *pucPicture ���ͼƬ����ģ����      							  *
* 	   *pucPictureSize ���ͼƬ�Ĵ�С                                                         *
* 	   ReplaceORAppend ���ֿ�ѡ�ķ�ʽ                                                         *
* ����ֵ : void                                                                                	  *
* ����  :   ����                                                                               	  *
**************************************************************************************************/
void GUI_Mix(INT8U ucX,INT8U ucY,const INT8U *pucPicture,const Size_t *pucPictureSize,BOOLEAN ReplaceORAppend)
{
  INT8U xloop = 0;
  INT8U yloop = 0;

  for(yloop = ucY; yloop < ucY + (pucPictureSize -> ucHight); yloop += 8){
    for(xloop = ucX;xloop < ucX + pucPictureSize -> ucLength; xloop++){
      if(ReplaceORAppend == APPEND)
      {
	// ���һά�����ģ������LCD12864�ڴ�Ķ�Ӧ��ϵ�����������ʵ�����ʽ���
        LCD12864_Screen[yloop/8][xloop]  |= pucPicture[(yloop- ucY)/8*(pucPictureSize -> ucLength) + xloop - ucX];
      }
      else
      {
	// ���һά�����ģ������LCD12864�ڴ�Ķ�Ӧ��ϵ����һ�θ�ֵ��ʵ�ָ���ʽ���
        LCD12864_Screen[yloop/8][xloop]  = pucPicture[(yloop- ucY)/8*(pucPictureSize -> ucLength) + xloop - ucX];
      }
      // ˢ����Ļ
      LCD12864Driver_DisplayByte(yloop/8,xloop,LCD12864_Screen[yloop/8][xloop]);
    }
  }
}

/**************************************************************************************************
* ������ : GUI_DisplayTime                                                                        *
* �������� : ��ʾ��Ϸ���е�ʱ��                                                                	  *
* ����  :  2009-07-18                                                          			  *
* ����  :  ucSeconds ��Ϸ���еĺ�����         							  *
* ����ֵ : void                                                                               	  *
* ����  :  ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayTime(INT32U ucSeconds)
{
  ucSeconds/=1000;  //����ת��Ϊ��
  //�ж���Ϸ�����Ƿ񳬹�10��
  if(ucSeconds%60 < 10)
  {
    str_Second[0] = '0';
    str_Second[1] =(ucSeconds%60)+'0';
  }
  else
  {
    str_Second[0] = ((ucSeconds%60)/10)+'0';
    str_Second[1] = ((ucSeconds%60)%10)+'0';
  }
  //�ж���Ϸ�����Ƿ񳬹�60��
  if(ucSeconds/60 < 10)
  {
    str_Minute[0] = '0';
    str_Minute[1] = (ucSeconds/60)+'0';
  }
  else
  {
    str_Minute[0] = ((ucSeconds/60)/10)+'0';
    str_Minute[1] = ((ucSeconds/60)%10)+'0';
  }
  LCD1602Driver_DisplayString(0,MINUTE_X,str_Minute);
  LCD1602Driver_DisplayString(0,CURSOR_MINUTE_X,":");
  LCD1602Driver_DisplayString(0,SECOND_X,str_Second);
}

/**************************************************************************************************
* ������ :  GUI_DisplayScore                                                                      *
* �������� : С������ʾ��Ϸ���÷���                                                           	  *
* ����  :    2009-07-16                                                        			  *
* ����  :    ucScore  ��Ϸ���÷���            							  *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayScore(INT32U ucScore)
{
  // �жϷ����Ƿ񳬹�10,���û�У�ʮλ����ʾ0
  // �������10�֣�ʮλ���ű仯
  if(ucScore < 10)
  {
  	str_Score[0] = '0';
	str_Score[1] = (ucScore%10)+'0';
  }
  else
  {
  	str_Score[0] = ucScore/10+'0';
	str_Score[1] = ucScore%10+'0';
  }
#if DEBUG==TRUE
  debug("Score:");
  debug(str_Score);
#endif
  LCD1602Driver_DisplayString(1,SCORE_X,str_Score);
}

/**************************************************************************************************
* ������ :  GUI_DisplayLevel                                                                      *
* �������� : С������ʾ��Ϸ���õȼ�                                                           	  *
* ����  :    2009-07-16                                                        			  *
* ����  :    ucLevel  ��Ϸ���õȼ�            							  *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayLevel(INT8U ucLevel)
{
  // �жϵȼ��Ƿ񳬹�10,���û�У�ʮλ����ʾ0
  // �������10����ʮλ���ű仯
  if(ucLevel < 10)
  {
  	str_Level[0] = '0';
	  str_Level[1] = (ucLevel%10)+'0';
  }
  else
  {
  	str_Level[0] = ucLevel/10+'0';
	  str_Level[1] = ucLevel%10+'0';
  }
#if DEBUG==TRUE
  debug("Level:");
  debug(str_Level);
#endif
  LCD1602Driver_DisplayString(1,LEVEL_X,str_Level);
}

/**************************************************************************************************
* ������ :  GUI_DrawNode                                                                          *
* �������� : �����ӣ��������ϵ�һ���ڵ�                                                        	  *
* ����  :    2009-07-17                                                        			  *
* ����  :    ucX  �ڵ���ʼ������                                                                  *
*            ucY  �ڵ���ʼ������                                                                  *
*            DrawORClear �ǻ��㻹�����                                                           *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DrawNode(INT8U ucX,INT8U ucY,BOOLEAN DrawORClear)
{
  INT8U realX = 0;
  INT8U realY = 0;

  INT8U xloop = 0;
  INT8U yloop = 0;

  // ��Ϊ�ߵĽڵ���4*4,�ⲿ�����߿���������
  // Ϊ16*32,�����ڴ�֮ǰ������ָ�
  realX = ucX * 4;
  realY = ucY * 4;

  for(yloop = realY; yloop < realY + NODE_HIGHT; yloop += 8)
  {
    for(xloop = realX;xloop < realX +NODE_LENGTH; xloop++)
    {
      if(DrawORClear == DRAWNODE)
      {
        if(yloop%8 < 4)  //�ж��Ƿ��ǵ���λ
        {

          LCD12864_Screen[yloop/8][xloop] |= Snake_Up[xloop - realX]; //����ǻ��㣬���������
        }
        else // ����Ǹ���λ
        {
          LCD12864_Screen[yloop/8][xloop] |= Snake_Down[xloop - realX];
        }
        LCD12864Driver_DisplayByte(yloop/8,xloop,LCD12864_Screen[yloop/8][xloop]);
      }
      else  // ��������һ���ڵ�
      {
        if(yloop%8 < 4) //�ж��Ƿ��ǵ���λ
        {
          LCD12864_Screen[yloop/8][xloop] &= Snake_Down[xloop - realX]; // ����㣬���������
	}
        else  // ����Ǹ���λ
        {
          LCD12864_Screen[yloop/8][xloop] &= Snake_Up[xloop - realX];
        }
        LCD12864Driver_DisplayByte(yloop/8,xloop,LCD12864_Screen[yloop/8][xloop]);
      }
    }

  }
}

/**************************************************************************************************
* ������ :  GUI_DisplayMiniMap                                                                    *
* �������� : ѡ���ͼʱ����ʾС��ͼ                                                        	  *
* ����  :    2009-07-17                                                        			  *
* ����  :    ucMiniMapNumber С��ͼ�ı��                                                         *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayMiniMap(INT8U ucMiniMapNumber)
{
  GUI_Mix(0,0,ucChooseMapBmp,&ucChooseMapBmpSize,REPLACE);//�����������������ؾ�̬ͼƬ
  GUI_Mix(MINI_MAP_X,MINI_MAP_Y,pucaMiniMaps[ucMiniMapNumber],&MiniMapSize,REPLACE); //����֮ǰ����ʾ��С��ͼ
#if DEBUG==TRUE
  debug("Change the map:");
  debug_INT8U(ucMiniMapNumber);
#endif
}

/**************************************************************************************************
* ������ :  GUI_DisplayMap                                                                        *
* �������� : ��ʾ�����ѡ��ͼ                                                           	  *
* ����  :    2009-07-17                                                        			  *
* ����  :    ucMapNumber �ڵ�ͼ�ı��                                                             *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayMap(INT8U ucMapNumber)
{
    GUI_Mix(0,0,pucaMaps[ucMapNumber],&MapSize,REPLACE); // ����������������ʾ��ͼ
}

/**************************************************************************************************
* ������ : GUI_DisplayPicture                                                                     *
* �������� : ��ʾ��̬ͼƬ                                                               	  *
* ����  :  2009-07-15                                                                  		  *
* ����  :  ucX  ͼƬ����ʼ������                                                                  *
* 	   ucY  ͼƬ����ʼ������                                                                  *
* 	   *pucPicture ���ͼƬ����ģ����      							  *
* 	   *pucPictureSize ���ͼƬ�Ĵ�С                                                         *
* ����ֵ : void                                                                                	  *
* ����  :   ����                                                                               	  *
**************************************************************************************************/
void GUI_DisplayPicture(INT8U ucX,INT8U ucY,const INT8U *pucPicture,const Size_t *Size_tPictureSize)
{
  INT8U ucPage,ucCol;

  INT8U ucHight = Size_tPictureSize -> ucHight;
  INT8U ucLength = Size_tPictureSize -> ucLength;

  for(ucPage = ucY;ucPage<ucY+ucHight;ucPage += 8)
    for(ucCol = ucX;ucCol<ucX+ ucLength;ucCol++)
      //��8bit��ѯˢ����Ļ
      LCD12864Driver_DisplayByte(ucPage/8,ucCol,pucPicture[(ucPage-ucY)/8*ucLength + ucCol - ucX]);
}
/**************************************************************************************************
* ������ :  GUI_DisplayHeroName                                                                   *
* �������� : ������Ӣ���������ϣ���λ��ʾ��ҵ�����                                            	  *
* ����  :    2009-07-18                                                        			  *
* ����  :    Heros[] ��ȡ�û������ַ�����Ӧ����ĸ������±�����                                   *
* 	     CurPosition ��ǰ����λ��                                                           *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayHeroName(INT8U Heros[],INT8U CurPosition)
{
  INT8U loop = 0;
  INT8U Gap = 10;
  INT8U inputName_x = INPUT_NAME_X;

  // �����������
  INT8U cursor_x  = inputName_x;
  INT8U cursor_y  = INPUT_NAME_Y + 8;

  GUI_Mix(0,0,ucCongratulationsBmp,&ucCongratulationsBmpSize,REPLACE);
  GUI_Mix(cursor_x + CurPosition * Gap,cursor_y,ucCursorBmp,&ucCursorBmpSize,APPEND);

  for(loop =0; loop < 3; loop++)
  {
      inputName_x += Gap; // ��һ���ļ�϶�ƶ����
      GUI_Mix(inputName_x,INPUT_NAME_Y,ucLetters[Heros[loop]],&LetterSize,REPLACE);
  }
}

/**************************************************************************************************
* ������ :  GUI_DisplayHero                                                                       *
* �������� : ��ʾӢ�۰�                                                                  	  *
* ����  :    2009-07-17                                                        			  *
* ����  :    aHero_tHeroes[] ����Ӣ����Ϣ�Ľṹ��                                                 *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayHero(Hero_Score_t aHero_tHeroes[])
{
  INT8U xloop = 0;
  INT8U yloop = 0;
  INT8U xGap = 10;
  INT8U yGap = 8;
  INT8U HeroScore[] = {0,0,0};

  // Ӣ�۰����ֵ���ʼ����
  INT8U HeroBoardName_x = HERO_BOARD_NAME_X;
  INT8U HeroBoardName_y = HERO_BOARD_NAME_Y;

  // ��������ʼ����
  INT8U score_x = HERO_BOARD_SCORE_X;
  INT8U score_y = HERO_BOARD_NAME_Y ;

  GUI_Mix(0,0,ucHeroBoardBmp,&ucHeroBoardSize,REPLACE);

  for(xloop = 0; xloop < 3;xloop++)
  {
    HeroBoardName_y += yGap;
    score_y += yGap;

	HeroScore[0] = aHero_tHeroes[xloop].ucScore/100;  // ����Ӣ�۷����İ�λ
	HeroScore[1] = aHero_tHeroes[xloop].ucScore/10;   // ����Ӣ�۷�����ʮλ
	HeroScore[2] = aHero_tHeroes[xloop].ucScore%10;   // ����Ӣ�۷����ĸ�λ

    for(yloop = 0; yloop < 3; yloop++)
    {
      HeroBoardName_x += xGap;
      score_x += xGap;

      // �ֲ���ӡ��Ӣ�۵�����
      GUI_Mix(HeroBoardName_x,HeroBoardName_y,ucLetters[aHero_tHeroes[xloop].cName[yloop]],&LetterSize,APPEND);

      // �ֲ���ӡ��Ӣ�۵ķ���
      GUI_Mix(score_x,score_y,ucNumbers[HeroScore[yloop]],&LetterSize,APPEND);
    }
      // ��ӡ��һ��֮�󣬻ָ����ֺͷ�������ʼ���꣬׼������һ��
      HeroBoardName_x = HERO_BOARD_NAME_X;
      score_x = HERO_BOARD_SCORE_X;
  }
}

/**************************************************************************************************
* ������ :  GUI_DisplayPause                                                                      *
* �������� : ��ʾ��ͣ��ʾͼƬ                                                           	  *
* ����  :    2009-07-17                                                        			  *
* ����  :    void			                                                          *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DisplayPause()
{
  GUI_Mix(PAUSE_BMP_X,PAUSE_BMP_Y,ucPauseBmp,&ucPauseBmpSize,REPLACE);
}

/**************************************************************************************************
* ������ :  GUI_TwinklePicTask                                                                    *
* �������� : ��Ļ��˸����                                                               	  *
* ����  :    2009-07-18                                                        			  *
* ����  :    void			                                                          *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_TwinklePicTask(void *arg)
{
#if OS_CRITICAL_METHOD == 3
  OS_CPU_SR  cpu_sr;
#endif
#if DEBUG==TRUE
  debug("Twinkle task begin.");
#endif
      // ͨ����������������֮��Ŀ����л��ﵽ��˸��Ч��
      GUI_Mix(TWINK_PIC_X,TWINK_PIC_Y,ucContinueBmp,&ucContinueBmpSize,REPLACE);         // �Ȼ���������ֵ�ͼƬ
      OSTimeDlyHMSM(0,0,0,TWINK_DELAY_TIME);
      GUI_Mix(TWINK_PIC_X,TWINK_PIC_Y,ucTwinkleBlankBmp,&ucTwinkleBlankBmpSize,REPLACE); // �ٻ����û���ֵ�ͼƬ
      OSTimeDlyHMSM(0,0,0,TWINK_DELAY_TIME);
#if DEBUG==TRUE
  debug("Twinkle task end.");
#endif
}

/**************************************************************************************************
* ������ :  GUI_TwinklePic                                                                        *
* �������� : ������˸����                                                               	  *
* ����  :    2009-07-18                                                        			  *
* ����  :    void			                                                          *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_TwinklePic()
{
  OSTaskCreate(GUI_TwinklePicTask,NULL,&TwinkleTaskStk[TASK_STK_SIZE-1],TWINK_PIC_PRIO);
}

/**************************************************************************************************
* ������ :  GUI_DelTwinkTask                                                                      *
* �������� : ɾ����˸����                                                               	  *
* ����  :    2009-07-18                                                        			  *
* ����  :    void			                                                          *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_DelTwinkTask(void *arg){
  GUI_Mix(TWINK_PIC_X,TWINK_PIC_Y,ucTwinkleBlankBmp,&ucTwinkleBlankBmpSize,REPLACE);
  OSTaskDel(TWINK_PIC_PRIO);
  OSTaskDel(OS_PRIO_SELF);
}

/**************************************************************************************************
* ������ :  GUI_KeyPress                                                                          *
* �������� : ����ɾ����˸����                                                           	  *
* ����  :    2009-07-18                                                        			  *
* ����  :    void			                                                          *
* ����ֵ :   void                                                                              	  *
* ����  : ����                                                                                	  *
**************************************************************************************************/
void GUI_KeyPress(INT8U ucKeyValue)
{
  if( OSTCBPrioTbl[TWINK_PIC_PRIO]!=(OS_TCB*)0){
    OSTaskCreate(GUI_DelTwinkTask,NULL,&DelTwinkleStk[TASK_STK_SIZE-1],DEL_TWINK_PRIO);
  }
}


