#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

// File structure
typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int size;
    char* data;
} File;

// File system structure
typedef struct {
    File files[MAX_FILES];
    int fileCount;
} FileSystem;

FileSystem myFileSystem;

void createFile(const char* name, int size) {
    if (myFileSystem.fileCount >= MAX_FILES) {
        printf("File system is full. Cannot create more files.\n");
        return;
    }

    if (size < 0) {
        printf("Invalid file size. File not created.\n");
        return;
    }

    File newFile;
    strncpy(newFile.name, name, MAX_FILENAME_LENGTH);
    newFile.size = size;
    newFile.data = (char*)malloc(size * sizeof(char));

    myFileSystem.files[myFileSystem.fileCount++] = newFile;

    printf("File '%s' created successfully.\n", name);
}

void deleteFile(const char* name) {
    int i;
    for (i = 0; i < myFileSystem.fileCount; ++i) {
        if (strcmp(myFileSystem.files[i].name, name) == 0) {
            free(myFileSystem.files[i].data);
            myFileSystem.files[i] = myFileSystem.files[--myFileSystem.fileCount];
            printf("File '%s' deleted successfully.\n", name);
            return;
        }
    }

    printf("File '%s' not found. Deletion failed.\n", name);
}

void readFile(const char* name) {
    int i;
    for (i = 0; i < myFileSystem.fileCount; ++i) {
        if (strcmp(myFileSystem.files[i].name, name) == 0) {
            printf("File '%s':\n", name);
            printf("%s\n", myFileSystem.files[i].data);
            return;
        }
    }

    printf("File '%s' not found. Read operation failed.\n", name);
}

void writeFile(const char* name, const char* data) {
    int i;
    for (i = 0; i < myFileSystem.fileCount; ++i) {
        if (strcmp(myFileSystem.files[i].name, name) == 0) {
            int dataSize = strlen(data);
            if (dataSize > myFileSystem.files[i].size) {
                printf("Data exceeds file size. Write operation failed.\n");
                return;
            }

            strncpy(myFileSystem.files[i].data, data, dataSize);
            printf("Data written to file '%s' successfully.\n", name);
            return;
        }
    }

    printf("File '%s' not found. Write operation failed.\n", name);
}
