# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_INT_CPU_TIME.f"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_INT_CPU_TIME.f"
*> \brief \b SECOND Using INTERNAL function CPU_TIME.
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
*>  This version gets the time from the INTERNAL function CPU_TIME.
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
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*
* =====================================================================
*
*     .. Local Scalars ..
*
      REAL T
*
* .. Intrinsic Functions ..
*
      INTRINSIC CPU_TIME
*
* .. Executable Statements .. *
*
      CALL CPU_TIME( T )
      SECOND = T
      RETURN
*
*     End of SECOND
*
      END
