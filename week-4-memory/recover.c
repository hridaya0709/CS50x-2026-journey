#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid arguemnts\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");

    if (raw == NULL)
    {
        printf("No data available\n");
        return 1;
    }

    int bytes = 512;
    uint8_t block[bytes];

    int counter = 0;
    char fileName[8];
    bool openFile = false;
    FILE *jpeg;

    while (fread(block, 1, bytes, raw) == bytes)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (openFile == true)
            {
                fclose(jpeg);
                openFile = false;
            }

            sprintf(fileName, "%03i.jpg", counter++);
            jpeg = fopen(fileName, "w");
            openFile = true;
            fwrite(block, 1, bytes, jpeg);
        }
        else if (openFile == true)
        {
            fwrite(block, 1, bytes, jpeg);
        }
    }

    if (openFile == true)
    {
        fclose(jpeg);
    }

    fclose(raw);
}
