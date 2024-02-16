#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_pswe(unsigned char *,unsigned long);
extern	void	decode_g8b2bmp(unsigned char *,char *);
extern	void	decode_g4b2bmp(unsigned char *,char *);



void	decode_pswe(unsigned char *src,unsigned long size)
{	unsigned char	*ITB=*(unsigned long *)(src+0x10)+src;
	unsigned char	*INM=*(unsigned long *)(src+0x18)+src+8;
	unsigned long	 IMX=*(unsigned long *)ITB;
	unsigned long	 INB;
	unsigned long	 IAD;
	unsigned char	*ITP;

	for(INB=0;INB!=IMX;INB++){
		IAD=*(unsigned long *)(ITB+0x20);
		if(IAD==0)	goto	item_skip;

		ITP=src+IAD;

		if(	(*(unsigned long *)(ITP+0x00)==0x10000046)	&&
			(*(unsigned long *)(ITP+0x0c)==0x50000046)		){
			decode_g8b2bmp(ITP,(char *)INM);
			goto	item_skip;					}						//8bit

		if(	(*(unsigned long *)(ITP+0x00)==0x1000000a)	&&
			(*(unsigned long *)(ITP+0x0c)==0x5000000a)		){
			decode_g4b2bmp(ITP,(char *)INM);
			goto	item_skip;					}						//4bit

			printf("item skip - %s %08X %08X %08X\n",(char *)INM,
			IAD,
			*(unsigned long *)(ITP+0x00),
			*(unsigned long *)(ITP+0x0c));
item_skip:
		INM+=strlen((char *)INM)+1;
		ITB+=0x30;
	}
}
