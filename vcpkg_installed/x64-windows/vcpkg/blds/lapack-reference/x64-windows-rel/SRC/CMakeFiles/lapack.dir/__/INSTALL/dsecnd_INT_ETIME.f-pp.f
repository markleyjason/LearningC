# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/dsecnd_INT_ETIME.f"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/dsecnd_INT_ETIME.f"
*> \brief \b DSECND Using the INTERNAL function ETIME.
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at
*            http://www.netlib.org/lapack/explore-html/
*
*  Definition:
*  ===========
*
*      DOUBLE PRECISION FUNCTION DSECND( )
*
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*>  DSECND returns the user time for a process in seconds.
*>  This version gets the time from the INTERNAL function ETIME.
*> \endverbatim
*
*  Authors:
*  ========
*
*> \author Univ. of Tennessee
*> \author Univ. of California Berkeley
*> \author Univ. of Colorado Denver
*> \author NAG Ltd.
*
*> \ingroup auxOTHERauxiliary
*
*  =====================================================================
      DOUBLE PRECISION FUNCTION DSECND( )
*
*  -- LAPACK auxiliary routine --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*
* =====================================================================
*
*     .. Local Scalars ..
      REAL               T1
*     ..
*     .. Local Arrays ..
      REAL               TARRAY( 2 )
*     ..
*     .. Intrinsic Functions ..
      REAL               ETIME
      INTRINSIC          ETIME
*     ..
*     .. Executable Statements ..
*
      T1 = ETIME( TARRAY )
      DSECND = TARRAY( 1 )
      RETURN
*
*     End of DSECND
*
      END
