/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Sebastian Pancratz
    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;

    printf("pow_binomial....");
    fflush(stdout);

    fmpz_poly_randinit();

    /* Check aliasing of a and b */
    for (i = 0; i < 2000; i++)
    {
        fmpz_poly_t a, b;
        ulong exp;

        fmpz_poly_init(a);
        fmpz_poly_init2(b, 2);

        fmpz_randtest(b->coeffs, n_randint(100));
        fmpz_randtest_not_zero(b->coeffs + 1, n_randint(100) + 1);
        _fmpz_poly_set_length(b, 2);
        
        exp = n_randtest() % 100UL;

        fmpz_poly_pow_binomial(a, b, exp);
        fmpz_poly_pow_binomial(b, b, exp);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL(1):\n");
            printf("exp = %lu\n", exp);
            printf("a = "), fmpz_poly_print(a), printf("\n\n");
            printf("b = "), fmpz_poly_print(b), printf("\n\n");
            abort();
        }

        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    /* Compare with fmpz_poly_pow */
    for (i = 0; i < 2000; i++)
    {
        fmpz_poly_t a, b;
        ulong exp;

        fmpz_poly_init(a);
        fmpz_poly_init2(b, 2);
        
        fmpz_randtest(b->coeffs, n_randint(100));
        fmpz_randtest_not_zero(b->coeffs + 1, n_randint(100) + 1);
        _fmpz_poly_set_length(b, 2);

        exp = n_randtest() % 100UL;

        fmpz_poly_pow_binomial(a, b, exp);
        fmpz_poly_pow(b, b, exp);

        result = (fmpz_poly_equal(a, b));
        if (!result)
        {
            printf("FAIL(2):\n");
            printf("exp = %lu\n", exp);
            printf("a = "), fmpz_poly_print(a), printf("\n\n");
            printf("b = "), fmpz_poly_print(b), printf("\n\n");
            abort();
        }

        fmpz_poly_clear(a);
        fmpz_poly_clear(b);
    }

    fmpz_poly_randclear();
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}