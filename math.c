/****************************************************************
Copyright (C) Lucent Technologies 1997
All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name Lucent Technologies or any of
its entities not be used in advertising or publicity pertaining
to distribution of the software without specific, written prior
permission.

LUCENT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL LUCENT OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
****************************************************************/

#pragma STDC FENV_ACCESS ON

#include <errno.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>

#include "awk.h"

#ifndef FE_DIVBYZERO
#define FE_DIVBYZERO 0
#endif

#ifndef FE_INVALID
#define FE_INVALID 0
#endif

#ifndef FE_OVERFLOW
#define FE_OVERFLOW 0
#endif

#ifndef FE_UNDERFLOW
#define FE_UNDERFLOW 0
#endif

#define errclear()							\
	do {								\
		errno = 0;						\
		feclearexcept(FE_ALL_EXCEPT);				\
	} while (0)

static double errcheck(double x, const char *s)
{
	if (errno == EDOM || fetestexcept(FE_INVALID)) {
		errno = 0;
		WARNING("%s argument out of domain", s);
		x = 1;
	} else if (errno == ERANGE || fetestexcept(FE_DIVBYZERO | FE_OVERFLOW |
	    FE_UNDERFLOW)) {
		errno = 0;
		WARNING("%s result out of range", s);
		x = 1;
	}

	return x;
}

double exp_errcheck(double x)
{
	errclear();
	return errcheck(exp(x), "exp");
}

double log_errcheck(double x)
{
	errclear();
	return errcheck(log(x), "log");
}

double pow_errcheck(double x, double y)
{
	errclear();
	return errcheck(pow(x, y), "pow");
}

double sqrt_errcheck(double x)
{
	errclear();
	return errcheck(sqrt(x), "sqrt");
}
