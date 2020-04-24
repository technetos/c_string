#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct String {
  // len includes the '\0' terminator
  size_t len;
  char * data;
};

struct String new_string() {
  struct String s;
  s.len = 0;
  s.data = NULL;
  return s;
}

void fill_string(struct String * s, char * data) {
  // strlen returns the length of the string - \n
  size_t len = strlen(data) + 1;
  char * str = malloc(len);
  memset(str, '\0', len);
  memcpy(str, data, len - 1);
  s->len = len;
  s->data = str;
}

// allocate an array of characters on the heap and return a string
struct String string_from(char * data) {
  struct String s = new_string();
  fill_string(&s, data);
  return s;
}

// set the letters in the string to uppercase
void uppercase(struct String * s) {
  int i;
  for(i = 0; i < s->len; i++) {
    char tmp = s->data[i];
    s->data[i] = toupper(tmp);
  }
}

// set the letters in the string to lowercase
void lowercase(struct String * s) {
  int i;
  for(i = 0; i < s->len; i++) {
    char tmp = s->data[i];
    s->data[i] = tolower(tmp);
  }
}

// Returns 1 or 0 representing true or false, c has no real bool
int starts_with(struct String * s, char * data) {
  size_t len = strlen(data);
  if(strncmp(s->data, data, len) == 0) {
    return 1;
  } else {
    return 0;
  }
}

// Returns 1 or 0 representing true or false, c has no real bool
int ends_with(struct String * s, char * data) {
  size_t len = strlen(data);
  if(len > s->len) {
    return 0;
  }
  if(strncmp(s->data + (s->len-1) - len, data, len) == 0) {
    return 1;
  } else {
    return 0;
  }
}

// Returns 1 or 0 representing true or false, c has no real bool
int contains(struct String * s, char * data) {
  if(strstr(s->data, data) != NULL) {
    return 1;
  } else {
    return 0;
  }
}

// Append a char * array to the end of the string
void append(struct String * s, char * data) {
  size_t data_len = strlen(data);
  // new_len includes the '\0' terminator
  size_t new_len = data_len + s->len;

  char * old_str = s->data;
  char * new_str = malloc(new_len);
  memset(new_str, '\0', new_len);

  memcpy(new_str, s->data, s->len - 1);
  strncat(new_str, data, data_len);


  s->data = new_str;
  s->len = new_len;

  free(old_str);
}

// Prepend a char * array to the beginning of the string
void prepend(struct String * s, char * data) {
  size_t data_len = strlen(data);
  // new_len includes the '\0' terminator
  size_t new_len = data_len + s->len;

  char * old_str = s->data;
  char * new_str = malloc(new_len);
  memset(new_str, '\0', new_len);

  memcpy(new_str, data, data_len);
  strncat(new_str, s->data, s->len - 1);

  s->data = new_str;
  s->len = new_len;
  
  free(old_str);
}

int main(int argc, char *argv[]) {
  int count = argc - 1;
  struct String *args = malloc(sizeof(struct String) * count);

  int i;
  for(i = 0; i < count; i++) {
    args[i] = string_from(argv[i + 1]);
    printf("%s with length %zu\n", args[i].data, args[i].len);
  }

  uppercase(&args[0]);

  printf("%s\n", args[0].data);

  lowercase(&args[0]);

  printf("%s\n", args[0].data);

  if(starts_with(&args[0], "--")) {
    printf("yes\n");
  }

  if(ends_with(&args[0], "gg")) {
    printf("yes\n");
  }

  if(contains(&args[0], "g")) {
    printf("yes\n");
  }

  append(&args[0], " all this text has been appended to the end of the string");

  printf("%s\n", args[0].data);

  prepend(&args[0], "all this text has been prepended to the beginning of the string ");

  printf("%s\n", args[0].data);

  for(i = 0; i < count; i++) {
    free(args[i].data);
  }

  free(args);

  return 0;
}
