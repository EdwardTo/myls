/*
 *
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 *
 */

int 
mtimeSortAscending(const void *p1, const void *p2)
{

  struct fileInfo* name1 = (struct fileInfo *) p1;
  struct fileInfo* name2 = (struct fileInfo *) p2;

  struct stat stat1 = name1->stbuf;
  struct stat stat2 = name2->stbuf;
 
  time_t time1 = stat1.st_mtime;
  time_t time2 = stat2.st_mtime;

  int num = time2-time1;

  return num;
    
}
