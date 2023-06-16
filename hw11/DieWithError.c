#include <stdio.h>
#include <stdlib.h>

#include "DieWithError.h"

void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}
