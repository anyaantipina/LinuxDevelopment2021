#include <stdio.h>
#include <errno.h> 


int emergency_return(FILE *infile, FILE *outfile, char* infile_name, char* outfile_name, int return_code) {

    fclose(infile);
    if (outfile != NULL) {
        remove(outfile_name);
    }
    return return_code;
}

int regular_return(FILE *infile, FILE *outfile, char* infile_name, char* outfile_name) {

    if (fclose(infile) == EOF) {
        printf("Can't close infile %s\n", infile_name);
        remove(outfile_name);
        return 5;
    }

    if (fclose(outfile) == EOF) {
        printf("Can't close outfile %s\n", outfile_name);
        remove(outfile_name);
        return 6;
    }

    if (remove(infile_name) == -1) {
        printf("Can't remove infile %s\n", infile_name);
        printf("Error code: %d\n", errno);
        return errno;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    char* infile_name;
    char* outfile_name;
    if (argc >= 3) {
        infile_name = argv[1];
        outfile_name = argv[2];
    }
    else {
        printf("missing operand\n");
        printf("syntax: move infile outfile\n");
		return 1;
    }

    FILE *infile;
    FILE *outfile;
	if ((infile = fopen(infile_name, "r")) == NULL) {
		printf("Can't open infile %s\n", infile_name);
		return 2;
	}
    if ((outfile = fopen(outfile_name, "w")) == NULL) {
		printf("Can't create or open outfile %s\n", outfile_name);
        return emergency_return(infile, NULL, infile_name, NULL, 3);
	}
    
    char c;
    while ((c = fgetc(infile)) != EOF){
		fputc(c, outfile);
	}
    if (errno != 0) {
        printf("Error while reading infile %s\n", infile_name);
        printf("Error code: %d\n", errno);
        return emergency_return(infile, outfile, infile_name, outfile_name, 4);
    }

	return regular_return(infile, outfile, infile_name, outfile_name);
}