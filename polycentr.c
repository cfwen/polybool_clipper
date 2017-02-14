/*
 * A mex function to compute the center of gravity of one or more polygons.
 * 
 * [cg] = polycentr(pa);
 *
 * pa :  cell array of length N containing polygons (nx2 matrices)
 * cg :  Nx2 array with centers of gravity, one per row
 *
 * Ulf Griesmann, NIST, November 2016
 */

#include <math.h>
#include <string.h>
#include <mex.h>

#ifdef __GNUC__
   #define RESTRICT __restrict
   #define INLINE __inline__
#else
   #define RESTRICT
   #define INLINE
#endif


/*-- local prototypes -----------------------------------------*/

INLINE void
polygon_centroid(double * RESTRICT p, int M, int m, double *cgx, double *cgy);


/*-------------------------------------------------------------*/

void 
mexFunction(int nlhs, mxArray *plhs[], 
	    int nrhs, const mxArray *prhs[])
{
   mxArray *par;     /* pointer to array structure */
   double *pda;      /* polynom data */
   double *pout;     /* pointer to output data */
   int m, M;
   int k, Na;

   /* check argument pa */
   if ( !mxIsCell(prhs[0]) ) {
      mexErrMsgTxt("argument must be a cell array.");
   }
   Na = mxGetNumberOfElements(prhs[0]);
   if (!Na) {
      mexErrMsgTxt("no input polygons pa.");
   }

   /* create output array */
   plhs[0] = mxCreateDoubleMatrix(Na, 2, mxREAL);
   pout = (double *)mxGetData(plhs[0]);

   /* calculate polygon areas */
   for (k=0; k<Na; k++) {

      /* get the next polygon from the cell array */ 
      par = mxGetCell(prhs[0], k); /* ptr to mxArray */
      pda = mxGetData(par);        /* ptr to a data */     
      M = m = mxGetM(par);         /* rows = vertex number */

      /* check if last vertex is duplicate of first */
      if ( (pda[0] == pda[m-1]) && (pda[m] == pda[2*m-1]) ) {
	  m--;
      }

      /* check if enough vertices */
      if (m <= 2) {
	  mexErrMsgTxt("polygons must have at least 3 vertices.");
      }

      /* calculate centroids */
      polygon_centroid(pda, M, m, &pout[k], &pout[Na+k]);
   }
}


/*
 * calculate the centroid of a simple polygon
 */
INLINE void
polygon_centroid(double * RESTRICT p, int M, int m, double *cgx, double *cgy)
{
    int k;
    double X,Y;
    double A, beta;

    A = X = Y = 0.0;

    for (k=0; k<m; k++) {
        beta = p[k]*p[M+k+1] - p[k+1]*p[M+k];
	A += beta;
        X += beta * (p[k] + p[k+1]);
	Y += beta * (p[M+k] + p[M+k+1]);
    }

    A *= 3.0;
    *cgx = X / A;
    *cgy = Y / A;
}
