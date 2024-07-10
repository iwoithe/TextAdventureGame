#include "iwstring.h"

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace iw;

static const char* iw::getCodeFromColor(Color colorCode, ColorLayer colorLayer)
{
    bool isForeground;
    switch (colorLayer) {
        case ColorLayer::Foreground:
            isForeground = true;
            break;
        case ColorLayer::Background:
            isForeground = false;
            break;
    }

    switch (colorCode) {
        case (Color::None):
            return "\033[0m";
        case (Color::Default):
            return isForeground ? "\033[39m" : "\033[49m";
        case (Color::Black):
            return isForeground ? "\033[30m" : "\033[40m";
        case (Color::Red):
            return isForeground ? "\033[31m" : "\033[41m";
        case (Color::Green):
            return isForeground ? "\033[32m" : "\033[42m";
        case (Color::Yellow):
            return isForeground ? "\033[33m" : "\033[43m";
        case (Color::Blue):
            return isForeground ? "\033[34m" : "\033[44m";
        case (Color::Magenta):
            return isForeground ? "\033[35m" : "\033[45m";
        case (Color::Cyan):
            return isForeground ? "\033[36m" : "\033[46m";
        case (Color::White):
            return isForeground ? "\033[37m" : "\033[47m";
    }

    return "\033[0m";
};

String::String()
{
    initData(0);
}

String::String(const double& d)
{
    setData(std::to_string(d).data(), false);
}

String::String(const float& f)
{
    setData(std::to_string(f).data(), false);
}

String::String(const int& i)
{
    setData(std::to_string(i).data(), false);
}

String::String(const size_t& s)
{
    setData(std::to_string(s).data(), false);
}

String::String(char c)
{
    setData(c, false);
}

String::String(const char* str)
{
    setData(str, false);
}

String::String(const String& str)
{
    setData(str, false);
}

String::~String()
{
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
}

String& String::operator=(const char* str)
{
    if (m_data == nullptr) {
        setData(str, false);
    } else {
        setData(str);
    }
    return *this;
}

String& String::operator=(const String& other)
{
    if (m_data == nullptr) {
        setData(other, false);
    } else {
        setData(other);
    }
    return *this;
}

String String::operator+(const String& other)
{
    return append(other);
}

String& String::operator+=(const String& other)
{
    append(other);
    return *this;
}

bool String::operator<(const String& other) const
{
    int res = strcmp(m_data, other.m_data);

    if (res < 0) {
        return true;
    } else {
        return false;
    }
}

bool String::operator>(const String& other) const
{
    int res = strcmp(m_data, other.m_data);

    if (res > 0) {
        return true;
    } else {
        return false;
    }
}

std::ostream& iw::operator<<(std::ostream& os, const String other)
{
    os << other.cStr() << std::endl;
    return os;
}

char& String::operator[](const size_t& index)
{
    if (index >= length() || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

const char& String::operator[](const size_t& index) const
{
    if (index >= length() || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    return m_data[index];
}

bool String::operator==(const String& other) const
{
    return equalTo(other);
}

bool String::operator!=(const String& other) const
{
    return !(m_data == other.data());
}

String& String::append(const double& other)
{
    return append(std::to_string(other).data());
}

String& String::append(const float& other)
{
    return append(std::to_string(other).data());
}

String& String::append(const int& other)
{
    return append(std::to_string(other).data());
}

String& String::append(const size_t& other)
{
    return append(std::to_string(other).data());
}

String& String::append(const String& other)
{
    int len = length() + other.length(true);
    char* newStr = new char[len];

    // Copy current contents
    for (int i = 0; i < length(); i++) {
        newStr[i] = m_data[i];
    }

    // Copy the other string's contents
    for (int i = 0; i < other.length(true); i++) {
        newStr[length() + i] = other.characterAt(i);
    }

    clearData(len);
    strcpy_s(m_data, len, newStr);
    delete[] newStr;
    newStr = nullptr;

    return *this;
}

String& String::appendColor(Color color, ColorLayer colorLayer)
{
    append(getCodeFromColor(color, colorLayer));
    return *this;
}

String& String::stripFormatting()
{
    // Removes all ANSI escape codes
    // There's a little custom behaviour here, hence why the replace method can't be used

    // Find the first ANSI escape code (if it exists)
    size_t findIndex = find("\033[");

    while (findIndex != -1) {
        int ansiStrLen = 1;
        // Pre-set the nextChar to the first letter
        char nextChar = m_data[findIndex + ansiStrLen - 1];
        while (nextChar != 'm') {
            // Assign nextChar to the next letter
            nextChar = m_data[findIndex + ansiStrLen];
            ansiStrLen++;
        }

        // Copy the whole ANSI escape code into a string
        char* ansiStr = new char[ansiStrLen];
        for (int i = 0; i < ansiStrLen; i++) {
            ansiStr[i] = m_data[findIndex + i];
        }

        // Copy the remainder of the string
        int remainingStrLength = length(true) - (findIndex + ansiStrLen);
        char* remainingStr = new char[remainingStrLength + 1];
        for (int i = 0; i < remainingStrLength; i++) {
            remainingStr[i] = m_data[findIndex + ansiStrLen + i];
        }

        int newStrLength = findIndex + remainingStrLength;

        char* newStr = new char[newStrLength];
        newStr[0] = '\0';

        // Copy the part of the string prior to the find string
        char* data = new char[findIndex + 1];
        for (int i = 0; i < findIndex; i++) {
            data[i] = m_data[i];
        }

        data[findIndex] = '\0';

        // Concatenate the first part of the string onto a new string
        strcat_s(newStr, newStrLength, data);
        // Concatenate the remaining part of the string (not including the find string)
        strcat_s(newStr, newStrLength, remainingStr);

        setData(newStr);

        findIndex = find("\033[");

        delete[] remainingStr;
        remainingStr = nullptr;
        delete[] newStr;
        newStr = nullptr;
        delete[] ansiStr;
        ansiStr = nullptr;
    }

    return *this;
}

char& String::characterAt(size_t index) const
{
    return m_data[index];
}

String& String::clear()
{
    clearData();
    return *this;
}

String& String::clear(const int newLength)
{
    clearData(newLength);
    return *this;
}

String& String::clear(const int newLength, const bool appendNullTerminator_)
{
    clearData(newLength, appendNullTerminator_);
    return *this;
}

const char* String::cStr() const
{
    // A wrapper for String::data()
    return data();
}

String& String::setColor(Color color, ColorLayer colorLayer)
{
    return setColor(color, colorLayer, true);
}

String& String::setColor(Color color, ColorLayer colorLayer, const bool& clearAtEndOfLine)
{
    prepend(getCodeFromColor(color, colorLayer));
    if (clearAtEndOfLine) {
        append(getCodeFromColor(Color::None, ColorLayer::Foreground));
    }

    return *this;
}

const char* String::data() const
{
    return m_data;
}

bool String::equalTo(const String& other) const
{
    // This data length
    int tDataLen = strlen(m_data);
    // Other data length
    int oDataLen = strlen(other.data());

    if (tDataLen != oDataLen) {
        // Prevents from running the for loop, which is inefficient for just a mismatch in string size
        return false;
    }

    for (int i = 0; i < tDataLen; i++) {
        if (m_data[i] == other.data()[i]) {
            // Characters are the same
            continue;
        } else {
            // Character mismatch
            return false;
        }
    }

    return true; 
}

void String::setData(char c)
{
    setData(c, true);
}

void String::setData(const char* d)
{
    setData(d, true);
}

void String::setData(const String& str)
{
    setData(str, true);
}

void String::setData(char c, bool clearFirst)
{
    if (clearFirst) {
        // Initialize m_data - deletes m_data first
        clearData(1, true);
    } else {
        // Initializes m_data - does not delete m_data first
        initData(1, true);
    }

    m_data[0] = c;
    m_data[1] = '\0';
}

void String::setData(const char* d, bool clearFirst)
{
    int len = String::length(d, true);

    if (clearFirst) {
        // Initialize m_data - deletes m_data first
        clearData(String::length(d), true);
    } else {
        // Initializes m_data - does not delete m_data first
        initData(String::length(d), true);
    }

    strcpy_s(m_data, len, d);
    appendNullTerminator();
}

void String::setData(const String& str, bool clearFirst)
{
    if (clearFirst) {
        // Initialize m_data - deletes m_data first
        clearData(str.length(), true);
    } else {
        // Initializes m_data - does not delete m_data first
        initData(str.length(), true);
    }

    // Copy the contents of str into m_data
    for (int i = 0; i < str.length(true); i++) {
        m_data[i] = str.characterAt(i);
    }

    appendNullTerminator();
}

const size_t String::find(const String& findStr) const
{
    return find(0, findStr);
}

const size_t String::find(const size_t& startIndex, const String& findStr) const
{
    // A brute-force algorithm
    // Loop through all characters
    for (int i = startIndex; i < length(); i++) {
        // Loop through each index of findStr
        for (int j = 0; j < findStr.length(); j++) {
            if (m_data[i + j] == findStr.characterAt(j)) {
                if (j < findStr.length() - 1) {
                    // Not at the end of the string, loop j again
                    continue;
                } else {
                    // At the end of the find string's indexes
                    // Strings matched
                    return i;
                }
            } else {
                // Characters didn't match, loop i again
                break;
            }
        }
    }

    return -1;
}

const size_t String::length() const
{
    return length(false);
}

const size_t String::length(const bool includeNullTerminator) const
{
    if (m_data) {
        if (includeNullTerminator) {
            return strlen(m_data) + 1;
        } else {
            return strlen(m_data);
        }
    } else {
        return -1;
    }
}

const size_t String::length(const char* str)
{
    return length(str, false);
}

const size_t String::length(const char* str, const bool includeNullTerminator)
{
    if (str) {
        if (includeNullTerminator) {
            return strlen(str) + 1;
        } else {
            return strlen(str);
        }
    } else {
        return -1;
    }
}

const size_t String::length(const String& str)
{
    return length(str.data(), false);
}

const size_t String::length(const String& str, const bool includeNullTerminator)
{
    return length(str.data(), includeNullTerminator);
}

String& String::prepend(const String& other)
{
    String res;
    // Append the other string first
    res.append(other);
    // Append m_data on the end
    res.append(m_data);

    int resLength = res.length(true);
    clearData(resLength, false);
    strcpy_s(m_data, resLength, res.data());

    return *this;
}

String& String::replace(const String& findStr, const String& replaceStr)
{
    // Find the first find string (if it exists)
    size_t findIndex = find(findStr);

    while (findIndex != -1) {
        // Copy the remainder of the string after the find string
        int remainingStrLength = length(true) - (findIndex + findStr.length());
        char* remainingStr = new char[remainingStrLength + 1];
        for (int i = 0; i < remainingStrLength; i++) {
            remainingStr[i] = m_data[findIndex + findStr.length() + i];
        }


        // Copy m_data up until the start of findStr into a new string for concatenatation
        char* data = new char[findIndex + 1];
        for (int i = 0; i < findIndex; i++) {
            data[i] = m_data[i];
        }

        data[findIndex] = '\0';

        int newStrLength = findIndex + replaceStr.length() + remainingStrLength;

        char* newStr = new char[newStrLength];
        newStr[0] = '\0';

        // Concatenate all the strings together not including the findStr
        strcat_s(newStr, newStrLength, data);
        strcat_s(newStr, newStrLength, replaceStr.data());
        strcat_s(newStr, newStrLength, remainingStr);

        setData(newStr);

        findIndex = find(findStr);

        delete[] remainingStr;
        remainingStr = nullptr;
        delete[] newStr;
        newStr = nullptr;
    }

    return *this;
}

std::vector<char> String::toCharVector() const
{
    std::vector<char> charVector;

    for (int i = 0; i < strlen(m_data); i++) {
        charVector.push_back(m_data[i]);
    }

    return charVector;
}

String& String::toLower()
{
    _strlwr_s(m_data, length(true));
    return *this;
}

String& String::toUpper()
{
    _strupr_s(m_data, length(true));
    return *this;
}

void String::readFromConsole()
{
    int len = 100000;
    char* str = new char[len];

    std::cin.getline(str, len);

    clearData(String::length(str), true);

    strcpy_s(m_data, strlen(str) + 1, str);

    delete[] str;
    str = nullptr;

    std::cin.clear();
}

void String::writeToConsole() const
{
    writeToConsole(true);
}

void String::writeToConsole(const bool& flushEndOfLine) const
{
    std::cout << m_data;
    if (flushEndOfLine) {
        std::cout << std::endl;
    }
}

void String::appendNullTerminator()
{
    int len = length();

    if (m_data[len - 1] != '\0') {
        char* temp = new char[len + 1];
        temp[len] = '\0';
        strcpy_s(temp, len + 1, m_data);
        delete[] m_data;
        m_data = nullptr;
        m_data = new char[len + 1];
        strcpy_s(m_data, len + 1, temp);
        delete[] temp;
        temp = nullptr;
    }
}

void String::clearData()
{
    delete[] m_data;
    m_data = nullptr;
    initData(0, true);
}

void String::clearData(const int newLength)
{
    clearData(newLength, true);
}

void String::clearData(const int newLength, const bool appendNullTerminator_)
{
    delete[] m_data;
    m_data = nullptr;

    if (appendNullTerminator_) {
        initData(newLength + 1);
    } else {
        initData(newLength);
    }
}

void String::initData(const int newLength)
{
    initData(newLength, true);
}

void String::initData(const int newLength, const bool appendNullTerminator_)
{
    // WARNING: This method is dangerous
    // Deleting `m_data` MUST be handled separately from this method
    if (appendNullTerminator_) {
        m_data = new char[newLength + 1];
    } else {
        m_data = new char[newLength];
    }

    if (newLength == 0 && appendNullTerminator_) {
        // Initialize m_data with the null terminator
        m_data[0] = '\0';
    }
}
