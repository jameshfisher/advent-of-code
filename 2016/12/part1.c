#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "deps/vec/vec.c"

enum instr_ty { CPY, CPY_LIT, INC, DEC, JNZ, NOP, JMP };
typedef enum instr_ty instr_ty;

struct instr
{
  instr_ty type;
  int arg1;
  int arg2; // Some instrs don't use this
};
typedef struct instr instr;

typedef vec_t(instr) instr_vec_t;

instr_vec_t program;
int pc = 0;  // start at first instr
int reg[4] = { 0, 0, 0, 0 };  // registers a, b, c, d

int parse_reg_name(char reg_name)
{
  printf("Parsing reg name: %c\n", reg_name);
  int ret = reg_name - 'a';
  assert (0 <= ret && ret < 4);
  return ret;
}

void read_prog_from_stdin(void)
{
  char * line_buf = NULL;
  size_t buf_len = 0;
  while (1)
  {
    size_t bytes_read = getline(&line_buf, &buf_len, stdin);

    printf("Parsing line: %s\n", line_buf);

    char reg1;
    char reg2;
    int lit1;
    int lit2;

    instr i;
    if (sscanf(line_buf, "cpy %d %c\n", &lit1, &reg2) == 2)
    {
      i.type = CPY_LIT;
      i.arg1 = lit1;
      i.arg2 = parse_reg_name(reg2);
    }
    else if (sscanf(line_buf, "cpy %c %c\n", &reg1, &reg2) == 2)
    {
      i.type = CPY;
      i.arg1 = parse_reg_name(reg1);
      i.arg2 = parse_reg_name(reg2);
    }
    else if (sscanf(line_buf, "inc %c\n", &reg1) == 1)
    {
      i.type = INC;
      i.arg1 = parse_reg_name(reg1);
    }
    else if (sscanf(line_buf, "dec %c\n", &reg1) == 1)
    {
      i.type = DEC;
      i.arg1 = parse_reg_name(reg1);
    }
    else if (sscanf(line_buf, "jnz %d %d\n", &lit1, &lit2) == 2)
    {
      if (lit1 == 0)
      {
        i.type = NOP;
      }
      else
      {
        i.type = JMP;
        i.arg1 = lit2;
      }
    }
    else if (sscanf(line_buf, "jnz %c %d\n", &reg1, &lit2) == 2)
    {
      i.type = JNZ;
      i.arg1 = parse_reg_name(reg1);
      i.arg2 = lit2;
    }
    else
    {
      printf("Could not parse instruction: %s\n", line_buf);
      break;
    }

    vec_push(&program, i);
  }
  free(line_buf);
}

void print_instr(instr i)
{
  switch (i.type)
  {
    case CPY:
      printf("cpy %d %d", i.arg1, i.arg2);
      break;

    case CPY_LIT:
      printf("cpy_lit %d %d", i.arg1, i.arg2);
      break;

    case INC:
      printf("inc %d", i.arg1);
      break;

    case DEC:
      printf("dec %d", i.arg1);
      break;

    case JNZ:
      printf("jnz %d %d", i.arg1, i.arg2);
      break;

    case JMP:
      printf("jmp %d", i.arg1);
      break;

    case NOP:
      printf("nop");
      break;
  }
  printf("\n");
}

void print_prog(void)
{
  printf("Parsed program:\n");

  for (int i = 0; i < program.length; i++)
  {
    print_instr(program.data[i]);
  }
}

void run_prog(void)
{
  printf("State: [pc=%d] [a=%d b=%d c=%d d=%d]\n", pc, reg[0], reg[1], reg[2], reg[3]);

  while (pc < program.length)
  {
    instr current_instr = program.data[pc];

    printf("Executing instruction: ");
    print_instr(current_instr);

    switch (current_instr.type)
    {
      case CPY:
        reg[current_instr.arg2] = reg[current_instr.arg1];
        pc++;
        break;

      case CPY_LIT:
        reg[current_instr.arg2] = current_instr.arg1;
        pc++;
        break;

      case INC:
        reg[current_instr.arg1]++;
        pc++;
        break;

      case DEC:
        reg[current_instr.arg1]--;
        pc++;
        break;

      case JNZ:
        if (reg[current_instr.arg1] == 0)
        {
          pc++;
        }
        else
        {
          pc += current_instr.arg2;
        }
        break;

      case JMP:
        pc += current_instr.arg1;
        break;

      case NOP:
        pc++;
        break;
    }

    printf("State: [pc=%d] [a=%d b=%d c=%d d=%d]\n", pc, reg[0], reg[1], reg[2], reg[3]);
  }
}


int main(void)
{
  vec_init(&program);

  read_prog_from_stdin();
  print_prog();
  run_prog();

  printf("Value in register a: %d\n", reg[0]);

  return EXIT_SUCCESS;
}
