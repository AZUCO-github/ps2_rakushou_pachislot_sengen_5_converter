#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);

void	decode_dat(HANDLE);



void	decode_dat(HANDLE hndl)
{
	unsigned char	buf[0x40];
	unsigned long	size=GetFileSize(hndl,NULL);
	unsigned long	p;
	unsigned long	tmp;
	HANDLE			hbin;

	hbin=0;	hbin=0;

	for(p=0;p<size;p+=0x10){
						SetFilePointer(hndl,p,0,FILE_BEGIN);
						ReadFile(hndl,buf,0x40,&tmp,NULL);

//*.psw check
		if(	(buf[0]==0x1f)	&&
			(buf[1]==0x8b)	&&
			(buf[2]==0x08)	&&
			(buf[3]==0x08)		){

			if(hbin!=0)	CloseHandle(hbin);

				hbin=	NonOverWriteCreateFile((LPCSTR)(buf+10));
				if(hbin==(HANDLE)-1){
					printf("\tError\tcan't create file %s\n",buf+10);
					exit(-1);	}

			printf("No.%08X ",p);
			printf("%s\n",(char *)buf+10);
		}
		if(hbin!=0)		WriteFile(hbin,buf,0x10,&tmp,NULL);
	}
			if(hbin!=0)	CloseHandle(hbin);
}
