#include "test.h"
#include "myls.h"
#include <stdlib.h>
#include <limits.h>
#include "buildFileInfoTable.c"

void
testbuildFileInfoTable(){

   struct fileInfo* blah;
   printf("Testing buildFileInfoTable()\n");
    char *d;
  //  d = "/dev/fd";
   d = "/home/solaris/ieng9/cs30x/cs30xer/pa4";
 //  d = "myls.h";
   
   int test = buildFileInfoTable( d, &blah);

   printf("%d\n", test);


   printf("Finished running tests on buildFileInfotable()\n");

}

int
main(){

    testbuildFileInfoTable();

    return 0;
}
