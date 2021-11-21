#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

int subst_prerprocessing(char* subst, char* preproc_subst, regmatch_t* pm, int pn, char* string) {
    if (strlen(subst) == 0) {
        preproc_subst = subst;
        return 0;
    }

    int supplied_pockets = 0;
    int result_len = 1;
    int pocket_number_len = 0;
    int pocket_number = 0;
    int is_digit = 0;
    int pockets_numbers[strlen(subst)/2];
    int pockets_positions[strlen(subst)/2][2];
    for (int i = 1; i < strlen(subst); i++) {
        if (!is_digit && (subst[i-1] == '\\') && (isdigit(subst[i]))) {
            is_digit = 1;
            pocket_number_len = 1;
            pocket_number = subst[i] - '0';
            continue;
        }
        if (is_digit && isdigit(subst[i])) {
            pocket_number = pocket_number*(10^pocket_number_len) + (subst[i] - '0');
            pocket_number_len++;
            continue;
        }
        if (is_digit) {
            is_digit = 0;
            if (pocket_number >= pn) {
                printf("invalid reference \\%d\n", pocket_number);
                return -4;
            }
            pockets_positions[supplied_pockets][0] = i - pocket_number_len - 1;
            pockets_positions[supplied_pockets][1] = i;
            pockets_numbers[supplied_pockets] = pocket_number;
            supplied_pockets++;
            result_len += pm[pocket_number].rm_eo - pm[pocket_number].rm_so;
            continue;
        }
        
        result_len++;
    }

    preproc_subst = realloc(preproc_subst, result_len*sizeof(char));
    int subst_len = 0;
    for (int i = 0; i < strlen(subst); i++) {
        int j;
        for (j = 0; j < supplied_pockets; j++) {
            if (pockets_positions[j][0] == i) {
                break;
            }
        }
        if (j == supplied_pockets) {
            preproc_subst[subst_len] = subst[i];
            subst_len++;
            continue;
        }

        int pocket_num = pockets_numbers[j];
        for (int k = pm[pocket_num].rm_so; k < pm[pocket_num].rm_eo; k++) {
            preproc_subst[subst_len] = string[k];
            subst_len++;
        }
        i = pockets_positions[j][1] - 1;
    }

    return subst_len;
}

int string_prerprocessing(char* string, char* preproc_string) {
    char* pc = string;
    char c;
    int slash_flag = 0;
    int i = 0;
    int preprocessed_len = 0;
    while ((c = *pc++) != '\0') {
        if ((c == '\\') && slash_flag) {
            slash_flag = 0;
            continue;
        }

        if (c == '\\') {
            slash_flag = 1;
            preproc_string[i] = c;
            preprocessed_len++;
            i++;
            continue;
        }

        slash_flag = 0;
        preproc_string[i] = c;
        preprocessed_len++;
        i++;
    }
    return preprocessed_len;
}

int count_pockets_number(char* regexp) {
    int pockets_number = 0;
    int open_pockets = 0;
    for (int i = 0; i < strlen(regexp); i++) {
        if (regexp[i] == '(') {
            open_pockets++;
            continue;
        }
        if (regexp[i] == ')') {
            if (open_pockets == 0) {
                printf("incorrect placement of pockets\n");
                return -2;
            }
            open_pockets--;
            pockets_number++;
        }
    }
    if (open_pockets != 0) {
        printf("incorrect placement of pockets\n");
        return -3;
    }
    return pockets_number + 1;
}

int replace(char* string, regmatch_t* pm, int pockets_number, char* subst, char* result_string) {
    int subst_len = 0;
    if (subst != NULL) {
        subst_len = strlen(subst);
    }
    int match_len = pm[0].rm_eo - pm[0].rm_so;
    int result_len = strlen(string) - match_len + subst_len;
    result_string = realloc(result_string, result_len*sizeof(char));
    for (int i = 0; i < pm[0].rm_so; i++) {
        result_string[i] = string[i];
    }

    int j = 0;
    for (int i = pm[0].rm_so; i < pm[0].rm_so + subst_len; i++) {
        result_string[i] = subst[j++];
    }
    j = pm[0].rm_eo;
    for (int i = pm[0].rm_so + subst_len; i < result_len; i++) {
        result_string[i] = string[j++];
    }
    return result_len;
}

void process_error(size_t regerr, regex_t* r, char* error_type) {
    int errbuf_size = regerror(regerr, r, NULL, 0);
    char* errbuf = malloc(errbuf_size*sizeof(char));
    regerror(regerr, r, errbuf, errbuf_size);
    printf("%s failed! regerror=%ld, %s\n", error_type, regerr, errbuf);
    free(errbuf);
}

void free_memory(char* preprocessed_string, char* preprocessed_subst, char* result) {
    if (preprocessed_subst != NULL) {
        free(preprocessed_subst);
    }
    if (preprocessed_string != NULL) {
        free(preprocessed_string);
    }
    if (result != NULL) {
        free(result);
    }
}

int main(int argc, char* argv[]) {
    char* regexp;
    char* substitution;
    char* string;

    if (argc >= 4) {
        regexp = argv[1];
        substitution = argv[2];
        string = argv[3];
    }
    else {
        printf("missing operand\n");
        printf("syntax: esub regexp substitution string\n");
		return 1;
    }

    char* preprocessed_string = malloc(strlen(string)*sizeof(char));
    int preprocessed_len = string_prerprocessing(string, preprocessed_string);
    preprocessed_string = realloc(preprocessed_string, preprocessed_len*sizeof(char));

    int pockets_number = count_pockets_number(regexp);
    if (pockets_number < 0) {
        free_memory(preprocessed_string, NULL, NULL);
        return -5;
    }


    regmatch_t pm[pockets_number];
    regex_t r;
    int regerr = 0;

    if (regerr = regcomp(&r, regexp, REG_EXTENDED)){
        process_error(regerr, &r, "regcomp");
        free_memory(preprocessed_string, NULL, NULL);
        return regerr;
    }

    if (regerr = regexec(&r, preprocessed_string, pockets_number, pm, 0)) {
        process_error(regerr, &r, "regexec");
        free_memory(preprocessed_string, NULL, NULL);
        return regerr;
    }

    char* preprocessed_subst = malloc(strlen(substitution)*sizeof(char));
    int subst_len = subst_prerprocessing(substitution, preprocessed_subst, pm, pockets_number, preprocessed_string);
    if (subst_len < 0) {
        free_memory(preprocessed_string, preprocessed_subst, NULL);
        return subst_len;
    }
    preprocessed_subst = realloc(preprocessed_subst, subst_len*sizeof(char));

    char* result = malloc(preprocessed_len*sizeof(char));
    int res_len = replace(preprocessed_string, pm, pockets_number, preprocessed_subst, result);
    result = realloc(result, res_len*sizeof(char));
    printf("%s\n", result);

    free_memory(preprocessed_string, preprocessed_subst, result);
	return 0;
}