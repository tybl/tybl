// License: The Unlicense (https://unlicense.org)
#include "json/value.hpp"

#include <parse/character.hpp>
#include <vodka/basic_fixed_string.hpp>
#include <vodka/parse_error.hpp>

#include <cassert>
#include <iostream>
#include <regex>
#include <string_view>
#include <vector>

namespace tybl::json {

static const std::regex str_re{R"("(?:\\(?:["\\\/bfnrt]|u[a-fA-F0-9]{4})|[^"\\\0-\x1F\x7F]+)*")",
                               std::regex_constants::ECMAScript | std::regex_constants::optimize};

static const std::regex num_re{"^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?",
                               std::regex_constants::ECMAScript | std::regex_constants::optimize};

struct json_parser {

  static auto parse_json(std::string_view& p_in) -> value { return json_parser::parse_element(p_in); }

private:
  static constexpr const tybl::vodka::basic_fixed_string FALSE{"false"};
  static constexpr const tybl::vodka::basic_fixed_string NIL{"null"};
  static constexpr const tybl::vodka::basic_fixed_string TRUE{"true"};
  static constexpr std::string_view WHITESPACE_CHARS{"\x09\x0A\x0D\x20"};

  static auto is_digit(char p_c) -> bool { return is_in_range<char, '0', '9'>(p_c); }

  static auto is_hex(char p_c) -> bool {
    return is_digit(p_c) || is_in_range<char, 'A', 'F'>(p_c) || is_in_range<char, 'a', 'f'>(p_c);
  }

  template <class Type, Type low, Type high>
  static auto is_in_range(Type p_c) -> bool {
    static_assert(low <= high, "Calling is_in_range with invalid range");
    return ((low <= p_c) && (p_c <= high));
  }

  static auto parse_array(std::string_view& p_in) -> std::vector<value> {
    if (!parse::character<'['>(p_in)) {
      throw vodka::parse_error("Error: JSON Array not found");
    }
    // printf("[");
    std::vector<value> result;
    parse_whitespace(p_in);
    if (!p_in.empty() && ']' != p_in.front()) {
      result.push_back(parse_value(p_in));
      parse_whitespace(p_in);
      while (parse::character<','>(p_in)) {
        // printf(",");
        result.push_back(parse_element(p_in));
      }
    }
    if (!parse::character<']'>(p_in)) {
      throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON Array");
    }
    // printf("]");
    return result;
  }

  static auto parse_element(std::string_view& p_in) -> value {
    json_parser::parse_whitespace(p_in);
    auto result = json_parser::parse_value(p_in);
    json_parser::parse_whitespace(p_in);
    return result;
  }

  template <tybl::vodka::basic_fixed_string Literal>
  static auto parse_literal(std::string_view& p_in) -> std::string_view {
    auto result = p_in.substr(0, Literal.size());
    if (static_cast<std::string_view>(Literal) != result) {
      throw vodka::parse_error("Error: Expected to find JSON literal '{}'");
    }
    p_in.remove_prefix(Literal.size());
    // printf(Literal);
    return result;
  }

  static auto parse_number(std::string_view& p_in) -> std::string_view {
    static std::regex re("^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?");
    const auto rei = std::cregex_iterator(p_in.begin(), p_in.end(), re);
    if (!rei->ready() || rei->empty() || rei->position() != 0) {
      throw vodka::parse_error("Error: Expected JSON Number");
    }
    auto len = static_cast<size_t>(rei->length());
    auto result = p_in.substr(0, len);
    p_in.remove_prefix(len);
    // printf("#");
    return result;
  }

  static auto parse_object(std::string_view& p_in) -> std::map<std::string_view, value> {
    if (!parse::character<'{'>(p_in)) {
      throw vodka::parse_error("Error: JSON Object not found");
    }
    // printf("{");
    std::map<std::string_view, value> result;
    parse_whitespace(p_in);
    if (!p_in.empty() && '}' != p_in.front()) {
      std::string_view key = parse_string(p_in);
      parse_whitespace(p_in);
      if (!parse::character<':'>(p_in)) {
        throw vodka::parse_error("Error: Missing ':' within JSON Object1");
      }
      // printf(":");
      result[key] = parse_element(p_in);
      while (parse::character<','>(p_in)) {
        // printf(",");
        parse_whitespace(p_in);
        key = parse_string(p_in);
        parse_whitespace(p_in);
        if (!parse::character<':'>(p_in)) {
          throw vodka::parse_error("Error: Missing ':' within JSON Object2");
        }
        // printf(":");
        result[key] = parse_element(p_in);
      }
    }
    if (!parse::character<'}'>(p_in)) {
      throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON Object");
    }
    // printf("}");
    return result;
  }

  static auto parse_string(std::string_view& p_in) -> std::string_view {
    if (!parse::character<'"'>(p_in)) {
      throw vodka::parse_error("Error: JSON String not found");
    }
    size_t i = 0;
    for (; (i < p_in.size()) && ('"' != p_in[i]); ++i) {
      if (is_in_range<char, 0x0, 0x19>(p_in[i])) {
        throw vodka::parse_error("Error: String includes unescaped character in the range 0000 . 0019");
      }
      if ('\\' == p_in[i]) {
        if (i + 1 >= p_in.size()) {
          throw vodka::parse_error("Error: Not enough hexadecimal characters after escape");
        }
        ++i;
        if (('"' != p_in[i]) && ('\\' != p_in[i]) && ('/' != p_in[i]) && ('b' != p_in[i]) && ('f' != p_in[i]) &&
            ('n' != p_in[i]) && ('r' != p_in[i]) && ('t' != p_in[i]) && ('u' != p_in[i])) {
          throw vodka::parse_error("Error: Unexpected escaped character");
        }
        if ('u' == p_in[i]) {
          if (i + 4 >= p_in.size()) {
            throw vodka::parse_error("Error: Not enough hexadecimal characters in escaped 'u'");
          }
          if (!is_hex(p_in[i + 1]) || !is_hex(p_in[i + 2]) || !is_hex(p_in[i + 3]) || !is_hex(p_in[i + 4])) {
            throw vodka::parse_error("Error: Non-hexadecimal characters in escaped 'u'");
          }
          i += 4;
        }
      }
    }
    if (p_in.size() == i) {
      throw vodka::parse_error("Error: JSON input ended before string was closed");
    }
    auto result = p_in.substr(0, i);
    p_in.remove_prefix(i + 1);
    // printf("\"");
    return result;
  }

  static auto parse_value(std::string_view& p_in) -> value {
    value result;
    if (p_in.empty()) {
      throw vodka::parse_error("Error: Expected JSON value before end of input");
    }
    switch (p_in.front()) {
      case '"': result = parse_string(p_in); break;
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': result = parse_number(p_in); break;
      case '[': result = parse_array(p_in); break;
      case 'f': result = parse_literal<FALSE>(p_in); break;
      case 'n': result = parse_literal<NIL>(p_in); break;
      case 't': result = parse_literal<TRUE>(p_in); break;
      case '{': result = parse_object(p_in); break;
      default: throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON value");
    }
    return result;
  }

  static void parse_whitespace(std::string_view& p_in) {
    auto pos = p_in.find_first_not_of(WHITESPACE_CHARS);
    p_in.remove_prefix((std::string_view::npos != pos) ? pos : 0); // consume whitespace
  }

}; // struct json_parser

#if 0
static const std::regex str_re(R"("(?:\\(?:["\\\/bfnrt]|u[a-fA-F0-9]{4})|[^"\\\0-\x1F\x7F]+)*")",
                               std::regex_constants::ECMAScript | std::regex_constants::optimize);

static const std::regex num_re("^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?",
                               std::regex_constants::ECMAScript | std::regex_constants::optimize);

constexpr bool is_onenine(char p_c) { return is_in_range<char, '1', '9'>(p_c); }

constexpr bool is_whitespace(char p_c) {
  return (('\x09' == p_c) || ('\x0A' == p_c) || ('\x0D' == p_c) || ('\x20' == p_c));
}
#endif

enum class TokenType {
  NIL,
  TRUE,
  FALSE,
  OBJECT_OPEN,
  OBJECT_CLOSE,
  ARRAY_OPEN,
  ARRAY_CLOSE,
  SEPARATOR,
  DELIMITER,
  STRING,
  NUMBER,
  UNKNOWN,
};

// Intent: Represents an individual atom of parsed JSON text.
// Examples:
//    * ',': TokenType::DELIMITER
//    * '"This is a string: [nothing inside is a token]"': TokenType::STRING
// Caveats:
//    * Does not retain JSON text, references it only
// Invariants:
//    * Non-zero length
//    * No leading whitespace
//    * Must be valid token (i.e. string...)
struct token {

  [[nodiscard]] auto type() const -> TokenType { return calculate_type(m_value); }

  [[nodiscard]] auto value() const -> std::string_view { return m_value; }

  explicit token(std::string_view p_sv)
    : m_value(p_sv) {}

  // Intent: Determine the token type of the input.
  // Caveats:
  //    * Empty input:
  //       - Return UNKNOWN:
  //       - Ignore error:
  //    * Leading whitespace:
  //       - Return TokenType::WHITESPACE:
  //       - Return TokenType::UNKNOWN: May be interpreted as an error
  //       - Iterate to first non-whitespace: Location of first non-whitespace
  //                                          code-point is not indicated
  // Decisions:
  //    * Empty input:
  //    * Leading whitespace:
  static auto calculate_type(std::string_view p_in) -> TokenType {
    assert(!p_in.empty());
    TokenType result = TokenType::UNKNOWN;
    // TODO(tblyons): Can we guarantee this function will never be called with
    //                an empty input? If so, we can remove this redundant call
    //                to in.empty().
    if (!p_in.empty()) {
      switch (p_in.front()) {
        case '"': result = TokenType::STRING; break;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': result = TokenType::NUMBER; break;
        case '[': result = TokenType::ARRAY_OPEN; break;
        case ']': result = TokenType::ARRAY_CLOSE; break;
        case 'f': result = TokenType::FALSE; break;
        case 'n': result = TokenType::NIL; break;
        case 't': result = TokenType::TRUE; break;
        case '{': result = TokenType::OBJECT_OPEN; break;
        case '}': result = TokenType::OBJECT_CLOSE; break;
        case ',': result = TokenType::DELIMITER; break;
        case ':': result = TokenType::SEPARATOR; break;
        default: break;
      }
    }
    return result;
  }

  // Intent: Calculate length of JSON token in the input.
  // Caveats:
  //    * Empty input:
  //       - Return zero:
  //       - Ignore error:
  //    * Invalid token:
  //       - Return zero: Empty value and unknown type.
  //                      Consumers must know to move beyond it.
  //       - Return one: The token has a value and a type.
  //                     It could be ignored if desired. Loses context.
  //       - Return length of invalid points:
  // Decisions:
  //    * Empty input:
  //    * Invalid token:
  static auto length(std::string_view p_in) -> size_t {
    size_t result = 1;
    if (p_in.empty()) {
      return 0;
    }
    switch (calculate_type(p_in)) {
      case TokenType::NIL:
      case TokenType::TRUE: result = 4; break;
      case TokenType::FALSE: result = 5; break;
      case TokenType::STRING:
        result = static_cast<size_t>(std::cregex_iterator(p_in.begin(), p_in.end(), str_re)->length());
        break;
      case TokenType::NUMBER:
        result = static_cast<size_t>(std::cregex_iterator(p_in.begin(), p_in.end(), num_re)->length());
        break;
      case TokenType::OBJECT_OPEN:
      case TokenType::OBJECT_CLOSE:
      case TokenType::ARRAY_OPEN:
      case TokenType::ARRAY_CLOSE:
      case TokenType::SEPARATOR:
      case TokenType::DELIMITER:
      case TokenType::UNKNOWN: break; // default value of 1 is correct
    }
    return result;
  }

private:
  std::string_view m_value;
}; // struct token

#if 0
struct token_iterator {

  token_iterator(std::string_view p_in) : m_value(p_in) {}

  token_iterator operator++() {
    m_value.remove_prefix(token::length(m_value));
      while (!m_value.empty() && is_whitespace(m_value.front()))
      {
        m_value.remove_prefix(1);
      }
      return *this;
   }

   token operator*() {
      return token(m_value);
   }

private:
   std::string_view m_value;
}; // struct token_iterator

struct Json {
   struct iterator {
      explicit iterator() {}
      iterator& operator++() { /* Logic here */ return *this; }
      iterator operator++(int) { iterator r = *this; ++(*this); return r; }
   private:
      void function() {
      }
   };
   iterator begin() { return iterator(); }
   iterator end() { return iterator(); }
private:
   std::string m_value;
}; // struct Json
#endif

static auto lex(std::string_view p_in) -> std::vector<token> {
  std::vector<token> result;
  while (!p_in.empty()) {
    switch (p_in.front()) {
      case '\x09':
      case '\x0A':
      case '\x0D':
      case '\x20':
        // Whitespace
        p_in.remove_prefix(1);
        break;
      case '"': {
        // String
        auto len = static_cast<size_t>(std::cregex_iterator(p_in.begin(), p_in.end(), str_re)->length());
        result.emplace_back(p_in.substr(0, len));
        p_in.remove_prefix(len);
        break;
      }
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        // Number
        auto len = static_cast<size_t>(std::cregex_iterator(p_in.begin(), p_in.end(), num_re)->length());
        result.emplace_back(p_in.substr(0, len));
        p_in.remove_prefix(len);
        break;
      }
      case '[':
      case ']':
      case '{':
      case '}':
      case ',':
      case ':':
        result.emplace_back(p_in.substr(0, 1));
        p_in.remove_prefix(1);
        break;
      case 'f':
        result.emplace_back(p_in.substr(0, 5));
        p_in.remove_prefix(5);
        break;
      case 'n':
      case 't':
        result.emplace_back(p_in.substr(0, 4));
        p_in.remove_prefix(4);
        break;
      default:
        // printf("not sure what to do with: '%c'\n", p_in.front());
        throw vodka::parse_error("Error: Encountered unexpected character while lexing JSON");
    }
  }
  return result;
}

#if 0
value parse_element(std::string_view& p_in);
value parse_value(std::string_view& p_in);

static void parse_whitespace(std::string_view& p_in) {
  static constexpr std::string_view WHITESPACE_CHARS("\x09\x0A\x0D\x20");
  auto pos = p_in.find_first_not_of(WHITESPACE_CHARS);
  p_in.remove_prefix((std::string_view::npos != pos) ? pos : 0); // consume whitespace
} // parse_whitespace(std::string_view&)

static std::string_view parse_number(std::string_view& p_in) {
  static std::regex re("^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?");
  auto rei = std::cregex_iterator(p_in.begin(), p_in.end(), re);
  if (!rei->ready() || rei->empty() || rei->position() != 0) {
    throw vodka::parse_error("Error: Expected JSON Number");
  }
  auto len = static_cast<size_t>(rei->length());
  std::string_view result(p_in.data(), len);
  p_in.remove_prefix(len);
  printf("#");
  return result;
} // parse_number(std::string_view&)

static std::string_view parse_string(std::string_view& p_in) {
  if (!parse::parse_char<'"'>(p_in)) {
    throw vodka::parse_error("Error: JSON String not found");
  }
  size_t i = 0;
  for (; (i < p_in.size()) && ('"' != p_in[i]); ++i) {
    if (is_in_range<char, 0x0, 0x19>(p_in[i])) {
      throw vodka::parse_error("Error: String includes unescaped character in the range 0000 . 0019");
    }
    if ('\\' == p_in[i]) {
      if (i + 1 >= p_in.size()) {
        throw vodka::parse_error("Error: Not enough hexadecimal characters after escape");
      }
      ++i;
      if (('"' != p_in[i]) && ('\\' != p_in[i]) && ('/' != p_in[i]) && ('b' != p_in[i]) && ('f' != p_in[i]) &&
          ('n' != p_in[i]) && ('r' != p_in[i]) && ('t' != p_in[i]) && ('u' != p_in[i])) {
        throw vodka::parse_error("Error: Unexpected escaped character");
      }
      if ('u' == p_in[i]) {
        if (i + 4 >= p_in.size()) {
          throw vodka::parse_error("Error: Not enough hexadecimal characters in escaped 'u'");
        }
        if (!is_hex(p_in[i + 1]) || !is_hex(p_in[i + 2]) || !is_hex(p_in[i + 3]) || !is_hex(p_in[i + 4])) {
          throw vodka::parse_error("Error: Non-hexadecimal characters in escaped 'u'");
        }
        i += 4;
      }
    }
  }
  if (p_in.size() == i) {
    throw vodka::parse_error("Error: JSON input ended before string was closed");
  }
  auto result = p_in.substr(0, i);
  p_in.remove_prefix(i + 1);
  printf("\"");
  return result;
} // parse_string(std::string_view&)

// Recursive
static std::vector<value> parse_array(std::string_view& p_in) {
  if (!parse::parse_char<'['>(p_in)) {
    throw vodka::parse_error("Error: JSON Array not found");
  }
  printf("[");
  std::vector<value> result;
  parse_whitespace(p_in);
  if (!p_in.empty() && ']' != p_in.front()) {
    result.push_back(parse_value(p_in));
    parse_whitespace(p_in);
    while (parse::parse_char<','>(p_in)) {
      printf(",");
      result.push_back(parse_element(p_in));
    }
  }
  if (!parse::parse_char<']'>(p_in)) {
    throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON Array");
  }
  printf("]");
  return result;
} // parse_array(std::string_view&)

// Recursive
static std::map<std::string_view, value> parse_object(std::string_view& p_in) {
  if (!parse::parse_char<'{'>(p_in)) {
    throw vodka::parse_error("Error: JSON Object not found");
  }
  printf("{");
  std::map<std::string_view, value> result;
  parse_whitespace(p_in);
  if (!p_in.empty() && '}' != p_in.front()) {
    std::string_view key = parse_string(p_in);
    parse_whitespace(p_in);
    if (!parse::parse_char<':'>(p_in)) {
      throw vodka::parse_error("Error: Missing ':' within JSON Object1");
    }
    printf(":");
    result[key] = parse_element(p_in);
    while (parse::parse_char<','>(p_in)) {
      printf(",");
      parse_whitespace(p_in);
      key = parse_string(p_in);
      parse_whitespace(p_in);
      if (!parse::parse_char<':'>(p_in)) {
        throw vodka::parse_error("Error: Missing ':' within JSON Object2");
      }
      printf(":");
      result[key] = parse_element(p_in);
    }
  }
  if (!parse::parse_char<'}'>(p_in)) {
    throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON Object");
  }
  printf("}");
  return result;
} // parse_object(std::string_view&)

// Recursive
value parse_value(std::string_view& p_in) {
  value result;
  if (p_in.empty()) {
    throw vodka::parse_error("Error: Expected JSON value before end of input");
  }
  switch (p_in.front()) {
    case '"': result = parse_string(p_in); break;
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': result = parse_number(p_in); break;
    case '[': result = parse_array(p_in); break;
    case 'f': result = parse_literal<FALSE>(p_in); break;
    case 'n': result = parse_literal<NIL>(p_in); break;
    case 't': result = parse_literal<TRUE>(p_in); break;
    case '{': result = parse_object(p_in); break;
    default: throw vodka::parse_error("Error: Encountered unexpected character while parsing JSON value");
  }
  return result;
} // parse_value(std::string_view&)

// Recursive
value parse_element(std::string_view& p_in) {
  parse_whitespace(p_in);
  auto result = parse_value(p_in);
  parse_whitespace(p_in);
  return result;
} // parse_element(std::string_view&)

static value parse_json(std::string_view& p_in) {
  return parse_element(p_in);
} // parse_json(std::string_view&)
#endif

} // namespace tybl::json

auto main() -> int {
  std::string_view input(
      R"([ { "_id": "5e02311eb4f7fff26d6c8646", "index": 0, "guid": "0ea86154-c909-4220-97bc-21ae68a58474", "isActive": false, "balance": "$3,305.12", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "green", "name": { "first": "Toni", "last": "Griffin" }, "company": "WAZZU", "email": "toni.griffin@wazzu.info", "phone": "+1 (869) 462-3047", "address": "570 Lake Street, Brazos, Wisconsin, 2880", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, June 26, 2015 10:53 PM", "latitude": "-81.846796", "longitude": "-144.778871", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Colon Vargas" }, { "id": 1, "name": "Hahn Summers" }, { "id": 2, "name": "Battle Gilliam" } ], "greeting": "Hello, Toni! You have 9 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e2d3ae05377159db2", "index": 1, "guid": "ae96247d-dc1f-42f6-bc81-1cdd6b5c6829", "isActive": false, "balance": "$1,216.58", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "brown", "name": { "first": "Betsy", "last": "Jacobson" }, "company": "JETSILK", "email": "betsy.jacobson@jetsilk.io", "phone": "+1 (904) 459-3265", "address": "402 Little Street, Oasis, Kentucky, 6452", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, July 9, 2015 4:20 AM", "latitude": "-70.234084", "longitude": "152.163603", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Guzman Landry" }, { "id": 1, "name": "Schroeder Whitfield" }, { "id": 2, "name": "Guerrero Glass" } ], "greeting": "Hello, Betsy! You have 10 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311eaaec27bddb05708e", "index": 2, "guid": "cff1b9ac-f291-414f-97ca-101976eaeef6", "isActive": true, "balance": "$2,621.82", "picture": "http://placehold.it/32x32", "age": 24, "eyeColor": "green", "name": { "first": "Clark", "last": "Barnes" }, "company": "PYRAMAX", "email": "clark.barnes@pyramax.tv", "phone": "+1 (943) 500-2711", "address": "339 Polar Street, Bowmansville, Missouri, 1724", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, February 5, 2016 6:26 AM", "latitude": "-18.563984", "longitude": "46.697694", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Elba Huff" }, { "id": 1, "name": "Kathleen Conner" }, { "id": 2, "name": "Hannah Burns" } ], "greeting": "Hello, Clark! You have 6 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311ebd588df9ba3e0efe", "index": 3, "guid": "50f54d1c-aaeb-45c8-bcaa-3c7912acd29a", "isActive": true, "balance": "$3,393.94", "picture": "http://placehold.it/32x32", "age": 31, "eyeColor": "brown", "name": { "first": "Keller", "last": "Bates" }, "company": "OVIUM", "email": "keller.bates@ovium.co.uk", "phone": "+1 (873) 573-3712", "address": "809 Quay Street, Lorraine, Maryland, 8007", "about": "<TypeError: loremIpsum is not a function>", "registered": "Monday, April 18, 2016 11:35 AM", "latitude": "-38.828076", "longitude": "-11.594935", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Lorene Stephens" }, { "id": 1, "name": "Rosanna Pierce" }, { "id": 2, "name": "Ana Travis" } ], "greeting": "Hello, Keller! You have 10 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ec64656551ff176fd", "index": 4, "guid": "efa71fb6-e9a7-4126-9fdd-7e8c364bdbca", "isActive": true, "balance": "$2,071.33", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "blue", "name": { "first": "Ursula", "last": "Rosario" }, "company": "TWIIST", "email": "ursula.rosario@twiist.org", "phone": "+1 (961) 466-2258", "address": "142 Lawrence Avenue, Caspar, Pennsylvania, 7497", "about": "<TypeError: loremIpsum is not a function>", "registered": "Saturday, April 7, 2018 12:14 AM", "latitude": "8.87866", "longitude": "159.005552", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Espinoza Harding" }, { "id": 1, "name": "Cynthia Washington" }, { "id": 2, "name": "Felecia Mayo" } ], "greeting": "Hello, Ursula! You have 7 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311e0b2739a8ab4c2b73", "index": 5, "guid": "424b50e2-7426-4ad3-9895-1915674ac20c", "isActive": false, "balance": "$1,763.35", "picture": "http://placehold.it/32x32", "age": 27, "eyeColor": "green", "name": { "first": "Parsons", "last": "Reynolds" }, "company": "BIOTICA", "email": "parsons.reynolds@biotica.us", "phone": "+1 (954) 537-2763", "address": "758 Highland Avenue, Sims, Northern Mariana Islands, 5317", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, April 13, 2017 7:29 PM", "latitude": "51.800116", "longitude": "-166.912803", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Carmella Rasmussen" }, { "id": 1, "name": "Cox Pope" }, { "id": 2, "name": "Christian Mills" } ], "greeting": "Hello, Parsons! You have 5 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e9a939b787c8962f5", "index": 6, "guid": "c040191c-4d08-438a-8a18-bffb81725b29", "isActive": true, "balance": "$2,125.23", "picture": "http://placehold.it/32x32", "age": 20, "eyeColor": "brown", "name": { "first": "Sanford", "last": "Luna" }, "company": "REPETWIRE", "email": "sanford.luna@repetwire.ca", "phone": "+1 (986) 418-3119", "address": "206 Truxton Street, Tryon, South Carolina, 7676", "about": "<TypeError: loremIpsum is not a function>", "registered": "Sunday, January 17, 2016 3:58 AM", "latitude": "-5.489691", "longitude": "18.393453", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Katharine Leach" }, { "id": 1, "name": "Jackie Howard" }, { "id": 2, "name": "Ericka Kelley" } ], "greeting": "Hello, Sanford! You have 8 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ed0701d0ce968a58c", "index": 7, "guid": "6956ec95-c140-4a7d-bdbf-186d2788abe4", "isActive": true, "balance": "$2,766.13", "picture": "http://placehold.it/32x32", "age": 38, "eyeColor": "blue", "name": { "first": "Witt", "last": "Winters" }, "company": "VETRON", "email": "witt.winters@vetron.net", "phone": "+1 (836) 510-3138", "address": "132 Wogan Terrace, Maury, Ohio, 1113", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, November 2, 2018 7:53 PM", "latitude": "28.934741", "longitude": "149.678983", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Iva Garcia" }, { "id": 1, "name": "Meyers Gentry" }, { "id": 2, "name": "Kenya Carpenter" } ], "greeting": "Hello, Witt! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311e615133e998ffb689", "index": 8, "guid": "76f59cf9-a1f5-4289-8f04-97be29cbd557", "isActive": true, "balance": "$2,317.41", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "green", "name": { "first": "Reilly", "last": "Meadows" }, "company": "CENTICE", "email": "reilly.meadows@centice.name", "phone": "+1 (987) 457-3166", "address": "132 Llama Court, Elrama, American Samoa, 5050", "about": "<TypeError: loremIpsum is not a function>", "registered": "Wednesday, August 17, 2016 1:43 AM", "latitude": "87.182673", "longitude": "97.286414", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Louisa Oneil" }, { "id": 1, "name": "Hendricks Franco" }, { "id": 2, "name": "Sherrie Cote" } ], "greeting": "Hello, Reilly! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311ea3a55d6ed92a7718", "index": 9, "guid": "e7d3104c-18b7-4251-a0e3-eba8f26e5dc6", "isActive": true, "balance": "$3,915.23", "picture": "http://placehold.it/32x32", "age": 36, "eyeColor": "green", "name": { "first": "Buchanan", "last": "Dean" }, "company": "AMTAS", "email": "buchanan.dean@amtas.com", "phone": "+1 (986) 461-3487", "address": "950 Moffat Street, Century, New York, 8233", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, December 19, 2019 9:00 PM", "latitude": "-34.83994", "longitude": "-46.420874", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Woodard Stone" }, { "id": 1, "name": "Sharon Fulton" }, { "id": 2, "name": "Dejesus Reid" } ], "greeting": "Hello, Buchanan! You have 8 unread messages.", "favoriteFruit": "banana" } ])");
  auto result = tybl::json::json_parser::parse_json(input);
  static_cast<void>(result);
  // document count = json/"root"/"home"/"user"/"doc"/"fin"/"budget"/"count";
  input = static_cast<std::string_view>(
      R"([ { "_id": "5e02311eb4f7fff26d6c8646", "index": 0, "guid": "0ea86154-c909-4220-97bc-21ae68a58474", "isActive": false, "balance": "$3,305.12", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "green", "name": { "first": "Toni", "last": "Griffin" }, "company": "WAZZU", "email": "toni.griffin@wazzu.info", "phone": "+1 (869) 462-3047", "address": "570 Lake Street, Brazos, Wisconsin, 2880", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, June 26, 2015 10:53 PM", "latitude": "-81.846796", "longitude": "-144.778871", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Colon Vargas" }, { "id": 1, "name": "Hahn Summers" }, { "id": 2, "name": "Battle Gilliam" } ], "greeting": "Hello, Toni! You have 9 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e2d3ae05377159db2", "index": 1, "guid": "ae96247d-dc1f-42f6-bc81-1cdd6b5c6829", "isActive": false, "balance": "$1,216.58", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "brown", "name": { "first": "Betsy", "last": "Jacobson" }, "company": "JETSILK", "email": "betsy.jacobson@jetsilk.io", "phone": "+1 (904) 459-3265", "address": "402 Little Street, Oasis, Kentucky, 6452", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, July 9, 2015 4:20 AM", "latitude": "-70.234084", "longitude": "152.163603", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Guzman Landry" }, { "id": 1, "name": "Schroeder Whitfield" }, { "id": 2, "name": "Guerrero Glass" } ], "greeting": "Hello, Betsy! You have 10 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311eaaec27bddb05708e", "index": 2, "guid": "cff1b9ac-f291-414f-97ca-101976eaeef6", "isActive": true, "balance": "$2,621.82", "picture": "http://placehold.it/32x32", "age": 24, "eyeColor": "green", "name": { "first": "Clark", "last": "Barnes" }, "company": "PYRAMAX", "email": "clark.barnes@pyramax.tv", "phone": "+1 (943) 500-2711", "address": "339 Polar Street, Bowmansville, Missouri, 1724", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, February 5, 2016 6:26 AM", "latitude": "-18.563984", "longitude": "46.697694", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Elba Huff" }, { "id": 1, "name": "Kathleen Conner" }, { "id": 2, "name": "Hannah Burns" } ], "greeting": "Hello, Clark! You have 6 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311ebd588df9ba3e0efe", "index": 3, "guid": "50f54d1c-aaeb-45c8-bcaa-3c7912acd29a", "isActive": true, "balance": "$3,393.94", "picture": "http://placehold.it/32x32", "age": 31, "eyeColor": "brown", "name": { "first": "Keller", "last": "Bates" }, "company": "OVIUM", "email": "keller.bates@ovium.co.uk", "phone": "+1 (873) 573-3712", "address": "809 Quay Street, Lorraine, Maryland, 8007", "about": "<TypeError: loremIpsum is not a function>", "registered": "Monday, April 18, 2016 11:35 AM", "latitude": "-38.828076", "longitude": "-11.594935", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Lorene Stephens" }, { "id": 1, "name": "Rosanna Pierce" }, { "id": 2, "name": "Ana Travis" } ], "greeting": "Hello, Keller! You have 10 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ec64656551ff176fd", "index": 4, "guid": "efa71fb6-e9a7-4126-9fdd-7e8c364bdbca", "isActive": true, "balance": "$2,071.33", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "blue", "name": { "first": "Ursula", "last": "Rosario" }, "company": "TWIIST", "email": "ursula.rosario@twiist.org", "phone": "+1 (961) 466-2258", "address": "142 Lawrence Avenue, Caspar, Pennsylvania, 7497", "about": "<TypeError: loremIpsum is not a function>", "registered": "Saturday, April 7, 2018 12:14 AM", "latitude": "8.87866", "longitude": "159.005552", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Espinoza Harding" }, { "id": 1, "name": "Cynthia Washington" }, { "id": 2, "name": "Felecia Mayo" } ], "greeting": "Hello, Ursula! You have 7 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311e0b2739a8ab4c2b73", "index": 5, "guid": "424b50e2-7426-4ad3-9895-1915674ac20c", "isActive": false, "balance": "$1,763.35", "picture": "http://placehold.it/32x32", "age": 27, "eyeColor": "green", "name": { "first": "Parsons", "last": "Reynolds" }, "company": "BIOTICA", "email": "parsons.reynolds@biotica.us", "phone": "+1 (954) 537-2763", "address": "758 Highland Avenue, Sims, Northern Mariana Islands, 5317", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, April 13, 2017 7:29 PM", "latitude": "51.800116", "longitude": "-166.912803", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Carmella Rasmussen" }, { "id": 1, "name": "Cox Pope" }, { "id": 2, "name": "Christian Mills" } ], "greeting": "Hello, Parsons! You have 5 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e9a939b787c8962f5", "index": 6, "guid": "c040191c-4d08-438a-8a18-bffb81725b29", "isActive": true, "balance": "$2,125.23", "picture": "http://placehold.it/32x32", "age": 20, "eyeColor": "brown", "name": { "first": "Sanford", "last": "Luna" }, "company": "REPETWIRE", "email": "sanford.luna@repetwire.ca", "phone": "+1 (986) 418-3119", "address": "206 Truxton Street, Tryon, South Carolina, 7676", "about": "<TypeError: loremIpsum is not a function>", "registered": "Sunday, January 17, 2016 3:58 AM", "latitude": "-5.489691", "longitude": "18.393453", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Katharine Leach" }, { "id": 1, "name": "Jackie Howard" }, { "id": 2, "name": "Ericka Kelley" } ], "greeting": "Hello, Sanford! You have 8 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ed0701d0ce968a58c", "index": 7, "guid": "6956ec95-c140-4a7d-bdbf-186d2788abe4", "isActive": true, "balance": "$2,766.13", "picture": "http://placehold.it/32x32", "age": 38, "eyeColor": "blue", "name": { "first": "Witt", "last": "Winters" }, "company": "VETRON", "email": "witt.winters@vetron.net", "phone": "+1 (836) 510-3138", "address": "132 Wogan Terrace, Maury, Ohio, 1113", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, November 2, 2018 7:53 PM", "latitude": "28.934741", "longitude": "149.678983", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Iva Garcia" }, { "id": 1, "name": "Meyers Gentry" }, { "id": 2, "name": "Kenya Carpenter" } ], "greeting": "Hello, Witt! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311e615133e998ffb689", "index": 8, "guid": "76f59cf9-a1f5-4289-8f04-97be29cbd557", "isActive": true, "balance": "$2,317.41", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "green", "name": { "first": "Reilly", "last": "Meadows" }, "company": "CENTICE", "email": "reilly.meadows@centice.name", "phone": "+1 (987) 457-3166", "address": "132 Llama Court, Elrama, American Samoa, 5050", "about": "<TypeError: loremIpsum is not a function>", "registered": "Wednesday, August 17, 2016 1:43 AM", "latitude": "87.182673", "longitude": "97.286414", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Louisa Oneil" }, { "id": 1, "name": "Hendricks Franco" }, { "id": 2, "name": "Sherrie Cote" } ], "greeting": "Hello, Reilly! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311ea3a55d6ed92a7718", "index": 9, "guid": "e7d3104c-18b7-4251-a0e3-eba8f26e5dc6", "isActive": true, "balance": "$3,915.23", "picture": "http://placehold.it/32x32", "age": 36, "eyeColor": "green", "name": { "first": "Buchanan", "last": "Dean" }, "company": "AMTAS", "email": "buchanan.dean@amtas.com", "phone": "+1 (986) 461-3487", "address": "950 Moffat Street, Century, New York, 8233", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, December 19, 2019 9:00 PM", "latitude": "-34.83994", "longitude": "-46.420874", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Woodard Stone" }, { "id": 1, "name": "Sharon Fulton" }, { "id": 2, "name": "Dejesus Reid" } ], "greeting": "Hello, Buchanan! You have 8 unread messages.", "favoriteFruit": "banana" } ])");
  for (auto lexed_result = tybl::json::lex(input); auto lr : lexed_result) {
    std::cout << lr.value() << std::endl;
  }
  return 0;
}
