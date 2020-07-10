#pragma once

#include "point3.hpp"
#include "vec3.hpp"

#include "util.hpp"

#include <array>
#include <algorithm>
#include <iomanip>

namespace gm {

    template<typename Type, REQUIRES(std::is_arithmetic<Type>())>
    class Matrix4x4 {
    private:
        std::array<std::array<Type, 4>, 4> m;
    public:

        constexpr Matrix4x4
        (Type a00, Type a01, Type a02, Type a03,
         Type a10, Type a11, Type a12, Type a13,
         Type a20, Type a21, Type a22, Type a23,
         Type a30, Type a31, Type a32, Type a33)
            : m({ a00, a01, a02, a03,
                 a10, a11, a12, a13,
                 a20, a21, a22, a23,
                 a30, a31, a32, a33 }) {
        }

        auto constexpr operator()(int i, int j) -> Type& { return m[i][j]; }
        auto constexpr operator()(int i, int j) const -> Type const& { return m[i][j]; }

        auto constexpr operator==(Matrix4x4<Type> other) const -> bool {
            return m == other.m; 
        }

        auto constexpr operator!=(Matrix4x4<Type> other) const -> bool {
            return m != other.m; 
        }

        static auto constexpr fill_with(Type val) -> Matrix4x4<Type> {
            return { 
                val, val, val, val,
                val, val, val, val,
                val, val, val, val,
                val, val, val, val 
            };
        }

        constexpr Matrix4x4(Matrix4x4<Type> const& mtx) : m(mtx.m) {}
        constexpr Matrix4x4(Matrix4x4<Type>&& mtx) : m(std::move(mtx.m)) {}

        auto constexpr transpose() const -> Matrix4x4 {
            auto tmp = Matrix4x4::fill_with(1);
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    tmp.m[i][j] = m[j][i];

            return tmp;
        }

        static auto constexpr identity() -> Matrix4x4<Type> {
            return { 1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1 };
        }

        auto inverse() const -> Matrix4x4 {
            //static_assert(N == M, "Matrix is not square!");

            auto tmp = *this;
            auto invTmp = tmp.identity();

            // Switch rows around so there is a leading number in each
            // Set the diagonal to 1 by dividing the row with the leading element
            // Reduce upper right-hand entries to zero by subtracting fractions of below rows
            // This is all done in parallel to the adjoined identity matrix

            for (int i = 0; i < 4; ++i) {
                if (tmp.m[i][i] == 0) // Our row had a leading zero
                {
                    auto big = i;
                    for (int j = 0; j < 4; ++j) // Check remaining rows
                    {
                        if (std::abs(tmp.m[j][i]) > std::abs(tmp.m[big][i])) {
                            big = j; // Another row has a (absolute) larger leading value
                        }
                    }

                    if (big != i)  // The matrix wasn't singular, i.e. another row could be switched in
                    {
                        for (int k = 0; k < 4; ++k) {
                            std::swap(tmp.m[i][k], tmp.m[big][k]); // swap rows
                            std::swap(invTmp.m[i][k], invTmp.m[big][k]);
                        }
                    }
                }

                auto divisor = tmp.m[i][i];
                for (int j = 0; j < 4; ++j) {
                    tmp.m[i][j] /= divisor;
                    invTmp.m[i][j] /= divisor;
                }

                for (int j = 0; j < 4; ++j) {
                    if (j != i && tmp.m[i][i] != 0) {
                        auto coefficient = tmp.m[j][i] / tmp.m[i][i];
                        if (coefficient != 0) {
                            for (int k = 0; k < 4; ++k) {
                                tmp.m[j][k] -= coefficient * tmp.m[i][k];
                                tmp.m[j][k] = 0;
                                invTmp.m[j][k] -= coefficient * invTmp.m[i][k];
                            }

                        }
                    }
                }

            }

            return invTmp;
        }


        static auto constexpr multiply(Matrix4x4<Type> const& a, Matrix4x4<Type> const& b, Matrix4x4<Type>& c) -> void {
            // rolled up version rather than writing out the arguments
            for (uint8_t i = 0; i < 4; ++i) {
                for (uint8_t j = 0; j < 4; ++j) {
                    c.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] +
                        a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
                }
            }
        }

        auto constexpr operator*(Matrix4x4<Type> const& other) const -> Matrix4x4<Type> {
            Matrix4x4 tmp;
            multiply(*this, other, tmp);
            return tmp;
        }


        auto constexpr operator*=(Matrix4x4<Type> const& other) -> Matrix4x4<Type>& {
            Matrix4x4 tmp;
            multiply(*this, other, tmp);
            *this = tmp;
            return *this;
        }


        auto constexpr multiply(Point3<Type> const& point) const -> Point3<Type> {
            auto a = point[0] * m[0][0] + point[1] * m[1][0] + point[2] * m[2][0] + m[3][0];
            auto b = point[0] * m[0][1] + point[1] * m[1][1] + point[2] * m[2][1] + m[3][1];
            auto c = point[0] * m[0][2] + point[1] * m[1][2] + point[2] * m[2][2] + m[3][2];
            auto w = point[0] * m[0][3] + point[1] * m[1][3] + point[2] * m[2][3] + m[3][3];

            return { a / w, b / w, c / w };
        }

        auto constexpr multiply(const Vec3<Type>& vec) const -> Vec3<Type> {
            auto a = vec[0] * m[0][0] + vec[1] * m[1][0] + vec[2] * m[2][0] + m[3][0];
            auto b = vec[0] * m[0][1] + vec[1] * m[1][1] + vec[2] * m[2][1] + m[3][1];
            auto c = vec[0] * m[0][2] + vec[1] * m[1][2] + vec[2] * m[2][2] + m[3][2];
            auto w = vec[0] * m[0][3] + vec[1] * m[1][3] + vec[2] * m[2][3] + m[3][3];

            return { a, b, c };
        }

        // TODO: scalar multiplication, matrix-matrix addition and subtraction

    };
    typedef Matrix4x4<float> Matrix4x4f;

}