/******************************************************************************\
**  版    权：深圳市和而泰智能控制股份有限公司所有（2020）
**  文件名称：het_key.c
**  功能描述：按键模块化程序，支持短按，长按，连发，组合等按键功能。
**  作    者：王斌<letlink@126.com>
**  日    期：2018-01-01
**  版    本：V0.0.1
**  变更记录：1.首次创建
\******************************************************************************/

/******************************************************************************\
                             Includes
\******************************************************************************/

#include "het_key.h"
/******************************************************************************\
                             Variables definitions
\******************************************************************************/
TS_KEY_INFO KeyInfo;
/******************************************************************************\
                             Functions definitions
\******************************************************************************/
#define PIN_BUTTON 24
/*
* 函数名称 : KEY_Init
* 功能描述 : 按键初始化函数
* 参    数 : NONE
* 返回值   : NONE
*/
/******************************************************************************/
void KEY_Init(void)
/******************************************************************************/  
{
	wiringPiSetupPhys();
    pinMode(PIN_BUTTON, INPUT);
}

/*
* 函数名称 : GetKey
* 功能描述 : 获取键值,返回值每一位代表一个按键按下，支持组合按键
* 参    数 : NONE
* 返回值   : 返回按键值
*/
/******************************************************************************/
uint32_t GetKey(void)
/******************************************************************************/  
{
	int key_value=0;

	key_value=!(digitalRead(PIN_BUTTON));

	//  printf("key_value %d\n",key_value);

    return key_value;
} 

/*
* 函数名称 : KeyModuleProcess
* 功能描述 : 按键检测流程
* 参    数 : 按键结构体指针
* 返回值   : 返回TRUE表示有触发(按下或抬起)，FALSE表示无触发
*/
/******************************************************************************/
static uint8_t KeyModuleProcess(TS_KEY_INFO* pKeyInfo) 
/******************************************************************************/  
{ 
    static uint32_t KeyLast = 0;
	uint32_t KeyCur = 0;

	KeyCur = GetKey();
	
	// printf("pKeyInfo->KeyState %d\n",pKeyInfo->KeyState);

	switch(pKeyInfo->KeyState) 
    { 
        case KEY_STATE_INIT: 
			KeyLast = 0;
			pKeyInfo->KeyDwTmr = 0; 
			KeyInfo.KeyEvent = KEY_EVT_NULL;
			if(KeyCur != KEY_NONE)    
			{
				pKeyInfo->KeyState = KEY_STATE_WOBBLE; 
			}				     
        break; 
        
        case KEY_STATE_WOBBLE://消抖
			pKeyInfo->KeyState = KEY_STATE_DWON;   
        break; 
        
        case KEY_STATE_DWON:
			pKeyInfo->KeyDwTmr++;
			if(KeyCur == KeyLast) 
			{  
				if(pKeyInfo->KeyDwTmr >= KEY_DOWM_TMR) //长按
				{
					pKeyInfo->KeyCur = KeyLast;
					pKeyInfo->KeyEvent |= KEY_EVT_DOWN;
					pKeyInfo->KeyState = KEY_STATE_WAITUP;
					//  printf("key long press\n");
				}
			} 
			else 
			{ 
				if(KeyCur == KEY_NONE) 
				{
					if(pKeyInfo->KeyDwTmr >= KEY_PRESSED_TMR) //点按
					{
						pKeyInfo->KeyCur = KeyLast;
						pKeyInfo->KeyEvent |= KEY_EVT_PRESSED;
						pKeyInfo->KeyState = KEY_STATE_INIT;
						//  printf("key short press\n");
					}
				}
				else
				{
					pKeyInfo->KeyState = KEY_STATE_INIT;
				}
			} 
        break;       	
        
        case KEY_STATE_WAITUP: 
			if(KeyCur == KeyLast) 
			{ 
				if(++pKeyInfo->KeyDwTmr >= KEY_REPEAT_TMR) //连发
				{
					pKeyInfo->KeyCur = KeyLast;
					pKeyInfo->KeyEvent |= KEY_EVT_REPEAT;
					pKeyInfo->KeyDwTmr = 0;
				}
			} 
			else
			{
				if(KeyCur == KEY_NONE)  
				{
					pKeyInfo->KeyCur = KeyLast;
					pKeyInfo->KeyEvent |= KEY_EVT_UP;
					pKeyInfo->KeyState = KEY_STATE_INIT; 
				}
			}
        break;
        
        default: 
        break; 
    } 
    
    if(KeyLast != KeyCur)
    {
        KeyLast = KeyCur;               //保存上次的按键值
    }
    return(0);  
}  

/*
* 函数名称 : KeyDrv
* 功能描述 : 按键驱动函数,需放10ms的循环时间片中
* 参    数 : NONE
* 返回值   : NONE
*/
/******************************************************************************/
void KEY_Drv(void)
/******************************************************************************/  
{	 	
    KeyModuleProcess(&KeyInfo);	
}

/*
* 函数名称 : IsKey
* 功能描述 : 按键事件判断API
* 参    数 : KeyId:按键ID / KeyEvent:按键事件类型
* 返回值   : 1:有KeyEvent事件发生 / 0:无
*/
/******************************************************************************/
uint8_t IsKey(uint32_t KeyId, TE_KEY_EVENT KeyEvent)
/******************************************************************************/  
{
	if(KeyInfo.KeyCur == KeyId)
	{
		if(KeyInfo.KeyEvent & KeyEvent)
		{
			KeyInfo.KeyEvent = KEY_EVT_NULL;
			return 1;
		}
	}
	return 0;
}
/******************************* End of File (C) ******************************/

