/*
 * This program is for setting TTF files to Installable Embedding mode.
 *
 * Note that using this to embed fonts which you are not licensed to embed
 * does not make it legal.
 *
 * This code was written by Tom Murphy 7, and is public domain. Use at your
 * own risk...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned long readbe32(FILE *f)
{
    unsigned long v;
    v  = fgetc(f) << 24;
    v |= fgetc(f) << 16;
    v |= fgetc(f) << 8;
    v |= fgetc(f);
    return v;
}

void fstype0(char *filename, int dry_run)
{
    FILE *inways;
    if ((inways = fopen(filename, dry_run ? "rb" : "rb+"))) {
        int x;
        char type[5];
        type[4]=0;

        unsigned long ftype = readbe32(inways);
        if (ftype != 0x00010000 && ftype != 0x4f54544f) {
            fprintf(stderr, "%s: Not TTF/OTF\n", filename);
            fclose(inways);
            return;
        }
        if (fseek(inways,12,0)) goto funk;
        for (;;) {
            for (x=0;x<4;x++)
                if (EOF == (type[x] = getc(inways))) goto funk;
            if (!strcmp(type,"OS/2")) {
                int length;
                unsigned long loc, fstype, oldfstype, sum=0;
                loc=ftell(inways); /* location for checksum */
                (void)readbe32(inways);
                fstype = readbe32(inways);
                length = readbe32(inways);
                if (fseek(inways,fstype+8,0)) goto funk;
                oldfstype = fgetc(inways) << 8;
                oldfstype |= fgetc(inways);
                if (oldfstype != 0) {
                    if (!dry_run) {
                        if (fseek(inways,fstype+8,0)) goto funk;
                        fputc(0,inways);
                        fputc(0,inways);
                        fseek(inways,fstype,0);
                        for (x=length;x>0;x-=4)
                            sum += readbe32(inways);
                        fseek(inways,loc,0); /* write checksum */
                        fputc(sum>>24,inways);
                        fputc(255&(sum>>16),inways);
                        fputc(255&(sum>>8), inways);
                        fputc(255&sum    ,  inways);
                    } else {
                        printf("fstype=%04lx %s\n", oldfstype, filename);
                    }
                }
                fclose(inways);
                break;
            }
            for (x=12;x--;) if (EOF == getc(inways)) goto funk;
        }
    } else {
        perror(filename);
    }
    return;
funk:
    fprintf(stderr, "%s: Malformed TTF\n", filename);
    fclose(inways);
    return;
}

int main (int argc, char *argv[])
{
    int dry_run = 0, opt;

    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
        case 'n':
            dry_run = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-n] font.ttf\n", argv[0]);
            exit(1);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n] font.ttf\n", argv[0]);
        exit(1);
    }

    while (optind < argc)
        fstype0(argv[optind++], dry_run);

    return 0;
}
