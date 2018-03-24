#include"header.h"

UFDT UFDTArr[50];						//object of UFDT structure
SUPERBLOCK SUPERBLOCKobj;					//object of SUPERBLOCK structure
PINODE head = NULL;						//pointer pointing to first node of DILB

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	man
// Author	:	Nalin
// Input	:	char *name	: It accepts name of command from user
// Output	:	Nothing
// Description	:	It display information about commands used in project		
///////////////////////////////////////////////////////////////////////////////////////////////////

void man(char *name)
{
	if (name == NULL)
	{
		return;
	}
	if (strcmp(name, "create") == 0)
	{
		printf("Description : Used to create new regular file\n");
		printf("Usage : create File_name Permission\n");
	}
	else if (strcmp(name, "read") == 0)
	{
		printf("Description : Used to read data from regular file\n");
		printf("Usage : read File_name No_Of_Bytes_To_Read\n");
	}
	else if (strcmp(name, "write") == 0)
	{
		printf("Description : Used to write into regular file\n");
		printf("Usage : write File_name\n After this enter the data that we want to write\n");
	}
	else if (strcmp(name, "ls") == 0)
	{
		printf("Description : Used to list all information of files\n");
		printf("Usage : ls\n");
	}
	else if (strcmp(name, "stat") == 0)
	{
		printf("Description : Used to display information of file\n");
		printf("Usage : stat File_name\n");
	}
	else if (strcmp(name, "fstat") == 0)
	{
		printf("Description : Used to display information of file\n");
		printf("Usage : fstat File_Descriptor\n");
	}
	else if (strcmp(name, "truncate") == 0)
	{
		printf("Description : Used to remove data from file\n");
		printf("Usage : truncate File_name\n");
	}
	else if (strcmp(name, "open") == 0)
	{
		printf("Description : Used to open existing file file\n");
		printf("Usage : open File_name mode\n");
	}
	else if (strcmp(name, "close") == 0)
	{
		printf("Description : Used to close opened file\n");
		printf("Usage : close File_name\n");
	}
	else if (strcmp(name, "closeall") == 0)
	{
		printf("Description : Used to close all opened files\n");
		printf("Usage : closeall\n");
	}
	else if (strcmp(name, "lseek") == 0)
	{
		printf("Description : Used to change file offset\n");
		printf("Usage : lseek File_name ChangeInOffset StartPoint\n");
	}
	else if (strcmp(name, "rm") == 0)
	{
		printf("Description : Used to delete the file\n");
		printf("Usage : rm File_name\n");
	}
	else if (strcmp(name, "chmod") == 0)
	{
		printf("Description : Used to change the mode of file\n");
		printf("Usage : chmod File_name mode\n");
	}
	else if (strcmp(name, "offset") == 0)
	{
		printf("Description : Used to display read and write offset of file\n");
		printf("Usage : offset File_name\n");
	}
	else if (strcmp(name, "ftruncate") == 0)
	{
		printf("Description : Used to remove data from file\n");
		printf("Usage : ftruncate File_Descriptor\n");
	}
	else if (strcmp(name, "ls -a") == 0)
	{
		printf("Description : Used to display full information of the file\n");
		printf("Usage : ls -a\n");
	}
	else
	{
		printf("ERROR : No manual entry available.\n");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	DisplayHelp
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It display information about commands used in project		
///////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
	printf("ls	:	To list out all files\n");
	printf("clear	:	To clear console\n");
	printf("open	:	To open the file\n");
	printf("close	:	To close the file\n");
	printf("closeall :	To close all opened file\n");
	printf("read	:	To read the contents from file\n");
	printf("write	:	To write contents into file\n");
	printf("exit	: 	To terminate the file system\n");
	printf("stat	: 	To display information of file using name\n");
	printf("fstat	:	To display information of file using file descriptor\n");
	printf("truncate :	To remove all data from file\n");
	printf("rm	:	To delete the file\n");
	printf("ftruncate :	To remove all data from file using file descriptor\n");
	printf("chmod	:	To change mode of the file\n ");
	printf("offset	:	To display read and write offset of file\n");
	printf("ls -a	:	To display detailed information file\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	GetFDFromName
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	It returns file descriptor of file which is of type intger
// Description	:	It is used to get file descriptor from the file name		
///////////////////////////////////////////////////////////////////////////////////////////////////

int GetFDFromName(char *name)
{
	int i = 0;

	if (SUPERBLOCKobj.FreeInode == MAXINODE)
	{
		return -1;
	}

	while (i < 50)
	{
		if (UFDTArr[i].ptrfiletable != NULL)
		{
			if (UFDTArr[i].ptrfiletable->ptrinode->FileType != 0)
			{
				if (strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName), name) == 0)
				{
					break;
				}
			}
		}
		i++;
	}

	if (i == 50)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	Get_Inode
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	It returns address of inode structure
// Description	:	It is used to get address of inode structure from file name
///////////////////////////////////////////////////////////////////////////////////////////////////

PINODE Get_Inode(char *name)
{
	PINODE temp = head;

	if ((name == NULL) || (SUPERBLOCKobj.FreeInode == MAXINODE))
	{
		return NULL;
	}

	while (temp != NULL)
	{
		if ((strcmp(name, temp->FileName) == 0) && (temp->FileType != 0))
		{
			break;
		}
		temp = temp->next;
	}
	return temp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CreateDILB
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to create DILB
///////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
	PINODE newn = NULL;
	PINODE temp = head;
	int i = 1;

	while (i <= 50)
	{
		newn = (PINODE)malloc(sizeof(INODE));
		newn->LinkCount = newn->ReferenceCount = 0;
		newn->FileType = newn->FileSize = 0;
		newn->Buffer = NULL;
		newn->next = NULL;
		newn->InodeNumber = i;
		if (temp == NULL)
		{
			head = newn;
			temp = head;
		}
		else
		{
			temp->next = newn;
			temp = temp->next;
		}
		i++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	InitialiseSuperBlock
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to initialise contents of superblock
///////////////////////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
	int i = 0;
	while (i < 50)
	{
		UFDTArr[i].ptrfiletable = NULL;
		i++;
	}

	SUPERBLOCKobj.TotalInodes = MAXINODE;
	SUPERBLOCKobj.FreeInode = MAXINODE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CreateFile
// Author	:	Nalin
// Input	:	char *name	:	It accepts name of file from user
//			int permission	:	It accepts which permission should given to file	
// Output	:	It returns file descriptor of file which is of type integer
// Description	:	It is used to create a file
///////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(char *name, int permission)
{
	int i = 0;
	PINODE temp = head;

	if ((name == NULL) || (permission == 0) || (permission > 3))
	{
		return -1;
	}
	if (SUPERBLOCKobj.FreeInode == 0)
	{
		return -2;
	}
	if (Get_Inode(name) != NULL)
	{
		return -3;
	}

	(SUPERBLOCKobj.FreeInode)--;

	while (temp != NULL)
	{
		if (temp->FileType == 0)
			break;
		temp = temp->next;
	}

	while (i < 50)
	{
		if (UFDTArr[i].ptrfiletable == NULL)
			break;
		i++;
	}

	UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
	if (UFDTArr[i].ptrfiletable == NULL)
		return -4;

	UFDTArr[i].ptrfiletable->count = 1;
	UFDTArr[i].ptrfiletable->mode = permission;
	UFDTArr[i].ptrfiletable->readoffset = 0;
	UFDTArr[i].ptrfiletable->writeoffset = 0;

	UFDTArr[i].ptrfiletable->ptrinode = temp;
	strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName, name);
	UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR;
	UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1;
	UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
	UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
	UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
	UFDTArr[i].ptrfiletable->ptrinode->permission = permission;
	UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);
	memset(UFDTArr[i].ptrfiletable->ptrinode->Buffer, 0, 1024);

	return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	rm_File
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	Integer
// Description	:	It is used to remove the file
///////////////////////////////////////////////////////////////////////////////////////////////////

int rm_File(char *name)
{
	int fd = 0;

	fd = GetFDFromName(name);
	if (fd == -1)
	{
		return -1;
	}

	(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;

	if (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
	{
		UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
		free(UFDTArr[fd].ptrfiletable);
		free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
	}

	UFDTArr[fd].ptrfiletable = NULL;
	(SUPERBLOCKobj.FreeInode)++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	ReadFile
// Author	:	Nalin
// Input	:	int fd		:	It accepts file descriptor of file 
//			char *arr	:	It is a address of empty buffer
//			int isize	:	It accepts how many bytes to read
// Output	:	It returns how many bytes are read successfully
// Description	:	It is used to read file
///////////////////////////////////////////////////////////////////////////////////////////////////

int ReadFile(int fd, char *arr, int isize)
{
	int read_size = 0;

	if (UFDTArr[fd].ptrfiletable == NULL)
	{
		return -1;
	}
	if ((UFDTArr[fd].ptrfiletable->mode != READ) &&
		(UFDTArr[fd].ptrfiletable->mode != READ + WRITE))
	{
		return -2;
	}
	if ((UFDTArr[fd].ptrfiletable->ptrinode->permission != READ) &&
		(UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE))
	{
		return -2;
	}
	if (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize == 0)
	{
		return 0;
	}
	if (UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
	{
		return -3;
	}
	if (UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
	{
		return -4;
	}

	read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->readoffset);

	if (read_size <= isize)
	{
		strncpy(arr,
			(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),
			read_size
		);

		UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size;
		return read_size;
	}
	else
	{
		strncpy(arr,
			(UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset),
			isize
		);

		(UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + isize;
		return isize;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	WriteFile
// Author	:	Nalin
// Input	:	int fd		:	It accepts file descriptor of file
//			char *arr	:	It accepts address of filled buffer
//			int isize	:	It accepts how many bytes to write
// Output	:	It returns how many bytes are written
// Description	:	It is used to write data into file
///////////////////////////////////////////////////////////////////////////////////////////////////

int WriteFile(int fd, char *arr, int isize)
{
	if (((UFDTArr[fd].ptrfiletable->mode) != WRITE) &&
		((UFDTArr[fd].ptrfiletable->mode) != READ + WRITE))
	{
		return -1;
	}
	if (((UFDTArr[fd].ptrfiletable->ptrinode->permission) != WRITE) &&
		((UFDTArr[fd].ptrfiletable->ptrinode->permission) != READ + WRITE))
	{
		return -1;
	}
	if ((UFDTArr[fd].ptrfiletable->writeoffset) == MAXFILESIZE)
	{
		return -2;
	}
	if ((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR)
	{
		return -3;
	}

	strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->writeoffset), arr, isize);

	(UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + isize;

	(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + isize;

	return isize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	OpenFile
// Author	:	Nalin
// Input	:	char *name	:	It accepts name of file from user
//			int mode	:	It accepts in which mode you want to open file
// Output	:	It returns file descriptor of file
// Description	:	It is used to open file
///////////////////////////////////////////////////////////////////////////////////////////////////

int OpenFile(char *name, int mode)
{
	int i = 0;
	PINODE temp = NULL;

	if ((name == NULL) || (mode <= 0) || (mode > 3))
	{
		return -1;
	}

	temp = Get_Inode(name);
	if (temp == NULL)
	{
		return -2;
	}

	if (temp->permission < mode)
	{
		return -3;
	}

	while (i < 50)
	{
		if (UFDTArr[i].ptrfiletable == NULL)
		{
			break;
		}
		i++;
	}
	if (i == 50)
	{
		return -5;
	}

	UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
	if (UFDTArr[i].ptrfiletable == NULL)
	{
		return -4;
	}
	UFDTArr[i].ptrfiletable->count = 1;
	UFDTArr[i].ptrfiletable->mode = mode;

	if (mode == READ + WRITE)
	{
		UFDTArr[i].ptrfiletable->readoffset = 0;
		UFDTArr[i].ptrfiletable->writeoffset = 0;
	}
	else if (mode == READ)
	{
		UFDTArr[i].ptrfiletable->readoffset = 0;
	}
	else if (mode == WRITE)
	{
		UFDTArr[i].ptrfiletable->writeoffset = 0;
	}
	UFDTArr[i].ptrfiletable->ptrinode = temp;
	(UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;

	return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CloseFileByName
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	returns 0 if file is closed
// Description	:	It is used to close the file
///////////////////////////////////////////////////////////////////////////////////////////////////

int CloseFileByName(char *name)
{
	int i = 0;

	i = GetFDFromName(name);
	if (i == -1)
	{
		return -1;
	}
	if (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount == 0)
	{
		return -2;
	}

	UFDTArr[i].ptrfiletable->readoffset = 0;
	UFDTArr[i].ptrfiletable->writeoffset = 0;
	(UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CloseAllFile
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to close all files
///////////////////////////////////////////////////////////////////////////////////////////////////

void CloseAllFile()
{
	int i = 0;
	while (i < 50)
	{
		if (UFDTArr[i].ptrfiletable != NULL)
		{
			if (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount != 0)
			{
				UFDTArr[i].ptrfiletable->readoffset = 0;
				UFDTArr[i].ptrfiletable->writeoffset = 0;
				(UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
			}
		}
		i++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	LseekFile
// Author	:	Nalin
// Input	:	int fd		:	It accepts file descriptor of file
//			int size	:	It accepts how many bytes to be shift
//			int from	:	It accepts from where to shift
// Output	:	It returns how many bytes are shift
// Description:	It is used to shift offset of file
///////////////////////////////////////////////////////////////////////////////////////////////////

int LseekFile(int fd, int size, int from)
{
	if ((from < 0) || (from > 2))
	{
		return -1;
	}
	if (UFDTArr[fd].ptrfiletable == NULL)
	{
		return -1;
	}


	if ((UFDTArr[fd].ptrfiletable->mode == READ) ||
		(UFDTArr[fd].ptrfiletable->mode == READ + WRITE))
	{
		if (from == CURRENT)
		{
			if (((UFDTArr[fd].ptrfiletable->readoffset) + size) >
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				return -1;
			}
			if (((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
			{
				return -1;
			}
			(UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + size;
		}
		else if (from == START)
		{
			if (size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				return -1;
			}
			if (size < 0)
			{
				return -1;
			}
			(UFDTArr[fd].ptrfiletable->readoffset) = size;
		}
		else if (from == END)
		{
			if ((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)
			{
				return -1;
			}
			if (((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
			{
				return -1;
			}
			(UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
		}
	}
	else if (UFDTArr[fd].ptrfiletable->mode == WRITE)
	{
		if (from == CURRENT)
		{
			if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) > MAXFILESIZE)
			{
				return -1;
			}
			if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)
			{
				return -1;
			}
			if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) >
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;
			}
			(UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;
		}
		else if (from == START)
		{
			if (size > MAXFILESIZE)
			{
				return -1;
			}
			if (size < 0)
			{
				return -1;
			}
			if (size >(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = size;
			}
			(UFDTArr[fd].ptrfiletable->writeoffset) = size;
		}
		else if (from == END)
		{
			if ((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)
			{
				return -1;
			}
			if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)
			{
				return -1;
			}
			(UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
			(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->writeoffset);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	ls_file
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to display names of file
///////////////////////////////////////////////////////////////////////////////////////////////////

void ls_file()
{
	PINODE temp = head;

	if (SUPERBLOCKobj.FreeInode == MAXINODE)
	{
		printf("\nError : There are no files\n");
		return;
	}

	printf("\nFile Name\tInode number\tFile size\tLink Count\n");
	printf("----------------------------------------------------------\n");
	while (temp != NULL)
	{
		if (temp->FileType != 0)
		{
			printf("%s\t\t%d\t\t%d\t\t%d\n",
				temp->FileName, temp->InodeNumber, temp->FileActualSize, temp->LinkCount);
		}
		temp = temp->next;
	}
	printf("----------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	ls_All
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to display all information of all files
///////////////////////////////////////////////////////////////////////////////////////////////////

void ls_All()
{
	PINODE temp = head;

	if (SUPERBLOCKobj.FreeInode == MAXINODE)
	{
		printf("\nError : There are no files\n");
		return;
	}

	printf("\nFile Name\tInode number\tFile size\tLink Count\tReference Count\t\tPermission\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	while (temp != NULL)
	{
		if (temp->FileType != 0)
		{
			printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
				temp->FileName, temp->InodeNumber, temp->FileActualSize, temp->LinkCount, temp->ReferenceCount,temp->permission);
		}
		temp = temp->next;
	}
	printf("----------------------------------------------------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	fstat_file
// Author	:	Nalin
// Input	:	int fd	:	It accepts file descriptor of file
// Output	:	It returns 0 if file information is displayed successfully
// Description	:	It is used to display file information
///////////////////////////////////////////////////////////////////////////////////////////////////

int fstat_file(int fd)
{
	PINODE temp = head;

	if ((fd < 0) || (fd > MAXINODE-1))
	{
		return -1;
	}
	if (UFDTArr[fd].ptrfiletable == NULL)
	{
		return -2;
	}

	temp = UFDTArr[fd].ptrfiletable->ptrinode;

	printf("----------Statistical Information about file----------\n");
	printf("File Name : %s\n", temp->FileName);
	printf("Inode Number : %d\n", temp->InodeNumber);
	printf("File Size : %d\n", temp->FileSize);
	printf("Actual File Size : %d\n", temp->FileActualSize);
	printf("Link Count : %d\n", temp->LinkCount);
	printf("Reference Count : %d\n", temp->ReferenceCount);

	if (temp->permission == 1)
	{
		printf("File Permission : Read only\n");
	}
	else if (temp->permission == 2)
	{
		printf("File Permission : Write\n");
	}
	else if (temp->permission == 3)
	{
		printf("File Permission : Read & Write\n");
	}
	printf("------------------------------------------------------\n\n");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	stat_file
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	It returns 0 if file information displayed successfully
// Description	:	It is used to display information of file
///////////////////////////////////////////////////////////////////////////////////////////////////

int stat_file(char *name)
{
	PINODE temp = head;

	if (name == NULL)
	{
		return -1;
	}

	if (SUPERBLOCKobj.FreeInode == MAXINODE)
	{
		return -1;
	}

	while (temp != NULL)
	{
		if (temp->FileType != 0)
		{
			if (strcmp(name, temp->FileName) == 0)
			{
				break;
			}
			temp = temp->next;
		}
	}

	if (temp == NULL)
	{
		return -2;
	}

	printf("----------Statistical Information about file----------\n");
	printf("File Name : %s\n", temp->FileName);
	printf("Inode Number : %d\n", temp->InodeNumber);
	printf("File Size : %d\n", temp->FileSize);
	printf("Actual File Size : %d\n", temp->FileActualSize);
	printf("Link Count : %d\n", temp->LinkCount);
	printf("Reference Count : %d\n", temp->ReferenceCount);

	if (temp->permission == 1)
	{
		printf("File Permission : Read only\n");
	}
	else if (temp->permission == 2)
	{
		printf("File Permission : Write\n");
	}
	else if (temp->permission == 3)
	{
		printf("File Permission : Read & Write\n");
	}
	printf("------------------------------------------------------\n\n");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	truncate_File
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	Integer
// Description	:	It is used to delete data from file
///////////////////////////////////////////////////////////////////////////////////////////////////

int truncate_File(char *name)
{
	int fd = GetFDFromName(name);
	if (fd == -1)
	{
		return -1;
	}

	if (UFDTArr[fd].ptrfiletable->writeoffset != 0)
	{
		memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer, 0, (UFDTArr[fd].ptrfiletable->writeoffset + 1));
		UFDTArr[fd].ptrfiletable->readoffset = 0;
		UFDTArr[fd].ptrfiletable->writeoffset = 0;
		UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	ftruncate
// Author	:	Nalin
// Input	:	int fd	: It accepts file descriptor of file
// Output	:	Integer
// Description	:	It is used to delete data from file
///////////////////////////////////////////////////////////////////////////////////////////////////

int Ftruncate(int fd)
{
	if ((fd == -1) || (fd > MAXINODE -1))
	{
		return -1;
	}

	if (UFDTArr[fd].ptrfiletable == NULL)
	{
		return -2;
	}

	if (UFDTArr[fd].ptrfiletable->writeoffset != 0)
	{
		memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer, 0, (UFDTArr[fd].ptrfiletable->writeoffset + 1));
		UFDTArr[fd].ptrfiletable->readoffset = 0;
		UFDTArr[fd].ptrfiletable->writeoffset = 0;
		UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	chmod
// Author	:	Nalin
// Input	:	char *name	:	It accepts name of file from user
//				int mode	:	It accepts mode to change
// Output	:	Integer
// Description	:	It is used to change mode of file
///////////////////////////////////////////////////////////////////////////////////////////////////

int chmod(char *name, int mode)
{
	if ((name == NULL) || (mode <= 0) || (mode > 3))
	{
		return -1;
	}
	
	int fd = GetFDFromName(name);
	if (fd == -1)
	{
		return -2;
	}
	if((UFDTArr[fd].ptrfiletable->mode == mode) || (UFDTArr[fd].ptrfiletable->ptrinode->permission == mode))
	{
		return -3;
	}

	if (mode == READ)
	{
		UFDTArr[fd].ptrfiletable->mode = mode;
		UFDTArr[fd].ptrfiletable->ptrinode->permission = mode;
		UFDTArr[fd].ptrfiletable->readoffset = 0;
	}
	else if(mode == WRITE)
	{
		UFDTArr[fd].ptrfiletable->mode = mode;
		UFDTArr[fd].ptrfiletable->ptrinode->permission = mode;
		UFDTArr[fd].ptrfiletable->writeoffset = 0;
	}
	else if (mode == READ + WRITE)
	{
		UFDTArr[fd].ptrfiletable->mode = mode;
		UFDTArr[fd].ptrfiletable->ptrinode->permission = mode;
		UFDTArr[fd].ptrfiletable->readoffset = 0;
		UFDTArr[fd].ptrfiletable->mode = mode;
		UFDTArr[fd].ptrfiletable->ptrinode->permission = mode;
		UFDTArr[fd].ptrfiletable->readoffset = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	GetFileOffset
// Author	:	Nalin
// Input	:	char *name	: It accepts name of file from user
// Output	:	Integer
// Description	:	It is used to display file offset
///////////////////////////////////////////////////////////////////////////////////////////////////

int GetFileOffset(char *name)
{
	if (name == NULL)
	{
		return -1;
	}

	int fd = GetFDFromName(name);
	if (fd == -1)
	{
		return -2;
	}

	printf("\nRead Offset\tWrite Offset\n");
	printf("-------------------------------------\n");
	printf("%d\t\t%d\t\t\n", UFDTArr[fd].ptrfiletable->readoffset, UFDTArr[fd].ptrfiletable->writeoffset);
	printf("-------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CreateBackup
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to take backup of files
///////////////////////////////////////////////////////////////////////////////////////////////////

void CreateBackup()
{
	int fd, ret;
	struct inode
	{
		char FileName[50];
		int InodeNumber;
		int FileSize;
		int FileActualSize;
		int FileType;
		char arr[1024];
		int LinkCount;
		int ReferenceCount;
		int permission;
	}obj;
	PINODE temp = head;
	
	fd = creat("backup.txt",0700);
	if(fd == -1)
	{
		return;
	}
	while(temp != NULL)
	{
		if(temp->FileType != 0)
		{
			strcpy(obj.FileName,temp->FileName);
			obj.InodeNumber = temp->InodeNumber;
			obj.FileSize = temp->FileSize;
			obj.FileActualSize = temp->FileActualSize;
			obj.FileType = temp->FileType;
			obj.LinkCount = temp->LinkCount;
			obj.ReferenceCount = temp->ReferenceCount;
			obj.permission = temp->permission;
			strcpy(obj.arr,temp->Buffer);
			write(fd, &obj, sizeof(obj));
			if(ret == -1)
			{
				printf("\n Fail in write\n");
			}
			memset(&obj,0,sizeof(obj));
		}
		temp = temp->next;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	RestoreBackup
// Author	:	Nalin
// Input	:	Nothing
// Output	:	Nothing
// Description	:	It is used to restore the backup of files
///////////////////////////////////////////////////////////////////////////////////////////////////

void RestoreBackup()
{
	int filedes, ret, fd;
	struct inode
	{
		char FileName[50];
		int InodeNumber;
		int FileSize;
		int FileActualSize;
		int FileType;
		char arr[1024];
		int LinkCount;
		int ReferenceCount;
		int permission;
	}obj;
	PINODE temp = head;
	
	filedes = open("backup.txt", O_RDONLY);
	if(filedes == -1)
	{
		return;
	}
	
	while(temp != NULL)
	{
		ret = read(filedes, &obj, sizeof(obj));
		if(ret == -1)
		{
			return;
		}
		if(obj.InodeNumber == temp->InodeNumber)
		{
			SUPERBLOCKobj.FreeInode--;
			fd = obj.InodeNumber - 1;
			UFDTArr[fd].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
			UFDTArr[fd].ptrfiletable->readoffset = 0;
			UFDTArr[fd].ptrfiletable->writeoffset = 0;
			UFDTArr[fd].ptrfiletable->count = 0;
			UFDTArr[fd].ptrfiletable->mode = obj.permission;
			UFDTArr[fd].ptrfiletable->ptrinode = temp;
			strcpy(temp->FileName,obj.FileName);
			temp->InodeNumber = obj.InodeNumber;
			temp->FileSize = obj.FileSize;
			temp->FileActualSize = obj.FileActualSize;
			temp->FileType = obj.FileType;
			temp->LinkCount = obj.LinkCount;
			temp->ReferenceCount = obj.ReferenceCount;
			temp->permission = obj.permission;
			temp->Buffer = (char *)malloc(MAXFILESIZE);
			strcpy(temp->Buffer,obj.arr);
		}
		temp = temp->next;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name		:	CheckLoginDetails
// Author	:	Nalin
// Input	:	char *user1	:	It accepts address of original username
//			char *user2	:	It accepts address of user entered username
//			char *pass1	:	It accepts address of original password
//			char *pass2	:	It accepts address of user entered password
// Output	:	BOOL
//			returns TRUE if username and password is correct
//			returns FALSE if username and password is incorrect
// Description	:	It is used to check wheather user entered username and password is correct
//			or not
///////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CheckLoginDetails	(
				char *user1,
				char *user2,
				char *pass1,
				char *pass2
			)
{
	if((user1 == NULL) ||  (user2 == NULL) ||(pass1 == NULL) || (pass2 == NULL))
	{
		return FALSE;
	}
	
	if(((strcmp(user1, user2)) == 0) && ((strcmp(pass1, pass2)) == 0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
