#include <stdio.h>
#include <stdlib.h>

#define INPUT "input.c"
#define OUTPUT "output.c"

enum {
    
    NULSTAT,
    CSTAT,
    CPPSTAT,
    EOFSTAT
    
};

static int status = NULSTAT;

void do_null_stat(FILE *ipf,FILE *opf)
{
    int ch = fgetc(ipf);
    
    switch (ch) {
            
        case '/':
        {
            int s = fgetc(ipf);
            
            switch (s) {
                case '/':
                    fputc('/', opf);
                    fputc('/', opf);
                    status = CPPSTAT;
                    break;
                case '*':
                    fputc('/', opf);
                    fputc('/', opf);
                    status = CSTAT;
                    break;
                default:
                    fputc('/', opf);
                    ungetc(s, ipf);
                    status = NULSTAT;
                    break;
            }
            break;
        }
        
        case EOF:
            status = EOFSTAT;
            break;
        default:
            fputc(ch, opf);
            status = NULSTAT;
            break;
            
    }
}

void do_c_stat(FILE *ipf,FILE *opf)
{
    
    int ch = fgetc(ipf);
    
    switch (ch) {
            
        case '*':
        {
            int s = fgetc(ipf);
            
            switch (s)
            {
                case '/':
                {   int n = fgetc(ipf);
                    switch (n) {
                        case '\n': //若mac平台为\r
                            fputc('\n', opf);
                            break;
                            
                        default:
                            fputc('\n', opf);
                            ungetc(n, ipf);
                            break;
                    }

                    status = NULSTAT;
                }
                break;
                default:
                    fputc('*', opf);
                    ungetc(s, ipf);
                    break;
            }
        }
            break;
        case '\n':
            fputc('\n', opf);
            fputc('/', opf);
            fputc('/', opf);
            status = CSTAT;
            break;
        case EOF:
            status = EOFSTAT;
            break;
        default:
            fputc(ch, opf);
            status = CSTAT;
            break;
            
    }
    
    
}

void do_cpp_stat(FILE *ipf,FILE *opf)  //cdsjhkjd \n
{
    
    int ch = fgetc(ipf);
    
    switch (ch) {
            
        case '\n':
        {
            fputc(ch, opf);
            status = NULSTAT;
            break;
        }
        case EOF:
            status = EOFSTAT;
            break;
        default:
            fputc(ch, opf);
            status = CPPSTAT;
            break;
            
    }
    
    
    
    
}

void do_eof_stat(FILE *ipf,FILE *opf)
{
    
    exit(1);
    
}

void convert_work(FILE *ipf,FILE *opf)
{
    while ( status != EOFSTAT ) {
        
        switch (status) {
            case NULSTAT:
                do_null_stat(ipf,opf);
                break;
            case CSTAT:
                do_c_stat(ipf,opf);
                break;
            case CPPSTAT:
                do_cpp_stat(ipf,opf);
                break;
            case EOFSTAT:
                do_eof_stat(ipf,opf);
                break;
            default:
                break;
        }
        
    }
    
}




void convert_main()
{
    FILE *ipf = fopen(INPUT, "r");
    FILE *opf = fopen(OUTPUT, "w");
    
    if (ipf == NULL || opf == NULL) {
        fprintf(stdout, "err\n");
        exit(1);
    }
    
    
    convert_work(ipf,opf);
    
    
    fclose(ipf);
    fclose(opf);
    
    
}
