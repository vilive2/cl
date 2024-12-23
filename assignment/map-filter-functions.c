/*---------------------------------------------------------------------------
 * MAPS
 */
void map1(void *input, void *output) { /* char to char */
    char in = * (char *) input;
    char *out = output;
    if (isdigit(in)) *out = 'A' + in - '0';
    else if (isalpha(in)) *out = '0' + in % 10;
    else *out = in;
    return;
}

void map2(void *input, void *output) { /* char * to int */
    char *out = * (char **) input;
    int sum = 0, *ptr = output;
    while (*out) sum += *out++;
    *ptr = sum;
    return;
}

void map3(void *input, void *output) { /* int to float */
    int in = * (int *) input;
    float f = in, *fp = output;
    *fp = sqrtf(f);
    return;
}

/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
 * FILTERS
 */
int filter1(void *input) { /* is odd */
    int in = * (int *) input;
    return in%2;
}

int filter2(void *input) { /* is vowel */
    char in = tolower(* (char *) input);
    return (in == 'a' || in == 'e' || in == 'i' || in == 'o' || in == 'u');
}

int filter3(void *input) {
    return 0;
}
/*---------------------------------------------------------------------------*/
