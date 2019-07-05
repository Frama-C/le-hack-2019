#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

// syslog priorities
#define LOG_DEBUG 7        // debug-level message
#define LOG_INFO 6         // informational message
#define LOG_NOTICE 5       // normal, but interesting condition
#define LOG_WARNING 4      // warning condition
#define LOG_ERROR 3        // error condition
#define LOG_CRITICAL 2     // critical condition
#define LOG_ALERT 1        // immediate action required
#define LOG_EMERGENCY 0    // system is unusable

#define LOGLEVEL LOG_INFO

#define MAX_SYSLOG_LEN 1024

int syslog(int priority, const char *format, ...);

typedef struct _syslog_codes {
  char    *code_name;
  int     code_val;
} CODES;

CODES priorities_array[9];

int sendall(int fd, const char *buf, const size_t size);

int recvline(int fd, char *buf, size_t size);

int receive(int fd, void *buf, size_t size, size_t *readLen);

char *strtokc(char *str, char delim);

#define transmit_all sendall

char *itoa (int value, char *str);

char to_hex(unsigned char v);

#endif //__LIBC_H
