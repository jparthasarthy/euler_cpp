#ifndef EULER_CPP_BIGINTIMPL_H
#define EULER_CPP_BIGINTIMPL_H

#include <cstdint>
#include <array>
#include <vector>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>
#include <string>

#include "BigIntUtility.h"

namespace bigint {
    namespace impl {

        class BigIntImpl {

            // TODO:: divide, mod, pow, add, subtract, multiply
            // TODO:: Bitwise operators
            // TODO:: Ask someone to verify if the move is working as expected
            // TODO:: Make sure the result of pow is moved properly
            // TODO:: Check out testing with catch2
            // http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

        public:
            int GetInt(int n) const ;
            int FirstNonZeroIntIndex() const;

            int sign_num_; // sign of the bigint - 0 is for 0 BigIntImpl, -1 is negative, 1 is positive
            uint32_t *magnitude_; // dynamic array stores int in big-endian order
            int size_ = 0; // count of array elements in magnitude_

            // Constructors / destructors
            BigIntImpl();

            ~BigIntImpl();

            explicit BigIntImpl(int num);

            explicit BigIntImpl(int64_t num);

            explicit BigIntImpl(std::string const &value);

            BigIntImpl(const BigIntImpl &bigint);

            BigIntImpl(BigIntImpl &&bigint) noexcept;

            BigIntImpl(uint32_t digits[], int size, int sign_num); // assumes digits has already been dynamically allocated

            // Copy / move operators
            BigIntImpl &operator=(const BigIntImpl &bigint);

            BigIntImpl &operator=(BigIntImpl &&bigint) noexcept;

            std::vector<int> magnitude() const { return std::vector<int>(magnitude_, magnitude_ + size_); };

            int64_t Int64Value() const ;

            std::string ToString() const;

            void Print() const;

            // Comparison
            bool Equals(const BigIntImpl &bigint) const;

            bool operator==(const BigIntImpl &bigint) const { return this->Equals(bigint); }

            bool operator!=(const BigIntImpl &bigint) const { return !(this->Equals(bigint)); }

            bool operator<(const BigIntImpl &bigint) const;

            bool operator>(const BigIntImpl &bigint) const { return (bigint < (*this)); }

            bool operator<=(const BigIntImpl &bigint) const { return !(bigint < (*this)); }

            bool operator>=(const BigIntImpl &bigint) const { return !(bigint > (*this)); }

            bool IsZero() const { return sign_num_ == 0; };

            // Math
            BigIntImpl Abs() const;

            BigIntImpl Pow(int exponent) const; // 0^0 is 1 in this case // TODO:: Finish

            BigIntImpl Divide(BigIntImpl const &divisor, BigIntImpl &remainder) const; // returns floor division

            BigIntImpl ShiftLeft(int shift) const;

            BigIntImpl ShiftRight(int shift) const; //TODO::FINISH

        };
    } // impl
} // bigint

#endif //EULER_CPP_BIGINTIMPL_H
