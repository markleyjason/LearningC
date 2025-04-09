# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_EXT_ETIME_.f"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x64-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_EXT_ETIME_.f"
*> \brief \b SECOND  Using ETIME_
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at
*            http://www.netlib.org/lapack/explore-html/
*
*  Definition:
*  ===========
*
*      REAL FUNCTION SECOND( )
*
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*>  SECOND returns the user time for a process in seconds.
*>  This version gets the time from the system function ETIME_.
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
      REAL FUNCTION SECOND( )
*
*  -- LAPACK auxiliary routine --
*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..
*=====================================================================
*
*     .. Local Scalars ..
      REAL               T1
*     ..
*     .. Local Arrays ..
      REAL               TARRAY( 2 )
*     ..
*     .. External Functions ..
      REAL               ETIME_
      EXTERNAL           ETIME_
*     ..
*     .. Executable Statements ..
*
      T1 = ETIME_( TARRAY )
      SECOND = TARRAY( 1 )
      RETURN
*
*     End of SECOND
*
      END

