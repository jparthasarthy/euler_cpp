#include "BigIntImpl.h"


bigint::impl::BigIntImpl::BigIntImpl() {

    magnitude_ = new uint32_t[1]{0};
    size_ = 1;
    sign_num_ = 0;
}

bigint::impl::BigIntImpl::~BigIntImpl() { // NOLINT

    delete[] magnitude_;
}

bigint::impl::BigIntImpl::BigIntImpl(int num) {

    magnitude_ = new uint32_t[1]{(uint32_t) abs(num)};
    size_ = 1;
    sign_num_ = (num == 0) ? 0 : (num > 0) ? 1 : -1;
}

bigint::impl::BigIntImpl::BigIntImpl(int64_t num) {

    // if the number is 0 use default constructor
    if (num == 0) {
        *this = BigIntImpl();
        return;
    }

    if (num < 0) { // make number positive
        sign_num_ = -1;
        num *= -1;
    } else {
        sign_num_ = 1;
    }

    auto high = (int) (num >> 32);
    if (high == 0) { // number fits into an int32
        magnitude_ = new uint32_t[1]{static_cast<uint32_t>(num)};
        size_ = 1;
    } else {
        magnitude_ = new uint32_t[2]{(uint32_t) high, (uint32_t) num};
        size_ = 2;
    }
}

bigint::impl::BigIntImpl::BigIntImpl(std::string const &value) {
    throw;
}

bigint::impl::BigIntImpl::BigIntImpl(const bigint::impl::BigIntImpl &bigint) {

    size_ = bigint.size_;
    sign_num_ = bigint.sign_num_;
    magnitude_ = new uint32_t[size_]{0};

    for (int i = 0; i < size_; i++) {
        magnitude_[i] = bigint.magnitude_[i];
    }
}

bigint::impl::BigIntImpl::BigIntImpl(bigint::impl::BigIntImpl &&bigint) noexcept {

    if (this == &bigint) return;

    size_ = bigint.size_;
    sign_num_ = bigint.sign_num_;
    magnitude_ = bigint.magnitude_;

    bigint.magnitude_ = nullptr;
    bigint.size_ = 0;
    bigint.sign_num_ = 0;
}

bigint::impl::BigIntImpl::BigIntImpl(uint32_t *digits, int size, int sign_num) {

    magnitude_ = digits;
    size_ = size;
    sign_num_ = (size != 0) ? sign_num : 0;
}

bigint::impl::BigIntImpl &bigint::impl::BigIntImpl::operator=(const bigint::impl::BigIntImpl &bigint) {

    if (this == &bigint) return *this;

    size_ = bigint.size_;
    sign_num_ = bigint.sign_num_;

    delete[] magnitude_;
    magnitude_ = new uint32_t[size_]{0};

    for (int i = 0; i < size_; i++) {
        magnitude_[i] = bigint.magnitude_[i];
    }
    return *this;
}

bigint::impl::BigIntImpl &bigint::impl::BigIntImpl::operator=(bigint::impl::BigIntImpl &&bigint) noexcept {

    if (this == &bigint) return *this;

    size_ = bigint.size_;
    delete[] magnitude_;
    magnitude_ = bigint.magnitude_;
    sign_num_ = bigint.sign_num_;

    bigint.magnitude_ = nullptr;
}


std::string bigint::impl::BigIntImpl::ToString() const {

    std::stringstream stream;

    if (sign_num_) {
        stream << ((sign_num_ == 1) ? "" : "-");
    }

    for(int i = 0; i < size_; i++) {
        stream << magnitude_[i];
    }

    return stream.str();
}

void bigint::impl::BigIntImpl::Print() const {
    throw;
}


bool bigint::impl::BigIntImpl::Equals(const bigint::impl::BigIntImpl &bigint) const {
    throw;
}

bool bigint::impl::BigIntImpl::operator<(const bigint::impl::BigIntImpl &bigint) const {
    throw;
}

bigint::impl::BigIntImpl bigint::impl::BigIntImpl::Abs() const {
    throw;
}

bigint::impl::BigIntImpl bigint::impl::BigIntImpl::Pow(int exponent) const {
    throw;
}

bigint::impl::BigIntImpl
bigint::impl::BigIntImpl::Divide(bigint::impl::BigIntImpl const &divisor, bigint::impl::BigIntImpl &remainder) const {

    // using Algorithm D in Knuth section 4.3.1

    if (divisor.size_ == 0) return bigint::impl::BigIntImpl(0); // cannot divide by zero

    if (this->size_ == 0) return bigint::impl::BigIntImpl(0); // zero dividend returns 0 result

    if (*this < divisor) return bigint::impl::BigIntImpl(0); // zero result if dividend is smaller than divisor

    if (*this == divisor) return bigint::impl::BigIntImpl(1); // one result if they are equal

    // divisor copy
    int div_cpy_len = divisor.size_;
    auto div_cpy = new uint32_t[div_cpy_len];
    for (int i = 0; i < divisor.size_; i++) {
        div_cpy[i] = divisor.magnitude_[i];
    }

    // create remainder array that has enough space for a copy of dividend and a leading 0
    int rem_offset = 1;
    int rem_cpy_len = this->size_;
    auto rem_cpy = new uint32_t[rem_cpy_len + 1];
    for(int i = 0; i < this->size_; i++) {
        rem_cpy[i + rem_offset] = this->magnitude_[i];
    }
    remainder = bigint::impl::BigIntImpl(rem_cpy, rem_cpy_len, 1);
    int nlen = rem_cpy_len; // used for the algorithm

    // set quotient size
    int quo_len = nlen - div_cpy_len + 1;
    auto quo = new uint32_t[quo_len];

    // normalize (align) the divisor
    int shift = 32 - bigint::utils::BitLength(div_cpy[0]);
    if (shift > 0) {
        bigint::utils::PrimitiveLeftShift(div_cpy, div_cpy_len, shift);
        remainder = std::move(remainder.ShiftLeft(shift)); // check if the std::move is necessary
    }

    // if the length did not change, put a leading 0
    if(rem_cpy_len == nlen) {
        rem_offset = 0;
        rem_cpy[0] = 0;
        rem_cpy_len++;
    }

    uint32_t dh = div_cpy[0];
    uint64_t dh_64 = dh;
    uint32_t dl = div_cpy[1];
    uint32_t q_word[2]{0};

    // initialize j
    for(int j = 0; j < quo_len; j++) {
        //calculate qhat
        uint32_t qhat = 0;
        uint32_t qrem = 0;

        bool skip_correction = false;
        uint32_t nh = rem_cpy[j + rem_offset];
        uint32_t nh2 = nh + 0x80000000;
        uint32_t nm = rem_cpy[j + 1 + rem_offset];

        if(nh == dh) {
            qhat = ~0;
            qrem = nh + nm;
            skip_correction = (qrem + 0x80000000 < nh2);
        } else {
            uint64_t n_chunk = (((uint64_t)nh) << 32) | (uint64_t)nm; // could be a problem
            if ( n_chunk >= 0) {
                qhat = (uint32_t) (n_chunk / dh_64);
                qrem = (uint32_t) (n_chunk - (qhat * dh_64));
            } else {
                bigint::utils::DivideWord(q_word, n_chunk, dh);
                qhat = q_word[0];
                qrem = q_word[1];
            }
        }

        if (qhat == 0) continue;

        if(!skip_correction) {// correct qhat
            uint64_t nl = rem_cpy[j + 2 + rem_offset];
            uint64_t rs = ((uint64_t) qrem << 32) | nl;
            uint64_t est_product = ((uint64_t) dl) * ((uint64_t) qhat);

            if ( est_product  > rs ) { // unsigned long compare

                qhat--;
                qrem = (uint32_t) ((uint64_t)qrem + dh_64);
                if((uint64_t) qrem >= dh_64) {
                    est_product = (uint64_t)dl * (uint64_t)qhat;
                    rs = (((uint64_t) qrem ) <<32 ) | nl;
                    if(est_product > rs) {
                        qhat--;
                    }
                }
            }
        }

        // multiply and subtract

        rem_cpy[j + rem_offset] = 0;
        uint32_t borrow = bigint::utils::MulSub(rem_cpy, div_cpy, qhat, div_cpy_len, j+rem_offset); //TODO:: REWIRTE THIS FUNCTION
    }









}

bigint::impl::BigIntImpl bigint::impl::BigIntImpl::ShiftLeft(int shift) const { //TODO::CLEAN UP

    if (this->sign_num_ == 0) return bigint::impl::BigIntImpl(new uint32_t[0], 1, 0);

    if (shift == 0) return bigint::impl::BigIntImpl(*this);

    if (shift < 0) return ShiftRight(-shift);

    int num_ints = (uint32_t)shift >> 5;
    int num_bits = shift & 0x1f;

    uint32_t *new_magnitude = nullptr;
    int new_size = -1;

    if (num_bits == 0) {
        new_size = this->size_ + num_ints;
        new_magnitude = new uint32_t[new_size];

        for (int i = 0; i < this->size_; i++) {
            new_magnitude[i] = this->magnitude_[i];
        }
    } else {
        int i = 0;
        int num_bits_complement = 32 - num_bits;
        int high_bits = this->magnitude_[0] >> num_bits_complement;

        if (high_bits != 0) {
            new_size = this->size_ + num_ints + 1;
            new_magnitude = new uint32_t[new_size];
            new_magnitude[i++] = (uint32_t)high_bits;
        } else {
            new_size = this->size_ + num_ints;
            new_magnitude = new uint32_t[new_size];
        }

        int j = 0;
        while (j < this->size_ - 1) {
            new_magnitude[i++] = this->magnitude_[j++] << num_bits | this->magnitude_[j] >> num_bits_complement;
        }
        new_magnitude[i] = this->magnitude_[j] << num_bits;
    }

    return bigint::impl::BigIntImpl(new_magnitude, new_size, this->sign_num_);
}

bigint::impl::BigIntImpl bigint::impl::BigIntImpl::ShiftRight(int shift) const {
    throw;
}

int64_t bigint::impl::BigIntImpl::Int64Value() const {

    int64_t value = 0;
    int limit = (size_ >= 2) ? 2 : size_; // used if magnitude is only 1 index long

    for (int i = 0; i < limit; i++) {
        value = (value << 32) + magnitude_[i];
    }
    return value * sign_num_;
}

int bigint::impl::BigIntImpl::FirstNonZeroIntIndex() const {

//    int i;
//    for(i = size_; i >= 0 && magnitude_[i] == 0; i--) {}
//
//    return size_ - i - 1;
    throw;
}

int bigint::impl::BigIntImpl::GetInt(int n) const {

//    if (n < 0) return 0;
//    if(n > size_) return (sign_num_  < 0)? -1:0;
//
//    int magnitude_int = magnitude_[size_ - n - 1];
//    return ((sign_num_ >= 0) ? magnitude_int : ((n <= FirstNonZeroIntIndex()) ? -magnitude_int : ~magnitude_int));
    throw;
}

