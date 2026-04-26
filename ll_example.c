#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

int main( void )
{
    LLPtr startPtr = NULL;
    unsigned int choice;
    int id;
    char name[50];

    instructions();
    printf( "%s", "? " );
    scanf( "%u", &choice );

    while ( choice != 3 ) {

        switch ( choice ) {

            case 1:
                printf( "%s", "Enter id: " );
                scanf( "%d", &id );
                printf( "%s", "Enter name: " );
                scanf( "%49s", name );
                insert( &startPtr, id, name );
                printList( startPtr );
                printListReverse( startPtr );
                break;

            case 2:
                if ( !isEmpty( startPtr ) ) {
                    printf( "%s", "Enter id to delete: " );
                    scanf( "%d", &id );

                    if ( deletes( &startPtr, id ) ) {
                        printf( "%d deleted.\n", id );
                        printList( startPtr );
                        printListReverse( startPtr );
                    }
                    else {
                        printf( "%d not found.\n\n", id );
                    }
                }
                else {
                    puts( "List is empty.\n" );
                }
                break;

            default:
                puts( "Invalid choice.\n" );
                instructions();
                break;

        } // end switch

        printf( "%s", "? " );
        scanf( "%u", &choice );

    } // end while

    // choice == 3: free all remaining nodes before exit
    if ( !isEmpty( startPtr ) ) {
        printf( "Freeing remaining nodes...\n" );
        printList( startPtr );
        freeAll( &startPtr );
        printf( "All nodes freed.\n" );
    }

    puts( "End of run." );
    return 0;
}