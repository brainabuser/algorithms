#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <vector>
#include <string>
#include <variant>

struct UnknownToken {
    std::string value;
};

struct PlusToken {
};

struct MinusToken {

};

struct NumberToken {
    int value;
};

struct MultiplyToken {

};

struct DivideToken {

};

struct ResidualToken {

};

struct SqrToken {

};

struct MinToken {

};

struct AbsToken {

};

struct MaxToken {

};

struct OpeningBracketToken {

};

struct ClosingBracketToken {

};

using Token = std::variant<
        UnknownToken,
        PlusToken,
        MinusToken,
        NumberToken,
        MultiplyToken,
        DivideToken,
        ResidualToken,
        SqrToken,
        MinToken,
        AbsToken,
        MaxToken,
        OpeningBracketToken,
        ClosingBracketToken
>;

std::vector<Token> Tokenize(const std::string &input);

bool operator==(const PlusToken &lhs, const PlusToken &rhs);
bool operator==(const MinusToken &lhs, const MinusToken &rhs);
bool operator==(const MultiplyToken &lhs, const MultiplyToken &rhs);
bool operator==(const DivideToken &lhs, const DivideToken &rhs);
bool operator==(const ResidualToken &lhs, const ResidualToken &rhs);
bool operator==(const SqrToken &lhs, const SqrToken &rhs);
bool operator==(const MinToken &lhs, const MinToken &rhs);
bool operator==(const MaxToken &lhs, const MaxToken &rhs);
bool operator==(const AbsToken &lhs, const AbsToken &rhs);
bool operator==(const OpeningBracketToken &lhs, const OpeningBracketToken &rhs);
bool operator==(const ClosingBracketToken &lhs, const ClosingBracketToken &rhs);
bool operator==(const UnknownToken &lhs, const UnknownToken &rhs);
bool operator==(const NumberToken &lhs, const NumberToken &rhs);

#endif // TOKENIZE_H
