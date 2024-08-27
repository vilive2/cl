#define Malloc(n, type) (type *) malloc( (unsigned) (n * sizeof(type)))
#define Realloc(loc, n, type) (type *) realloc( (char *)(loc), \
                                    (unsigned) (n*sizeof(type)))