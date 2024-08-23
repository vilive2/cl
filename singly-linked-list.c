#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef char AirportCode[4];

typedef struct NodeTag {
    AirportCode Airport;
    struct NodeTag *Link;
} NodeType;

typedef NodeType *NodePointer;

NodePointer ListSearch(char *A, NodePointer L) {

    NodePointer N; /* N points to successive nodes on the list L */
    
    /* Initialization */
    N = L; /* let N start by pointing to the first node of the list L */

    /* While N points to a non-null node on list L */
    /* examine the node to which N points */

    while (N != NULL) {

        if (strcmp(N->Airport, A)==0) { /* if N's Airport == A */

            return N; /* return the node pointer in N */
        } else { /* otherwise */

            N = N->Link; /* advance N to the next node on the list */

        }

    }

    return N; /* return NULL if no node's Airport == A */

}

void PrintList(NodePointer L) {

    NodePointer N;                          /* N points to successive nodes on list L */

    /* First, print a left parenthesis */
    printf("(");

    /* Let N start by pointing to the first node on the list L */
    N = L;

    /* Provided N doesn't point to an empty node, print N's Airport */
    /* and advance N to point to the next node on the list */

    while (N != NULL) {
        printf("%s", N->Airport);       /* print airport code */
        N = N->Link;                    /* make N point to next node on list */
        if (N != NULL) printf(", ");    /* print comma between items */
    }

    /* Finally, print a closing right parenthesis */
    printf(")\n");

}

void InsertNewLastNode(char *A, NodePointer *L) { /* Again, expect **L */
                                                /* to be the address of */
                                                /* a variable L containing a */
                                                /* pointer to the first node of the list */
    NodePointer N, P;

    /* Allocate a new node N with Airport == A and Link == NULL */
    N = (NodePointer) malloc(sizeof(NodeType));
    strcpy(N->Airport, A);
    N->Link = NULL;

    if (*L == NULL) {               /* If list *L is empty */

        *L = N;                     /* let N become the new value for *L */
    
    }   else {                      /* Otherwise, */

        /* Locate the last node of list L, using pointer variable P */
        P = *L;
        while(P->Link != NULL) P = P->Link;

        /* Finally, link node N onto the end of the list */
        P->Link = N;
    }

}

void InsertBeforeNodeN(NodePointer N, NodePointer M) { /* expect N and M are not null */
                                                        /* N is a Node in a List L */
                                                        /* M is a new Node to be inserted */
                                                        /* so that M->Link == N */

    /* Insert M after N */
    M->Link = N->Link;                              /* Make M->Link point to N->Link */
    N->Link = M;                                    /* Make N->Link point to M */
    
    /* Swap(N->Airport, M->Airport) */
    char tmp[4];
    strcpy(tmp, N->Airport);
    strcpy(N->Airport, M->Airport);
    strcpy(M->Airport, tmp);
}

void DeleteLastNode(NodePointer *L) {           /* Note: **L is the address of the */
                                                /* variable L, whose value points */
                                                /* to the fist node of list L */

    NodePointer PreviousNode, CurrentNode;
    if (*L != NULL) {                           /* do nothing if *L was the empty list */

        if ((*L)->Link == NULL) {               /* if *L has exactly one node, then */
    
            free(*L);                           /* free the node's storage, */
            *L = NULL;                          /* set L to be the empty list, and terminate */

        } else {                                /* otherwise, L must have two or more nodes */

            /* Initialize a pair of pointers, (PreviousNode, CurrentNode) ) */
            /* to point to the first and second nodes. */

            PreviousNode = *L;
            CurrentNode = (*L)->Link;

            /* Advance the pointer pair along L until CurrentNode */
            /* points to the last node */

            while(CurrentNode->Link != NULL) {
                PreviousNode = CurrentNode;
                CurrentNode = CurrentNode->Link;
            }

            /* Now PreviousNode points to the next-to-last node on the list */
            /* and CurrentNode points to the last node on the list. */

            PreviousNode->Link = NULL;          /* last node gets NULL link */
            free(CurrentNode);                  /* recycle storage for discarded node */

        }

    }

}

NodePointer Copy(NodePointer L) { /* Expect Pointer to list L to be copied */
                                    /* Creates new copy of L and return first node of new list */

    NodePointer CL, P ;             /* CL be copy list */
                                    /* P be prev node added in CL */
                            
    if (L != NULL) {              /* If L is not empty */

        /* Initialize CL with new storage and Copy Airport of L */
        CL = (NodePointer) malloc(sizeof(NodeType));
        strcpy(CL->Airport, L->Airport);
        CL->Link = NULL;
        
        L = L->Link;            /* Advance L */

        P = CL;                 /* Initialize P with CL */
        
        while (L != NULL) {     /* Until L is not NULL */

            /* Add New node in CL at P->Link with same Airport as L */
            P->Link = (NodePointer) malloc(sizeof(NodeType));
            strcpy(P->Link->Airport, L->Airport);
            P->Link->Link = NULL;

            /* Advance L and P */
            L = L->Link;
            P = P->Link;
        }

    }

    return CL;      /* return CL */
}

void Reverse(NodePointer *L) { /* expect **L is the address of the */
                                /* variable L whose value points to */
                                /* first node in List L */

    /* RL reverse list of L*/
    /* P node in L accessing sequentially one by one */
    /* NP next node in L coming to be accessed */
    NodePointer RL, P, NP;

    if ( *L != NULL ) {     /* If L is not empty */

        /* Initialize P by value of L */
        P = *L;
        RL = NULL;

        while( P != NULL ) {    /* Until P is not NULL */

            NP = P->Link;       /* Keep next node in NP */

            /* Add P as new first node in RL */
            P->Link = RL;
            RL = P;

            P = NP;         /* Make P point to NP */
        }

        /* Overide value of L with RL */
        *L = RL;
    }

}

int main() {

    NodePointer L;
    
    /* First, construct the list L == (DUS, ORD, SAN) and print it */

    /* To start things off, let L be the empty list */
    L = NULL;

    /* Insert a new last node in L with airport code "DUS" */
    InsertNewLastNode("DUS", &L);

    /* Insert a new last node in L with airport code "ORD" */
    InsertNewLastNode("ORD", &L);

    /* Insert a new last node in L with airport code "SAN" */
    InsertNewLastNode("SAN", &L);

    /* Now, print the list, to show what it looks like before changing it */
    PrintList(L);

    /* Then, insert a new last node with the airport code "BRU" */
    InsertNewLastNode("BRU", &L);

    /* Print the modified list */
    PrintList(L);

    /* Delete the last node of the list */
    DeleteLastNode(&L);

    /* Finally, print the shortened list */
    PrintList(L);

    /* Insert CCU before ORD */
    NodePointer ord = ListSearch("ORD", L);
    if(ord != NULL) {
        NodePointer ccu = (NodePointer) malloc(sizeof(NodeType));
        strcpy(ccu->Airport, "CCU");
        ccu->Link = NULL;
        InsertBeforeNodeN(ord, ccu);

        PrintList(L);
    } else {
        printf("ORD not found\n");
    }

    /* Copy L into CL */
    NodePointer CL = Copy(L);

    /* Print CL */
    printf("copy of L as CL : ");
    PrintList(CL);

    /* Reverse L */
    printf("L : ");
    PrintList(L);
    Reverse(&L);
    printf("Reversed L : ");
    PrintList(L);

    return 0;
}