/*
 *
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


/*
 *
 */

int
nameSortDescending( const void * p1, const void * p2)
{

  struct fileInfo* name1 = (struct fileInfo *) p1;
  struct fileInfo* name2 = (struct fileInfo *) p2;
  int num;

  /*returns 0 if equal, negative if name2 is bigger, positive if name1 is
   * bigger
   */
  num = strcmp(name2->name, name1->name);
  
  return num; 
  
}
