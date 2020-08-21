#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_PATH 1024

//#ifndef DIRSIZ
//#define DIRSIZ 14
//#endif 

void fsize(char*);
void dirwalk(char*, void(*fcn)(char*));

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		fsize(".");
	}
	else
	{
		while (--argc > 0)
		{
			fsize(*++argv);
		}
	}

	return 0;
}

void fsize(char* name)
{
	struct stat stbuf;
	struct tm mt;

	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		dirwalk(name,fsize);
	}

	printf("%d %d ", stbuf.st_uid, stbuf.st_gid);
	printf("%12ld ", stbuf.st_size);

	mt = *localtime(&stbuf.st_mtime);
	printf("%4d-%02d-%02d %02d:%02d ", (1900 + mt.tm_year), mt.tm_mday, mt.tm_hour, mt.tm_min);

	printf("%81d %s\n", stbuf.st_size, name);
}

void dirwalk(char* dir, void(*fcn)(char*))
{
	char name[MAX_PATH];
	struct dirent* dp;
	DIR* dfd;

	if ((dfd = opendir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: не могу открыть %s\n", dir);
		return;
	}

	while ((dp = readdir(dfd)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
		{
			continue;
		}

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
		{
			fprintf(stderr, "dirwalk: слишком длинное имя %s/%s\n", dir, dp->d_name);
		}
		else
		{
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}

	closedir(dfd);
}