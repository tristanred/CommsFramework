#pragma once

class XFile;
class XDirectory;
class EncryptedPackageFile;

#include <cstdio>
#include <string>

#include "FileReader.h"
#include "PointerList.h"

#define FILENAME_MAX_LENGTH 256
#define PACK_FILE_SIG_LENGTH 4

/*
    =Format=
    Header
    (4 bytes) signature = 'PACK'
    (4 bytes, int) offset to start of directory (offset is absolute)
    (4 bytes, int) directory lenght

    Directory entries
    (256 bytes, char) file name
    (4 bytes, int) file position (position is absolute)
    (4 bytes, int) file lenght

    Data Store
    (N bytes, char) File data
*/

#define HEADER_SIZE 12
struct Header {
    char sig[PACK_FILE_SIG_LENGTH];
    int dirOffset;
    int dirLength;
};

#define DIRECTORY_ENTRY_SIZE 264
struct DirectoryEntry {
    char fileName[FILENAME_MAX_LENGTH];
    int filePosition;
    int fileLength;

    char* fileContents;
};

/** \brief The PackageFile class is used to bundle files together that can be extracted afterwards.
*			The empty constructor is used to initiate a blank package where files can be added. 
*			The second constructor PackageFile(string) is used to specify an existing package file
*			that is used to extract files from.
* 
* PackageFile is implementing the PACK format from Quake. The 
* 
*
*/
class PackageFile
{
public:
    PackageFile();

	/**
		Constructor used to open an existing package. 

		This constructor needs to be used because there is no function Load(packagePath).
	*/
    PackageFile(std::string packageFilePath);

    ~PackageFile();

    virtual const char* GetFile(std::string filename, int& fileSize);

    PointerList<std::string>* GetAllFiles();

    void AddFile(std::string filename);
    void AddFile(XFile* file);

    void AddDirectory(std::string directoryPath);
    void AddDirectory(XDirectory* directory);

    void RemoveFile(std::string filename);

    EncryptedPackageFile* SaveEncrypt(std::string savePath, char* key);

    virtual void Save(std::string savePath);

    virtual void Extract(std::string outPath);

protected:

    virtual void AddFile(std::string filename, std::string directoryRoot);

    /**
    * Read the package's directory and puts the list of Entries in the entries list.
    *
    * The data is not read at this point, only the file names and offsets. */
    virtual void ReadPackage();

    virtual void ReadBytes(char* targetBuffer, int nbBytes, std::iostream* stream);

    virtual void WriteBytes(char* targetBuffer, int nbBytes, std::iostream* stream);

    struct FileListEntry
    {
        XFile* File;

        std::string RelativeDirectoryParentRoot;
    };

    /*
     * Indicate that the package has been read from disk after creating the PackageFile instance.
     *  If false, the function ReadPackage needs to be called to load the entries.
     */
    bool packageRead; 

    Header* packageHeader;

    PointerList<FileListEntry*>* filesList;

    PointerList<DirectoryEntry*>* entries;

    FileContents* contents;

    std::string TargetPackage;

    std::string OutputFileName;

    std::iostream* memStream;
};

