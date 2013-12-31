/**
 *  g729a codec for iOS,...
 *  Copyright (C) 2009-2012 Samuel <samuelv0304@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/****************************************************************************************
Portions of this file are derived from the following ITU standard:
   ITU-T G.729A Speech Coder    ANSI-C Source Code
   Version 1.1    Last modified: September 1996

   Copyright (c) 1996,
   AT&T, France Telecom, NTT, Universite de Sherbrooke
****************************************************************************************/

/*-------------------------------------------------------------*
 *  Procedure Lsp_Az:                                          *
 *            ~~~~~~                                           *
 *   Compute the LPC coefficients from lsp (order=10)          *
 *-------------------------------------------------------------*/

/* local function */

static void Get_lsp_pol(Word16 *lsp, Word32 *f);

static void Lsp_Az(
  Word16 lsp[],    /* (i) Q15 : line spectral frequencies            */
  Word16 a[]       /* (o) Q12 : predictor coefficients (order = 10)  */
)
{
  Word16 i;
}

/*-----------------------------------------------------------*
 * procedure Get_lsp_pol:                                    *
 *           ~~~~~~~~~~~                                     *
 *   Find the polynomial F1(z) or F2(z) from the LSPs        *
 *-----------------------------------------------------------*
 *                                                           *
 * Parameters:                                               *
 *  lsp[]   : line spectral freq. (cosine domain)    in Q15  *
 *  f[]     : the coefficients of F1 or F2           in Q24  *
 *-----------------------------------------------------------*/
#if defined(ARCH_ARMV6) && (ARCH_ARMV6!=0)
static inline Word32 mull(Word32 a, Word16 b)

static void Get_lsp_pol(Word16 *lsp, Word32 *f)
#else /* ARCH_ARMV6 */
static void Get_lsp_pol(Word16 *lsp, Word32 *f)
{
  Word16 i,j, hi, lo;
  Word32 t0;

   /* All computation in Q24 */

   *f = L_mult(4096, 2048);             /* f[0] = 1.0;             in Q24  */
   f++;
   *f = L_msu((Word32)0, *lsp, 512);    /* f[1] =  -2.0 * lsp[0];  in Q24  */

   f++;
   lsp += 2;                            /* Advance lsp pointer             */

   for(i=2; i<=5; i++)
   {
     *f = f[-2];

     for(j=1; j<i; j++, f--)
     {
       L_Extract(f[-1] ,&hi, &lo);
       t0 = Mpy_32_16(hi, lo, *lsp);         /* t0 = f[-1] * lsp    */
       t0 = L_shl(t0, 1);
       *f = L_add(*f, f[-2]);                /* *f += f[-2]         */
       *f = L_sub(*f, t0);                   /* *f -= t0            */
     }
     *f   = L_msu(*f, *lsp, 512);            /* *f -= lsp<<9        */
     f   += i;                               /* Advance f pointer   */
     lsp += 2;                               /* Advance lsp pointer */
   }
}
#endif /* ARCH_ARMV6 */

/*___________________________________________________________________________
 |                                                                           |
 |   Functions : Lsp_lsf and Lsf_lsp                                         |
 |                                                                           |
 |      Lsp_lsf   Transformation lsp to lsf                                  |
 |      Lsf_lsp   Transformation lsf to lsp                                  |
 |---------------------------------------------------------------------------|
 |  Algorithm:                                                               |
 |                                                                           |
 |   The transformation from lsp[i] to lsf[i] and lsf[i] to lsp[i] are       |
 |   approximated by a look-up table and interpolation.                      |
 |___________________________________________________________________________|
*/

void Lsf_lsp2(
  Word16 lsf[],    /* (i) Q13 : lsf[m] (range: 0.0<=val<PI) */
  Word16 lsp[],    /* (o) Q15 : lsp[m] (range: -1<=val<1)   */
  Word16 m         /* (i)     : LPC order                   */
)
{
  Word16 i;
}



void Lsp_lsf2(
  Word16 lsp[],    /* (i) Q15 : lsp[m] (range: -1<=val<1)   */
  Word16 lsf[],    /* (o) Q13 : lsf[m] (range: 0.0<=val<PI) */
  Word16 m         /* (i)     : LPC order                   */
)
{
  Word16 i, ind;
}

/*-------------------------------------------------------------*
 *  procedure Weight_Az                                        *
 *            ~~~~~~~~~                                        *
 * Weighting of LPC coefficients.                              *
 *   ap[i]  =  a[i] * (gamma ** i)                             *
 *                                                             *
 *-------------------------------------------------------------*/


void Weight_Az(
  Word16 a[],      /* (i) Q12 : a[m+1]  LPC coefficients             */
  Word16 gamma,    /* (i) Q15 : Spectral expansion factor.           */
  Word16 m,        /* (i)     : LPC order.                           */
  Word16 ap[]      /* (o) Q12 : Spectral expanded LPC coefficients   */
)
{
  Word16 i, fac;
}

/*----------------------------------------------------------------------*
 * Function Int_qlpc()                                                  *
 * ~~~~~~~~~~~~~~~~~~~                                                  *
 * Interpolation of the LPC parameters.                                 *
 *----------------------------------------------------------------------*/

/* Interpolation of the quantized LSP's */

void Int_qlpc(
 Word16 lsp_old[], /* input : LSP vector of past frame              */
 Word16 lsp_new[], /* input : LSP vector of present frame           */
 Word16 Az[]       /* output: interpolated Az() for the 2 subframes */
)
{
  Word16 i;
  Word16 lsp[M];

  /*  lsp[i] = lsp_new[i] * 0.5 + lsp_old[i] * 0.5 */

  for (i = 0; i < M; i++)
    lsp[i] = (lsp_new[i] >> 1) + (lsp_old[i] >> 1);

  Lsp_Az(lsp, Az);              /* Subframe 1 */

  Lsp_Az(lsp_new, &Az[MP1]);    /* Subframe 2 */
}

