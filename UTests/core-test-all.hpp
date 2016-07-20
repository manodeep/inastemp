///////////////////////////////////////////////////////////////////////////
// Inastemp - Berenger Bramas MPCDF - 2016
// Under MIT Licence, please you must read the LICENCE file.
///////////////////////////////////////////////////////////////////////////
#ifndef CORETESTALL_HPP
#define CORETESTALL_HPP

#include "InastempConfig.h"
#include "UTester.hpp"

#include <cmath>
#include <cstring>

template < class VecType >
class TestAll : public UTester< TestAll< VecType > > {
    using Parent = UTester< TestAll< VecType > >;

    using RealType = typename VecType::RealType;
    using MaskType = typename VecType::MaskType;

    void equalToVecType(const VecType vec,
                       const VecType inReal) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(vec.at(idx), inReal.at(idx));
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        RealType realsReals[VecType::VecLength];
        inReal.storeInArray( realsReals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(reals[idx], realsReals[idx]);
        }
    }

    void equalToScalar(const VecType vec,
                       const RealType inReal) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(vec.at(idx), inReal);
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(reals[idx], inReal);
        }
    }

    void equalToScalarMask(const MaskType vec,
                           const MaskType inReal) {
        VecType vecval = VecType::IfTrue(vec, VecType(1));
        VecType realval = VecType::IfTrue(inReal, VecType(1));
        equalToVecType(vecval, realval);
    }

    void equalToArray(const VecType vec,
                      const RealType inReals[]) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(vec.at( idx), inReals[idx]);
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTEEQUAL(reals[idx], inReals[idx]);
        }
    }

    bool approxEqual(const float v1, const float v2) {
        return (std::abs(v1 - v2) / v2) <= 9.9999999999E-6f;
    }

    bool approxEqual(const double v1, const double v2) {
        return (std::abs(v1 - v2) / v2) <= 9.999999999999999E-13;
    }

    bool approxEqualLowAcc(const float v1, const float v2) {
        return (std::abs(v1 - v2) / v2) <= 9.9999999999E-2f;
    }

    bool approxEqualLowAcc(const double v1, const double v2) {
        return (std::abs(v1 - v2) / v2) <= 9.999999999999999E-5;
    }

    void approxEqualToScalar(const VecType vec,
                             const RealType inReal) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqual(vec.at( idx), inReal));
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqual(reals[idx], inReal));
        }
    }

    void approxEqualToArray(const VecType vec,
                            const RealType inReals[]) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqual(vec.at( idx), inReals[idx]));
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqual(reals[idx], inReals[idx]));
        }
    }

    void approxLowAccEqualToArray(const VecType vec,
                            const RealType inReals[]) {
        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqualLowAcc(vec.at( idx), inReals[idx]));
        }

        RealType reals[VecType::VecLength];
        vec.storeInArray( reals);

        for (int idx = 0; idx < VecType::VecLength; ++idx) {
            UASSERTETRUE(approxEqualLowAcc(reals[idx], inReals[idx]));
        }
    }

    void TestBasic() {
        equalToScalar(VecType(1), 1);
        equalToScalar(VecType(RealType(0)), 0);

        {
            RealType reals[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                reals[idx] = 1;
            }
            equalToScalar(VecType(reals), 1);
        }

        {
            RealType real = 1;
            int indirect[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                indirect[idx] = 0;
            }
            equalToScalar(VecType().setFromIndirectArray(&real, indirect), 1);
        }

        {
            RealType reals[VecType::VecLength];
            int indirect[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                indirect[idx] = idx;
                reals[idx]    = RealType(idx);
            }
            equalToArray(VecType().setFromIndirectArray(reals, indirect), reals);
        }

        {
            RealType reals[VecType::VecLength];
            int indirect[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                indirect[idx] = idx;
                reals[idx]    = RealType(idx);
            }
            equalToArray(VecType().setFromIndirectArray(reals, indirect), reals);
        }

        {
            RealType real                     = 1;
            int indirect[VecType::VecLength] = { 0 };
            equalToScalar(VecType().setFromIndirect2DArray(&real, indirect, 0, indirect), 1);
        }

        {
            RealType reals[VecType::VecLength * 2];
            int indirect1[VecType::VecLength];
            int indirect2[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                indirect1[idx]                   = idx;
                indirect2[idx]                   = 1;
                reals[idx]                       = RealType(idx);
                reals[idx + VecType::VecLength] = RealType(idx * 2);
            }
            equalToArray(VecType().setFromIndirect2DArray(reals, indirect1, 0, indirect1), reals);
            equalToArray(VecType().setFromIndirect2DArray(reals, indirect2, VecType::VecLength, indirect1), &reals[VecType::VecLength]);
        }

        {
            UASSERTEEQUAL(VecType(1).horizontalSum(), RealType(VecType::VecLength));
            UASSERTEEQUAL(VecType(10).horizontalSum(), RealType(10 * VecType::VecLength));

            UASSERTEEQUAL(VecType(1).horizontalMul(), RealType(1));
            UASSERTEEQUAL(VecType(10).horizontalMul(), RealType(pow(10, VecType::VecLength)));
        }

        {
            equalToScalar(VecType::Min(VecType(1),
                                         VecType(1)), RealType(1));
            equalToScalar(VecType::Min(VecType(RealType(0)),
                                         VecType(1)), RealType(0));
            equalToScalar(VecType::Min(VecType(1),
                                         VecType(RealType(0))), RealType(0));

            equalToScalar(VecType::Max(VecType(1),
                                         VecType(1)), RealType(1));
            equalToScalar(VecType::Max(VecType(RealType(0)),
                                         VecType(1)), RealType(1));
            equalToScalar(VecType::Max(VecType(1),
                                         VecType(RealType(0))), RealType(1));

            equalToScalar(VecType(1).abs(), RealType(1));
            equalToScalar(VecType(-1).abs(), RealType(1));
            equalToScalar(VecType(RealType(0)).abs(), RealType(0));
        }

        {
            RealType reals[VecType::VecLength];
            RealType sum = 0;
            RealType mul = 1;
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                reals[idx] = RealType(idx);
                sum += reals[idx];
                mul *= reals[idx];
            }
            UASSERTEEQUAL(VecType(reals).horizontalSum(), sum);
            UASSERTEEQUAL(VecType(reals).horizontalMul(), mul);
        }

        {
            equalToScalar(VecType::GetZero(), 0);
            equalToScalar(VecType::GetOne(), 1);
        }

        {
            RealType reals[VecType::VecLength];
            RealType expres[VecType::VecLength];
            RealType expreslowacc[VecType::VecLength];
            RealType sqrtres[VecType::VecLength];
            RealType rsqrtres[VecType::VecLength];
            for (int idx = 0; idx < VecType::VecLength; ++idx) {
                reals[idx]    = RealType(idx + 1);
                expres[idx]   = RealType(exp(reals[idx]));
                expreslowacc[idx]   = RealType(exp(reals[idx]));
                sqrtres[idx]  = RealType(sqrt(reals[idx]));
                rsqrtres[idx] = RealType(1 / sqrt(reals[idx]));
            }

            approxEqualToArray(VecType(reals).exp(), expres);
            approxLowAccEqualToArray(VecType(reals).expLowAcc(), expreslowacc);
            approxEqualToArray(VecType(reals).sqrt(), sqrtres);
            approxEqualToArray(VecType(reals).rsqrt(), rsqrtres);
        }

        {
            equalToScalar(VecType(RealType(0)).signOf(), 0);
            equalToScalar(VecType(-1).signOf(), -1);
            equalToScalar(VecType(1).signOf(), 1);
            equalToScalar(VecType(-10).signOf(), -1);
            equalToScalar(VecType(10).signOf(), 1);

            equalToScalar(VecType(RealType(0)).isPositive(), 1);
            equalToScalar(VecType(-1).isPositive(), 0);
            equalToScalar(VecType(1).isPositive(), 1);
            equalToScalar(VecType(-10).isPositive(), 0);
            equalToScalar(VecType(10).isPositive(), 1);

            equalToScalar(VecType(RealType(0)).isNegative(), 1);
            equalToScalar(VecType(-1).isNegative(), 1);
            equalToScalar(VecType(1).isNegative(), 0);
            equalToScalar(VecType(-10).isNegative(), 1);
            equalToScalar(VecType(10).isNegative(), 0);

            equalToScalar(VecType(RealType(0)).isPositiveStrict(), 0);
            equalToScalar(VecType(-1).isPositiveStrict(), 0);
            equalToScalar(VecType(1).isPositiveStrict(), 1);
            equalToScalar(VecType(-10).isPositiveStrict(), 0);
            equalToScalar(VecType(10).isPositiveStrict(), 1);

            equalToScalar(VecType(RealType(0)).isNegativeStrict(), 0);
            equalToScalar(VecType(-1).isNegativeStrict(), 1);
            equalToScalar(VecType(1).isNegativeStrict(), 0);
            equalToScalar(VecType(-10).isNegativeStrict(), 1);
            equalToScalar(VecType(10).isNegativeStrict(), 0);


            equalToScalar(VecType(RealType(0)).isZero(), 1);
            equalToScalar(VecType(RealType(0)).isNotZero(), 0);

            equalToScalar(VecType(1).isZero(), 0);
            equalToScalar(VecType(1).isNotZero(), 1);
            equalToScalar(VecType(1).isZero(), 0);
            equalToScalar(VecType(1).isNotZero(), 1);
        }
        {
            equalToScalar(VecType::IsLowerOrEqual(VecType(RealType(0)),
                                                    VecType(RealType(0))),
                          1);
            equalToScalar(VecType::IsLowerOrEqual(VecType(-1),
                                                    VecType(-1)),
                          1);
            equalToScalar(VecType::IsLowerOrEqual(VecType(-1),
                                                    VecType(1)),
                          1);
            equalToScalar(VecType::IsLowerOrEqual(VecType(1),
                                                    VecType(-1)),
                          0);

            equalToScalar(VecType::IsLower(VecType(RealType(0)),
                                             VecType(RealType(0))),
                          0);
            equalToScalar(VecType::IsLower(VecType(-1),
                                             VecType(-1)),
                          0);
            equalToScalar(VecType::IsLower(VecType(-1),
                                             VecType(1)),
                          1);
            equalToScalar(VecType::IsLower(VecType(1),
                                             VecType(-1)),
                          0);

            equalToScalar(VecType::IsGreaterOrEqual(VecType(RealType(0)),
                                                      VecType(RealType(0))),
                          1);
            equalToScalar(VecType::IsGreaterOrEqual(VecType(-1),
                                                      VecType(-1)),
                          1);
            equalToScalar(VecType::IsGreaterOrEqual(VecType(-1),
                                                      VecType(1)),
                          0);
            equalToScalar(VecType::IsGreaterOrEqual(VecType(1),
                                                      VecType(-1)),
                          1);

            equalToScalar(VecType::IsGreater(VecType(RealType(0)),
                                               VecType(RealType(0))),
                          0);
            equalToScalar(VecType::IsGreater(VecType(-1),
                                               VecType(-1)),
                          0);
            equalToScalar(VecType::IsGreater(VecType(-1),
                                               VecType(1)),
                          0);
            equalToScalar(VecType::IsGreater(VecType(1),
                                               VecType(-1)),
                          1);

            equalToScalar(VecType::IsEqual(VecType(RealType(0)),
                                             VecType(RealType(0))),
                          1);
            equalToScalar(VecType::IsEqual(VecType(-1),
                                             VecType(-1)),
                          1);
            equalToScalar(VecType::IsEqual(VecType(-1),
                                             VecType(1)),
                          0);
            equalToScalar(VecType::IsEqual(VecType(1),
                                             VecType(-1)),
                          0);

            equalToScalar(VecType::IsNotEqual(VecType(RealType(0)),
                                                VecType(RealType(0))),
                          0);
            equalToScalar(VecType::IsNotEqual(VecType(-1),
                                                VecType(-1)),
                          0);
            equalToScalar(VecType::IsNotEqual(VecType(-1),
                                                VecType(1)),
                          1);
            equalToScalar(VecType::IsNotEqual(VecType(1),
                                                VecType(-1)),
                          1);
        }
        {
            const MaskType trueMask(true);
            const MaskType falseMask(false);

            equalToScalarMask(VecType(RealType(0)).isPositiveMask(), trueMask);
            equalToScalarMask(VecType(-1).isPositiveMask(), falseMask);
            equalToScalarMask(VecType(1).isPositiveMask(), trueMask);
            equalToScalarMask(VecType(-10).isPositiveMask(), falseMask);
            equalToScalarMask(VecType(10).isPositiveMask(), trueMask);

            equalToScalarMask(VecType(RealType(0)).isNegativeMask(), trueMask);
            equalToScalarMask(VecType(-1).isNegativeMask(), trueMask);
            equalToScalarMask(VecType(1).isNegativeMask(), falseMask);
            equalToScalarMask(VecType(-10).isNegativeMask(), trueMask);
            equalToScalarMask(VecType(10).isNegativeMask(), falseMask);

            equalToScalarMask(VecType(RealType(0)).isPositiveStrictMask(), falseMask);
            equalToScalarMask(VecType(-1).isPositiveStrictMask(), falseMask);
            equalToScalarMask(VecType(1).isPositiveStrictMask(), trueMask);
            equalToScalarMask(VecType(-10).isPositiveStrictMask(), falseMask);
            equalToScalarMask(VecType(10).isPositiveStrictMask(), trueMask);

            equalToScalarMask(VecType(RealType(0)).isNegativeStrictMask(), falseMask);
            equalToScalarMask(VecType(-1).isNegativeStrictMask(), trueMask);
            equalToScalarMask(VecType(1).isNegativeStrictMask(), falseMask);
            equalToScalarMask(VecType(-10).isNegativeStrictMask(), trueMask);
            equalToScalarMask(VecType(10).isNegativeStrictMask(), falseMask);


            equalToScalarMask(VecType(RealType(0)).isZeroMask(), trueMask);
            equalToScalarMask(VecType(RealType(0)).isNotZeroMask(), falseMask);

            equalToScalarMask(VecType(1).isZeroMask(), falseMask);
            equalToScalarMask(VecType(1).isNotZeroMask(), trueMask);
            equalToScalarMask(VecType(1).isZeroMask(), falseMask);
            equalToScalarMask(VecType(1).isNotZeroMask(), trueMask);
        }

        {
            const MaskType trueMask(true);
            const MaskType falseMask(false);

            equalToScalarMask(VecType::IsLowerOrEqualMask(VecType(RealType(0)),
                                                            VecType(RealType(0))),
                              trueMask);
            equalToScalarMask(VecType::IsLowerOrEqualMask(VecType(-1),
                                                            VecType(-1)),
                              trueMask);
            equalToScalarMask(VecType::IsLowerOrEqualMask(VecType(-1),
                                                            VecType(1)),
                              trueMask);
            equalToScalarMask(VecType::IsLowerOrEqualMask(VecType(1),
                                                            VecType(-1)),
                              falseMask);

            equalToScalarMask(VecType::IsLowerMask(VecType(RealType(0)),
                                                     VecType(RealType(0))),
                              falseMask);
            equalToScalarMask(VecType::IsLowerMask(VecType(-1),
                                                     VecType(-1)),
                              falseMask);
            equalToScalarMask(VecType::IsLowerMask(VecType(-1),
                                                     VecType(1)),
                              trueMask);
            equalToScalarMask(VecType::IsLowerMask(VecType(1),
                                                     VecType(-1)),
                              falseMask);

            equalToScalarMask(VecType::IsGreaterOrEqualMask(VecType(RealType(0)),
                                                              VecType(RealType(0))),
                              trueMask);
            equalToScalarMask(VecType::IsGreaterOrEqualMask(VecType(-1),
                                                              VecType(-1)),
                              trueMask);
            equalToScalarMask(VecType::IsGreaterOrEqualMask(VecType(-1),
                                                              VecType(1)),
                              falseMask);
            equalToScalarMask(VecType::IsGreaterOrEqualMask(VecType(1),
                                                              VecType(-1)),
                              trueMask);

            equalToScalarMask(VecType::IsGreaterMask(VecType(RealType(0)),
                                                       VecType(RealType(0))),
                              falseMask);
            equalToScalarMask(VecType::IsGreaterMask(VecType(-1),
                                                       VecType(-1)),
                              falseMask);
            equalToScalarMask(VecType::IsGreaterMask(VecType(-1),
                                                       VecType(1)),
                              falseMask);
            equalToScalarMask(VecType::IsGreaterMask(VecType(1),
                                                       VecType(-1)),
                              trueMask);

            equalToScalarMask(VecType::IsEqualMask(VecType(RealType(0)),
                                                     VecType(RealType(0))),
                              trueMask);
            equalToScalarMask(VecType::IsEqualMask(VecType(-1),
                                                     VecType(-1)),
                              trueMask);
            equalToScalarMask(VecType::IsEqualMask(VecType(-1),
                                                     VecType(1)),
                              falseMask);
            equalToScalarMask(VecType::IsEqualMask(VecType(1),
                                                     VecType(-1)),
                              falseMask);

            equalToScalarMask(VecType::IsNotEqualMask(VecType(RealType(0)),
                                                        VecType(RealType(0))),
                              falseMask);
            equalToScalarMask(VecType::IsNotEqualMask(VecType(-1),
                                                        VecType(-1)),
                              falseMask);
            equalToScalarMask(VecType::IsNotEqualMask(VecType(-1),
                                                        VecType(1)),
                              trueMask);
            equalToScalarMask(VecType::IsNotEqualMask(VecType(1),
                                                        VecType(-1)),
                              trueMask);
        }

        {
            equalToScalar(VecType(RealType(1)).floor(), std::floor(RealType(1)));
            equalToScalar(VecType(RealType(1.5)).floor(), std::floor(RealType(1.5)));
            equalToScalar(VecType(RealType(1.9)).floor(), std::floor(RealType(1.9)));
            equalToScalar(VecType(RealType(100000.9999)).floor(), std::floor(RealType(100000.9999)));
            equalToScalar(VecType(RealType(-100000.9999)).floor(), std::floor(RealType(-100000.9999)));
        }
        {
            const VecType trueMask(1);
            const VecType falseMask(RealType(0));

            equalToVecType(VecType::BitsOr(falseMask,
                                                falseMask),
                              falseMask);
            equalToVecType(VecType::BitsOr(trueMask,
                                                falseMask),
                              trueMask);
            equalToVecType(VecType::BitsOr(trueMask,
                                                trueMask),
                              trueMask);

            equalToVecType(VecType::BitsAnd(falseMask,
                                                 falseMask),
                              falseMask);
            equalToVecType(VecType::BitsAnd(trueMask,
                                                 falseMask),
                              falseMask);
            equalToVecType(VecType::BitsAnd(trueMask,
                                                 trueMask),
                              trueMask);


            equalToVecType(VecType::BitsXor(falseMask,
                                                 falseMask),
                              falseMask);
            equalToVecType(VecType::BitsXor(trueMask,
                                                 falseMask),
                              trueMask);
            equalToVecType(VecType::BitsXor(trueMask,
                                                 trueMask),
                              falseMask);


            equalToVecType(VecType::BitsNotAnd(falseMask,
                                                    falseMask),
                              falseMask);
            equalToVecType(VecType::BitsNotAnd(trueMask,
                                                    falseMask),
                              falseMask);
            equalToVecType(VecType::BitsNotAnd(trueMask,
                                                    trueMask),
                              falseMask);
            equalToVecType(VecType::BitsNotAnd(falseMask,trueMask),
                              trueMask);
        }
        {
            equalToScalar(VecType(0.) + VecType(0.),0);
            equalToScalar(VecType(0.) + VecType(10.),10);
            equalToScalar(VecType(10.) + VecType(10.),20);
            equalToScalar(VecType(10.) + VecType(0.),10);

            equalToScalar(VecType(0.) - VecType(0.),0);
            equalToScalar(VecType(0.) - VecType(10.),-10);
            equalToScalar(VecType(10.) - VecType(10.),0);
            equalToScalar(VecType(10.) - VecType(0.),10);

            equalToScalar(VecType(0.) * VecType(0.),0);
            equalToScalar(VecType(0.) * VecType(10.),0);
            equalToScalar(VecType(10.) * VecType(10.),100);
            equalToScalar(VecType(10.) * VecType(0.),0);

            equalToScalar(VecType(0.) / VecType(10.),0);
            equalToScalar(VecType(10.) / VecType(10.),1);
        }
        {
            equalToScalar(VecType(0.) += VecType(0.),0);
            equalToScalar(VecType(0.) += VecType(10.),10);
            equalToScalar(VecType(10.) += VecType(10.),20);
            equalToScalar(VecType(10.) += VecType(0.),10);

            equalToScalar(VecType(0.) -= VecType(0.),0);
            equalToScalar(VecType(0.) -= VecType(10.),-10);
            equalToScalar(VecType(10.) -= VecType(10.),0);
            equalToScalar(VecType(10.) -= VecType(0.),10);

            equalToScalar(VecType(0.) *= VecType(0.),0);
            equalToScalar(VecType(0.) *= VecType(10.),0);
            equalToScalar(VecType(10.) *= VecType(10.),100);
            equalToScalar(VecType(10.) *= VecType(0.),0);

            equalToScalar(VecType(0.) /= VecType(10.),0);
            equalToScalar(VecType(10.) /= VecType(10.),1);
        }
        {
            equalToScalar(-VecType(-4.),4.);
            equalToScalar(-VecType(4.),-4.);
            VecType a = 1.;
            equalToScalar(-a,-1.);
            equalToScalar((-1.) * a,-1.);
            a = VecType(-1.);
            equalToScalar(-a,1.);
            equalToScalar((-1.) * a,1.);
        }

        {
            equalToScalar(VecType(1.).pow(0),1.);
            equalToScalar(VecType(1.).pow(1),1.);
            equalToScalar(VecType(1.).pow(2),1.);

            equalToScalar(VecType(2.).pow(2),4.);

            equalToScalar(VecType(5.).pow(10),RealType(std::pow(5., 10)));
            equalToScalar(VecType(2.).pow(12),RealType(std::pow(2., 12)));
        }
    }

    void SetTests() {
        Parent::AddTest(&TestAll::TestBasic, "Basic test for vec type");
    }
};

#endif