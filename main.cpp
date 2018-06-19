#include <iostream>
#include <chrono>
#include <memory>
#include "src/Q1_20/1_20.h"

#include "src/helpers/BigInt/BigIntImpl.h"

#include <bitset>

void SolveQuestion(std::unique_ptr<IQuestion> const &question);

int main(void) {

    int64_t value = 10000000;
    auto b = bigint::impl::BigIntImpl(value);

    std::cout << b.magnitude_[0] << " " << b.magnitude_[1] << std::endl;
    std::cout << std::bitset<32>(b.magnitude_[0]) << " " << std::bitset<32>(b.magnitude_[1]) << std::endl;

    std::cout << ((int64_t)b.magnitude_[0] << 32 ) + (int64_t)b.magnitude_[1] << std::endl;


    std::cout << b.sign_num_ << std::endl;
    std::cout << b.size_ << " " << std::bitset<32>(b.magnitude_[0] )<<  std::bitset<32>( b.magnitude_[1]) << std::endl;
    std::cout << "  " << (std::bitset<64>(value)).to_string() << std::endl;

    std::cout << "  " << std::bitset<64>(b.Int64Value()) << std::endl;
    std::cout << b.Int64Value() << std::endl;
    auto c = b.ShiftLeft(20);
    std::cout << c.Int64Value() << std::endl;
    std::cout << c.size_ << " " << std::bitset<32>(c.magnitude_[0] )<<  std::bitset<32>( c.magnitude_[1]) << std::endl;
//    std::cout << b.ToString() << std::endl;

//    std::cout << 0xde0b6b3a7640000L << std::endl;

    uint32_t l = ~0;
    int v = ~0;
    std::cout << std::bitset<32>(l) << std::endl;
    std::cout << std::bitset<32>(v) << std::endl;

    std::cout << std::bitset<64>(0xffffffffL) << std::endl;

    // TODO:: CHECK DIVIDE WORD


    std::cout << (uint32_t) std::numeric_limits<int>::min() << std::endl;
    std::cout << std::bitset<32>(std::numeric_limits<int>::min()) << std::endl;
    std::cout << std::numeric_limits<int>::min() << std::endl;





//    std::unique_ptr<IQuestion> question = std::make_unique<Question2>();
//    SolveQuestion(question);


    return 0;
}

void SolveQuestion(std::unique_ptr<IQuestion> const &question) {

    auto start_time = std::chrono::steady_clock::now();
    i64 result = question->Solve();

    auto stop_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> time = stop_time - start_time;

    std::cout << "In " << time.count() << " seconds: " << result;

}
