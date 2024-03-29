#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wiring.h"

#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
void Print::write(const char *str)
{
  while (*str)
    write(*str++);
}

/* default implementation: may be overridden */
void Print::write(const uint8_t *buffer, size_t size)
{
  while (size--)
    write(*buffer++);
}

void Print::print(uint8_t b)
{
  this->write(b);
}

void Print::print(char c)
{
  print((byte) c);
}

void Print::print(const char str[])
{
  write(str);
}

void Print::print(int n)
{
  print((long) n);
}

void Print::print(unsigned int n)
{
  print((unsigned long) n);
}

void Print::print(long n)
{
  if (n < 0) {
    print('-');
    n = -n;
  }
  printNumber(n, 10);
}

void Print::print(unsigned long n)
{
  printNumber(n, 10);
}

void Print::print(long n, int base)
{
  if (base == 0)
    print((char) n);
  else if (base == 10)
    print(n);
  else
    printNumber(n, base);
}

void Print::print(double n)
{
  printFloat(n, 2);
}

void Print::println(void)
{
  print('\r');
  print('\n');
}

void Print::println(char c)
{
  print(c);
  println();
}

void Print::println(const char c[])
{
  print(c);
  println();
}

void Print::println(uint8_t b)
{
  print(b);
  println();
}

void Print::println(int n)
{
  print(n);
  println();
}

void Print::println(unsigned int n)
{
  print(n);
  println();
}

void Print::println(long n)
{
  print(n);
  println();
}

void Print::println(unsigned long n)
{
  print(n);
  println();
}

void Print::println(long n, int base)
{
  print(n, base);
  println();
}

void Print::println(double n)
{
  print(n);
  println();
}

// Private Methods /////////////////////////////////////////////////////////////

void Print::printNumber(unsigned long n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

void Print::printFloat(double number, uint8_t digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}
