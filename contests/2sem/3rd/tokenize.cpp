#include "tokenize.h"
#include <string>
#include <algorithm>

bool isNumber(const std::string &s) {
    auto it = (s.front() == '+' || s.front() == '-') ? s.begin() + 1 : s.begin();
    it = std::find_if_not(it, s.end(), [](char c) {
        return std::isdigit(c);
    });
    return it == s.end();
}

std::vector<Token> Tokenize(const std::string &input) {
    const std::string delims = " ";
    std::string::size_type head = input.find_first_not_of(delims, 0);
    std::string::size_type pos = input.find_first_of(delims, head);
    std::vector<Token> result;
    std::string item;
    while (pos != std::string::npos || head != std::string::npos) {
        item = input.substr(head, pos - head);
        if (item == "+") {
            result.emplace_back(PlusToken());
        } else if (item == "-") {
            result.emplace_back(MinusToken());
        } else if (item == "*") {
            result.emplace_back(MultiplyToken());
        } else if (item == "/") {
            result.emplace_back(DivideToken());
        } else if (item == "%") {
            result.emplace_back(ResidualToken());
        } else if (item == "sqr") {
            result.emplace_back(SqrToken());
        } else if (item == "min") {
            result.emplace_back(MinToken());
        } else if (item == "max") {
            result.emplace_back(MaxToken());
        } else if (item == "abs") {
            result.emplace_back(AbsToken());
        } else if (item == "(") {
            result.emplace_back(OpeningBracketToken());
        } else if (item == ")") {
            result.emplace_back(ClosingBracketToken());
        } else if (isNumber(item)) {
            result.emplace_back(NumberToken{std::stoi(item)});
        } else {
            result.emplace_back(UnknownToken{item});
        }
        head = input.find_first_not_of(delims, pos);
        pos = input.find_first_of(delims, head);
    }
    return result;
}
bool operator==(const PlusToken &, const PlusToken &) {
    return true;
}
bool operator==(const MinusToken &, const MinusToken &) {
    return true;
}
bool operator==(const MultiplyToken &, const MultiplyToken &) {
    return true;
}
bool operator==(const DivideToken &, const DivideToken &) {
    return true;
}
bool operator==(const ResidualToken &, const ResidualToken &) {
    return true;
}
bool operator==(const SqrToken &, const SqrToken &) {
    return true;
}
bool operator==(const MinToken &, const MinToken &) {
    return true;
}
bool operator==(const MaxToken &, const MaxToken &) {
    return true;
}
bool operator==(const AbsToken &, const AbsToken &) {
    return true;
}
bool operator==(const OpeningBracketToken &, const OpeningBracketToken &) {
    return true;
}
bool operator==(const ClosingBracketToken &, const ClosingBracketToken &) {
    return true;
}
bool operator==(const NumberToken &lhs, const NumberToken &rhs) {
    return lhs.value == rhs.value;
}
bool operator==(const UnknownToken &lhs, const UnknownToken &rhs) {
    return lhs.value == rhs.value;
}
