#pragma once

#include <string>
#include <stdio.h>

enum FileAccessFlags
{
    READ,
    WRITE,
    READWRITE
};

struct FileContents
{
    char* buffer;
    int fileSize;
};

class FileReader
{
public:
    FileReader();
    ~FileReader();

    void OpenFile(char* fileName, FileAccessFlags access);

	void OpenFile(const char* fileName, FileAccessFlags access);

	FileContents * GetFileContents();

private:
    FILE* file;

	char* newContent;
	int contentSize;

    char* TranslateAccessFlag(FileAccessFlags flag);

	int GetFileSize(FILE* target);
};

