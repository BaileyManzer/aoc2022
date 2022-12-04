#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_CHARS_TO_READ 50
#define BASE_10 10

uint32_t solution_day_1_p2(const char *filename);
uint32_t solution_day_1(const char *filename);

int main() {
  printf("Day 1 solution: %lu \n", (unsigned long)solution_day_1("inputs/day1input.txt"));
  printf("Day 1 problem 2 solution: %lu \n", (unsigned long)solution_day_1_p2("inputs/day1input.txt"));

  return 0;
}

uint32_t solution_day_1_p2(const char *filename) {
  uint32_t most_calories_carried = 0;

  FILE *input = fopen(filename, "r");
  if (!input) {
    return -1;
  }

  uint32_t highest_elf_total = 0;
  uint32_t second_highest_elf_total = 0;
  uint32_t third_highest_elf_total = 0;
  uint32_t single_elf_total = 0;
  char input_value[MAX_CHARS_TO_READ] = {0};

  while(NULL != fgets(input_value, sizeof(input_value), input)) {
    char *tmp_ptr;
    uint32_t tmp = (uint32_t)strtoul(input_value, &tmp_ptr, BASE_10);
    if (0 != tmp) {
      single_elf_total += tmp;
    } else {
      if (single_elf_total >= highest_elf_total) {
        third_highest_elf_total = second_highest_elf_total;
        second_highest_elf_total = highest_elf_total;
        highest_elf_total = single_elf_total;
        single_elf_total = 0;
        continue;
      }
      if (single_elf_total >= second_highest_elf_total) {
        third_highest_elf_total = second_highest_elf_total;
        second_highest_elf_total = single_elf_total;
        single_elf_total = 0;
        continue;
      }
      if (single_elf_total > third_highest_elf_total) {
        third_highest_elf_total = single_elf_total;
        single_elf_total = 0;
        continue;
      }
      single_elf_total = 0;
    }
  }
  if (0 != fclose(input)) {
    return -1;
  }
  return highest_elf_total + second_highest_elf_total + third_highest_elf_total;
}

uint32_t solution_day_1(const char *filename) {
  uint32_t most_calories_carried = 0;
  
  FILE *input = fopen(filename, "r");
  if (!input) {
    return -1;
  }

  uint32_t highest_elf_total = 0;
  uint32_t single_elf_total = 0;
  char input_value[MAX_CHARS_TO_READ] = {0};

  while(NULL != fgets(input_value, sizeof(input_value), input)) {
    char *tmp_ptr;
    uint32_t tmp = (uint32_t)strtoul(input_value, &tmp_ptr, BASE_10);
    if (0 != tmp) {
      single_elf_total += tmp;
    } else {
      if (single_elf_total > highest_elf_total) {
        highest_elf_total = single_elf_total;
      }
      single_elf_total = 0;
    }
  }
  if (0 != fclose(input)) {
    return -1;
  }
  return highest_elf_total;
}
