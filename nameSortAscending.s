/*
 *
 */

    .global nameSortAscending

    .section ".text"

nameSortAscending:

    save %sp, -96, %sp

    mov %i0, %o0
    mov %i1, %o1

    call strcmp
    nop

    mov %o0, %i0

    ret
    restore
