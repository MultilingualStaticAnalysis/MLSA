
//Necessary Includes
#include <waveplay.cpp>
#include <dos.h>
#include <iostream.h>
#include <math.h>
#include <mem.h>
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#define VRETRACE            0x08
#define INPUT_STATUS        0x03da
#define SCREEN_WIDTH 320
#define SVGA 0x13
#define TEXT 0x03
#define SET_MODE 0x00
#define VIDEO_INT 0x10
#define sgn(x) ((x<0)?-1:((x>0)?1:0))
//Necessary declarations
typedef unsigned short word;
typedef unsigned char  byte;
byte far *VGA = (byte far*)0xA0000000L;        /* this points to video memory. */
typedef long     fixed16_16;
typedef unsigned long  dword;
static fixed16_16 SIN_ACOS[1024];
int palorig[256][3];
//FUNCTION DECLARATIONS
void fillrect(int topx, int topy, int bottomx, int bottomy, int color);
byte Get_Pixel(unsigned x, unsigned y);
void fpixel(int x, int y, int color);
void wait_for_retrace(void);
void set_mode(byte mode);
void SetPalEntry(unsigned char entry, int red, int green, int blue);
void SavePal(void);
void line(int x1, int y1, int x2, int y2, int color);
void rectangle(int left,int top, int right, int bottom, int color);
void GetPal(unsigned char ColorNo, int &R,
	    int &G,      int &B);
void FadeIn(int pause);
void FadeOut(int pause = 0);
void setup(void);
void circle(int x,int y, int radius, int color);
void fillcircle(int x,int y, int radius, int color);
void ClearPal(void);
void setup()
{
int i;
for(i=0;i<1024;i++)                 /* create the sin(arccos(x)) table. */
  {
    SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
  }
}
void fpixel(int x,int y,int color)
{
  VGA[y*SCREEN_WIDTH+x]=color;
}
void set_mode(byte mode)
{
  union REGS regs;
  regs.h.ah = SET_MODE;
  regs.h.al = mode;
  int86(VIDEO_INT, &regs, &regs);
}
void line(int x1, int y1, int x2, int y2, int color)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;
  VGA[(py<<8)+(py<<6)+px]=color;
  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      fpixel(px,py,color);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      fpixel(px,py,color);
    }
  }
}
void rectangle(int left,int top, int right, int bottom, int color)
{
  line(left, top, right, top, color);
line(left, top, left, bottom, color);
line(right, top, right, bottom, color);
line(left, bottom, right, bottom, color);
}
void circle(int x,int y, int radius, int color)
{
  fixed16_16 n=0,invradius=(1/(float)radius)*0x10000L;
  int dx=0,dy=radius-1;
  word dxoffset,dyoffset,offset = (y<<8)+(y<<6)+x;
  while (dx<=dy)
  {
    dxoffset = (dx<<8) + (dx<<6);
    dyoffset = (dy<<8) + (dy<<6);
    VGA[offset+dy-dxoffset] = color;  /* octant 0 */
    VGA[offset+dx-dyoffset] = color;  /* octant 1 */
    VGA[offset-dx-dyoffset] = color;  /* octant 2 */
    VGA[offset-dy-dxoffset] = color;  /* octant 3 */
    VGA[offset-dy+dxoffset] = color;  /* octant 4 */
    VGA[offset-dx+dyoffset] = color;  /* octant 5 */
    VGA[offset+dx+dyoffset] = color;  /* octant 6 */
    VGA[offset+dy+dxoffset] = color;  /* octant 7 */
    dx++;
    n+=invradius;
    dy = (radius * SIN_ACOS[n>>6]) >>16;
  }
}
void GetPal(unsigned char ColorNo, int &R,
	    int &G,      int &B) {
  outp (0x03C7,ColorNo); // here is the pallette color I want read
  R = inp (0x03C9);
  G = inp (0x03C9);
  B = inp (0x03C9);
}
void SetPalEntry(unsigned char entry, int red, int green, int blue)
  {
    // tell the VGA card which register we will be writing
    outportb(0x3C8, entry);
    outportb(0x3C9, red);
    outportb(0x3C9, green);
    outportb(0x3C9, blue);
  }
void ClearPal()
{
    int entry;
    for (entry = 0; entry < 256; entry++)
    {
      SetPalEntry(entry, 0, 0, 0);
    }
  }
  void wait_for_retrace(void)
{
    /* wait until done with vertical retrace */
    while  ((inp(INPUT_STATUS) & VRETRACE));
    /* wait until done refreshing */
    while (!(inp(INPUT_STATUS) & VRETRACE));
}
  void FadeIn(int pause)
  {
    int intensity, entry, red, green, blue;
    for (intensity = 0; intensity < 64; intensity++)
    {
      //wait_for_retrace();
      for (entry = 0; entry < 256; entry++)
      {
	red   = palorig[entry][0] * intensity / 63;
        green = palorig[entry][1] * intensity / 63;
        blue  = palorig[entry][2] * intensity / 63;
        SetPalEntry(entry, red, green, blue);
      }
      // use this one if you feel it's all to fast for you
      delay(pause);
    }
  }
  void FadeOut(int pause)
  {
    int intensity, entry, red, green, blue;
    for (intensity = 63; intensity >= 0; intensity--)
    {
      wait_for_retrace();
      for (entry = 0; entry < 256; entry++)
      {
        red   = palorig[entry][0] * intensity / 63;
        green = palorig[entry][1] * intensity / 63;
	blue  = palorig[entry][2] * intensity / 63;
	SetPalEntry(entry, red, green, blue);
      }
      // use this one if you feel it's all to fast for you
      delay(pause);
    }
  }
void fillrect(int topx, int topy, int bottomx, int bottomy, int color)
{
	int a;
	rectangle(topx, topy, bottomx, bottomy, color);
	do
	{
	rectangle(topx++, topy, bottomx, bottomy, color);
        }
	while(topx!=bottomx);
	rectangle(topx++, topy, bottomx, bottomy, color);
}
void SavePal()
{
int red, green, blue,a;
for(a=0; a<256; a++)
{
GetPal(a, red, green, blue);
palorig[a][0]=red;
palorig[a][1]=green;
palorig[a][2]=blue;
}
}