/*
 * Filename: buildFileInfoTable.c
 * Author: Edward To
 * Userid: cs30xer
 * 
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/*
 *
 */

int
buildFileInfoTable(const char* filename, struct fileInfo** const tablePtr){

  DIR *directPtr;
  struct stat statStruct;
  struct fileInfo* tmpPtr;
  struct fileInfo* oldPtr = NULL;
  struct dirent *pDirent;
  char pathname[MAXNAMLEN];
  char errMsg[BUFSIZ];
  int numOfEntries;

  /* checks to see if there is a stat error */
  errno = 0;
  if(lstat(filename, &statStruct) != 0){
    (void)snprintf(errMsg, BUFSIZ, "lstat -- ");
    perror(errMsg);
    exit(EXIT_FAILURE);
  }


  //-------------------------------------------------------

  /* if myls is called on a directory*/
  if(S_ISDIR(statStruct.st_mode)){

    //open directory for filename and set to directPtr
    directPtr = opendir(filename);

    // if directory does not exist, print out error message
    if(directPtr == NULL){
      (void)snprintf(errMsg, BUFSIZ, "opendir -- %s", filename);
      perror(errMsg);
      exit(EXIT_FAILURE);
    }

    //print out name of directory
    (void)printf("%s:\n", filename);

    numOfEntries = 0;
    //Get name of each file in directory and save info into fileinfo struct
    while((pDirent = readdir(directPtr)) != NULL){
      (void)snprintf(pathname, MAXNAMLEN, "%s/%s", filename, pDirent->d_name);
      (void)lstat(pathname, &statStruct);
      tmpPtr = realloc( oldPtr ,sizeof(struct fileInfo)*(numOfEntries+1));
      if(tmpPtr == NULL){
        (void)fprintf(stderr, "Trying to realloc another struct fileInfo ");
        (void)fprintf(stderr, "(in buildFileInfoTable())\n");
        (void)fprintf(stderr, "Only partial info will be displayed.\n");
        (*tablePtr) = oldPtr;
        return numOfEntries;
      }

      oldPtr = tmpPtr;
      numOfEntries++;

      (void)strcpy(oldPtr[numOfEntries - 1].name, pDirent->d_name);
      oldPtr[numOfEntries - 1].stbuf = statStruct;

    }

    (void)closedir(directPtr);
    (*tablePtr) = oldPtr;


    return numOfEntries;

  }
  else{          //is file
    //allocate memory for the fileinfo struct
    tmpPtr = (struct fileInfo *)malloc(sizeof(struct fileInfo));

    //if allocation failed, print error message and exit
    if(tmpPtr == NULL){
       (void)fprintf(stderr, "Trying to malloc a struct fileInfo ");
       (void)fprintf(stderr, "(in buildFileInfoTable())\n");
       exit(EXIT_FAILURE);
    }

    //clear memory for the name
    (void)memset(tmpPtr->name, 0, sizeof(tmpPtr->name));

    //set name element in struct to filename
    (void)strcpy(tmpPtr->name, filename);

    //set stbuf with file information
    tmpPtr->stbuf = statStruct;
   
    //set tablePtr to the tmpPtr
    (*tablePtr) = tmpPtr;
       //return amount of entries (1)
    return 1;

  }

}
