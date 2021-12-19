/** @file guess_the_number.c
 * Guesses the number you have guessed with the help of leading "yes/no" questions.
 * 
 * By default, it works in decimal notation. It is possible to work in the Roman numeral system.
 * 
 * - *r* - enable the Roman numeral system
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <argp.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

const char *argp_program_version =
  "guess_the_number 1.0";
const char *argp_program_bug_address =
  "<anya.antipina@gmail.com>";

/**
 * Used by main to communicate with parse_opt. 
 */
struct arguments
{
  int roman;              /**< Roman numeral system flag */
};

/**
 * Parse a single option key with option argument arg when staet is state.
 */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /** Get the input argument from argp_parse, which we 
   * know is a pointer to our arguments structure. 
   */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'r':
      arguments->roman = 1;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/**
 * Сonverts a number from decimal to Roman numeral system.
 * @param number a number in the decimal numeral system.
 * @return a number in the Roman numeral system represented as a string.
 */
char* get_roman_number(int number) {
    if (number == 1) return "I";
if (number == 2) return "II";
if (number == 3) return "III";
if (number == 4) return "IV";
if (number == 5) return "V";
if (number == 6) return "VI";
if (number == 7) return "VII";
if (number == 8) return "VIII";
if (number == 9) return "IX";
if (number == 10) return "X";
if (number == 11) return "XI";
if (number == 12) return "XII";
if (number == 13) return "XIII";
if (number == 14) return "XIV";
if (number == 15) return "XV";
if (number == 16) return "XVI";
if (number == 17) return "XVII";
if (number == 18) return "XVIII";
if (number == 19) return "XIX";
if (number == 20) return "XX";
if (number == 21) return "XXI";
if (number == 22) return "XXII";
if (number == 23) return "XXIII";
if (number == 24) return "XXIV";
if (number == 25) return "XXV";
if (number == 26) return "XXVI";
if (number == 27) return "XXVII";
if (number == 28) return "XXVIII";
if (number == 29) return "XXIX";
if (number == 30) return "XXX";
if (number == 31) return "XXXI";
if (number == 32) return "XXXII";
if (number == 33) return "XXXIII";
if (number == 34) return "XXXIV";
if (number == 35) return "XXXV";
if (number == 36) return "XXXVI";
if (number == 37) return "XXXVII";
if (number == 38) return "XXXVIII";
if (number == 39) return "XXXIX";
if (number == 40) return "XL";
if (number == 41) return "XLI";
if (number == 42) return "XLII";
if (number == 43) return "XLIII";
if (number == 44) return "XLIV";
if (number == 45) return "XLV";
if (number == 46) return "XLVI";
if (number == 47) return "XLVII";
if (number == 48) return "XLVIII";
if (number == 49) return "XLIX";
if (number == 50) return "L";
if (number == 51) return "LI";
if (number == 52) return "LII";
if (number == 53) return "LIII";
if (number == 54) return "LIV";
if (number == 55) return "LV";
if (number == 56) return "LVI";
if (number == 57) return "LVII";
if (number == 58) return "LVIII";
if (number == 59) return "LIX";
if (number == 60) return "LX";
if (number == 61) return "LXI";
if (number == 62) return "LXII";
if (number == 63) return "LXIII";
if (number == 64) return "LXIV";
if (number == 65) return "LXV";
if (number == 66) return "LXVI";
if (number == 67) return "LXVII";
if (number == 68) return "LXVIII";
if (number == 69) return "LXIX";
if (number == 70) return "LXX";
if (number == 71) return "LXXI";
if (number == 72) return "LXXII";
if (number == 73) return "LXXIII";
if (number == 74) return "LXXIV";
if (number == 75) return "LXXV";
if (number == 76) return "LXXVI";
if (number == 77) return "LXXVII";
if (number == 78) return "LXXVIII";
if (number == 79) return "LXXIX";
if (number == 80) return "LXXX";
if (number == 81) return "LXXXI";
if (number == 82) return "LXXXII";
if (number == 83) return "LXXXIII";
if (number == 84) return "LXXXIV";
if (number == 85) return "LXXXV";
if (number == 86) return "LXXXVI";
if (number == 87) return "LXXXVII";
if (number == 88) return "LXXXVIII";
if (number == 89) return "LXXXIX";
if (number == 90) return "XC";
if (number == 91) return "XCI";
if (number == 92) return "XCII";
if (number == 93) return "XCIII";
if (number == 94) return "XCIV";
if (number == 95) return "XCV";
if (number == 96) return "XCVI";
if (number == 97) return "XCVII";
if (number == 98) return "XCVIII";
if (number == 99) return "XCIX";
if (number == 100) return "C";
}

/**
 * Сonverts a number from Roman to decimal numeral system.
 * @param roman_number a number in the Roman numeral system represented as a string.
 * @return a number in the decimal numeral system represented as a string.
 */
char* get_decimal_number(char* roman_number) {
   if (!strcmp(roman_number, "I")) return "1";
if (!strcmp(roman_number, "II")) return "2";
if (!strcmp(roman_number, "III")) return "3";
if (!strcmp(roman_number, "IV")) return "4";
if (!strcmp(roman_number, "V")) return "5";
if (!strcmp(roman_number, "VI")) return "6";
if (!strcmp(roman_number, "VII")) return "7";
if (!strcmp(roman_number, "VIII")) return "8";
if (!strcmp(roman_number, "IX")) return "9";
if (!strcmp(roman_number, "X")) return "10";
if (!strcmp(roman_number, "XI")) return "11";
if (!strcmp(roman_number, "XII")) return "12";
if (!strcmp(roman_number, "XIII")) return "13";
if (!strcmp(roman_number, "XIV")) return "14";
if (!strcmp(roman_number, "XV")) return "15";
if (!strcmp(roman_number, "XVI")) return "16";
if (!strcmp(roman_number, "XVII")) return "17";
if (!strcmp(roman_number, "XVIII")) return "18";
if (!strcmp(roman_number, "XIX")) return "19";
if (!strcmp(roman_number, "XX")) return "20";
if (!strcmp(roman_number, "XXI")) return "21";
if (!strcmp(roman_number, "XXII")) return "22";
if (!strcmp(roman_number, "XXIII")) return "23";
if (!strcmp(roman_number, "XXIV")) return "24";
if (!strcmp(roman_number, "XXV")) return "25";
if (!strcmp(roman_number, "XXVI")) return "26";
if (!strcmp(roman_number, "XXVII")) return "27";
if (!strcmp(roman_number, "XXVIII")) return "28";
if (!strcmp(roman_number, "XXIX")) return "29";
if (!strcmp(roman_number, "XXX")) return "30";
if (!strcmp(roman_number, "XXXI")) return "31";
if (!strcmp(roman_number, "XXXII")) return "32";
if (!strcmp(roman_number, "XXXIII")) return "33";
if (!strcmp(roman_number, "XXXIV")) return "34";
if (!strcmp(roman_number, "XXXV")) return "35";
if (!strcmp(roman_number, "XXXVI")) return "36";
if (!strcmp(roman_number, "XXXVII")) return "37";
if (!strcmp(roman_number, "XXXVIII")) return "38";
if (!strcmp(roman_number, "XXXIX")) return "39";
if (!strcmp(roman_number, "XL")) return "40";
if (!strcmp(roman_number, "XLI")) return "41";
if (!strcmp(roman_number, "XLII")) return "42";
if (!strcmp(roman_number, "XLIII")) return "43";
if (!strcmp(roman_number, "XLIV")) return "44";
if (!strcmp(roman_number, "XLV")) return "45";
if (!strcmp(roman_number, "XLVI")) return "46";
if (!strcmp(roman_number, "XLVII")) return "47";
if (!strcmp(roman_number, "XLVIII")) return "48";
if (!strcmp(roman_number, "XLIX")) return "49";
if (!strcmp(roman_number, "L")) return "50";
if (!strcmp(roman_number, "LI")) return "51";
if (!strcmp(roman_number, "LII")) return "52";
if (!strcmp(roman_number, "LIII")) return "53";
if (!strcmp(roman_number, "LIV")) return "54";
if (!strcmp(roman_number, "LV")) return "55";
if (!strcmp(roman_number, "LVI")) return "56";
if (!strcmp(roman_number, "LVII")) return "57";
if (!strcmp(roman_number, "LVIII")) return "58";
if (!strcmp(roman_number, "LIX")) return "59";
if (!strcmp(roman_number, "LX")) return "60";
if (!strcmp(roman_number, "LXI")) return "61";
if (!strcmp(roman_number, "LXII")) return "62";
if (!strcmp(roman_number, "LXIII")) return "63";
if (!strcmp(roman_number, "LXIV")) return "64";
if (!strcmp(roman_number, "LXV")) return "65";
if (!strcmp(roman_number, "LXVI")) return "66";
if (!strcmp(roman_number, "LXVII")) return "67";
if (!strcmp(roman_number, "LXVIII")) return "68";
if (!strcmp(roman_number, "LXIX")) return "69";
if (!strcmp(roman_number, "LXX")) return "70";
if (!strcmp(roman_number, "LXXI")) return "71";
if (!strcmp(roman_number, "LXXII")) return "72";
if (!strcmp(roman_number, "LXXIII")) return "73";
if (!strcmp(roman_number, "LXXIV")) return "74";
if (!strcmp(roman_number, "LXXV")) return "75";
if (!strcmp(roman_number, "LXXVI")) return "76";
if (!strcmp(roman_number, "LXXVII")) return "77";
if (!strcmp(roman_number, "LXXVIII")) return "78";
if (!strcmp(roman_number, "LXXIX")) return "79";
if (!strcmp(roman_number, "LXXX")) return "80";
if (!strcmp(roman_number, "LXXXI")) return "81";
if (!strcmp(roman_number, "LXXXII")) return "82";
if (!strcmp(roman_number, "LXXXIII")) return "83";
if (!strcmp(roman_number, "LXXXIV")) return "84";
if (!strcmp(roman_number, "LXXXV")) return "85";
if (!strcmp(roman_number, "LXXXVI")) return "86";
if (!strcmp(roman_number, "LXXXVII")) return "87";
if (!strcmp(roman_number, "LXXXVIII")) return "88";
if (!strcmp(roman_number, "LXXXIX")) return "89";
if (!strcmp(roman_number, "XC")) return "90";
if (!strcmp(roman_number, "XCI")) return "91";
if (!strcmp(roman_number, "XCII")) return "92";
if (!strcmp(roman_number, "XCIII")) return "93";
if (!strcmp(roman_number, "XCIV")) return "94";
if (!strcmp(roman_number, "XCV")) return "95";
if (!strcmp(roman_number, "XCVI")) return "96";
if (!strcmp(roman_number, "XCVII")) return "97";
if (!strcmp(roman_number, "XCVIII")) return "98";
if (!strcmp(roman_number, "XCIX")) return "99";
if (!strcmp(roman_number, "C")) return "100";
}

/**
 * Converts a decimal number to a text format (Roman or decimal representation), 
 * depending on whether the '-r' option is enabled.
 * @param number the number that needs to be presented in text form.
 * @param roman a boolean value indicating whether the Roman numeral system is used
 * @return a number in a text representation in decimal or Roman numeral system, 
 * depending on the roman.
 */
char* process_number_to_string(int number, int roman) {
  char* roman_number = get_roman_number(number);
  if (roman) {
    return roman_number;
  }
  return get_decimal_number(roman_number);
}

/**
 * Asks leading 'yes/no' questions and narrows the answer space to guess the number.
 * @param start the beginning of the range of possible numbers to guess (inclusive).
 * @param end the end of the range of possible numbers to guess (inclusive).
 * @param roman a boolean value indicating whether the Roman numeral system is used.
 * @return the guessed number.
 */
int guess_the_number(int start, int end, int roman) {
  if (end == start) {
      return end;
  }
  int half = start + ((end - start + 1) / 2) - 1;
  printf(_("Is the number greater than %s? (yes/no)\n"), process_number_to_string(half, roman));
  char answer[10];
  fgets(answer, 10, stdin);
  if (!strcmp(answer, _("yes\n"))) {
      return guess_the_number(half + 1, end, roman);
  }
  if (!strcmp(answer, _("no\n"))) {
      return guess_the_number(start, half, roman);
  }
  printf(_("I didn't understand your answer \"%s\". Try again\n"), answer);
  return guess_the_number(start, end, roman);
}

/**
 * Parses the input parameters and calls the 'guess_the_number' function.
 * @see guess_the_number()
 */

int main(int argc, char* argv[]) {
  static char doc[] = "guess_the_number -- a program that guesses numbers";
  static char args_doc[] = "";
  struct arguments arguments;
  static struct argp_option options[] = {
      {"roman",  'r', 0,      0,  "Enable the Roman numeral system" },
      { 0 }
  };
  static struct argp argp = { options, parse_opt, args_doc, doc };
  arguments.roman = 0;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  printf ("ROMAN = %s\n",
          arguments.roman ? "yes" : "no");

  setlocale (LC_ALL, "");
	bindtextdomain ("guess_the_number", LOCALE_PATH);
	textdomain ("guess_the_number");
  printf(_("Think a number from %s to %s\n"), process_number_to_string(1, arguments.roman), process_number_to_string(100, arguments.roman));

	printf(_("I know what number you made up! This is %s\n"), process_number_to_string(guess_the_number(1, 100, arguments.roman), arguments.roman));
  return 0;
}