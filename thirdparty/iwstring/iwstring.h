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
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;
    char& operator[](const size_t& index);
    const char& operator[](const size_t& index) const;
    // Internally uses the `equalTo` method
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;

    // Insert `other` to the end of `m_data`
    String& append(const double& other);
    String& append(const float& other);
    String& append(const int& other);
    String& append(const size_t& other);
    String& append(const String& other);

    // Returns the character in `m_data` at position `index`
    // Internally uses the `[]` operator
    char& characterAt(size_t index) const;

    // clear methods call clearData and return the string (clearData returns no value)
    String& clear();
    // newLength: the length to initialize the string to
    String& clear(const int newLength);
    // appendNullTerminator_: appends one character to length to accomodate the null terminator
    String& clear(const int newLength, const bool appendNullTerminator_);

    // Just a wrapper method for `data()`
    const char* cStr() const;

    // Appends the color on color layer to the string
    String& appendColor(Color color, ColorLayer colorLayer);
    // Sets the color of the whole (at the time of calling this method) string
    // Clears the color at the end of the line by default
    String& setColor(Color color, ColorLayer colorLayer);
    String& setColor(Color color, ColorLayer colorLayer, const bool& clearAtEndOfLine);

    // Strip all ANSI formatting from the string
    String& stripFormatting();

    // Return a const value of `m_data`
    const char* data() const;
    // `setData()` handles the repetive code of setting `m_data` over and over again
    void setData(char c);
    void setData(const char* d);
    void setData(const String& str);
    // clearFirst: whether to delete and reassign m_data first
    // WARNING: Only set to false if there is *no* previous initialization of `m_data`
    // i.e. these overloads are used only in the constructors of `String`
    void setData(char c, bool clearFirst);
    void setData(const char* d, bool clearFirst);
    void setData(const String& str, bool clearFirst);

    // Return if this string is equal to `other` string
    bool equalTo(const String& other) const;

    // `find()` finds the first occurence of `findStr`
    // Equivelent to calling `find(0, findStr)`
    const size_t find(const String& findStr) const;
    // startIndex: start searching the string from `startIndex`
    const size_t find(const size_t& startIndex, const String& findStr) const;

    // Return the length of `m_data`
    // `length()` does not include null terminator
    const size_t length() const;
    // `length(true)` includes null terminator
    const size_t length(const bool includeNullTerminator) const;
    // Static utility methods to find the length of other data types that don't have a length method
    static const size_t length(const char* str);
    static const size_t length(const char* str, const bool includeNullTerminator);
    // Generally can just use `length()` directly on a string object instead of the static method
    static const size_t length(const String& str);
    static const size_t length(const String& str, const bool includeNullTerminator);

    // Insert `other` at the beginning of this string
    String& prepend(const String& other);

    // Replaces each occurance of `findStr` with `replaceStr`
    String& replace(const String& findStr, const String& replaceStr);

    // Convert the string to a vector of chars
    std::vector<char> toCharVector() const;

    // Convert the string to lower case
    String& toLower();
    // Convert the string to upper case
    String& toUpper();

    // Set input from the console into `m_data`
    void readFromConsole();
    // Print `m_data` to the console (calls `writeToConsole(true)`)
    void writeToConsole() const;
    // flushEndOfLine: appends `std::endl` to the end of the String
    void writeToConsole(const bool& flushEndOfLine) const;

private:
    char* m_data;

    // The user should never have to use this method
    // If they do it's a bug with this class
    void appendNullTerminator();

    // Clear `m_data` - deletes `m_data` then calls the respective
    // overload of `initData()` matching the call to `clearData()`
    void clearData();
    void clearData(const int newLength);
    void clearData(const int newLength, const bool appendNullTerminator_);

    // Initialize `m_data`
    // NOTE: Will crash if `m_data` is not cleared first
    void initData(const int newLength);
    void initData(const int newLength, const bool appendNullTerminator_);
};

// Allow strings to be printed out directly by `std::cout`
std::ostream& operator<<(std::ostream& os, const String other);
}

#endif // IWSTRING_H
