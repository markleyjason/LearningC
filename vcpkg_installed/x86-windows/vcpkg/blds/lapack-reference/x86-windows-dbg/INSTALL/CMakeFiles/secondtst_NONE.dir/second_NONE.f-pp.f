# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_NONE.f"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/INSTALL/second_NONE.f"
*> \brief \b SECOND returns nothing
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
*>  SECOND returns nothing instead of returning the user time for a process in seconds.
*>  If you are using that routine, it means that neither EXTERNAL ETIME,
*>  EXTERNAL ETIME_, INTERNAL ETIME, INTERNAL CPU_TIME is available  on
*>  your machine.
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
      SECOND = 0.0E+0
      RETURN
*
*     End of SECOND
*
      END
