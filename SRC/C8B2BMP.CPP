#include	<windows.h>
#include	<stdio.h>
#include	"pkzip.h"
#include	"le.h"

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_c8b2bmp(unsigned char *,char *);
extern	void	decode_palette_8bit(unsigned char *);



void	decode_c8b2bmp(
	unsigned char		*src,
	char				*name	)
{	unsigned char		*pal=src+0x70;
	unsigned long		sx=*(unsigned long *)(src+0x70+0x400+0x40);
	unsigned long		sy=*(unsigned long *)(src+0x70+0x400+0x44);
	unsigned char		*gdt=src+0x70+0x400+0x70;
	unsigned long		cx,cy;			//counter
	unsigned long		tl;				//tmp

	PKZIP				pkzip;
	char				tfn[0x100];
	HANDLE				hbmp;
	unsigned char		*bmp;
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;

	unsigned char		*bdst;
	unsigned long		sdst=0x1000000;

	bdst=new unsigned char[sdst];
	sdst=pkzip.m_extract(	src+0x70+(*(unsigned long *)(src+0x40))*(*(unsigned long *)(src+0x44))*4+0x1c,
							0x10000,
							bdst,
							sdst	);

	bmp=new unsigned char[sx*sy*4];
	memset(bmp,0x00,sx*sy*4);
	memset(&bf,0x00,sizeof(BITMAPFILEHEADER));
	memset(&bi,0x00,sizeof(BITMAPINFOHEADER));

	for(cx=0;cx<0x400;cx+=4){						//pal•ÏŠ·
		tl			=ler4(pal+cx);
		*(pal+cx+0)	=(unsigned char)(tl>> 8);		//B
		*(pal+cx+1)	=(unsigned char)(tl>>16);		//G
		*(pal+cx+2)	=(unsigned char)(tl>>24);		//R
		*(pal+cx+3)	=(unsigned char)(tl>> 0);	}	//X
	decode_palette_8bit(pal);						//ps2 pal•ÏŠ·

	sprintf(tfn,"%s.bmp",name);
	hbmp=NonOverWriteCreateFile((LPCSTR)tfn);
	if(hbmp==(HANDLE)-1){
		printf("\tError\tcan't create bmp file\n");
		exit(-1);									}

	*((char *)&bf.bfType+0)='B';
	*((char *)&bf.bfType+1)='M';
	bf.bfSize=			sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER)+
						sx*sy;								//image
	bf.bfOffBits=		sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER);
	bi.biSize=			sizeof(BITMAPINFOHEADER);
	bi.biWidth=			sx;
	bi.biHeight=		sy;
	bi.biPlanes=		1;
	bi.biBitCount=		32;
	WriteFile(hbmp,&bf,sizeof(BITMAPFILEHEADER),&tl,NULL);
	WriteFile(hbmp,&bi,sizeof(BITMAPINFOHEADER),&tl,NULL);

	for(cy=0;cy<sy;cy++)
		for(cx=0;cx<sx;cx++)
			memcpy(bmp+(cy*sx+cx)*4,pal+*(gdt+(sy-cy-1)*sx+cx)*4,4);

	WriteFile(hbmp,bmp,sx*sy*4,&tl,NULL);
	CloseHandle(hbmp);
	delete[]	bmp;
}
