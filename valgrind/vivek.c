/* C program to find the frequency of each English lowercase alphabet in the content of a file.
   The file input.txt is provided by the user. */

#include<stdlib.h>
#include<stdio.h>
#include <string.h>

int main(){

	FILE *fd;
	char c;
	int i = 0, ctr = 0;
	// int ctrl[26];
	int *ctrl = (int *)malloc(26*sizeof(int));
        char *dummy = (char *) malloc(100);
        
	while(i++ < 26)
		ctrl[i] = 0; // Stack smashing
	fd=fopen("input.txt", "r");
	fscanf(fd, "%c", &c);
	while((c = fgetc(fd)) != EOF){	
		if(c >= 'a' && c <= 'z')
			ctrl[c - 'a']++;
		if(c == 'e')
			ctr++;
	}

	fclose(fd);

	for(i = 0; i <= 26; i++) // Extra iteration due to wrong condition check
		printf("No. of '%c's in the file : %d\n ", (i+'a'), (ctrl[i]));
}
