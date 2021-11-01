#include <unistd.h>
#include <string.h>



int CompareWithCoding(const char *str1, const char *str2, const size_t coding){
    size_t i = 0;
    while ((i < coding) && (str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
        i++;
    if (i != coding)
        return 0;
    else
        return 1;
}


int CopyWithCoding(char *str1, const char *str2, const size_t coding){
    memcpy(str1, str2, coding);
    return 0;
}
