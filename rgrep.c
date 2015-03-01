#include <stdio.h>
#define MAXSIZE 4096

char next_char(char *string) {
	return *(string + sizeof(char));
}

char prev_char(char *string) {
	return *(string - sizeof(char));
}

void inc_char() {
	
}

//Accepts char, not pointer
int is_operator(char pattern) {
	switch(pattern) {
		case '.' :
			return 1;
		case '\\' :
			return 2;
		case '+' :
			return 3;
		case '\?' :
			return 4;
		default :
			return 0;
	}
}

int plus_modified(char *pattern) {
	if(next_char(pattern) == '+')
		return 1;
	return 0;
}

int question_modified(char *pattern) {
	if(next_char(pattern)  == '\?')
		return 1;
	return 0;
}

int escape_modified(char *pattern) {
	if(prev_char(pattern) == '\\')
		return 1;
	return 0;
}

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */

int matches_leading(char *line, char *pattern) {
	//Check direct match
	if(*line == *pattern && !is_operator(*pattern)) {
		return 1;
	}
	//Check wildcard match
	if(*pattern == '.' && !escape_modified(pattern)) {
		return 1;
	}
	//Check escaped operator match
	if(*line == *pattern && is_operator(*pattern) && escape_modified(pattern)) {
		return 1;
	}
	//Check for absent case of ? operator
	if(question_modified(pattern))
		return 1;
	return 0;
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

	//Base cases
	if(*line == '\0')
		return 0;

	if(*pattern == '\0')
		return 1;



	//Check for escape
	if((*pattern == '\\') && is_operator(next_char(pattern)))
		pattern += sizeof(char);



	//Check for match
	if(matches_leading(line, pattern)) {
		//For + modifier
		if(plus_modified(pattern)) {
			//Go to next nonmatching character
			//Stops one before because there is a line increment at the end of rgrep_matches
			while(*(line + sizeof(char)) == *pattern)
				line += sizeof(char);
			//Compensate for the character that the operator took
			pattern += sizeof(char);
		}
		//For ? modifier
		if(question_modified(pattern)) {
			//
			if(*line == *pattern && *line == *(pattern + 2 * sizeof(char)))
				return rgrep_matches(line, pattern + 2 * sizeof(char));
			//
			if(*line == *pattern && next_char(line) != *(pattern + 2 * sizeof(char)) && *line != *(pattern + 2 * sizeof(char)))
				return 0;
			//
			if(*line != *pattern && *line != *(pattern + 2 * sizeof(char)))
				return 0;
			//
			if(*pattern != '.' && *line != *pattern)
				line -= sizeof(char);
			//Compensate for the character that the operator took
			pattern += sizeof(char);
		}
		pattern += sizeof(char);
	}

	line += sizeof(char);



	//Recurse
	return rgrep_matches(line, pattern);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
