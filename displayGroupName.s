/*
 * Author: Edward To
 * Userid: cs30xer
 * Description: SPARC assembly program used to display the group name of the
 *              input file
 * Date: Dec 3, 2013
 * Sources of help: pa4 handout, piazza, google, discussion slides
 */

/*
 * Function name: displayGroupName
 * Function prototype:displayGroupName( const gid_t gid )
 * Description: Displays the group name of the file using the gid. if there is
 *              no group name, print gid
 * Parameters: 
 *        gid - the gid to search for group name
 * Side effects:
 * Error conditions:
 * Return value: none
 * Registers used:
 *            %i0 - input register for gid
 *            
 *            %l0 - local register used to store output value of getgrgid
 *            
 *            %o0 - output register to store gid to call getgrgid and
 *                  format for print statement
 *            %o1 - output register to store gid or groupname to print
 *
 *            %g0 - global null value reg
 */

    .global displayGroupName

    .section ".data"

gid:                        !format for gid
    .asciz "%-8ld "

groupname:                  !format for groupname
    .asciz "%-8s "

    .section ".text"

displayGroupName:

    save  %sp, -96, %sp

    mov %i0, %o0            !move input param to output 
    call getgrgid           !call getgrgid
    nop

    mov %o0, %l0            !move return value of getgrgid to local reg
    
    cmp %l0, %g0            !comepare %l0 to null
    be  printGid            !if equal, print gid
    nop

    set groupname, %o0      !print groupname if not equal to null
    ld [%l0], %o1
    call printf, 2
    nop

    ret
    restore

printGid:
    
    set gid, %o0            !print gid 
    mov %i0, %o1
    call printf, 2
    nop

    ret
    restore
