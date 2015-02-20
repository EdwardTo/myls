/*
 * Filename: displayPermissions.c
 * Author: Edward To
 * Userid: cs30xer
 * Description: C program meant to display the permissions for the input file
 * Date: Dec 3, 2013
 * Sources of help: PA4 handout, discussion slides, piazza, google
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
 * Function name: displayPermissions()
 * Description: Displays the user, group, and other permissions to either read,
 *              write or execute the file
 * Parameters: mode - the bitmask of the permissions
 * Side effects:
 * Error conditions:
 * Return value: none
 */

void
displayPermissions(const mode_t mode){

//user permissions
  if(mode & S_IRUSR){         //read
    (void)printf("r");         
  }
  else{
    (void)printf("-");
  }

  if(mode & S_IWUSR){         //write
    (void)printf("w");
  }
  else{
    (void)printf("-");
  }

  if(mode & S_IXUSR){         //execute
    (void)printf("x");
  }
  else{
    (void)printf("-");
  }
//---------------------end user permissions-------


//group permissions
  if(mode & S_IRGRP){         //read
    (void)printf("r");
  }
  else{
    (void)printf("-");
  }

  if(mode & S_IWGRP){         //write
    (void)printf("w");
  }
  else{
    (void)printf("-");
  }

  if(mode & S_IXGRP){
    (void)printf("x");        //execute
  }
  else{
    (void)printf("-");
  }
//----------------end group permissions--------------

//other user permissions
  if(mode & S_IROTH){         //read
    (void)printf("r");
  }
  else{
    (void)printf("-");
  }
  
  if(mode & S_IWOTH){         //write
    (void)printf("w");
  }
  else{
    (void)printf("-");
  }

  if(mode & S_IXOTH){         //execute
    (void)printf("x");
  }
  else{
    (void)printf("-");
  }
//------------end other user permissions----------

}
