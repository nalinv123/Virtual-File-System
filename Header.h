#define _CRT_SECURE_NO_WARNINGS
#define MAXINODE 50
#define READ 1
#define WRITE 2
#define MAXFILESIZE 1024
#define REGULAR 1
#define SPECIAL 2
#define START 0
#define CURRENT 1
#define END 2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<io.h>

/*
	Name		:	SUPERBLOCK
	Description	:	It is a structure which stores information about total and free inodes	
*/

typedef struct superblock
{
	int TotalInodes;					//count of total inodes
	int FreeInode;						//count of free inodes
}SUPERBLOCK, *PSUPERBLOCK;

/*
	Name		:	INODE
	Description	:	It is a structure which stores information about file
*/

typedef struct inode
{
	char FileName[50];					//name of file
	int InodeNumber;					//inode number of file
	int FileSize;						//size of file(always 1KB)
	int FileActualSize;					//file actual size i.e. no of characters in file
	int FileType;						//type of file i.e. regular or not
	char *Buffer;						//pointer to pointing to actual data
	int LinkCount;						//count of from how many ways file can be opened
	int ReferenceCount;					//count of how many times file is opened
	int permission;						//permission given to the file while creating
	struct inode *next;					//pointing to next node from linked list of DILB
}INODE, *PINODE, **PPINODE;

/*
	Name		:	FILETABLE
	Description	:	It is a structure which stores information of file offset
*/

typedef struct filetable
{
	int readoffset;						//maintain read offset of file from where we have to read
	int writeoffset;					//maintain write offset of file from where we have to write
	int count;							//maintains count of file
	int mode;							//maintains in which mode file is opened
	PINODE ptrinode;					//pointer pointing to node of INODE structure linked list
}FILETABLE, *PFILETABLE;

/*
	Name		:	UFDT
	Description	:	It is structure which contains pointer to file table
*/

typedef struct ufdt
{
	PFILETABLE ptrfiletable;			//pointer pointing to file table
}UFDT;

void CreateDILB();
void InitialiseSuperBlock();
void ls_file();
void ls_All();
void man(char *);
void DisplayHelp();
int GetFDFromName(char *);
PINODE Get_Inode(char *);
void CloseAllFile();
int stat_file(char *);
int fstat_file(int);
int CreateFile(char *, int);
int rm_File(char *);
int OpenFile(char *, int);
int CloseFileByName(char *);
int WriteFile(int, char *, int);
int ReadFile(int, char *, int);
int truncate_File(char *);
int ftruncate(int);
int LseekFile(int, int, int);
int GetFileOffset(char *);
int chmod(char *, int);