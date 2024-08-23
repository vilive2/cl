#include<stdio.h>
#include<string.h>

int main() {

    char text[] = "I dream a world where man "
                    "No other man will scorn, "
                "Where love will bless the earth "
                    "And peace its paths adorn "
                    "I dream a world where all "
                "Will know sweet freedom's way, "
              "Where greed no longer saps the soul "
                "Nor avarice blights our day. "
             "A world I dream where black or white, "
                "Whatever race you be, "
             "Will share the bounties of the earch "
                "And every man is free, "
            "Where wretchedness will hang its head "
                "And joy, like a pearl, "
            "Attends the needs of all mankind  "
                "Of such I dream, my world!";

    char pattern[] = "dream a world";

    int count = 0;

    int N = strlen(text);
    int M = strlen(pattern);

    for(int i = 0 ; i < N - M + 1 ; i++) {
        if(!strncasecmp(&text[i], pattern, M)) count++;
    }

    printf("pattern found %d times overlapping included\n", count);

    return 0;
}