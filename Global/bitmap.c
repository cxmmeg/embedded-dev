#include "Configure.h"

const INT8U BmpONE[]=
{
/*------------------------------------------------------------------------------
  源文件 / 文字 : 
  宽×高（像素）: 32×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/64字节
  数据转换日期  : 2009-7-16 10:49:27
------------------------------------------------------------------------------*/
0xFF,0x01,0x05,0x05,0x05,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};

const INT8U BmpTOW[]=
{
/*------------------------------------------------------------------------------
  源文件 / 文字 : 
  宽×高（像素）: 32×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/64字节
  数据转换日期  : 2009-7-16 13:13:10
------------------------------------------------------------------------------*/
0xFF,0x01,0x05,0x05,0x05,0x01,0x01,0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,
0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};



const INT8U BmpTHREE[]=
{
/*------------------------------------------------------------------------------
  源文件 / 文字 : C:\Documents and Settings\new\桌面\图\3.bmp
  宽×高（像素）: 32×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/64字节
  数据转换日期  : 2009-7-16 22:30:25
------------------------------------------------------------------------------*/
0xFF,0x01,0x05,0x05,0x05,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xF9,
0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x8F,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};




const INT8U BmpFOUR[]=
{
/*------------------------------------------------------------------------------
  源文件 / 文字 : C:\Documents and Settings\new\桌面\图\4.bmp
  宽×高（像素）: 32×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/64字节
  数据转换日期  : 2009-7-16 22:39:28
------------------------------------------------------------------------------*/
0xFF,0x01,0x05,0x05,0x05,0x01,0x01,0x01,0x01,0x01,0x81,0x81,0x81,0xF1,0x01,0xF1,
0x81,0x81,0x81,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x82,0x82,0x82,0x9E,0x80,0x9E,
0x82,0x82,0x82,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF
};


const INT8U * BMP[] ={
  BmpONE,BmpTOW,BmpTHREE,BmpFOUR
};

