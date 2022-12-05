#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_CHARS_TO_READ 50
#define BASE_10 10
#define DIFFERENCE_BETWEEN_ASCII_A_AND_X 23
#define POINTS_FOR_ROCK 1
#define POINTS_FOR_PAPER 2
#define POINTS_FOR_SCISSORS 3
#define POINTS_FOR_WINNING_RPS 6
#define POINTS_FOR_DRAWING_RPS 3

uint32_t solution_day_2_p2(const char *filename);
uint32_t solution_day_2(const char *filename);
uint32_t solution_day_1_p2(const char *filename);
uint32_t solution_day_1(const char *filename);

int main() {
  printf("Day 1 problem 1 solution: %lu \n", (unsigned long)solution_day_1("inputs/day1input.txt"));
  printf("Day 1 problem 2 solution: %lu \n", (unsigned long)solution_day_1_p2("inputs/day1input.txt"));
  printf("Day 2 problem 1 solution: %lu \n", (unsigned long)solution_day_2("inputs/day2input.txt"));
  printf("Day 2 problem 2 solution: %lu \n", (unsigned long)solution_day_2_p2("inputs/day2input.txt"));

  return 0;
}

uint32_t solution_day_2_p2(const char *filename) {
  FILE *input = fopen(filename, "r");
  if (!input) {
    return -1;
  }
  char opponent_choice = 0;
  char my_choice = 0;
  uint32_t my_score = 0;
  uint32_t old_score = 0;
  int counter = 0;
  while (EOF != fscanf(input, " %c %c\n", &opponent_choice, &my_choice)) {
    switch (opponent_choice) {
      case 'A':
        if (my_choice == 'X') {
          my_score = my_score + POINTS_FOR_SCISSORS;
        } else if (my_choice == 'Y') {
          my_score = my_score + POINTS_FOR_ROCK + POINTS_FOR_DRAWING_RPS;
        } else {
          my_score = my_score + POINTS_FOR_PAPER + POINTS_FOR_WINNING_RPS;
        }
        break;
      case 'B':
        if (my_choice == 'X') {
          my_score = my_score + POINTS_FOR_ROCK;
        } else if (my_choice == 'Y') {
          my_score = my_score + POINTS_FOR_PAPER + POINTS_FOR_DRAWING_RPS;
        } else {
          my_score = my_score + POINTS_FOR_SCISSORS + POINTS_FOR_WINNING_RPS;
        }
        break;
      case 'C':
        if (my_choice == 'X') {
          my_score = my_score + POINTS_FOR_PAPER;
        } else if (my_choice == 'Y') {
          my_score = my_score + POINTS_FOR_SCISSORS + POINTS_FOR_DRAWING_RPS;
        } else {
          my_score = my_score + POINTS_FOR_ROCK + POINTS_FOR_WINNING_RPS;
        }
        break;
      default:
        break;
    }
  }

  if (0 != fclose(input)) {
    return -1;
  }
  return my_score;
}
uint32_t solution_day_2(const char *filename) {
  FILE *input = fopen(filename, "r");
  if (!input) {
    return -1;
  }
  char opponent_choice = 0;
  char my_choice = 0;
  uint32_t my_score = 0;
  uint32_t old_score = 0;
  int counter = 0;
  while (EOF != fscanf(input, " %c %c\n", &opponent_choice, &my_choice)) {
    opponent_choice = opponent_choice + DIFFERENCE_BETWEEN_ASCII_A_AND_X;
    switch (my_choice) {
      case 'X':
        my_score += 1;
        if (opponent_choice == 'X') {
          my_score += 3;
        }
        if (opponent_choice == 'Z') {
          my_score += 6;
        }
        break;
      case 'Y':
        my_score += 2;
        if (opponent_choice == 'Y') {
          my_score += 3;
        }
        if (opponent_choice == 'X') {
          my_score += 6;
        }
        break;
      case 'Z':
        my_score += 3;
        if (opponent_choice == 'Z') {
          my_score += 3;
        }
        if (opponent_choice == 'Y') {
          my_score += 6;
        }
        break;
      default:
        break;
    }
  }

  if (0 != fclose(input)) {
    return -1;
  }
  return my_score;
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
