#include<stdlib.h>
#include<stdio.h>

int main() {
    // int arr[26];
    int *arr = (int *)malloc(26 * sizeof(int));
    
    int i = 0;
    while(i++ < 26)
		arr[i] = 0;

    // char c;
    // while((c = fgetc(stdin)) != EOF) {
    //     if(c >= 'a' && c <= 'z')
    //         arr[c - 'a']++;
    // }

    for(int i = 0 ; i <= 26 ; i++) printf("%d ", arr[i]);

    return 0;
}