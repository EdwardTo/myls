/*
 * Filename: displayFileInfo.c
 * Author: Edward To
 * Userid: cs30xer
 * Description: C program meant to print out the file information that user
 *             inputs  in myls.c
 * Date: Dec 3, 2013
 * Sources of help: pa4 handout, discussion slides, piazza, google,
 *                  cplusplus.com
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/mkdev.h>
#include <sys/time.h>
#include <strings.h>

/* 
 * Function name: displayFileInfo()
 * Description: Displays the file information depending on whether the input
 *              mode is -r, -l, -a, -t or any combination of them. 
 * Parameters: table - the fileInfo struct containing all the info about the
 *              file
 *             entries - amount of entries 
 *             displayMode - bit mask to tell what mode is input
 * Side effects:
 * Error conditions:
 * Return value: none
 */

void 
displayFileInfo(struct fileInfo* const table, const int entries, 
                const int displayMode){
  int i;                  //loop increment
  //char* time2;
  char* time;             //used to store time value from ctime
  int timeDiff;           //difference from 6months ago to now
  struct timeval timeval; //timeval struct to store time values
  char *nulPtr;           //used to set values in time ptr to null
  char *monthPtr;         //store month value
  char *dayPtr;           //store day value
  char *hourPtr;          //store hour value
  char *minPtr;           //store min value
  char *yearPtr;          //store year value
  char *secPtr;           //store second value
  char *timeStr;
  char *strPtr;
  int month = 15724800;   //6month value


  /*if the user inputs just ./myls, display in alphabetical order without
  hidden files*/
  if(displayMode == 0){
    qsort(table, entries, sizeof(struct fileInfo), nameSortAscending);
    for(i = 0; i<entries; i++){
      if(basename(table[i].name)[0] != '.')
        (void)printf("%s\n", table[i].name);
    }
  }

  /*check cases for all options with t flag set*/
  if(displayMode & TFLAG){

    /*sort descending time*/
    if(displayMode & RFLAG){
      (void)qsort(table, entries, sizeof(struct fileInfo),
        mtimeSortDescending);
    }
    /*sort ascending time*/
    else{
      (void)qsort(table, entries, sizeof(struct fileInfo),
        mtimeSortAscending);
    }
    /*display -t mode*/
    if(!(displayMode & LFLAG) && !(displayMode & AFLAG)){
      for(i = 0; i < entries; i++){
        if(basename(table[i].name)[0] != '.')
          (void)printf("%s \n", table[i].name);
      }
    }
    /* display -t -a modes*/
    else if(!(displayMode & LFLAG))
    {
      for(i = 0; i < entries; i++){
        (void)printf("%s \n", table[i].name);
      }
    }
    /*display -t -l modes*/
    else if(!(displayMode & AFLAG))
    {
      for(i = 0; i < entries; i++){
        if(basename(table[i].name)[0] != '.'){
          /*display type of entry */
          if(S_ISDIR(table[i].stbuf.st_mode)){
            (void)printf("d");
          }
          else if(S_ISLNK(table[i].stbuf.st_mode)){
            (void)printf("l");
          }
          else if(S_ISBLK(table[i].stbuf.st_mode)){
            (void)printf("b");
          }
          else if(S_ISCHR(table[i].stbuf.st_mode)){
            (void)printf("c");
          }
          else{
            (void)printf("-");
          }
          /*display permissions, num of links, owner & group name */
          displayPermissions(table[i].stbuf.st_mode);
          (void)printf(" %3lu ", table[i].stbuf.st_nlink);
          displayOwnerName(table[i].stbuf.st_uid);
          displayGroupName(table[i].stbuf.st_gid);
          /*if entry is character or block device, display major and minor
           * num, else print size
           */
          if(S_ISBLK(table[i].stbuf.st_mode) || S_ISCHR(table[i].stbuf.st_mode))
          {
            (void)printf("%3lu,", major(table[i].stbuf.st_rdev));
            (void)printf("%3lu", minor(table[i].stbuf.st_rdev));
          }
          else{
            (void)printf("%7ld ", table[i].stbuf.st_size);
          }
          /*display the time*/
          time = ctime(&(table[i].stbuf.st_mtime));
          (void)gettimeofday(&timeval, NULL);
          timeDiff = timeval.tv_sec - table[i].stbuf.st_mtime;
                   
          /*if mod time was < 6 months, disp month day hour:min */
          if(timeDiff < month){
            /*get month value*/
            monthPtr = strchr(time, ' ');
            nulPtr = monthPtr;  
            *nulPtr = '\0';
            monthPtr++;
      
            /*get day value*/
            dayPtr = strchr(monthPtr, ' ');
            nulPtr = dayPtr;
            *nulPtr = '\0';
            dayPtr++;

            /*get hour value*/
            hourPtr = strchr(dayPtr, ' ');
            nulPtr = hourPtr;
            *nulPtr = '\0';
            hourPtr++;

            /*get min value*/
            minPtr = strchr(hourPtr, ':');
            nulPtr = minPtr;
            *nulPtr = '\0';
            minPtr++;
    
            /*get sec value*/
            secPtr = strchr(minPtr, ':');
            nulPtr = secPtr;
            *nulPtr = '\0';
            secPtr++;

            /*get year value*/
            yearPtr = strchr(secPtr, ' ');
            nulPtr = yearPtr;
            *nulPtr = '\0';
            yearPtr++;


            (void)printf("%s %s %s:%s ", monthPtr, dayPtr, hourPtr, minPtr);
          }
          else{
            
            timeStr = strchr(time, ':');
            timeStr-=2;
            (void)memmove(timeStr,strchr(timeStr, ' '), 5);
            timeStr+=5;
            *timeStr = '\0';
            strPtr = strchr(time, ' ');
            strPtr++;
            (void)printf("%s ", strPtr);


          }
          (void)printf("%s \n", table[i].name);
        }
      }
    }
    /*display -t -l -a*/
    else{
      for(i = 0; i < entries; i++){
        /*display type of entry */
        if(S_ISDIR(table[i].stbuf.st_mode)){
          (void)printf("d");
        }
        else if(S_ISLNK(table[i].stbuf.st_mode)){
          (void)printf("l");
        }
        else if(S_ISBLK(table[i].stbuf.st_mode)){
          (void)printf("b");
        }
        else if(S_ISCHR(table[i].stbuf.st_mode)){
          (void)printf("c");
        }
        else{
          (void)printf("-");
        }
        /*display permissions, num of links, owner & group name */
        displayPermissions(table[i].stbuf.st_mode);
        (void)printf(" %3lu", table[i].stbuf.st_nlink);
        displayOwnerName(table[i].stbuf.st_uid);
        displayGroupName(table[i].stbuf.st_gid);
        /*if entry is character or block device, display major and minor
        * num, else print size
        */
        if(S_ISBLK(table[i].stbuf.st_mode) || S_ISCHR(table[i].stbuf.st_mode))
        {
          (void)printf("%3lu,", major(table[i].stbuf.st_rdev));
          (void)printf("%3lu", minor(table[i].stbuf.st_rdev));
        }
        else{
          (void)printf("%7ld ", table[i].stbuf.st_size);
        }
        /*display the time*/
        time = ctime(&(table[i].stbuf.st_mtime));

        (void)gettimeofday(&timeval, NULL);
        timeDiff = timeval.tv_sec - table[i].stbuf.st_mtime;

        /*if mod time was < 6 months, disp month day hour:min */
        if(timeDiff < month){
          /*get month value*/
          monthPtr = strchr(time, ' ');
          nulPtr = monthPtr;  
          *nulPtr = '\0';
          monthPtr++;
        
          /*get day value*/
          dayPtr = strchr(monthPtr, ' ');
          nulPtr = dayPtr;
          *nulPtr = '\0';
          dayPtr++;

          /*get hour value*/
          hourPtr = strchr(dayPtr, ' ');
          nulPtr = hourPtr;
          *nulPtr = '\0';
          hourPtr++;

          /*get min value*/
          minPtr = strchr(hourPtr, ':');
          nulPtr = minPtr;
          *nulPtr = '\0';
          minPtr++;
  
          /*get sec value*/
          secPtr = strchr(minPtr, ':');
          nulPtr = secPtr;
          *nulPtr = '\0';
          secPtr++;

          /*get year value*/
          yearPtr = strchr(secPtr, ' ');
          nulPtr = yearPtr;
          *nulPtr = '\0';
          yearPtr++;
          
          (void)printf(" %s %s %s:%s ", monthPtr, dayPtr, hourPtr, minPtr);
        }
        else{
            timeStr = strchr(time, ':');
            timeStr-=2;
            (void)memmove(timeStr,strchr(timeStr, ' '), 5);
            timeStr+=5;
            *timeStr = '\0';
            strPtr = strchr(time, ' ');
            strPtr++;
            (void)printf("%s ", strPtr);
        }
        (void)printf("%s \n", table[i].name);
      }
    }
  }

  /*check all options with lflag set but not tflag*/
  if(displayMode & LFLAG && !(displayMode & TFLAG)){
    
    /*sort descending name*/
    if(displayMode & RFLAG){
      (void)qsort(table, entries, sizeof(struct fileInfo),
        nameSortDescending);
    }
    /*sort ascending name*/
    else{
      (void)qsort(table, entries, sizeof(struct fileInfo),
        nameSortAscending);
    }
    /*display -l mode*/
    if(!(displayMode & AFLAG)){
      for(i = 0; i < entries; i++){
        if(basename(table[i].name)[0] != '.'){
          /*display type of entry */
          if(S_ISDIR(table[i].stbuf.st_mode)){  
            (void)printf("d");
          }
          else if(S_ISLNK(table[i].stbuf.st_mode)){
            (void)printf("l");
          }
          else if(S_ISBLK(table[i].stbuf.st_mode)){
            (void)printf("b");
          }
          else if(S_ISCHR(table[i].stbuf.st_mode)){
            (void)printf("c");
          }
          else{
            (void)printf("-");
          } 
          /*display permissions, num of links, owner & group name */
          displayPermissions(table[i].stbuf.st_mode);
          (void)printf(" %3lu ", table[i].stbuf.st_nlink);
          displayOwnerName(table[i].stbuf.st_uid);
          displayGroupName(table[i].stbuf.st_gid);
          /*if entry is character or block device, display major and minor
           * num, else print size
           */
          if(S_ISBLK(table[i].stbuf.st_mode) || S_ISCHR(table[i].stbuf.st_mode))
          {
            (void)printf("%3lu,", major(table[i].stbuf.st_rdev));
            (void)printf("%3lu", minor(table[i].stbuf.st_rdev));
          }
          else{
            (void)printf("%7ld ", table[i].stbuf.st_size);
          }
          /*display the time*/
          time = ctime(&(table[i].stbuf.st_mtime));
          (void)gettimeofday(&timeval, NULL);
          timeDiff = timeval.tv_sec - table[i].stbuf.st_mtime;

          /*if mod time was < 6 months, disp month day hour:min */
          if(timeDiff < month){
            /*get month value*/
            monthPtr = strchr(time, ' ');
            nulPtr = monthPtr;  
            *nulPtr = '\0';
            monthPtr++;
      
            /*get day value*/
            dayPtr = strchr(monthPtr, ' ');
            nulPtr = dayPtr;
            *nulPtr = '\0';
            dayPtr++;

            /*get hour value*/
            hourPtr = strchr(dayPtr, ' ');
            nulPtr = hourPtr;
            *nulPtr = '\0';
            hourPtr++;

            /*get min value*/
            minPtr = strchr(hourPtr, ':');
            nulPtr = minPtr;
            *nulPtr = '\0';
            minPtr++;
  
            /*get sec value*/
            secPtr = strchr(minPtr, ':');
            nulPtr = secPtr;
            *nulPtr = '\0';
            secPtr++;

            /*get year value*/
            yearPtr = strchr(secPtr, ' ');
            nulPtr = yearPtr;
            *nulPtr = '\0';
            yearPtr++;
  
            (void)printf("%s %s %s:%s ", monthPtr, dayPtr, hourPtr, minPtr);
          }
          else{

            timeStr = strchr(time, ':');
            timeStr-=2;
            (void)memmove(timeStr,strchr(timeStr, ' '), 5);
            timeStr+=5;
            *timeStr = '\0';
            strPtr = strchr(time, ' ');
            strPtr++;
            (void)printf("%s ", strPtr);

          }
          (void)printf("%s \n", table[i].name);
        }
      }
    }
    /*display -l -a */
    else{
      for(i = 0; i < entries; i++){
          /*display type of entry */
          if(S_ISDIR(table[i].stbuf.st_mode)){  
            (void)printf("d");
          }
          else if(S_ISLNK(table[i].stbuf.st_mode)){
            (void)printf("l");
          }
          else if(S_ISBLK(table[i].stbuf.st_mode)){
            (void)printf("b");
          }
          else if(S_ISCHR(table[i].stbuf.st_mode)){
            (void)printf("c");
          }
          else{
            (void)printf("-");
          } 
          /*display permissions, num of links, owner & group name */
          displayPermissions(table[i].stbuf.st_mode);
          (void)printf(" %3lu ", table[i].stbuf.st_nlink);
          displayOwnerName(table[i].stbuf.st_uid);
          displayGroupName(table[i].stbuf.st_gid);
          /*if entry is character or block device, display major and minor
           * num, else print size
           */
          if(S_ISBLK(table[i].stbuf.st_mode) || S_ISCHR(table[i].stbuf.st_mode))
          {
            (void)printf("%3lu,", major(table[i].stbuf.st_rdev));
            (void)printf("%3lu", minor(table[i].stbuf.st_rdev));
          }
          else{
            (void)printf("%7ld ", table[i].stbuf.st_size);
          }
          /*display the time*/
          time = ctime(&(table[i].stbuf.st_mtime));
          (void)gettimeofday(&timeval, NULL);         
          timeDiff = timeval.tv_sec - table[i].stbuf.st_mtime;

          /*if mod time was < 6 months, disp month day hour:min */
          if(timeDiff < month){
            /*get month value*/
            monthPtr = strchr(time, ' ');
            nulPtr = monthPtr;  
            *nulPtr = '\0';
            monthPtr++;
      
            /*get day value*/
            dayPtr = strchr(monthPtr, ' ');
            nulPtr = dayPtr;
            *nulPtr = '\0';
            dayPtr++;

            /*get hour value*/
            hourPtr = strchr(dayPtr, ' ');
            nulPtr = hourPtr;
            *nulPtr = '\0';
            hourPtr++;

            /*get min value*/
            minPtr = strchr(hourPtr, ':');
            nulPtr = minPtr;
            *nulPtr = '\0';
            minPtr++;
  
            /*get sec value*/
            secPtr = strchr(minPtr, ':');
            nulPtr = secPtr;
            *nulPtr = '\0';
            secPtr++;

            /*get year value*/
            yearPtr = strchr(secPtr, ' ');
            nulPtr = yearPtr;
            *nulPtr = '\0';
            yearPtr++;

            (void)printf(" %s %s %s:%s ", monthPtr, dayPtr, hourPtr, minPtr);
          }
          else{
            timeStr = strchr(time, ':');
            timeStr-=2;
            (void)memmove(timeStr,strchr(timeStr, ' '), 5);
            timeStr+=5;
            *timeStr = '\0';
            strPtr = strchr(time, ' ');
            strPtr++;
            (void)printf("%s ", strPtr);
          }
          (void)printf("%s \n", table[i].name); 
      }
    }
  }
  /*display -a*/
  if(!(displayMode & LFLAG) && !(displayMode & TFLAG) && 
    !(displayMode & RFLAG) && displayMode & AFLAG){
    /*sort descending name*/
    if(displayMode & RFLAG){
      (void)qsort(table, entries, sizeof(struct fileInfo),
        nameSortDescending);
    }
    /*sort ascending name*/
    else{
      (void)qsort(table, entries, sizeof(struct fileInfo),
        nameSortAscending);
    }
    for(i = 0; i < entries; i++){
      (void)printf("%s \n", table[i].name);
    }
  }

  /*display -r*/
  if(!(displayMode & LFLAG) && !(displayMode & TFLAG) && displayMode & RFLAG){
    /*sort descending*/
    (void)qsort(table, entries, sizeof(struct fileInfo),
      nameSortDescending);
    /*display -r -a */
    if(displayMode & AFLAG){
      for(i = 0; i < entries; i++){
        (void)printf("%s \n", table[i].name);
      }
    }
    /*display -r*/
    else{
     for(i = 0; i < entries; i++){
        if(basename(table[i].name)[0] != '.')
          (void)printf("%s \n", table[i].name);
     }
    }
  }

}
