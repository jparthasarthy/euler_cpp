#ifndef EULER_CPP_BIGINTHELPERS_H
#define EULER_CPP_BIGINTHELPERS_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <cmath>
#include <array>

#include<vector>

namespace bigint {

    namespace constants {
        const static int kDigitsPerInt_ = 9;
        const static int kBitsPerDigit_ = 3402;
        const static int kSuperRadix_ = int{0x3b9aca00};
        const static int64_t kint64Mask = int64_t{0xffffffffL};
    } // constants

    namespace error_messages {
        const static std::string kZeroLengthBigInt = "Zero length BigInt";
        const static std::string kIllegalEmbeddedSign = "Illegal embedded sign character";
        const static std::string kNegativeExponent = "Negative exponent";
        const static std::string kSuspectedOverOrUnderflow = "Suspected overflow/ underflow while computing exponent";
        const static std::string kNotImplemented = "Not implemented";
    } // error_messages

    namespace utils {

        int NumberOfDigits(int64_t num);

        int64_t Integer64Power(int64_t base, int exponent); // 0^0 = 1, returns -1 on error and negative exponents

        int TrimToNineLeastSignificantDigits(int64_t num);

        int64_t RemoveNineLeastSignificantDigits(int64_t num);

        // Destructive
        // Takes array x, shifts magnitude by kSuperRadix, and adds z, in-place (array x), used for string constructor
        // The function should always be given enough memory to insert the group
        void InsertGroup(int *x, int x_len, int z);

        // Returns the result of array x * y up the specified lengths, returns the size as z_len
        int *ArrayMultiply(const int *x, int x_len, const int *y, int y_len, int &z_len);

        int *TrustedStripLeadingZeroInts(int **array, int &size);

        int BitLength(int word);

        void PrimitiveLeftShift(uint32_t *array, int length, int shift); // assumes that array will not grow

        void PrimitiveRightShift(uint32_t *array, int length, int shift); // assumes that array will not grow

        // quotient, remainder are stored in result
        void DivideWord(uint32_t *result, uint64_t dividend, uint32_t divisor);

        // returns the carry when taking quotient - (array *x), used for division
        uint32_t MulSub(uint32_t *dividend, uint32_t const *array, int x, int array_len, int carry);

        // returns the carry when adding one multiple of array back into the dividend
        uint32_t DivAdd(uint32_t const *array, uint32_t *remainder, int array_length, int offset);
    } // utils
} // bigint

#endif //EULER_CPP_BIGINTHELPERS_H
