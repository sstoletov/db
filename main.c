#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *buffer;
  size_t buffer_length;
  size_t input_length;
} InputBuffer;

typedef enum {
  META_COMMAND_SUCCES,
  META_COMMAND_DENIED,
} META_COMMAND;

typedef enum {
  PREPARE_SUCCES,
  PREPARE_DENIED,
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT,
  STATEMENT_REMOVE,
} StatementType;

typedef struct {
  StatementType type;
} Statement;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strcmp(input_buffer->buffer, "INSERT") == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCES;
  }

  if (strcmp(input_buffer->buffer, "SELECT") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCES;
  }

  if (strcmp(input_buffer->buffer, "REMOVE") == 0) {
    statement->type = STATEMENT_REMOVE;
    return PREPARE_SUCCES;
  }

  return PREPARE_DENIED;
}

void print_promt() { printf("db:> "); }

void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("здесь будет вызов команды insert!\n");
      break;

    case (STATEMENT_REMOVE):
      printf("здесь будет вызов команды remove!\n");
      break;

    case (STATEMENT_SELECT):
      printf("здесь будет вызов команды select!\n");
      break;
  }
}

InputBuffer *new_input_buffer() {
  InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void read_input(InputBuffer *input_buffer) {
  ssize_t bytes =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes <= 0) {
    printf("...");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes - 1;
  input_buffer->buffer[input_buffer->input_length] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  input_buffer->input_length = 0;
  input_buffer->buffer_length = 0;
  free(input_buffer->buffer);

  free(input_buffer);
}

META_COMMAND do_meta(InputBuffer *input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    close_input_buffer(input_buffer);
    exit(EXIT_SUCCESS);
  } else return META_COMMAND_DENIED;
}

int main() {
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    print_promt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (do_meta(input_buffer)) {
      case (META_COMMAND_SUCCES):
        continue; // временно
      case (META_COMMAND_DENIED):
        printf("нераспознанная команда\n");
        continue;
      }
    }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCES):
        break;
      case (PREPARE_DENIED):
        printf("нераспознанная команда\n");
        continue;
    }

    execute_statement(&statement);
    printf("команда выполнена\n");
  }
}
