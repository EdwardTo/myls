/*
 *
 */

#include "myls.h"
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

/*
 *
 */

void
displayOwnerName(const uid_t uid)
{

  struct passwd * pwd; //passwd struct to store uid info for getpwuid

  pwd = getpwuid(uid); //set 
  if(pwd == NULL){
      (void)printf("%-8u ", uid);
  }
  else{
      (void)printf("%-8s ", pwd->pw_name);
  }

}


