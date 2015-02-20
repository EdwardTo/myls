    .global mtimeSortDescending

    .section ".text"

mtimeSortDescending:

     set OFFSET, %o2
     ld  [%o2], %o2

     add %o2, %o0, %o0
     add %o2, %o1, %o1

     ld [%o0], %o0
     ld [%o1], %o1

     sub %o0, %o1, %o0

     retl
     nop
