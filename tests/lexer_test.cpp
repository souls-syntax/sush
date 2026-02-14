#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "lexer.h"
#include "expander.h"

std::ostream& operator<<(std::ostream& os, const Segment& s) {
    std::string type;
    switch (s.quote) {
        case QuoteType::None: type = "None"; break;
        case QuoteType::SingleQuote: type = "SingleQuote"; break;
        case QuoteType::DoubleQuote: type = "DoubleQuote"; break;
    }
    return os << "{ text: \"" << s.text << "\", quote: " << type << " }";
}

// --- Test Fixture ---
class LexerTest : public ::testing::Test {
protected:
    std::vector<Segment> seg;
    void TearDown() override {
        seg.clear();
    }
};

// --- Tests ---
TEST_F(LexerTest, NormalText) {
    lexSegments("echo hello", seg);
    ASSERT_EQ(seg.size(), 1);
    EXPECT_EQ(seg[0].text, "echo hello");
    EXPECT_EQ(seg[0].quote, QuoteType::None);
}

TEST_F(LexerTest, SingleQuotes) {
    lexSegments("'hello world'", seg);
    ASSERT_EQ(seg.size(), 1);
    EXPECT_EQ(seg[0].text, "hello world"); 
    EXPECT_EQ(seg[0].quote, QuoteType::SingleQuote);
}

TEST_F(LexerTest, DoubleQuotes) {
    lexSegments("\"hello world\"", seg);
    ASSERT_EQ(seg.size(), 1);
    EXPECT_EQ(seg[0].text, "hello world");
    EXPECT_EQ(seg[0].quote, QuoteType::DoubleQuote);
}

TEST_F(LexerTest, MixedQuotes) {
    // echo 'foo' "bar" -> [echo ] [foo] [ ] [bar]
    
    lexSegments("echo 'foo' \"bar\"", seg);
    // 1. "echo " (None)
    // 2. "foo"   (Single)
    // 3. " "     (None)
    // 4. "bar"   (Double)
    
    ASSERT_EQ(seg.size(), 4);
    EXPECT_EQ(seg[0].text, "echo ");
    EXPECT_EQ(seg[1].text, "foo");
    EXPECT_EQ(seg[2].text, " ");
    EXPECT_EQ(seg[3].text, "bar");
}
// You'll need to declare the function in your header or top of test file
// extern void expandSegments(std::vector<Segment>& segs);

TEST_F(LexerTest, ExpandVariable) {
    // Setup: Simulate a Double Quoted segment with an env var
    // We mock the environment variable for the test
    setenv("TEST_VAR", "MissionSuccess", 1); 

    std::vector<Segment> segs = {
        { "Status: $TEST_VAR", QuoteType::DoubleQuote }
    };

    expandSegments(segs);

    EXPECT_EQ(segs[0].text, "Status: MissionSuccess");
}

TEST_F(LexerTest, IgnoreSingleQuote) {
    setenv("TEST_VAR", "Fail", 1);

    std::vector<Segment> segs = {
        { "Status: $TEST_VAR", QuoteType::SingleQuote }
    };

    expandSegments(segs);

    // Should remain strictly literal
    EXPECT_EQ(segs[0].text, "Status: $TEST_VAR");
}

TEST_F(LexerTest, ExpandMultiple) {
    setenv("A", "Alpha", 1);
    setenv("B", "Bravo", 1);

    std::vector<Segment> segs = {
        { "$A and $B", QuoteType::None }
    };

    expandSegments(segs);

    EXPECT_EQ(segs[0].text, "Alpha and Bravo");
}
