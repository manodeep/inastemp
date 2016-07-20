###########################################################################
# Inastemp - Berenger Bramas MPCDF - 2016
# Under MIT Licence, please you must read the LICENCE file.
###########################################################################
# Doc for intel :
# https://software.intel.com/en-us/articles/performance-tools-for-software-developers-intel-compiler-options-for-sse-generation-and-processor-specific-optimizations
# 
# Doc for gcc :
# https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html
###########################################################################
macro (GetCompilerInfosCore TYPE)    
string(TOUPPER ${TYPE} UTYPE)

# The original CPP file
set(checkTypeFile "${PROJECT_SOURCE_DIR}/CMakeModules/${UTYPE}/compileTest${UTYPE}.cpp")
set(checkPeFile "${PROJECT_SOURCE_DIR}/CMakeModules/${UTYPE}/check${UTYPE}pe.cpp")

# Fatal error if the file does not exist
if(NOT EXISTS ${checkTypeFile})
	message(FATAL_ERROR "The GetCompilerInfosFile does not exist (${checkTypeFile})")
endif()
if(NOT EXISTS ${checkPeFile})
	message(FATAL_ERROR "The GetCompilerInfosFile does not exist (${checkPeFile})")
endif()


try_compile(COMPILE_RESULT  ${CMAKE_CURRENT_BINARY_DIR}
      ${checkTypeFile}
      COMPILE_DEFINITIONS "-Wno-error ${${UTYPE}_FLAGS}"
      OUTPUT_VARIABLE COMPILE_OUTPUT)

if(${COMPILE_RESULT})
    set(COMPILER_INFO_${UTYPE} ON)

    if($ENV{VERBOSE})
        message(STATUS "GetCompilerInfos -- The compiler can compile ${TYPE}")
    endif()

    try_compile(COMPILE_RESULT_PE  ${CMAKE_CURRENT_BINARY_DIR}
          ${checkPeFile}
          COMPILE_DEFINITIONS "-Wno-error ${${UTYPE}_FLAGS}"
          OUTPUT_VARIABLE COMPILE_OUTPUT_PE)

    if(${COMPILE_RESULT_PE})
        set(COMPILER_INFO_${UTYPE}_NOOP OFF)

        if($ENV{VERBOSE})
            message(STATUS "GetCompilerInfos -- The compiler has operators for ${TYPE}")
        endif()
    else()
        set(COMPILER_INFO_${UTYPE}_NOOP ON)

        if($ENV{VERBOSE})
            message(STATUS "GetCompilerInfos -- The compiler needs operators for ${TYPE} : ${COMPILE_OUTPUT_PE}")
        endif()
    endif()
else()
    set(COMPILER_INFO_${UTYPE} OFF)

    if($ENV{VERBOSE})
        message(STATUS "GetCompilerInfos -- The compiler cannot compile ${TYPE} : ${COMPILE_OUTPUT}")
    endif()
endif()

endmacro(GetCompilerInfosCore)
###########################################################################################
###########################################################################################
macro(GetCompilerInfos)

SET( ARCH_NATIVE_FLAG "-march=native" CACHE STRING "Additional flag for the compiler capacities detection"  )

# (ADD-NEW-HERE for each compilers)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    if(APPLE) # INTEL APPLE
        set(SSE3_FLAGS  "-msse3 ${ARCH_NATIVE_FLAG}")
        set(SSSE3_FLAGS  "-mssse3 ${ARCH_NATIVE_FLAG}")
        set(SSE41_FLAGS  "-msse4 -msse4.1 ${ARCH_NATIVE_FLAG}")
        set(SSE42_FLAGS  "-msse4 -msse4.2 ${ARCH_NATIVE_FLAG}")
        set(AVX_FLAGS  "-mAVX ${ARCH_NATIVE_FLAG}")
        set(AVX2_FLAGS "-march=core-avx2 ${ARCH_NATIVE_FLAG}")
        set(AVX512KNL_FLAGS "-xCOMMON-AVX512 -xMIC-AVX512 ${ARCH_NATIVE_FLAG}")
    else() # INTEL LINUX
        set(SSE3_FLAGS  "-msse3 ${ARCH_NATIVE_FLAG}")
        set(SSSE3_FLAGS "-mssse3 ${ARCH_NATIVE_FLAG}")
        set(SSE41_FLAGS  "-msse4 -msse4.1 ${ARCH_NATIVE_FLAG}")
        set(SSE42_FLAGS  "-msse4 -msse4.2 ${ARCH_NATIVE_FLAG}")
        set(AVX_FLAGS  "-mAVX ${ARCH_NATIVE_FLAG}")
        set(AVX2_FLAGS "-march=core-avx2 ${ARCH_NATIVE_FLAG}")
        set(AVX512KNL_FLAGS "-xCOMMON-AVX512 -xMIC-AVX512 ${ARCH_NATIVE_FLAG}")
    endif()
else()
    if(APPLE) # GCC APPLE
        set(SSE3_FLAGS  "-msse3 ${ARCH_NATIVE_FLAG}")
        set(SSSE3_FLAGS  "-mssse3 ${ARCH_NATIVE_FLAG}")
        set(SSE41_FLAGS  "-msse4 -msse4.1 ${ARCH_NATIVE_FLAG}")
        set(SSE42_FLAGS  "-msse4 -msse4.2 ${ARCH_NATIVE_FLAG}")
        set(AVX_FLAGS  "-mavx ${ARCH_NATIVE_FLAG}")
        set(AVX2_FLAGS "-mavx2 ${ARCH_NATIVE_FLAG}")
        set(AVX512KNL_FLAGS "-mavx512f -mavx512pf -mavx512er -mavx512cd ${ARCH_NATIVE_FLAG}")
    else() # GCC LINUX
        set(SSE3_FLAGS  "-msse3 ${ARCH_NATIVE_FLAG}")
        set(SSSE3_FLAGS  "-mssse3 ${ARCH_NATIVE_FLAG}")
        set(SSE41_FLAGS  "-msse4 -msse4.1 ${ARCH_NATIVE_FLAG}")
        set(SSE42_FLAGS  "-msse4 -msse4.2 ${ARCH_NATIVE_FLAG}")
        set(AVX_FLAGS  "-mavx ${ARCH_NATIVE_FLAG}")
        set(AVX2_FLAGS "-mavx2 ${ARCH_NATIVE_FLAG}")
        set(AVX512KNL_FLAGS "-mavx512f -mavx512pf -mavx512er -mavx512cd ${ARCH_NATIVE_FLAG}")
    endif(APPLE)
endif()

# (ADD-NEW-HERE)
set(ALL_TYPES "SSE3;SSSE3;SSE41;SSE42;AVX;AVX2;AVX512KNL")

if($ENV{VERBOSE})
    foreach(TYPE ${ALL_TYPES})
        message(STATUS "GetCompilerInfos -- ${TYPE}_FLAGS = ${${TYPE}_FLAGS}")
    endforeach()
endif()

foreach(TYPE ${ALL_TYPES})
    GetCompilerInfosCore(${TYPE})
endforeach()

if($ENV{VERBOSE})    
    foreach(TYPE ${ALL_TYPES})
        message(STATUS "GetCompilerInfos -- COMPILER_INFO_${TYPE} = ${COMPILER_INFO_${TYPE}}")
    endforeach()
endif()

endmacro(GetCompilerInfos)