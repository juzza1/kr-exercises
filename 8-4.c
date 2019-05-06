#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* Max #files open at once */

typedef struct _iobuf {
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    struct {
        unsigned int _READ : 1;
        unsigned int _WRITE : 1;
        unsigned int _UNBUF : 1;
        unsigned int _EOF : 1;
        unsigned int _ERR : 1;
    } flags;
    int fd;     /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ = 01,     /* file open for reading */
    _WRITE = 02,    /* file open for writing */
    _UNBUF = 04,    /* file is unbuffered */
    _EOF = 010,     /* EOF has occured on this file */
    _ERR = 020      /* error occurred on this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);
int fseek(FILE *, long offset, int origin);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define PERMS 0666  /* RW for owner, group, others */

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    {0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
    {0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1},
    {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2}
};

FILE *fopen(char *name, char *mode);

int main()
{
    int i;
    FILE *fp;
    fp = fopen("krw.txt", "w");
    putc('y', fp);
    fflush(fp);
    return 0;
}

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'w') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flags._READ == 0 && fp->flags._WRITE == 0) {
            break;  /* found free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) {    /* no free slots */
        return NULL;
    }
    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) { /* couldn't access name */
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flags._READ = 1;
    } else {
        fp->flags._WRITE = 1;
    }
    return fp;
}

/* _fillbuf: allocat and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (fp->flags._READ == 0 || fp->flags._EOF == 1 || fp->flags._ERR == 1) {
        return EOF;
    }
    bufsize = fp->flags._UNBUF == 1 ? 1 : BUFSIZ;
    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;     /* can't get no buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flags._EOF = 1;
        } else {
            fp->flags._ERR = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    if (fp->flags._WRITE == 0 || fp->flags._EOF == 1 || fp->flags._ERR == 1) {
        return EOF;
    }
    write(fp->fd, fp->base, fp->ptr - fp->base);
    free(fp->base);
    bufsize = fp->flags._UNBUF == 1 ? 1 : BUFSIZ;
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
        return EOF;     /* can't get no buffer */
    }
    fp->cnt = bufsize;
    fp->ptr = fp->base;
    if (c >= 0) {
        *fp->ptr++ = (unsigned char) c;
    }
    return 0;
}

int fflush(FILE *fp)
{
    if (fp->flags._WRITE != 1 || fp->flags._EOF == 1 || fp->flags._ERR == 1) {
        return EOF;
    }
    _flushbuf(-1, fp);
    return 0;
}

int fclose(FILE *fp)
{
    if (fp->flags._EOF == 1 || fp->flags._ERR == 1) {
        return EOF;
    }
    if (fp->flags._WRITE == 1) {
        _fillbuf(fp);
    } else if (fp->flags._READ == 1) {
        _flushbuf(-1, fp);
    } else {
        return EOF;
    }
    if (fp->base != NULL) {
        free(fp->base);
    }
    close(fp->fd);
    return 0;
}

int fseek(FILE *fp, long offset, int origin)
{
    int c;
    if ((c = lseek(fp->fd, offset, origin)) >= 0) {
        fp->ptr += c;
        return 0;
    }
    return EOF;
}
