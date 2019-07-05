#include "libc.h"

CODES priorities_array[9] =
  {
   { "EMERGENCY", LOG_EMERGENCY },
   { "ALERT", LOG_ALERT },
   { "CRITICAL", LOG_CRITICAL },
   { "ERROR", LOG_ERROR },
   { "WARNING", LOG_WARNING },
   { "NOTICE", LOG_NOTICE },
   { "INFO", LOG_INFO },
   { "DEBUG", LOG_DEBUG },
   { NULL, -1 }
  };

int sendall(int fd, const char *buf, const size_t size) {
  size_t sent = 0;
  int ret;

  if (!buf)
    return 1;

  if (!size)
    return 2;

  while (sent < size) {
    ret = write(fd, buf + sent, size - sent);
    if (ret < 0) {
      return 3;
    }
    sent += ret;
  }

  return 0;
}

int syslog(int priority, const char *format, ...) {
  char log_entry[MAX_SYSLOG_LEN] = { 0 };
  char *log_entry_idx = log_entry;
  int ret;
  char *pri_str = priorities_array[priority].code_name;
  int log_entry_len;
  va_list args;

  va_start(args, format);
  // cgc_write priority to log_entry buffer
  log_entry_len = snprintf(log_entry_idx, MAX_SYSLOG_LEN, "%s: ", pri_str);
  log_entry_idx += log_entry_len;

  // process format string and cgc_write it to log_entry buffer
  log_entry_len += vsnprintf(log_entry_idx, MAX_SYSLOG_LEN - log_entry_len, format, args);
  va_end(args);

  // send log_entry to stdout
  ret = sendall(STDERR, log_entry, (log_entry_len < MAX_SYSLOG_LEN ? log_entry_len : MAX_SYSLOG_LEN));
  if (ret != 0)
    exit(4);

  return 0;
}

// mod from FASTLANE: lines terminated with \x07, diff return values,
int recvline(int fd, char *buf, size_t size) {
  ssize_t bytes_read = 0;
  ssize_t total_read = 0;

  if(!size)
    return 0;

  if (!buf)
    return -7;

  while (size) {
    bytes_read = read(fd, buf++, 1);
    if (bytes_read < 0)
      return -7;

    total_read++;
    size--;

    if(*(buf-1) == '\x0a')
      break;
  }

  if (*(buf-1) != '\x0a')
    return -77;
  else
    *(buf-1) = '\0';

  return total_read;
}

int receive(int fd, void *buf, size_t size, size_t *readLen) {
  ssize_t bytes_read;
  ssize_t total_read = 0;
  char *cbuf = buf;
  while (size > 0) {
    bytes_read = read(fd, cbuf, size);
    if (bytes_read < 0)
      return -7;
    size -= bytes_read;
    cbuf += bytes_read;
    total_read += bytes_read;
  }
  *readLen = total_read;
  return 0;
}

char *strtokc(char *str, char delim) {
  char delim_str[2];
  delim_str[0] = delim;
  delim_str[1] = 0;
  return strtok(str, delim_str);
}

char * itoa(int val, char *s) {
  char tmp = '\0';
  char *t = s;
  char *ret = s;

  if (val == 0)
    return strcpy(s, "0");

  if (val < 0) {
    s++;
    *t++ = '-';
    val = -val;
  }

  while (val) {
    *t++ = '0' + val % 10;
    val /= 10;
  }
  *t-- = '\0';

  while (t - s > 0) {
    tmp = *s;
    *s++ = *t;
    *t-- = tmp;
  }

  return ret;
}

char to_hex(unsigned char v) {
  if (v < 10)
    return '0' + v;
  else if (v < 16)
    return 'a' + (v - 10);
  else
    return '\0';
}
