#ifndef VM_PARSE_H
#define VM_PARSE_H

int is_whitespace(char);
int parse_label(char[], char[]);
int parse_skip(char[]);
int parse_lit(char[], char[]);
int parse_int_arg(char[], char[], int *);
int parse_reg_arg(char[], char[], char[]);
int parse_label_arg(char[], char[], char[]);
int parse_single(char[]);
int parse_double(char[]);

#endif
