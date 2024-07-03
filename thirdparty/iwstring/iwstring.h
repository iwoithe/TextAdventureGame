#ifndef IWSTRING_H
#define IWSTRING_H

#include <cstddef>
#include <cstring>
#include <vector>
#include <iostream>
#include <ostream>

namespace iw {
enum Color {
    None,
    Default,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

enum ColorLayer {
    Foreground,
    Background
};

static const char* getCodeFromColor(Color colorCode, ColorLayer colorLayer);

class String
{
public:
    String();
    String(const double& d);
    String(const float& f);
    String(const int& i);
    String(const size_t& s);
    String(char c);
    String(const char* str);
    String(const String& str);
    ~String();

    String& operator=(const char* str);
    String& operator=(const String& other);
    String operator+(const String& other);
    String& operator+=(const String& other);
    bool operator<(const String& other);
    bool operator>(const String& other);
    char& operator[](const size_t& index);
    const char& operator[](const size_t& index) const;
    bool operator==(const String& other);
    bool operator!=(const String& other);

    String& append(const double& other);
    String& append(const float& other);
    String& append(const int& other);
    String& append(const size_t& other);
    String& append(const String& other);

    char& characterAt(size_t index) const;

    String& clear();
    String& clear(const int newLength);
    String& clear(const int newLength, const bool appendNullTerminator_);

    const char* cStr() const;

    String& appendColor(Color color, ColorLayer colorLayer);
    String& setColor(Color color, ColorLayer colorLayer);
    String& setColor(Color color, ColorLayer colorLayer, const bool& clearAtEndOfLine);

    String& stripFormatting();

    const char* data() const;
    void setData(char c);
    void setData(const char* d);
    void setData(const String& str);
    void setData(char c, bool clearFirst);
    void setData(const char* d, bool clearFirst);
    void setData(const String& str, bool clearFirst);

    bool equalTo(const String& other);

    const size_t find(const String& findStr) const;
    const size_t find(const size_t& startIndex, const String& findStr) const;

    const size_t length() const;
    const size_t length(const bool includeNullTerminator) const;
    static const size_t length(const char* str);
    static const size_t length(const char* str, const bool includeNullTerminator);
    static const size_t length(const String& str);
    static const size_t length(const String& str, const bool includeNullTerminator);

    String& prepend(const String& other);

    String& replace(const String& findStr, const String& replaceStr);

    std::vector<char> toCharVector() const;
    String& toLower();
    String& toUpper();

    void readFromConsole();
    void writeToConsole() const;
    void writeToConsole(const bool& flushEndOfLine) const;

private:
    char* m_data;

    void appendNullTerminator();

    void clearData();
    void clearData(const int newLength);
    void clearData(const int newLength, const bool appendNullTerminator_);

    void initData(const int newLength);
    void initData(const int newLength, const bool appendNullTerminator_);
};

std::ostream& operator<<(std::ostream& os, const String other);
}

#endif // IWSTRING_H
