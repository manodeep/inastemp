///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef INAVECSXAFLOAT_HPP
#define INAVECSXAFLOAT_HPP

#include "InaIfElse.hpp"
#include "InaUtils.hpp"
#include "InaFastExp.hpp"

#include <velintrin.h>
#include <cmath>
#include <initializer_list>
#include <limits>

// Forward declarations
template <class RealType>
class InaVecMaskSXA;

template <class RealType>
class InaVecSXA;


// Mask type
template <>
class InaVecMaskSXA<float> {
    __vm512 mask;

    static unsigned long int _vel_pcvm_sml_512(__vm512 vmy, int vl) {
        return _vel_pcvm_sml(((__vm256*)&vmy)[0], vl)
                + _vel_pcvm_sml(((__vm256*)&vmy)[1], vl);
    }

public:
    // Classic constructors
    inline InaVecMaskSXA() {
        mask = _vel_xorm_MMM(mask,mask);
    }

    inline InaVecMaskSXA(const InaVecMaskSXA& inMask){
        mask = inMask.mask;
    }

    inline InaVecMaskSXA& operator=(const InaVecMaskSXA& inMask){
        mask = inMask.mask;
        return *this;
    }

    // Native data type compatibility
    inline /*not explicit*/ InaVecMaskSXA(const __vm512 inMask)
        : InaVecMaskSXA() {
        mask = (inMask);
    }

    inline InaVecMaskSXA& operator=(const __vm512 inMask){
        mask = inMask;
        return (*this);
    }

    inline explicit operator __vm512() const{
        return mask;
    }

    inline __vm512 getMask() const{
        return mask;
    }

    // Bool data type compatibility
    inline explicit InaVecMaskSXA(const bool inBool) : InaVecMaskSXA() {
        mask = (inBool? _vel_pvfmkat_Ml(0xFFFFFFFFU) : _vel_pvfmkat_Ml(0));
    }

    inline InaVecMaskSXA& operator=(const bool inBool){
        mask = (inBool? _vel_pvfmkat_Ml(0xFFFFFFFFU) : _vel_pvfmkat_Ml(0));
        return (*this);
    }

    // Binary methods
    inline InaVecMaskSXA Not() const{
        return _vel_negm_MM(mask);
    }

    inline bool isAllTrue() const{
        return _vel_pcvm_sml_512(mask, 512) == 512*8*8;
    }

    inline bool isAllFalse() const{
        // true if all zero
        return _vel_pcvm_sml_512(mask, 512) == 0;
    }

    // Float args methods
    inline static InaVecMaskSXA And(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_andm_MMM(inMask1.mask,inMask2.mask);
    }

    inline static InaVecMaskSXA NotAnd(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_andm_MMM(_vel_xorm_MMM(inMask1.mask, _vel_pvfmkat_Ml(0xFFFFFFFFU)),inMask2.mask);
    }

    inline static InaVecMaskSXA Or(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_orm_MMM(inMask1.mask,inMask2.mask);
    }

    inline static InaVecMaskSXA Xor(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_xorm_MMM(inMask1.mask,inMask2.mask);
    }

    inline static bool IsEqual(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_pcvm_sml_512(_vel_xorm_MMM(inMask1.mask,inMask2.mask), 512) == 0;
    }

    inline static bool IsNotEqual(const InaVecMaskSXA& inMask1, const InaVecMaskSXA& inMask2){
        return _vel_pcvm_sml_512(_vel_xorm_MMM(inMask1.mask,inMask2.mask), 512) != 0;
    }
};

// Mask must have operators
inline InaVecMaskSXA<float> operator&(const InaVecMaskSXA<float>& inMask1, const InaVecMaskSXA<float>& inMask2){
    return InaVecMaskSXA<float>::And(inMask1, inMask2);
}

inline InaVecMaskSXA<float> operator|(const InaVecMaskSXA<float>& inMask1, const InaVecMaskSXA<float>& inMask2){
    return InaVecMaskSXA<float>::Or(inMask1, inMask2);
}

inline InaVecMaskSXA<float> operator^(const InaVecMaskSXA<float>& inMask1, const InaVecMaskSXA<float>& inMask2){
    return InaVecMaskSXA<float>::Xor(inMask1, inMask2);
}

inline bool operator==(const InaVecMaskSXA<float>& inMask1, const InaVecMaskSXA<float>& inMask2){
    return InaVecMaskSXA<float>::IsEqual(inMask1, inMask2);
}

inline bool operator!=(const InaVecMaskSXA<float>& inMask1, const InaVecMaskSXA<float>& inMask2){
    return InaVecMaskSXA<float>::IsNotEqual(inMask1, inMask2);
}

// Vec type
template <>
class InaVecSXA<float> {
protected:
    __vr vec;

    static __vm512 _vel_vfmklgt_mvl_512(__vr vz, int vl){
        return __vm512();
    }

    static __vm512 _vel_vans_vvvl(__vm512 v1, __vm512 v2, int vl){
        return __vm512();
    }

public:
    using VecRawType           = __vr;
    using MaskType             = InaVecMaskSXA<float>;
    using RealType             = float;
    static const int Alignement= 1;
    static const bool IsOfFixedSize = true;

    static constexpr int GetVecLength(){
        return 512;
    }

    inline InaVecSXA() {
        vec = _vel_vbrds_vsl(0,512);
    }
    inline InaVecSXA(const InaVecSXA& inVec){
        vec = inVec.vec;
    }

    inline InaVecSXA& operator=(const InaVecSXA& inVec){
        vec = inVec.vec;
        return *this;
    }

    // Constructor from raw type
    inline /*not explicit*/ InaVecSXA(const __vr inVec)
        : InaVecSXA() {
        vec = (inVec);
    }

    inline InaVecSXA& operator=(const __vr inVec){
        vec = inVec;
        return *this;
    }

    inline void setFromRawType(const __vr inVec){
        vec = inVec;
    }

    inline explicit operator __vr() const{
        return vec;
    }

    inline __vr getVec() const{
        return vec;
    }

    // Constructor from scalar
    inline /*not explicit*/ InaVecSXA(const float val)
        : InaVecSXA() {
        vec = _vel_vbrds_vsl(val,512);
    }

    inline InaVecSXA& operator=(const float val){
        vec = _vel_vbrds_vsl(val,512);
        return *this;
    }

    inline void setFromScalar(const float val){
        vec = _vel_vbrds_vsl(val,512);
    }

    // Constructor from vec
    inline InaVecSXA(const std::initializer_list<float> lst)
        : InaVecSXA(lst.begin()){
    }

    inline explicit InaVecSXA(const float ptr[])
        : InaVecSXA() {
        vec = _vel_vld_vssl(8, ptr, 512);
    }

    inline InaVecSXA& setFromArray(const float ptr[]){
        vec = _vel_vld_vssl(8, ptr, 512);
        return *this;
    }

    inline InaVecSXA& setFromAlignedArray(const float ptr[]){
        vec = _vel_vld_vssl(8, ptr, 512);
        return *this;
    }

    inline InaVecSXA& setFromIndirectArray(const float values[], const int inIndirection[]) {
        __vr offset = _vel_vld_vssl(4, inIndirection, 512);
        vec = _vel_vldlsx_vssvl(0, values, offset, 512);
        return *this;
    }

    inline InaVecSXA& setFromIndirect2DArray(const float inArray[], const int inIndirection1[],
                                 const int inLeadingDimension, const int inIndirection2[]){
        __vr offset = _vel_vmulul_vvvl(_vel_vld_vssl(4, inIndirection1, 512),
                                      _vel_vld_vssl(4, inIndirection2, 512),
                                      512);
        vec = _vel_vldlsx_vssvl(0, inArray, offset, 512);
        return *this;
    }

    // Move back to array
    inline void storeInArray(float ptr[]) const {
        _vel_vst_vssl(vec, 8, ptr, 512);
    }

    inline void storeInAlignedArray(float ptr[]) const {
        _vel_vst_vssl(vec, 8, ptr, 512);
    }

    // Acce to individual values
    inline float at(const int index) const {
        return _vel_lvsl_svs(vec, index);
    }

    // Horizontal operation
    inline float horizontalSum() const {
      return _vel_lvsl_svs(_vel_vfsums_vvl(vec, 512),0);
    }

    inline float horizontalMul() const {
        float sum = at(0);
        for(int idx = 1 ; idx < int(GetVecLength()) ; ++idx){
            sum *= at(idx);
        }
        return sum;
    }

    inline InaVecSXA sqrt() const {
        return _vel_vfsqrts_vvl(vec, 512);
    }

    inline InaVecSXA exp() const {
        const __vr COEFF_LOG2E = _vel_vbrds_vsl(float(InaFastExp::CoeffLog2E()), 512);
        const __vr COEFF_A     = _vel_vbrds_vsl(float(InaFastExp::CoeffA32()), 512);
        const __vr COEFF_B     = _vel_vbrds_vsl(float(InaFastExp::CoeffB32()), 512);
        const __vr COEFF_P5_A  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_5()), 512);
        const __vr COEFF_P5_B  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_4()), 512);
        const __vr COEFF_P5_C  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_3()), 512);
        const __vr COEFF_P5_D  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_2()), 512);
        const __vr COEFF_P5_E  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_1()), 512);
        const __vr COEFF_P5_F  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient6_0()), 512);

        __vr x = _vel_vfmuls_vvvl(vec, COEFF_LOG2E, 512);

        const __vr fractional_part = _vel_vfsubs_vvvl(x, InaVecSXA(x).floor().vec, 512);

        __vr factor = _vel_vfadds_vvvl(
                         _vel_vfmuls_vvvl(_vel_vfadds_vvvl( _vel_vfmuls_vvvl(_vel_vfadds_vvvl(
                         _vel_vfmuls_vvvl(_vel_vfadds_vvvl( _vel_vfmuls_vvvl(_vel_vfadds_vvvl(
                         _vel_vfmuls_vvvl(COEFF_P5_A, fractional_part, 512),
                         COEFF_P5_B, 512), fractional_part, 512), COEFF_P5_C, 512),fractional_part, 512),
                         COEFF_P5_D, 512), fractional_part, 512), COEFF_P5_E, 512),fractional_part, 512),
                         COEFF_P5_F, 512);

        x = _vel_vfsubs_vvvl(x,factor, 512);

        x = _vel_vfadds_vvvl(_vel_vfmuls_vvvl(COEFF_A, x, 512), COEFF_B, 512);

        __vr castedInteger = _vel_vcvtldrz_vvl(x, 512);

        return (castedInteger); // Automatically reinterpret not cast
    }

    inline InaVecSXA expLowAcc() const {
        const __vr COEFF_LOG2E = _vel_vbrds_vsl(float(InaFastExp::CoeffLog2E()), 512);
        const __vr COEFF_A     = _vel_vbrds_vsl(float(InaFastExp::CoeffA32()), 512);
        const __vr COEFF_B     = _vel_vbrds_vsl(float(InaFastExp::CoeffB32()), 512);
        const __vr COEFF_P5_D  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient3_2()), 512);
        const __vr COEFF_P5_E  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient3_1()), 512);
        const __vr COEFF_P5_F  = _vel_vbrds_vsl(float(InaFastExp::GetCoefficient3_0()), 512);

        __vr x = _vel_vfmuls_vvvl(vec, COEFF_LOG2E, 512);

        const __vr fractional_part = _vel_vfsubs_vvvl(x, InaVecSXA(x).floor().vec, 512);

        __vr factor = _vel_vfadds_vvvl(_vel_vfmuls_vvvl(_vel_vfadds_vvvl(
                         _vel_vfmuls_vvvl(fractional_part, COEFF_P5_D, 512),
                                         COEFF_P5_E, 512), fractional_part, 512),
                                         COEFF_P5_F, 512);

        x = _vel_vfsubs_vvvl(x,factor, 512);

        x = _vel_vfadds_vvvl(_vel_vfmuls_vvvl(COEFF_A, x, 512), COEFF_B, 512);

        __vr castedInteger = _vel_vcvtldrz_vvl(x, 512);

        return (castedInteger); // Automatically reinterpret not cast
    }

    inline InaVecSXA rsqrt() const {
        // svrsqrte_f64(vec); seems low accurate
        return  _vel_vrsqrts_vvl(vec, 512);
    }

    inline InaVecSXA abs() const {
        return _vel_vand_vvvl( vec, _vel_pvbrd_vsl(0x7FFFFFFF7FFFFFFFUL, 256), 256);
    }

    inline InaVecSXA floor() const {
        __vm512 maskInLongInt = _vel_andm_MMM(
                                _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( _vel_vbrds_vsl(float(std::numeric_limits<int>::min()), 512), vec, 512), 512),
                                _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( vec, _vel_vbrds_vsl(float(std::numeric_limits<int>::max()), 512), 512), 512));
        __vr vecConvLongInt = _vel_vcvtldrz_vvl(vec, 512);
        __vr vecConvLongIntFloat = _vel_vcvtdl_vvl(vec, 512);
        __vm512 maskNegative = _vel_vfmklgt_mvl_512(_vel_vcmpsl_vsvl( 0, vec, 512), 512);
        return _vel_vmrgw_vvvMl(_vel_vmrgw_vvvMl(_vel_vfsubs_vvvl( vecConvLongIntFloat, _vel_vbrds_vsl(1, 512), 512),
                                               vecConvLongIntFloat,
                                               maskNegative,
                                               512),
                               vec,
                               maskInLongInt,
                               512);
    }

    inline InaVecSXA signOf() const {
        return _vel_vfcmps_vvvl(vec, _vel_vbrds_vsl(0, 512), 512);
    }

    inline InaVecSXA isPositive() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isPositiveMask()), 512);
    }

    inline InaVecSXA isNegative() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isNegativeMask()), 512);
    }

    inline InaVecSXA isPositiveStrict() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isPositiveStrictMask()), 512);
    }

    inline InaVecSXA isNegativeStrict() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isNegativeStrictMask()), 512);
    }

    inline InaVecSXA isZero() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isZeroMask()), 512);
    }

    inline InaVecSXA isNotZero() const {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(isNotZeroMask()), 512);
    }

    inline InaVecMaskSXA<float> isPositiveMask() const {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( _vel_vbrds_vsl(0-std::numeric_limits<float>::epsilon(), 512), vec, 512), 512);
    }

    inline InaVecMaskSXA<float> isNegativeMask() const {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( vec, _vel_vbrds_vsl(0+std::numeric_limits<float>::epsilon(), 512), 512), 512);
    }

    inline InaVecMaskSXA<float> isPositiveStrictMask() const {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( _vel_vbrds_vsl(0-std::numeric_limits<float>::epsilon(), 512), vec, 512), 512);
    }

    inline InaVecMaskSXA<float> isNegativeStrictMask() const {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( vec, _vel_vbrds_vsl(0+std::numeric_limits<float>::epsilon(), 512), 512), 512);
    }

    inline InaVecMaskSXA<float> isZeroMask() const {
        return _vel_negm_MM(_vel_vfmklgt_mvl_512(_vel_vand_vvvl( _vel_pvbrd_vsl(~0UL, 256), vec, 512), 512));
    }

    inline InaVecMaskSXA<float> isNotZeroMask() const {
        return _vel_vfmklgt_mvl_512(_vel_vand_vvvl( _vel_pvbrd_vsl(~0UL, 256), vec, 512), 512);
    }

    // Static basic methods
    inline static InaVecSXA GetZero() {
        return InaVecSXA(_vel_vbrds_vsl(0, 512));
    }

    inline static InaVecSXA GetOne() {
        return InaVecSXA(_vel_vbrds_vsl(1, 512));
    }

    inline static InaVecSXA Min(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vminswsx_vvvl( inVec1.vec, inVec2.vec, 512);
    }

    inline static InaVecSXA Max(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmaxswsx_vvvl( inVec1.vec, inVec2.vec, 512);
    }

    inline static InaVecSXA IsLowerOrEqual(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsLowerOrEqualMask(inVec1, inVec2)), 512);
    }

    inline static InaVecSXA IsLower(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsLowerMask(inVec1, inVec2)), 512);
    }

    inline static InaVecSXA IsGreaterOrEqual(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsGreaterOrEqualMask(inVec1, inVec2)), 512);
    }

    inline static InaVecSXA IsGreater(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsGreaterMask(inVec1, inVec2)), 512);
    }

    inline static InaVecSXA IsEqual(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsEqualMask(inVec1, inVec2)), 512);
    }

    inline static InaVecSXA IsNotEqual(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(1, 512), _vel_vbrds_vsl(0, 512), __vm512(IsNotEqualMask(inVec1, inVec2)), 512);
    }

    inline static InaVecMaskSXA<float> IsLowerOrEqualMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( _vel_vfsubs_vvvl(inVec1.vec, _vel_vbrds_vsl(std::numeric_limits<float>::epsilon(), 512), 512), inVec2.vec, 512), 512);
    }

    inline static InaVecMaskSXA<float> IsLowerMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( inVec1.vec, inVec2.vec, 512), 512);
    }

    inline static InaVecMaskSXA<float> IsGreaterOrEqualMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( inVec2.vec, inVec1.vec, 512), 512);
    }

    inline static InaVecMaskSXA<float> IsGreaterMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vfmklgt_mvl_512(_vel_vfcmps_vvvl( _vel_vfsubs_vvvl(inVec2.vec, _vel_vbrds_vsl(std::numeric_limits<float>::epsilon(), 512), 512), inVec1.vec, 512), 512);
    }

    inline static InaVecMaskSXA<float> IsEqualMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return  InaVecMaskSXA<float>::And(IsGreaterOrEqualMask(inVec1, inVec2), IsLowerOrEqualMask(inVec1, inVec2));
    }

    inline static InaVecMaskSXA<float> IsNotEqualMask(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return  InaVecMaskSXA<float>::Xor(IsGreaterOrEqualMask(inVec1, inVec2), IsLowerOrEqualMask(inVec1, inVec2));
    }

    inline static InaVecSXA BitsAnd(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vand_vvvl(inVec1.vec, inVec2.vec, 512);
    }

    inline static InaVecSXA BitsNotAnd(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vand_vvvl(_vel_vxor_vvvl(inVec1.vec, _vel_pvbrd_vsl(~0UL, 256), 512), inVec2.vec, 512);
    }

    inline static InaVecSXA BitsOr(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vor_vvvl(inVec1.vec, inVec2.vec, 512);
    }

    inline static InaVecSXA BitsXor(const InaVecSXA& inVec1, const InaVecSXA& inVec2) {
        return _vel_vxor_vvvl(inVec1.vec, inVec2.vec, 512);
    }

    inline static  const char* GetName() {
        return "InaVecSXA<float>";
    }

    inline static  InaIfElse< InaVecSXA<float> >::ThenClass If(const InaVecMaskSXA<float>& inTest) {
       return InaIfElse< InaVecSXA<float> >::IfClass().If(inTest);
    }

    inline static InaVecSXA IfElse(const InaVecMaskSXA<float>& inMask, const InaVecSXA& inIfTrue, const InaVecSXA& inIfFalse) {
        return _vel_vmrgw_vvvMl(inIfTrue.vec, inIfFalse.vec, __vm512(inMask), 512);
    }

    inline static InaVecSXA IfTrue(const InaVecMaskSXA<float>& inMask, const InaVecSXA& inIfTrue) {
        return _vel_vmrgw_vvvMl(inIfTrue.vec, _vel_vbrds_vsl(0, 512), __vm512(inMask), 512);
    }

    inline static InaVecSXA IfFalse(const InaVecMaskSXA<float>& inMask, const InaVecSXA& inIfFalse) {
        return _vel_vmrgw_vvvMl(_vel_vbrds_vsl(0, 512), inIfFalse.vec, __vm512(inMask), 512);
    }

    // Inner operators
    inline InaVecSXA<float>& operator+=(const InaVecSXA<float>& inVec){
        vec = _vel_vfadds_vvvl(vec,inVec.vec, 512);
        return *this;
    }

    inline InaVecSXA<float>& operator-=(const InaVecSXA<float>& inVec){
        vec = _vel_vfsubs_vvvl(vec,inVec.vec, 512);
        return *this;
    }

    inline InaVecSXA<float>& operator/=(const InaVecSXA<float>& inVec){
        vec = _vel_vfdivs_vvvl(vec,inVec.vec, 512);
        return *this;
    }

    inline InaVecSXA<float>& operator*=(const InaVecSXA<float>& inVec){
        vec = _vel_vfmuls_vvvl(vec,inVec.vec, 512);
        return *this;
    }

    inline InaVecSXA<float> operator-() const {
        return _vel_vxor_vvvl(vec, _vel_pvbrd_vsl(0x8000000080000000UL, 256), 512);
    }

    inline InaVecSXA<float> pow(std::size_t power) const{
        return InaUtils::FastPow<InaVecSXA<float>>(*this, power);
    }

    // Multiple sum
    template <class ... Args>
    inline static void MultiHorizontalSum(float sumRes[], const InaVecSXA<float>& inVec1,
                                          const InaVecSXA<float>& inVec2, const InaVecSXA<float>& inVec3,
                                          const InaVecSXA<float>& inVec4, const InaVecSXA<float>& inVec5,
                                          const InaVecSXA<float>& inVec6, const InaVecSXA<float>& inVec7,
                                          const InaVecSXA<float>& inVec8, Args ...args){
        MultiHorizontalSum(&sumRes[0], inVec1, inVec2, inVec3, inVec4 );
        MultiHorizontalSum(&sumRes[4], inVec5, inVec6, inVec7, inVec8 );

        MultiHorizontalSum(&sumRes[8], args... );
    }

    template <class ... Args>
    inline static void MultiHorizontalSum(float sumRes[], const InaVecSXA<float>& inVec1,
                                          const InaVecSXA<float>& inVec2, const InaVecSXA<float>& inVec3,
                                          const InaVecSXA<float>& inVec4, Args ...args){
        MultiHorizontalSum(&sumRes[0], inVec1, inVec2 );
        MultiHorizontalSum(&sumRes[2], inVec3, inVec4 );

        MultiHorizontalSum(&sumRes[4], args... );
    }

    template <class ... Args>
    inline static void MultiHorizontalSum(float sumRes[], const InaVecSXA<float>& inVec1,
                                          const InaVecSXA<float>& inVec2, Args ...args){

        MultiHorizontalSum(&sumRes[0], inVec1);
        MultiHorizontalSum(&sumRes[1], inVec2);

        MultiHorizontalSum(&sumRes[2], args... );
    }

    inline static void MultiHorizontalSum(float sumRes[], const InaVecSXA<float>& inVec){
        sumRes[0] += inVec.horizontalSum();
    }

    inline static void MultiHorizontalSum(float /*sumRes*/[]){
    }
};

// Bits operators
inline InaVecSXA<float> operator&(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::BitsAnd(inVec1, inVec2);
}

inline InaVecSXA<float> operator|(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::BitsOr(inVec1, inVec2);
}

inline InaVecSXA<float> operator^(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::BitsXor(inVec1, inVec2);
}

// Dual operators
inline InaVecSXA<float> operator+(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return _vel_vfadds_vvvl(inVec1.getVec(), inVec2.getVec(), 512);
}

inline InaVecSXA<float> operator-(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return _vel_vfsubs_vvvl(inVec1.getVec(), inVec2.getVec(), 512);
}

inline InaVecSXA<float> operator/(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return _vel_vfdivs_vvvl(inVec1.getVec(), inVec2.getVec(), 512);
}

inline InaVecSXA<float> operator*(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return _vel_vfmuls_vvvl(inVec1.getVec(), inVec2.getVec(), 512);
}

// Tests and comparions
inline InaVecMaskSXA<float> operator<(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsLowerMask(inVec1,inVec2);
}

inline InaVecMaskSXA<float> operator<=(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsLowerOrEqualMask(inVec1,inVec2);
}

inline InaVecMaskSXA<float> operator>(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsGreaterMask(inVec1,inVec2);
}

inline InaVecMaskSXA<float> operator>=(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsGreaterOrEqualMask(inVec1,inVec2);
}

inline InaVecMaskSXA<float> operator==(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsEqualMask(inVec1,inVec2);
}

inline InaVecMaskSXA<float> operator!=(const InaVecSXA<float>& inVec1, const InaVecSXA<float>& inVec2){
    return InaVecSXA<float>::IsNotEqualMask(inVec1,inVec2);
}


#endif
