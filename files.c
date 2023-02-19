#include <stdio.h>

int main() {
    FILE *file1, *file2;

    file1 = fopen(".\\file1.txt", "r");
    file2 = fopen(".\\file2.txt", "w");

    char buf;

    while ((fread(&buf, sizeof(buf), 1, file1)) != 0)
    {
        fwrite(&buf, sizeof(buf), 1, file2);
    }
    
    fclose(file1);
    fclose(file2);

    return 0;
}