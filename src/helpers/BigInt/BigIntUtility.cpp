#include "BigIntUtility.h"

int bigint::utils::NumberOfDigits(int64_t num) {
    if (num == 0) return 1;

    int count = 0;
    while (num) {
        num /= 10;
        count++;
    }
    return count;
}

int bigint::utils::TrimToNineLeastSignificantDigits(int64_t num) {

    int num_digits = NumberOfDigits(num);

    while (num_digits > 9) {
        num %= Integer64Power(10, --num_digits);
    }
    return static_cast<int>(num);
}

int64_t bigint::utils::RemoveNineLeastSignificantDigits(int64_t num) {

    return num / 1000000000;
}

int64_t bigint::utils::Integer64Power(int64_t base, int exponent) {

    if (exponent < 0) return -1;
    if (floor(log2(llabs(base)) * exponent > 64)) return -1;

    int64_t result = 1;
    auto base_i64 = static_cast<int64_t>(base);
    while (exponent) {
        if (exponent & 1) {
            result *= base_i64;
        }

        exponent >>= 1;
        base_i64 *= base_i64;
    }

    return result;
}

void bigint::utils::InsertGroup(int *x, int x_len, int z) {

    throw;


    auto z_i64 = static_cast<int64_t>(z);

    // multiplication - shift the magnitude of the existing number
    int64_t product = 0;
    int64_t carry = 0;
    for (int i = x_len - 1; i >= 0; i--) {
        product = constants::kSuperRadix_ * static_cast<int64_t>(x[i]) + carry;

        x[i] = utils::TrimToNineLeastSignificantDigits(product);
        carry = utils::RemoveNineLeastSignificantDigits(product);
    }

    //addition
    int64_t sum = static_cast<int64_t>(x[x_len - 1]) + z_i64;

    x[x_len - 1] = utils::TrimToNineLeastSignificantDigits(sum);
    carry = utils::RemoveNineLeastSignificantDigits(sum);

    for (int i = x_len - 2; i >= 0; i--) {
        sum = static_cast<int64_t>(x[i]) + carry;

        x[i] = utils::TrimToNineLeastSignificantDigits(sum);
        carry = utils::RemoveNineLeastSignificantDigits(sum);
    }
}

int *bigint::utils::ArrayMultiply(const int *x, int x_len, const int *y, int y_len, int &z_len) {

    // naive implementation just to get things going, should be done by index of z with multiplication pattern apparent
    // when written out
    throw;

    z_len = x_len + y_len;
    auto z = new int[z_len]{0};
    auto carry = new int64_t[z_len]{0};

    for (int i = 0; i < y_len; i++) {
        for (int j = 0; j < x_len; j++) {
            int64_t tmp = y[y_len - 1 - i] * x[x_len - 1 - j];
            z[z_len - 1 - i - j] = bigint::utils::TrimToNineLeastSignificantDigits(z[z_len - 1 - i - j] + tmp);
            carry[z_len - i - j] = bigint::utils::RemoveNineLeastSignificantDigits(z[z_len - 1 - i - j] + tmp);
        }
    }

    for (int i = z_len - 1; i > 0; i--) {
        z[i] = bigint::utils::TrimToNineLeastSignificantDigits(z[i] + carry[i]);
        carry[i + 1] = bigint::utils::RemoveNineLeastSignificantDigits(z[i] + carry[i]);
    }
    bigint::utils::TrustedStripLeadingZeroInts(&z, z_len);
    return z;

}

int *bigint::utils::TrustedStripLeadingZeroInts(int **array, int &size) {

    throw;

    int keep = 0;

    // find first nonzero byte
    while (keep < size && (*array)[keep] == 0)
        keep++;

    // only reallocate if needed
    if (keep > 0) {
        auto result = new int[size - keep]{0};

        for (int i = 0; i < size - keep; i++) {
            result[i] = (*array)[keep + i];
        }
        delete[] *array;
        (*array) = result;
        size -= keep;
    }
    return *array;
}

int ::bigint::utils::BitLength(int word) {

    // Binary search - decision tree (5 tests, rarely 6)

    return
            (word < 1 << 15 ?
             (word < 1 << 7 ?
              (word < 1 << 3 ?
               (word < 1 << 1 ? (word < 1 << 0 ? (word < 0 ? 32 : 0) : 1) : (word < 1 << 2 ? 2 : 3)) :
               (word < 1 << 5 ? (word < 1 << 4 ? 4 : 5) : (word < 1 << 6 ? 6 : 7))) :
              (word < 1 << 11 ?
               (word < 1 << 9 ? (word < 1 << 8 ? 8 : 9) : (word < 1 << 10 ? 10 : 11)) :
               (word < 1 << 13 ? (word < 1 << 12 ? 12 : 13) : (word < 1 << 14 ? 14 : 15)))) :
             (word < 1 << 23 ?
              (word < 1 << 19 ?
               (word < 1 << 17 ? (word < 1 << 16 ? 16 : 17) : (word < 1 << 18 ? 18 : 19)) :
               (word < 1 << 21 ? (word < 1 << 20 ? 20 : 21) : (word < 1 << 22 ? 22 : 23))) :
              (word < 1 << 27 ?
               (word < 1 << 25 ? (word < 1 << 24 ? 24 : 25) : (word < 1 << 26 ? 26 : 27)) :
               (word < 1 << 29 ? (word < 1 << 28 ? 28 : 29) : (word < 1 << 30 ? 30 : 31)))));
}

void ::bigint::utils::PrimitiveLeftShift(uint32_t *array, int length, int shift) { // TODO:: TEST

    if (length == 0 || shift == 0) return;

    int shift_complement = 32 - shift;
    for (int i = 0, c = array[i], m = i + length - 1; i < m; i++) {
        int b = c;
        c = array[i + 1];
        array[i] = (uint32_t )(b << shift) | (c >> shift_complement);
    }

    array[length - 1] <<= shift;
}

void bigint::utils::DivideWord(uint32_t *result, uint64_t dividend, uint32_t divisor) {


    uint64_t divisor_64 = divisor;

    // if dividing by 1, return dividend as quotient
    if (divisor_64 == 1) {
        result[0] = (uint32_t)dividend;
        result[1] = 0;
        return;
    }

    // approximate quotient and remainder
    uint64_t quotient = (dividend >> 1) / (divisor_64 >> 1);
    uint64_t remainder = dividend - quotient * divisor_64;

    // apply correction
    while (remainder < 0) {
        remainder += divisor_64;
        quotient--;
    }

    while (remainder >= divisor_64) {
        remainder -= divisor_64;
        quotient++;
    }

    result[0] = (uint32_t) quotient;
    result[1] = (uint32_t) remainder;
}

uint32_t bigint::utils::MulSub(uint32_t *dividend, uint32_t const *array, int x, int array_len, int offset) {

    auto x_64 = (uint64_t)x;
    uint64_t carry = 0;
    offset += array_len;

    for (int j = array_len - 1; j >= 0; j--) {
        uint64_t product = (uint64_t)array[j] * x_64 + carry;
        uint64_t difference = dividend[offset] - product;
        dividend[offset--] = (uint32_t)difference;

        carry = (product >> 32) + (((uint64_t)difference & bigint::constants::kint64Mask) >
                                    (((~static_cast<int>( product)) & bigint::constants::kint64Mask))) ? 1 : 0);
    }

    return static_cast<int>(carry);
}

uint32_t bigint::utils::DivAdd(uint32_t const *array, uint32_t *remainder, int array_length, int offset) {

//    int64_t carry = 0;
//
//    for (int j = array_length - 1; j >= 0; j--) {
//        int64_t sum =
//                (array[j] & bigint::constants::kint64Mask) + (remainder[j + offset] & bigint::constants::kint64Mask) +
//                carry;
//        remainder[j + offset] = static_cast<int>(sum);
//        carry = sum >> 32;
//    }
//    return static_cast<int>(carry);
    throw;
}

void ::bigint::utils::PrimitiveRightShift(uint32_t *array, int length, int shift) {
    throw;
}


