#include "findsubstr.h"
#include <string.h>

int find_sub_string(const char *str, const char *sub){
	return (strstr(str, sub)!=NULL)? 1:-1;
}
