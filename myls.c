/*
 * Filename: myls.c
 * Author: Edward To
 * Userid: cs30xer
 * Description: C main driver which displays the file or directory information
 *              based in input paramaters
 * Date: Dec 3, 2013
 * Sources of help: pa4, google, cplusplus, discussion slides, piazza
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Function name: myls()
 * Description: Main driver used to read in the directory or file and then the
 *              options and displays the relevant file info
 * Parameters: argc - amount of arguments input
 *             argv - array containing each argument input
 * Side effects:
 * Error conditions:
 * Return value:
 */

int OFFSET = (int)offsetof(struct fileInfo, stbuf.st_mtime);

int 
main( int argc, char * argv[])
{
  int c;        //switch statement case
  int flag = 0; // flag to set the bitmask in
  int file;     //how many entries
  int index;
  struct fileInfo* tablePtr = NULL;



  //loops through the operations
  while((c = getopt(argc, argv, "alrt")) != -1){

  //used to set the flags based on which opt is input
    switch(c)
    {
      case 'a':                 //display all
        flag = flag|AFLAG;
        break;

      case 'l':                 //display file info
        flag = flag|LFLAG;
        break;

      case 'r':                 //display reverse
        flag = flag|RFLAG;
        break;

      case 't':                 //display time order
        flag = flag|TFLAG;
        break;

      case '?':                 //usage print if error
        (void)fprintf(stderr, "Usage: %s [-alrt] [file ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  /*if there is only one directory/file */
    if(optind == argc){
      file = buildFileInfoTable(".", &tablePtr);
      displayFileInfo(tablePtr, file, flag);
      (void)free(tablePtr);
    }
   /* if there are multiple directories/files*/
    else{
      for(index = optind; index<argc; index++)
      {
        file = buildFileInfoTable(argv[index], &tablePtr);
        displayFileInfo(tablePtr, file, flag);
        (void)free(tablePtr);
      }
    }
    return 0;
}
