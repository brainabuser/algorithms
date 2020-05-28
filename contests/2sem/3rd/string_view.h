#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <ostream>
#include <utility>
#include <exception>
#include <cstring>
#include <iterator>

class StringView {
    const char *line;
    size_t length;
  public:
    class ConstIterator {
      private:
        const char *ptr;
      public:
        ConstIterator(const char *ptr) : ptr(ptr) {}
        ConstIterator &operator++() {
            ++ptr;
            return *this;
        }
        ConstIterator &operator--() {
            --ptr;
            return *this;
        }
        char operator*() {
            return *ptr;
        }
        bool operator==(const ConstIterator &that) {
            return this->ptr == that.ptr;
        }
        bool operator!=(const ConstIterator &that) {
            return !(*this == that);
        }
    };

    class ConstReverseIterator {
      private:
        const char *ptr;
      public:
        ConstReverseIterator(const char *ptr) : ptr(ptr) {}
        ConstReverseIterator &operator++() {
            --ptr;
            return *this;
        }
        ConstReverseIterator &operator--() {
            ++ptr;
            return *this;
        }
        char operator*() {
            return *ptr;
        }
        bool operator==(const ConstReverseIterator &that) {
            return this->ptr == that.ptr;
        }
        bool operator!=(const ConstReverseIterator &that) {
            return !(*this == that);
        }
    };

    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    ConstReverseIterator rbegin() const;
    ConstReverseIterator rend() const;
    ConstReverseIterator crbegin() const;
    ConstReverseIterator crend() const;

    StringView() : line(nullptr), length(0) {}
    StringView(const char *ptr) : line(ptr) {
        length = strlen(ptr);
    }
    StringView(const char *ptr, size_t size) : line(ptr), length(size) {}
    const char &operator[](const size_t &index) const;
    const char &At(const size_t &index) const;
    const char &Front() const;
    const char &Back() const;
    const size_t &Size() const;
    const size_t &Length() const;
    bool Empty() const;
    const char *Data() const;
    void Swap(StringView &other);
    void RemovePrefix(size_t prefix_size);
    void RemoveSuffix(size_t suffix_size);
    StringView Substr(size_t pos, size_t count = -1) const;
};

const char &StringView::operator[](const size_t &index) const {
    return line[index];
}

const char &StringView::At(const size_t &index) const {
    if (index >= length) {
        throw std::out_of_range("");
    }
    return line[index];
}

const char &StringView::Front() const {
    return operator[](0);
}

const char &StringView::Back() const {
    return operator[](length - 1);
}

const size_t &StringView::Size() const {
    return length;
}

const size_t &StringView::Length() const {
    return length;
}

bool StringView::Empty() const {
    return length == 0;
}

const char *StringView::Data() const {
    return line;
}

void StringView::Swap(StringView &other) {
    std::swap(*this, other);
}

void StringView::RemovePrefix(size_t prefix_size) {
    line += prefix_size;
    length -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
    length -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) const {
    StringView result(this->line);
    result.RemovePrefix(pos);
    result.RemoveSuffix(result.Size() - std::min(count, Size() - pos));
    return result;
}

StringView::ConstIterator StringView::begin() const {
    return {this->line};
}

StringView::ConstIterator StringView::end() const {
    return {this->line + length};
}

StringView::ConstIterator StringView::cbegin() const {
    return {this->line};
}

StringView::ConstIterator StringView::cend() const {
    return {this->line + length};
}

StringView::ConstReverseIterator StringView::rbegin() const {
    return {this->line + length - 1};
}

StringView::ConstReverseIterator StringView::rend() const {
    return {this->line - 1};
}

StringView::ConstReverseIterator StringView::crbegin() const {
    return {this->line + length - 1};
}

StringView::ConstReverseIterator StringView::crend() const {
    return {this->line - 1};
}

#endif // STRING_VIEW_H
