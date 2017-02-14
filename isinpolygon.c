/*
 * A mex function to check if points are inside a polygon
 * 
 * [inp] = inpolygon(polygon, xy);
 *
 * polygon :  an m x 2 array with polygon vertices
 * xy :       m x 2 array of points, one point per row
 * inp :      m x 1 logical vector
 *
 * Ulf Griesmann, NIST, June 2013
 */

#include <math.h>
#include <string.h>
#include "mex.h"

#ifdef __GNUC__
   #define RESTRICT __restrict
   #define INLINE __inline__
#else
   #define RESTRICT
   #define INLINE
#endif


/*-- local prototypes -----------------------------------------*/

static INLINE int
in_polygon(int N, double * RESTRICT pol, double X, double Y);


/*-------------------------------------------------------------*/

void 
mexFunction(int nlhs, mxArray *plhs[], 
	    int nrhs, const mxArray *prhs[])
{
   double *poly;              /* polygon data */
   double *xy;                /* array of points */
   mxLogical *inp;            /* pointer to output data */
   int k, Np, Mp, Nxy, Mxy;

   /* 
    * check number of arguments
    */
   if (nrhs < 2) {
      mexErrMsgTxt("isinpolygon :  missing input argument(s).");
   }

   /*
    * check polygon
    */
   Np = mxGetN(prhs[0]);
   Mp = mxGetM(prhs[0]);
   if (Mp < 3 || Np != 2) {
      mexErrMsgTxt("isinpolygon :  empty input polygon or wrong layout.");
   }
   poly = mxGetData(prhs[0]);

   /*
    * check array of points
    */
   Nxy = mxGetN(prhs[1]);
   Mxy = mxGetM(prhs[1]);
   if (Nxy != 2) {
      mexErrMsgTxt("isinpolygon :  polygon vertex array has wrong layout.");
   }
   xy = mxGetData(prhs[1]);

   /* 
    * create output array 
    */
   plhs[0] = mxCreateLogicalMatrix(Mxy, 1);
   inp = (mxLogical *)mxGetData(plhs[0]);

   /* 
    * check points 
    */
   for (k=0; k<Mxy; k++) {
      inp[k] = (mxLogical)in_polygon(Mp, poly, xy[k], xy[k+Mxy]); 
   }
}


/* Return != 0 if a point is inside the polygon
 * N vertices make up the polygon pol.
 *
 * Algorithm from Paul Bourke, http://paulbourke.net/geometry
 */
static INLINE int 
in_polygon(int N, double * RESTRICT pol, double X, double Y)
{
   int i, j, c = 0;
   register double * RESTRICT xp, * RESTRICT yp;

   /* 
    * point to x and y values of polygon vertices 
    * Note: xy is transposed !
    */
   xp = pol;
   yp = pol + N;

   for (i = 0, j = N-1; i < N; j = i++) {
      if (( ((yp[i] <= Y) && (Y < yp[j])) ||
	    ((yp[j] <= Y) && (Y < yp[i]))) &&
	  (X < (xp[j] - xp[i]) * (Y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
	c = !c;
   }
   return c;
}
