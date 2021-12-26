//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STC12C5A60S2,����30M  ��Ƭ��������ѹ3.3V
//QDtech-TFTҺ������ for C51
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567
//�ֻ�:15989313508���빤��
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/8/22
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
//********************************************************************************
//=========================================��Դ����================================================//
//5V��DC 3.3V/5V��Դ
//GND�ӵ�
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ4����SPI
//Һ����ģ��            ��Ƭ��
//  SDA          ��       P15        //SPIд�ź�
//=======================================Һ���������߽���==========================================//
//Һ����ģ��            ��Ƭ��
//  CS           ��       P13       //Ƭѡ�����ź�
//  RES          ��       P33       //��λ�ź�
//  DC           ��       P12       //����/����ѡ������ź�
//  SCL          ��       P17       //SPIʱ���ź�
//  BLK          ��       P32       //��������źţ����ʹ��STC89C52RC��Ƭ�����߲���Ҫ���ƣ���3.3V
//=========================================����������=========================================//
//STC89C52RC��Ƭ��ROM̫С���޷����д��������ܵĳ������Դ���������Ҫ����
//��ʹ�ô�������ģ�鱾������������ɲ�����
//������ʹ�õ�������������ΪSPI
//������ģ��            ��Ƭ��
//  T_CLK        ��       P36       //������SPIʱ���ź�
//  T_CS         ��       P37       //������Ƭѡ�����ź�
//  T_DIN        ��       P34       //������SPIд�ź�
//  T_DO         ��       P35       //������SPI���ź�
//  T_IRQ        ��       P40       //��������Ӧ����źţ��絥Ƭ����P4�飬�����и�����������IO���޸Ĵ��붨��
//**************************************************************************************************/
#include "../Inc/ST7735s.h"
#include "string.h"
#include "debug.h"
#include "../Inc/st7735s_gui.h"
#include "../Inc/ST7735s_test.h"
#include "../Inc/st7735s_096_pic.h"

//========================variable==========================//
u16 ColorTab[5] = {RED, GREEN, BLUE, YELLOW, BRED}; //������ɫ����
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/
void DrawTestPage(u8 *str)
{
	//���ƹ̶���up
	LCD_Clear(WHITE);
	LCD_Fill(0, 0, lcddev.width, 20, BLUE);
	//���ƹ̶���down
	//LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR = WHITE;
	Gui_StrCenter(0, 2, WHITE, BLUE, str, 16, 1); //������ʾ
	//Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"www.lcdwiki.com",16,1);//������ʾ
	//���Ʋ�������
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Display_ButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
 * @date       :2018-08-24 
 * @function   :Drawing a 3D button
 * @parameters :x1:the bebinning x coordinate of the button
                y1:the bebinning y coordinate of the button
								x2:the ending x coordinate of the button
								y2:the ending y coordinate of the button
 * @retvalue   :None
******************************************************************************/
void Display_ButtonUp(u16 x1, u16 y1, u16 x2, u16 y2)
{
	POINT_COLOR = WHITE;
	LCD_DrawLine(x1, y1, x2, y1); //H
	LCD_DrawLine(x1, y1, x1, y2); //V

	POINT_COLOR = GRAY1;
	LCD_DrawLine(x1 + 1, y2 - 1, x2, y2 - 1); //H
	POINT_COLOR = GRAY2;
	LCD_DrawLine(x1, y2, x2, y2); //H
	POINT_COLOR = GRAY1;
	LCD_DrawLine(x2 - 1, y1 + 1, x2 - 1, y2); //V
	POINT_COLOR = GRAY2;
	LCD_DrawLine(x2, y1, x2, y2); //V
}

/*****************************************************************************
 * @name       :void menu_test(void)
 * @date       :2018-08-24 
 * @function   :Drawing a 3D menu UI
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void menu_test(void)
{
	LCD_Clear(GRAY0);
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		Display_ButtonUp(27, 1, 133, 21); //x1,y1,x2,y2
		Gui_StrCenter(0, 2, BRED, BLUE, "ͼ����ʾ����", 16, 1);

		Display_ButtonUp(27, 29, 133, 49); //x1,y1,x2,y2
		Gui_StrCenter(0, 30, BROWN, GRAY0, "��ɫ������", 16, 1);

		Display_ButtonUp(27, 58, 133, 78); //x1,y1,x2,y2
		Gui_StrCenter(0, 59, BLUE, GRAY0, "������ʾ����", 16, 1);
	}
	else
	{
		Display_ButtonUp(2, 25, 77, 45); //x1,y1,x2,y2
		Gui_StrCenter(0, 26, BRED, BLUE, "ͼ����ʾ", 16, 1);

		Display_ButtonUp(2, 55, 77, 75); //x1,y1,x2,y2
		Gui_StrCenter(0, 56, BROWN, GRAY0, "��ɫ���", 16, 1);

		Display_ButtonUp(2, 85, 77, 105); //x1,y1,x2,y2
		Gui_StrCenter(0, 86, BLUE, GRAY0, "������ʾ", 16, 1);

		Display_ButtonUp(2, 115, 77, 135); //x1,y1,x2,y2
		Gui_StrCenter(0, 116, RED, GRAY0, "ͼƬ��ʾ", 16, 1);
	}
	mDelaymS(1500);
	mDelaymS(500);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	//	DrawTestPage("�ۺϲ��Գ���");
	//	Gui_StrCenter(0,23,RED,BLUE,"ȫ������",16,1);//������ʾ
	LCD_Clear(WHITE);
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		Gui_StrCenter(0, 0, RED, BLUE, "ȫ������", 16, 1);				//������ʾ
		Gui_StrCenter(0, 16, RED, BLUE, "�ۺϲ��Գ���", 16, 1);			//������ʾ
		Gui_StrCenter(0, 32, GREEN, BLUE, "0.96\" IPS ST7735S", 16, 1); //������ʾ
		Gui_StrCenter(0, 48, BLACK, BLUE, "80X160", 16, 1);				//������ʾ
		Gui_StrCenter(0, 64, BLUE, BLUE, "2019-07-08", 16, 1);			//������ʾ
	}
	else
	{
		Gui_StrCenter(0, 32, RED, BLUE, "ȫ������", 16, 1);		//������ʾ
		Gui_StrCenter(0, 48, RED, BLUE, "�ۺϲ���", 16, 1);		//������ʾ
		Gui_StrCenter(0, 64, GREEN, BLUE, "0.96\" IPS", 16, 1); //������ʾ
		Gui_StrCenter(0, 80, BLACK, BLUE, "ST7735S", 16, 1);	//������ʾ
		Gui_StrCenter(0, 96, BROWN, BLUE, "80x160", 16, 1);		//������ʾ
		Gui_StrCenter(0, 112, BLUE, BLUE, "2019-07-08", 16, 1); //������ʾ
	}

	mDelaymS(1500);
	mDelaymS(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09 
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	//DrawTestPage("����1:��ɫ������");
	LCD_Fill(0, 0, lcddev.width, lcddev.height, WHITE);
	Show_Str(20, 30, BLUE, YELLOW, "BL Test", 16, 1);
	mDelaymS(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, RED);
	Show_Str(20, 30, BLUE, YELLOW, "RED ", 16, 1);
	mDelaymS(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, GREEN);
	Show_Str(20, 30, BLUE, YELLOW, "GREEN ", 16, 1);
	mDelaymS(800);
	LCD_Fill(0, 0, lcddev.width, lcddev.height, BLUE);
	Show_Str(20, 30, RED, YELLOW, "BLUE ", 16, 1);
	mDelaymS(800);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2018-08-09 
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
	u8 i = 0;
	// if(lcddev.dir==1||lcddev.dir==3)
	// {
	// 	LCD_Clear(WHITE);
	// 	LCD_Fill(0,0,20,lcddev.height-1,BLUE);
	// 	POINT_COLOR=WHITE;
	// 	Show_Str(2,8,WHITE,BLUE,"��",16,1);
	// 	Show_Str(2,24,WHITE,BLUE,"��",16,1);
	// 	Show_Str(2,40,WHITE,BLUE,"��",16,1);
	// 	Show_Str(2,56,WHITE,BLUE,"��",16,1);
	// }
	// else
	// {
	// 	DrawTestPage("�������");
	// }
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		LCD_DrawRectangle(lcddev.width / 2 - 38 + (i * 11), lcddev.height / 2 - 38 + (i * 11), lcddev.width / 2 - 38 + (i * 11) + 30, lcddev.height / 2 - 38 + (i * 11) + 30);
	}
	mDelaymS(1500);
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Fill(21, 0, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	else
	{
		LCD_Fill(0, 21, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		LCD_DrawFillRectangle(lcddev.width / 2 - 38 + (i * 11), lcddev.height / 2 - 38 + (i * 11), lcddev.width / 2 - 38 + (i * 11) + 30, lcddev.height / 2 - 38 + (i * 11) + 30);
	}
	mDelaymS(1500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-09 
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	u8 i = 0;
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0, 0, 20, lcddev.height - 1, BLUE);
		POINT_COLOR = WHITE;
		Show_Str(2, 8, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 24, WHITE, BLUE, "Բ", 16, 1);
		Show_Str(2, 40, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 56, WHITE, BLUE, "��", 16, 1);
	}
	else
	{
		DrawTestPage("��Բ���");
	}
	for (i = 0; i < 5; i++)
		gui_circle(lcddev.width / 2 - 23 + (i * 11), lcddev.height / 2 - 23 + (i * 11), ColorTab[i], 15, 0);
	mDelaymS(1500);
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Fill(21, 0, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	else
	{
		LCD_Fill(0, 21, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	for (i = 0; i < 5; i++)
		gui_circle(lcddev.width / 2 - 23 + (i * 11), lcddev.height / 2 - 23 + (i * 11), ColorTab[i], 15, 1);
	mDelaymS(1500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2018-08-09 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0, 0, 20, lcddev.height - 1, BLUE);
		POINT_COLOR = WHITE;
		Show_Str(2, 8, WHITE, BLUE, "Ӣ", 16, 1);
		Show_Str(2, 24, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 40, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 56, WHITE, BLUE, "ʾ", 16, 1);
		Show_Str(22, 12, BLUE, GREEN, "6X12:abcdeABCDE012345", 12, 0);
		Show_Str(22, 24, BLUE, YELLOW, "6X12:~!@#$%^&*()_+{}:", 12, 1);
		Show_Str(22, 40, BLUE, YELLOW, "8X16:abcdABCD0123", 16, 0);
		Show_Str(22, 56, BLUE, YELLOW, "8X16:~!@#$%^&*()", 16, 1);
		mDelaymS(1500);
		LCD_Fill(21, 0, lcddev.width - 1, lcddev.height - 1, BLACK);
		Show_Str(22, 12, BLUE, GREEN, "6X12:abcdeABCDE012345", 12, 0);
		Show_Str(22, 24, BLUE, YELLOW, "6X12:~!@#$%^&*()_+{}:", 12, 1);
		Show_Str(22, 40, BLUE, YELLOW, "8X16:abcdABCD0123", 16, 0);
		Show_Str(22, 56, BLUE, YELLOW, "8X16:~!@#$%^&*()", 16, 1);
	}
	else
	{
		DrawTestPage("Ӣ����ʾ");
		Show_Str(2, 34, BLUE, GREEN, "6X12:abcdefg", 12, 0);
		Show_Str(2, 46, BLUE, YELLOW, "6X12:ABCDEFG", 12, 1);
		Show_Str(2, 58, BLUE, BRRED, "6X12:0123456", 12, 0);
		Show_Str(2, 70, BLUE, YELLOW, "6X12:~!@#$%^", 12, 1);
		Show_Str(2, 86, BLUE, GREEN, "8X16:abcde", 16, 0);
		Show_Str(2, 102, BLUE, YELLOW, "8X16:ABCDE", 16, 1);
		Show_Str(2, 118, BLUE, BRRED, "8X16:0123", 16, 0);
		Show_Str(2, 134, BLUE, YELLOW, "8X16:~!@#", 16, 1);
		mDelaymS(1500);
		LCD_Fill(0, 21, lcddev.width - 1, lcddev.height - 1, BLACK);
		Show_Str(2, 34, BLUE, GREEN, "6X12:abcdefg", 12, 0);
		Show_Str(2, 46, BLUE, YELLOW, "6X12:ABCDEFG", 12, 1);
		Show_Str(2, 58, BLUE, BRRED, "6X12:0123456", 12, 0);
		Show_Str(2, 70, BLUE, YELLOW, "6X12:~!@#$%^", 12, 1);
		Show_Str(2, 86, BLUE, GREEN, "8X16:abcde", 16, 0);
		Show_Str(2, 102, BLUE, YELLOW, "8X16:ABCDE", 16, 1);
		Show_Str(2, 118, BLUE, BRRED, "8X16:0123", 16, 0);
		Show_Str(2, 134, BLUE, YELLOW, "8X16:~!@#", 16, 1);
	}

	mDelaymS(1200);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-09 
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	u8 i = 0;
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0, 0, 20, lcddev.height - 1, BLUE);
		POINT_COLOR = WHITE;
		Show_Str(2, 0, WHITE, BLUE, "S", 16, 1);
		Show_Str(2, 16, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 32, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 48, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 64, WHITE, BLUE, "��", 16, 1);
	}
	else
	{
		DrawTestPage("S�������");
	}
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		Draw_Triangel(lcddev.width / 2 - 38 + (i * 11), lcddev.height / 2 - 10 + (i * 11), lcddev.width / 2 - 23 - 1 + (i * 11), lcddev.height / 2 - 10 - 26 - 1 + (i * 11), lcddev.width / 2 - 8 - 1 + (i * 11), lcddev.height / 2 - 10 + (i * 11));
	}
	mDelaymS(1500);
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Fill(21, 0, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	else
	{
		LCD_Fill(0, 21, lcddev.width - 1, lcddev.height - 1, WHITE);
	}
	for (i = 0; i < 5; i++)
	{
		POINT_COLOR = ColorTab[i];
		Fill_Triangel(lcddev.width / 2 - 38 + (i * 11), lcddev.height / 2 - 10 + (i * 11), lcddev.width / 2 - 23 - 1 + (i * 11), lcddev.height / 2 - 10 - 26 - 1 + (i * 11), lcddev.width / 2 - 8 - 1 + (i * 11), lcddev.height / 2 - 10 + (i * 11));
	}
	mDelaymS(1500);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0, 0, 20, lcddev.height - 1, BLUE);
		POINT_COLOR = WHITE;
		Show_Str(2, 8, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 24, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 40, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 56, WHITE, BLUE, "ʾ", 16, 1);
		Show_Str(22, 3, RED, YELLOW, "ȫ�����ӻ�ӭ��", 16, 0);
		Show_Str(22, 19, BLUE, YELLOW, "���Ĳ���", 24, 1);
		Show_Str(22, 47, BLACK, YELLOW, "�������", 32, 1);
		mDelaymS(1500);
		LCD_Fill(21, 0, lcddev.width - 1, lcddev.height - 1, BLACK);
		Show_Str(22, 3, RED, YELLOW, "ȫ�����ӻ�ӭ��", 16, 0);
		Show_Str(22, 19, BLUE, YELLOW, "���Ĳ���", 24, 1);
		Show_Str(22, 47, WHITE, YELLOW, "�������", 32, 1);
	}
	else
	{
		DrawTestPage("������ʾ");
		Show_Str(2, 26, RED, YELLOW, "ȫ������", 16, 0);
		Show_Str(2, 42, BLUE, YELLOW, "����", 24, 1);
		Show_Str(2, 66, BLUE, YELLOW, "����", 24, 1);
		Show_Str(2, 90, BLACK, YELLOW, "����", 32, 1);
		Show_Str(2, 122, BLACK, YELLOW, "����", 32, 1);
		mDelaymS(1500);
		LCD_Fill(0, 21, lcddev.width - 1, lcddev.height - 1, BLACK);
		Show_Str(2, 26, RED, YELLOW, "ȫ������", 16, 0);
		Show_Str(2, 42, BLUE, YELLOW, "����", 24, 1);
		Show_Str(2, 66, BLUE, YELLOW, "����", 24, 1);
		Show_Str(2, 90, WHITE, YELLOW, "����", 32, 1);
		Show_Str(2, 122, WHITE, YELLOW, "����", 32, 1);
	}
	mDelaymS(1200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09 
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
	u8 i = 0, j = 0;
	if (lcddev.dir == 1 || lcddev.dir == 3)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0, 0, 20, lcddev.height - 1, BLUE);
		POINT_COLOR = WHITE;
		Show_Str(2, 8, WHITE, BLUE, "ͼ", 16, 1);
		Show_Str(2, 24, WHITE, BLUE, "Ƭ", 16, 1);
		Show_Str(2, 40, WHITE, BLUE, "��", 16, 1);
		Show_Str(2, 56, WHITE, BLUE, "ʾ", 16, 1);
		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Gui_Drawbmp16(30 + j * 40, i * 40, gImage_qq);
			}
		}
	}
	else
	{
		DrawTestPage("ͼƬ��ʾ");
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 2; j++)
			{
				Gui_Drawbmp16(j * 40, 30 + i * 40, gImage_qq);
			}
		}
	}
	mDelaymS(1200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09 
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Rotate_Test(void)
{
	u8 i = 0;
	u8 *Direction[4] = {"R:0", "R:90", "R:180", "R:270"};
	for (i = 0; i < 4; i++)
	{
		LCD_direction(i);
		DrawTestPage("��Ļ�Ƕ�");
		Show_Str(2, 21, BLUE, YELLOW, Direction[i], 16, 1);
		Gui_Drawbmp16((lcddev.width - 40) / 2, (lcddev.height - 40) / 2 + 5, gImage_qq);
		mDelaymS(1000);
		mDelaymS(1000);
	}
	LCD_direction(USE_HORIZONTAL);
}
