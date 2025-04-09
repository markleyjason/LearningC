# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/SRC/la_xisnan.F90"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:\\Users\\markl\\source\\repos\\LearningC\\vcpkg_installed\\x86-windows\\vcpkg\\blds\\lapack-reference\\x86-windows-dbg//"
# 1 "C:/Users/markl/source/repos/LearningC/vcpkg_installed/x86-windows/vcpkg/blds/lapack-reference/src/v3.11.0-5e6de67bfb.clean/SRC/la_xisnan.F90"
module LA_XISNAN
   interface LA_ISNAN

   module procedure SISNAN
   module procedure DISNAN

   end interface

contains
   
   logical function SISNAN( x )
   use LA_CONSTANTS, only: wp=>sp





   real(wp) :: x





   sisnan = SLAISNAN(x,x)

   contains
   logical function SLAISNAN( x, y )
   use LA_CONSTANTS, only: wp=>sp
   real(wp) :: x, y
   SLAISNAN = ( x.ne.y )
   end function SLAISNAN

   end function SISNAN

   logical function DISNAN( x )
   use LA_CONSTANTS, only: wp=>dp





   real(wp) :: x





   DISNAN = DLAISNAN(x,x)

   contains
   logical function DLAISNAN( x, y )
   use LA_CONSTANTS, only: wp=>dp
   real(wp) :: x, y
   DLAISNAN = ( x.ne.y )
   end function DLAISNAN

   end function DISNAN

end module LA_XISNAN
