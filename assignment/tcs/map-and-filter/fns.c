#include<ctype.h>
#include<string.h>

void celsius_to_fahrenheit(void *input, void *output) {
    double temp_in_celsius = *(double *)input;
    double *temp_in_fahrenheit = output;
    *temp_in_fahrenheit = temp_in_celsius * 9 / 5 + 32;
}

void uppercase(void *input, void *output) {
    char *word = input;
    char *out = output;

    while(*word != '\0') {
        *out = toupper(*word);
        word++;
        out++;
    }
    *out = '\0';
}

typedef struct {
    char firstname[32];
    char lastname[32];
    int age;
} PERSON;

void person_name(void *input, void *output) {
    PERSON p = *(PERSON *)input;
    char *name = output;
    strcpy(name, p.firstname);
    strcat(name, " ");
    strcat(name, p.lastname);
}

char *pref = "Dear ";
void prepend_prefix(void *input, void *output) {
    char *word = input;
    char *out = output;
    strcpy(out, pref);
    strcat(out, word);
}

typedef struct {
    int date;
    int month;
    int year;
} DATE;

void parse_date(void *input, void *output) {
    DATE date = *(DATE *)input;
    char *out = output;
    sprintf(out, "%02d-%02d-%04d", date.date, date.month, date.year);
}

char domain[128] = "gmail.com";

int filter_email(void *input) {
    char *email = input;
    return strncmp(email + strlen(email) - strlen(domain), domain, strlen(domain)) == 0;
}

int senior_person(void *input) {
    PERSON p = *(PERSON *)input;
    return p.age > 60;
}

DATE start;
DATE end;

int is_after(DATE d1, DATE d2) {
    if(d1.year < d2.year) return 0;
    if(d1.year > d2.year) return 1;
    if(d1.month < d2.month) return 0;
    if(d1.month > d2.month) return 1;
    if(d1.date < d2.date) return 0;
    return 1;
}

int date_in_range(void *input) {
    DATE date = *(DATE *)input;
    return is_after(date, start) && is_after(end, date);
}