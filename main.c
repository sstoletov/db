#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char* buffer;
  size_t buffer_length;
  size_t input_length;
} InputBuffer;

void print_promt() { printf("db:> "); }

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  
  if (bytes <= 0) {
    printf("...");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes - 1;
  input_buffer->buffer[input_buffer->input_length] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  input_buffer->input_length = 0;
  input_buffer->buffer_length = 0;
  free(input_buffer->buffer);

  free(input_buffer);
}

int main() {
  InputBuffer* input_buffer = new_input_buffer();

  while (1) {
    print_promt();
    read_input(input_buffer);
  
    if (strcmp(".exit", input_buffer->buffer) == 0) {
      close_input_buffer(input_buffer); 
      exit(EXIT_SUCCESS);
    } else {
      printf("soon\n");
    }
  }
}
