#include "Configure.h"

//�������������¼��ǰ��ʾ���ǵڼ�����ͼ	
INT8U ucMiniMapCur;	 	

//��¼��ǰ���λ�ã�����0С��4��
INT8U ucCursorCur;		

//��¼Ӣ�۰������
Hero_Score_t apTopThree[TOP_NUMBER]={
  {{0, 0, 0},0},
  {{0, 0, 0},0},
  {{0, 0, 0},0}
};

//�����û������ֵ�3���ַ�
INT8U aucNameCur[3]={0,0,0};	

//��ĸ���
INT8U ucLetterID[3]={0,0,0};

//��ʱ����
INT8U ucScore;

//�����ڲ�����

//��ʼ��һЩ�ڲ�������GUIģ�飨��Ҫ����LCD1��LCD2��
void Environment_Initial(void);
//���ݰ���ֵ�͵�ǰ��ͼ�ı�����ı��ͼ
void Environment_ChangeMap(INT8U ucKeyValue);
//������Ϸ���н�����ķ�����ȷ���Ƿ����ͨ�ػ�����Ϸʧ��
BOOLEAN Environment_IsWin(INT8U ucScore);
//������Ϸ���н�����ķ�����ȷ������Ƿ��ܽ���ǰ3��
BOOLEAN Environment_IsTopThree(INT8U ucScore);
//���ݰ���ֵ�͵�ǰ�������ֵĹ���λ����ȷ�����������
void Environment_InputName(INT8U ucKeyValue);
//����Ӣ�۰�
void Environment_UpdateHeroboard(void);


/*************************************************************************************************
* ������ :    Environment_KeyPress                                                               *                    
* �������� :  ������ģ����ã����밴��ֵ                                                         *                    	  
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U  ucKeyValue                                                        			 *				
* ����ֵ :      0                                                                         	     *
*����  :        ŷ����                                                                           *
**************************************************************************************************/

INT8U Environment_KeyPress(INT8U ucKeyValue ){
#if DEBUG==TRUE
  debug("Environment get the press key.");
#endif

  switch(ucGameState)
  {
    case GAME_STAT_WELCOME:
      {
        GUI_DisplayMiniMap(0);
        ucGameState = GAME_STAT_CHANGEMAP;
#if DEBUG==TRUE
        debug("Set the Map state.");
#endif
        break;
      }
    case GAME_STAT_CHANGEMAP:
      {
        //���õ�ͼ�Ľ���
        if(ucKeyValue == LEFT||ucKeyValue == RIGHT)
        {
          Environment_ChangeMap(ucKeyValue);
        }
#if DEBUG==TRUE
        debug("Set the Map.");
#endif
        if(ucKeyValue == START)
        {
          GameControl_InitialGame(ucMiniMapCur);
          ucGameState = GAME_STAT_GAMING;
        }
#if DEBUG==TRUE
        debug("Finish the Map.");
#endif
        break;
      }
    case GAME_STAT_DEAD:
      {
        if(Environment_IsTopThree(ucScore) ==TRUE)
        {
          ucGameState = GAME_STAT_INPUTNAME;
#if DEBUG==TRUE
          debug("Press the name.");
#endif
        }
        else
        {
          ucGameState = GAME_STAT_DISPLAYHERO;
#if DEBUG==TRUE
          debug("Display the Hero List.");
#endif
        }
        break;
      }
    case GAME_STAT_DONE:
      {
        GUI_DisplayPicture(0, 0, ucCongratulationsBmp, &ucCongratulationsBmpSize);
        ucGameState = GAME_STAT_INPUTNAME;
#if DEBUG==TRUE
        debug("Get the name.");
#endif
        break;
      }
    case GAME_STAT_INPUTNAME:
      {
        if(ucKeyValue !=START)
        {
          Environment_InputName(ucKeyValue);
        }
        else
        {
          Environment_UpdateHeroboard();
        }
        break;
      }
    case GAME_STAT_DISPLAYHERO:
      {
        Environment_Initial();
        break;
      }
    default : 
      break;
  }
  return 0;

}


/*************************************************************************************************
* ������ :    Environment_PassScore                                                              *                      
* �������� :  ����Ϸ����ģ����ã��õ���Ϸ���н���ʱ�ķ���                                       *                                       	 
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U  ucScoreTmp                                                        			 *				
* ����ֵ :      0                                                                         	     *
*����  :        ŷ����                                                                           *
**************************************************************************************************/

INT8U Environment_PassScore(INT8U ucScoreTmp ){
#if DEBUG==TRUE
  debug("Environment get Score.");
#endif 
  ucScore = ucScoreTmp;
  if(Environment_IsWin(ucScore) ==TRUE)
  {
    ucGameState = GAME_STAT_DONE;
  }
  else
  {
    ucGameState = GAME_STAT_DEAD;
  }
  return 0;

}


/*************************************************************************************************
* ������ :    Environment_Initial                                                                *                  
* �������� :  ��ʼ��һЩ�ڲ�������GUIģ�飨��Ҫ����LCD1��LCD2��                                  *                                         	
* ����  :     2009-7-16                                                                      	 *
* ����     :  void                                                        						 *
* ����ֵ :      void                                                                         	 *
*����  :        ����                                                                             *
**************************************************************************************************/
void Environment_Initial(void){
  INT8U i;
  ucMiniMapCur = 0;
  ucCursorCur = 1;
  for(i=0;i<3;i++) 
  {
    aucNameCur[i] = 0;
    ucLetterID[i] = 0;
  }
  ucScore = 0;
  ucGameState =GAME_STAT_WELCOME;
  GUI_Init();
  Key_Init();
#if DEBUG==TRUE
  debug("Initial the vars.");
#endif

}


/*************************************************************************************************
* ������ :    Environment_ChangeMap                                                              *                  
* �������� :  ���ݰ���ֵ�͵�ǰ��ͼ�ı�����ı��ͼ                                               *                                         	 
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U ucKeyValue                                                       		     *
* ����ֵ :      void                                                                         	 *
*����  :        ����                                                                             *
**************************************************************************************************/
void Environment_ChangeMap(INT8U ucKeyValue){

  if(ucKeyValue == LEFT){
    if(ucMiniMapCur <= (INT8U)0)
      ucMiniMapCur = MAX_MAPS-(INT8U)1;
    else
      ucMiniMapCur--;
  }
  if(ucKeyValue == RIGHT){
    if(ucMiniMapCur >= (MAX_MAPS-(INT8U)1))
      ucMiniMapCur = 0;
    else
      ucMiniMapCur++;
  }

  GUI_DisplayMiniMap(ucMiniMapCur);

}


/*************************************************************************************************
* ������ :    Environment_IsWin                                                                  *                  
* �������� :  ������Ϸ���н�����ķ�����ȷ���Ƿ����ͨ�ػ�����Ϸʧ��                             *                                         	 
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U ucScore                                                       		         *
* ����ֵ :      TRUE/FALSE                                                                       *
*����  :        ����                                                                             *
**************************************************************************************************/
BOOLEAN Environment_IsWin(INT8U ucScore){

  if(ucScore==WIN_SCORE){
    GUI_DisplayPicture(0, 0, ucYouWinBmp, &ucYouWinBmpSize);
    GUI_TwinklePic();
    return TRUE;
  }
  else{
    GUI_DisplayPicture(0, 0, ucGameOverBmp, &ucGameOverBmpSize);
    GUI_TwinklePic();
    return FALSE;
  }

}


/*************************************************************************************************
* ������ :    Environment_IsTopThree                                                             *                  
* �������� :  ������Ϸ���н�����ķ�����ȷ������Ƿ��ܽ���ǰ3��                                  *                                         	 
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U ucScore                                                       		         *
* ����ֵ :      TRUE/FALSE                                                                       *
*����  :        ����                                                                             *
**************************************************************************************************/
BOOLEAN Environment_IsTopThree(INT8U ucScore){
  if(ucScore>=apTopThree[TOP_NUMBER-(INT8U)1].ucScore){
    GUI_DisplayPicture(0, 0, ucCongratulationsBmp, &ucCongratulationsBmpSize);
    return TRUE;
  }
  else{
    GUI_DisplayHero(apTopThree);
    return FALSE;
  }
}


/*************************************************************************************************
* ������ :    Environment_InPutName                                                              *                   
* �������� :  ���ݰ���ֵ�͵�ǰ�������ֵĹ���λ����ȷ�����������                               *                                         	 
* ����  :     2009-7-16                                                                      	 *
* ����     :  INT8U ucKeyValue                                                       		     *
* ����ֵ :      void                                                                             *
*����  :        ŷ����                                                                           *
**************************************************************************************************/
void Environment_InputName(INT8U ucKeyValue){
  if(ucKeyValue == LEFT){
    if(ucCursorCur == 1)
      ucCursorCur = 1;
    else
      ucCursorCur--;
  }
  if(ucKeyValue == RIGHT){
    if(ucCursorCur == 3)
      ucCursorCur = 3;
    else
      ucCursorCur++;
  }
  if(ucKeyValue == UP){
    if(ucLetterID[ucCursorCur-1]<= 0)
      ucLetterID[ucCursorCur-1] = 26;
    else
      ucLetterID[ucCursorCur-1]--;
  }
  if(ucKeyValue == DOWN)
  {
    if(ucLetterID[ucCursorCur-1] >= 26)
      ucLetterID[ucCursorCur-1] = 0;
    else
      ucLetterID[ucCursorCur-1]++;
  }
  aucNameCur[ucCursorCur -1] = ucLetterID[ucCursorCur-1];
  GUI_DisplayHeroName(aucNameCur,ucCursorCur);
}

//
/*************************************************************************************************
* ������ :    Environment_UpdateHeroboard                                                        *                  
* �������� :  ����Ӣ�۰�                                                                         *
* ����  :     2009-7-16                                                                      	 *
* ����     :  void                                                      		                 *
* ����ֵ :      void                                                                             *
*����  :        ŷ����                                                                           *
**************************************************************************************************/
void Environment_UpdateHeroboard(void)
{
  INT8U i ,j;
  for( i=0;i<TOP_NUMBER;i++)
  {
    if(ucScore >= apTopThree[i].ucScore)
      break;
  }
   for(j=TOP_NUMBER-1;j>i;j--)
      {
        apTopThree[j].cName[0] = apTopThree[j-1].cName[0];
        apTopThree[j].cName[1] = apTopThree[j-1].cName[1];
        apTopThree[j].cName[2] = apTopThree[j-1].cName[2];
        apTopThree[j].ucScore = apTopThree[j-1].ucScore;
      }
  apTopThree[i].cName[0] = aucNameCur[0];
  apTopThree[i].cName[1] = aucNameCur[1];
  apTopThree[i].cName[2] = aucNameCur[2];
  apTopThree[i].ucScore = ucScore;
  GUI_DisplayHero(apTopThree);
  ucGameState = GAME_STAT_DISPLAYHERO;
}

