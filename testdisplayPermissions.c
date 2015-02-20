#include "test.h"
#include "myls.h"
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include "displayPermissions.c"

void
testdisplayPermissions(){

   struct fileInfo* blah;
   struct stat statStruct;
   printf("Testing displayPermissions()\n");
    char *d;
  //  d = "/dev/fd";
 //  d = "/home/solaris/ieng9/cs30x/cs30xer/pa4";
   d = "myls.h";
   
  lstat(d, &statStruct);

  blah = (struct fileInfo*) malloc(sizeof(struct fileInfo));

 blah->stbuf=statStruct;
   displayPermissions(blah->stbuf.st_mode);


   printf("Finished running tests on displayPermissions()\n");

}

int
main(){

    testdisplayPermissions();

    return 0;
}
