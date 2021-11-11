#include <errno.h> 
#include "rhash.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int next_line(char** line, size_t* len_line) {
    printf("> ");
#if defined(HAVE_READLINE) && defined(ENABLE_READLINE)
#include <readline/readline.h>
    return (*line = readline(NULL)) != NULL;
#else
    return getline(line, len_line, stdin) != -1;
#endif
}

enum HashType {
    MD5,
    SHA1,
    TTH
};

enum OutputType {
    HEX,
    BASE64
};

enum InputType {
    FILE_NAME,
    STRING
};

char* input_analysis(char* line, enum InputType* input_type, enum HashType* hash_type, enum OutputType* output_type) {
    char* cmd = strtok(line, " ");
    if (strcmp(cmd, "MD5") == 0) {
        *hash_type = MD5;
        *output_type = HEX;
    }
    else if (strcmp(cmd,"md5") == 0) {
        *hash_type = MD5;
        *output_type = BASE64;
    }
    else if (strcmp(cmd,"SHA1") == 0) {
        *hash_type = SHA1;
        *output_type = HEX;
    }
    else if (strcmp(cmd, "sha1") == 0) {
        *hash_type = SHA1;
        *output_type = BASE64;
    }
    else if (strcmp(cmd, "TTH") == 0) {
        *hash_type = TTH;
        *output_type = HEX;
    }
    else if (strcmp(cmd, "tth") == 0) {
        *hash_type = TTH;
        *output_type = BASE64;
    }
    else {
        return NULL;
    }

    cmd = strtok(NULL, "\n ");
    if (cmd == NULL) {
        return NULL;
    }
    
    if (*cmd == '\"') {
        *input_type = STRING;
        return strtok(++cmd, "\"");
    }
    *input_type = FILE_NAME;
    return cmd;
}

int get_hash(char* cmd, enum InputType input_type, enum HashType hash_type, enum OutputType output_type, char* digest) {
    if ((input_type == FILE_NAME) && (hash_type == MD5)) {
        return rhash_file(RHASH_MD5, cmd, digest);
    }
    if ((input_type == FILE_NAME) && (hash_type == SHA1)) {
        return rhash_file(RHASH_SHA1, cmd, digest);
    }
    if ((input_type == FILE_NAME) && (hash_type == TTH)) {
        return rhash_file(RHASH_TTH, cmd, digest);
    }
    if ((input_type == STRING) && (hash_type == MD5)) {
        return rhash_msg(RHASH_MD5, cmd, strlen(cmd), digest);
    }
    if ((input_type == STRING) && (hash_type == SHA1)) {
        return rhash_msg(RHASH_SHA1, cmd, strlen(cmd), digest);
    }
    if ((input_type == STRING) && (hash_type == TTH)) {
        return rhash_msg(RHASH_TTH, cmd, strlen(cmd), digest);
    }
    return -1;
}

void output_hash(char* digest, enum HashType hash_type, enum OutputType output_type) {
    char output[130];
    if ((output_type == HEX) && (hash_type == MD5)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD5), (RHPR_HEX | RHPR_UPPERCASE));
    }
    if ((output_type == BASE64) && (hash_type == MD5)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD5), (RHPR_BASE64 | RHPR_UPPERCASE));
    }
    if ((output_type == HEX) && (hash_type == SHA1)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_SHA1), (RHPR_HEX | RHPR_UPPERCASE));
    }
    if ((output_type == BASE64) && (hash_type == SHA1)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_SHA1), (RHPR_BASE64 | RHPR_UPPERCASE));
    }
    if ((output_type == HEX) && (hash_type == TTH)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_TTH), (RHPR_HEX | RHPR_UPPERCASE));
    }
    if ((output_type == BASE64) && (hash_type == TTH)) {
        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_TTH), (RHPR_BASE64 | RHPR_UPPERCASE));
    }
    printf("%s\n", output);
}

int main(int argc, char* argv[]) {
    rhash_library_init();
    char digest[64];
    char* line = NULL;
    char* cmd;
    size_t len = 0;
    enum InputType input_type;
    enum HashType hash_type;
    enum OutputType output_type;

    while (next_line(&line, &len)) {
        if ((cmd = input_analysis(line, &input_type, &hash_type, &output_type)) == NULL) {
            fprintf(stderr, "command not found\n");
            continue;
        }
        if (get_hash(cmd, input_type, hash_type, output_type, digest) < 0) {
            fprintf(stderr, "digest calculation error\n");
            continue;
        }
        output_hash(digest, hash_type, output_type);
    }
    free(line);
	return 0;
}