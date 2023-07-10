/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    math.c

Abstract:




Revision History

--*/

#include "lib.h"


/* 
 *  Declare runtime functions
 */

#ifdef RUNTIME_CODE
#pragma RUNTIME_CODE(LShiftU64)
#pragma RUNTIME_CODE(RShiftU64)
#pragma RUNTIME_CODE(MultU64x32)
#pragma RUNTIME_CODE(DivU64x32)
#endif

/* 
 * 
 */

UINT64
LShiftU64 (
    IN UINT64   Operand,
    IN UINTN    Count
    )
/*  Left shift 64bit by 32bit and get a 64bit result */
{
    UINT64      Result;

    Result = Operand << Count;

    return Result;
}

UINT64
RShiftU64 (
    IN UINT64   Operand,
    IN UINTN    Count
    )
/*  Right shift 64bit by 32bit and get a 64bit result */
{
    UINT64      Result;

    Result = Operand >> Count;

    return Result;
}


UINT64
MultU64x32 (
    IN UINT64   Multiplicand,
    IN UINTN    Multiplier
    )
/*  Multiple 64bit by 32bit and get a 64bit result */
{
    UINT64      Result;

    Result = Multiplicand * Multiplier;

    return Result;
}

UINT64
DivU64x32 (
    IN UINT64   Dividend,
    IN UINTN    Divisor,
    OUT UINTN   *Remainder OPTIONAL
    )
/*  divide 64bit by 32bit and get a 64bit result
 *  N.B. only works for 31bit divisors!! */
{
    UINT64 Result;

    ASSERT (Divisor != 0);
    ASSERT ((Divisor >> 31) == 0);

    /* 
     *  For each bit in the dividend
     */

    Result = Dividend / Divisor;

    if (Remainder) {
        *Remainder = Dividend % Divisor;
    }

    return Result;
}
