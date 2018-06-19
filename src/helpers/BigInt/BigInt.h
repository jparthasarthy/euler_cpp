#ifndef EULER_CPP_BIGINT_H
#define EULER_CPP_BIGINT_H

#include "BigIntImpl.h"


namespace bigint {

    class BigInt {

    private:
        impl::BigIntImpl *bigint_;

        explicit BigInt(impl::BigIntImpl bigint) { bigint_ = new impl::BigIntImpl(std::move(bigint)); }; // for internal use only

    public:
        BigInt() { bigint_ = new impl::BigIntImpl(); } // NOLINT

        ~BigInt() { delete bigint_; } // NOLINT

        explicit BigInt(int num) { bigint_ = new impl::BigIntImpl(num); }

        explicit BigInt(int64_t num) { bigint_ = new impl::BigIntImpl(num); }

        explicit BigInt(std::string const &value) { bigint_ = new impl::BigIntImpl(value); }

        BigInt(const BigInt &bigint) { bigint_ = new impl::BigIntImpl(*bigint.bigint_); };

        BigInt(BigInt &&bigint) noexcept { bigint_ = new impl::BigIntImpl(std::move(*bigint.bigint_)); }

        // Copy / move operators
        BigInt &operator=(const BigInt &bigint) {
            if (this == &bigint) return *this;
            delete bigint_;
            bigint_ = new impl::BigIntImpl(*bigint.bigint_);
        }

        BigInt &operator=(BigInt &&bigint) noexcept {
            if (this == &bigint) return *this;
            delete bigint_;
            *bigint_ = std::move(*bigint.bigint_);
            bigint.bigint_ = nullptr;
        }

        // Getters
        int size() const { return bigint_->size_; }

        int sign_num() const { return bigint_->sign_num_; } // returns 1 for positive, 0 for 0, -1 for negative

        std::vector<int> magnitude() { return bigint_->magnitude(); }

        std::string ToString() const { return bigint_->ToString(); }

        void Print() const { bigint_->Print(); };

        // Comparison
        bool Equals(const BigInt &bigint) const { bigint_->Equals(*bigint.bigint_); };

        bool operator==(const BigInt &bigint) const { return this->Equals(bigint); }

        bool operator!=(const BigInt &bigint) const { return !(this->Equals(bigint)); }

        bool operator<(const BigInt &bigint) const { return *bigint_ < *bigint.bigint_; };

        bool operator>(const BigInt &bigint) const { return (bigint < (*this)); }

        bool operator<=(const BigInt &bigint) const { return !(bigint < (*this)); }

        bool operator>=(const BigInt &bigint) const { return !(bigint > (*this)); }

        bool IsZero() const { return bigint_->sign_num_ == 0; };

        // Math
        BigInt Abs() const { return BigInt(bigint_->Abs()); };

        BigInt Pow(int exponent) const { return BigInt(bigint_->Pow(exponent)); } // 0^0 is 1 in this case

        BigInt Divide(BigInt const& divisor, BigInt &remainder) const {return BigInt(bigint_->Divide(*divisor.bigint_, *remainder.bigint_));} // TODO::test

    };
}


#endif //EULER_CPP_BIGINT_H
