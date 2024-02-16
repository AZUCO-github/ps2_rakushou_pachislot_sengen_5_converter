#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_pake(unsigned char *,unsigned long);
extern	void	decode_g8b2bmp(unsigned char *,char *);
extern	void	decode_g4b2bmp(unsigned char *,char *);



void	decode_pake(unsigned char *src,unsigned long size)
{	unsigned char	*ip=src+0x10;
	unsigned long	 is=0;
	unsigned long	 ts=0x10;
	char			in[0x100];
	unsigned long	 tmp;
	HANDLE			hbin;

	for(;ts<=size;){
		sprintf(in,"%08X",ts);
		is=*(unsigned long *)ip;
		ts+=is+0x10;
		ip+=0x10;

		if(	(*(ip+0x00)==0x74)	&&			//tgs
			(*(ip+0x01)==0x67)	&&
			(*(ip+0x02)==0x73)	){

			sprintf(in,"%s.tgs",in);
			hbin=	NonOverWriteCreateFile((LPCSTR)in);
			if(hbin==(HANDLE)-1){
				printf("\tError\tcan't create file %s\n",in);	exit(-1);	}
			WriteFile(hbin,ip,is,&tmp,NULL);
			CloseHandle(hbin);
			goto	item_skip;					}

		if(	(*(ip+0x00)==0x58)	&&			//XMD
			(*(ip+0x01)==0x4d)	&&
			(*(ip+0x02)==0x44)	){

			sprintf(in,"%s.xmd",in);
			hbin=	NonOverWriteCreateFile((LPCSTR)in);
			if(hbin==(HANDLE)-1){
				printf("\tError\tcan't create file %s\n",in);	exit(-1);	}
			WriteFile(hbin,ip,is,&tmp,NULL);
			CloseHandle(hbin);
			goto	item_skip;					}

		if(	(*(ip+0x00)==0x53)	&&			//SW
			(*(ip+0x01)==0x57)	&&
			(*(ip+0x02)==0x10)	){

			sprintf(in,"%s.pswe",in);
			hbin=	NonOverWriteCreateFile((LPCSTR)in);
			if(hbin==(HANDLE)-1){
				printf("\tError\tcan't create file %s\n",in);	exit(-1);	}
			WriteFile(hbin,ip,is,&tmp,NULL);
			CloseHandle(hbin);
			goto	item_skip;					}

			sprintf(in,"%s.bin",in);
			hbin=	NonOverWriteCreateFile((LPCSTR)in);
			if(hbin==(HANDLE)-1){
				printf("\tError\tcan't create file %s\n",in);	exit(-1);	}
			WriteFile(hbin,ip,is,&tmp,NULL);
			CloseHandle(hbin);
item_skip:
		ip+=is;
	}
}
