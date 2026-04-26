// self-referential structure
struct Node {
    int id;
    char name[50];
    struct Node *nextPtr;
    struct Node *prevPtr; // NEW: previous pointer for doubly linked list
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// prototypes
int deletes( LLPtr *sPtr, int id );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int id, const char *name );
void printList( LLPtr currentPtr );
void printListReverse( LLPtr currentPtr );
void freeAll( LLPtr *sPtr );
void instructions( void );

// display program instructions to user
void instructions( void )
{
    puts( "Enter your choice:\n"
          "   1 to insert an element into the list.\n"
          "   2 to delete an element from the list.\n"
          "   3 to end." );
}

// insert a new node in sorted order by id
void insert( LLPtr *sPtr, int id, const char *name )
{
    LLPtr newPtr;
    LLPtr previousPtr;
    LLPtr currentPtr;

    newPtr = (LLPtr) malloc( sizeof( LLnode ) );

    if ( newPtr != NULL ) {
        newPtr->id = id;
        strncpy(newPtr->name, name, 49);
        newPtr->name[49] = '\0';
        newPtr->nextPtr = NULL;
        newPtr->prevPtr = NULL;

        previousPtr = NULL;
        currentPtr  = *sPtr;

        // walk to find correct sorted position by id
        while ( currentPtr != NULL && id > currentPtr->id ) {
            previousPtr = currentPtr;
            currentPtr  = currentPtr->nextPtr;
        }

        // insert at beginning
        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            if ( *sPtr != NULL ) {
                (*sPtr)->prevPtr = newPtr; // back-link
            }
            *sPtr = newPtr;
        }
        else {
            // insert between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->prevPtr      = previousPtr; // back-link to previous
            newPtr->nextPtr      = currentPtr;
            if ( currentPtr != NULL ) {
                currentPtr->prevPtr = newPtr;   // back-link from next node
            }
        }
    }
    else {
        printf( "%d not inserted. No memory available.\n", id );
    }
}

// delete a list element by id
int deletes( LLPtr *sPtr, int id )
{
    LLPtr currentPtr;
    LLPtr tempPtr;

    // delete first node
    if ( id == ( *sPtr )->id ) {
        tempPtr = *sPtr;
        *sPtr   = ( *sPtr )->nextPtr;
        if ( *sPtr != NULL ) {
            (*sPtr)->prevPtr = NULL; // new head has no previous
        }
        free( tempPtr );
        return id;
    }
    else {
        currentPtr = ( *sPtr )->nextPtr;

        // loop to find the correct node
        while ( currentPtr != NULL && currentPtr->id != id ) {
            currentPtr = currentPtr->nextPtr;
        }

        if ( currentPtr != NULL ) {
            tempPtr = currentPtr;
            // re-link previous node forward
            currentPtr->prevPtr->nextPtr = currentPtr->nextPtr;
            // re-link next node backward (if it exists)
            if ( currentPtr->nextPtr != NULL ) {
                currentPtr->nextPtr->prevPtr = currentPtr->prevPtr;
            }
            free( tempPtr );
            return id;
        }
    }

    return 0; // id not found
}

// return 1 if list is empty
int isEmpty( LLPtr sPtr )
{
    return sPtr == NULL;
}

// print the list forward
void printList( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty.\n" );
    }
    else {
        puts( "Forward: " );
        while ( currentPtr->nextPtr != NULL ) {
            printf( "%d:%s --> ", currentPtr->id, currentPtr->name );
            currentPtr = currentPtr->nextPtr;
        }
        printf( "%d:%s --> NULL\n", currentPtr->id, currentPtr->name );
    }
}

// print the list in reverse using prevPtr
void printListReverse( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) {
        return;
    }
    // walk to the tail first
    LLPtr tail = currentPtr;
    while ( tail->nextPtr != NULL ) {
        tail = tail->nextPtr;
    }
    // now walk backwards
    puts( "Backward:" );
    LLPtr cur = tail;
    while ( cur->prevPtr != NULL ) {
        printf( "%d:%s --> ", cur->id, cur->name );
        cur = cur->prevPtr;
    }
    printf( "%d:%s --> NULL\n", cur->id, cur->name );
}

// free all remaining nodes
void freeAll( LLPtr *sPtr )
{
    LLPtr cur = *sPtr;
    while ( cur != NULL ) {
        LLPtr temp = cur;
        cur = cur->nextPtr;
        free( temp );
    }
    *sPtr = NULL;
}