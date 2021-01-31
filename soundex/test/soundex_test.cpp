#include <gmock/gmock.h>
#include "soundex.h"

using testing::Eq;
using testing::StartsWith;


TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) 
{
    Soundex soundex;

    auto encoded = soundex.encode("A");

    ASSERT_THAT(encoded, Eq("A000"));
}

TEST(SoundexEncoding, PadingWithZerosToEnsureThreeDigits) 
{
    Soundex soundex;

    auto encoded = soundex.encode("I");

    ASSERT_THAT(encoded, Eq("I000"));
}

class SoundexEncodingTest : public testing::Test {
public:
    Soundex soundex;
};

TEST_F(SoundexEncodingTest, RetainsSoleLetterOfOneLetterWord)
{
    auto encoded = soundex.encode("A");

    ASSERT_THAT(encoded, Eq("A000"));
}

TEST_F(SoundexEncodingTest, PadingWithZerosToEnsureThreeDigits)
{
    auto encoded = soundex.encode("I");

    ASSERT_THAT(encoded, Eq("I000"));
}

TEST_F(SoundexEncodingTest, IgnoreNoAlphabeta)
{
    ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncodingTest, ReplacesConstantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
    EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
    ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncodingTest, ReplacesMultipleConstantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncodingTest, IgnoreVowels)
{
    EXPECT_THAT(soundex.encode("Aaeioucdl"), Eq("A234"));
}

TEST_F(SoundexEncodingTest, CombineRepeatDigits)
{
    EXPECT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncodingTest, UpperCaseFirst)
{
    ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncodingTest, LimitsLengthToFourCharacters)
{
    EXPECT_THAT(soundex.encode("Acbld").length(), Eq(4u));
}

TEST_F(SoundexEncodingTest, IgnoresVowelLikeLetters) {
    ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncodingTest, IgnoresCaseWhenEncodingConsonants)
{
    ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncodingTest, CombineDuplicateFirst)
{
    ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncodingTest, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
    ASSERT_THAT(soundex.encode("Jbob"), Eq("J110"));
}
