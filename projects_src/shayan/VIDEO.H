
#ifndef _VIDEO_INCLUDED
#define _VIDEO_INCLUDED

void _VIDEO_INIT_DEVICE();
void _VIDEO_DEINIT_DEVICE();
void _VIDEO_CLEAR_SCREEN();
void _VIDEO_SET_PAL(char pal[]);
void _VIDEO_FADE_IN(int x,int y,char *pic,char pal[]);
void _VIDEO_FADE_OUT(char pal[]);
void _VIDEO_SCREEN2MEM(int x1,int y1,int x2,int y2,char *mem);
void _VIDEO_MEM2SCREEN(int x1,int y1,char *mem);
void _VIDEO_LOAD_BITMAP(const char*fname);

#endif