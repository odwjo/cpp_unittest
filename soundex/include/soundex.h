#ifndef _SOUNDEX_H_
#define _SOUNDEX_H_

#include <string>
#include <unordered_map>

using namespace std;

class Soundex {
    static constexpr size_t MAX_CODE_LENGTH{4};
public:
    string encode(const string &word) const {
        return zeroPad(upperFront(head(word)) + tail(encodingDigits(word)));
    }
private:
    string head(const string &word) const {
        return word.substr(0, 1);
    }

    string upperFront(const string &word) const {
        return word.empty() ? "" : string(1, toupper(word.front()));
    }

    string tail(const string &word) const {
        return word.substr(1);
    }

    string encodingDigits(const string &word) const {
        string encodedStr;
        encodeHead(encodedStr, word);
        encodeTail(encodedStr, word);
        return encodedStr;
    }

    void encodeHead(string &encoding, const string &word) const {
        encoding += encodingDigit(word.front());
    }

    void encodeTail(string &encoding, const string &word) const {
        for (auto i = 1u; i < word.length(); i++) {
            if (!isComplete(encoding)) {
                encodeLetter(encoding, word[i], word[i - 1]);
            }
        }
    }

    void encodeLetter(string &encoding, char letter, char lastLetter) const {
        auto digit = encodingDigit(letter);
        if (digit != NotADigit && 
            (digit != lastDigit(encoding) || isVowel(lastLetter))) {
            encoding += digit;
        }
    }

    bool isVowel(char letter) const {
        return string("aeiouy").find(lower(letter)) != string::npos;
    }

    string lastDigit(const string &word) const {
        return word.empty() ? NotADigit : string(1, word.back());
    }

    bool isComplete(const string &word) const {
        return word.size() == MAX_CODE_LENGTH;
    }

    string encodingDigit(char c) const {
        const static unordered_map<char, string> digitMap{
            {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
            {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},
            {'s', "2"}, {'x', "2"}, {'z', "2"},
            {'d', "3"}, {'t', "3"},
            {'l', "4"},
            {'m', "5"}, {'n', "5"},
            {'r', "6"}
        };
        auto iter = digitMap.find(lower(c));
        return iter == digitMap.end() ? NotADigit : iter->second;
    }

    char lower(char c) const {
        return tolower(static_cast<unsigned char>(c));
    }

    string zeroPad(const string &word) const {
        string padZero;
        if (word.size() < MAX_CODE_LENGTH) {
            padZero = string(MAX_CODE_LENGTH - word.size(), '0');
        }
        return word + padZero;
    }

    const string NotADigit{"*"};
};

#endif