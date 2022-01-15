// License: The Unlicense (https://unlicense.org)
#include "json/value.hpp"
//#include "vodka/util/parse_error.hpp"   // for parse_error

#include <cassert>
#include <iostream>
#include <regex>
#include <vector>

static const std::regex
   str_re(R"("(?:\\(?:["\\\/bfnrt]|u[a-fA-F0-9]{4})|[^"\\\0-\x1F\x7F]+)*")",
          std::regex_constants::ECMAScript | std::regex_constants::optimize);

static const std::regex
   num_re("^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?",
          std::regex_constants::ECMAScript | std::regex_constants::optimize);

template <class TYPE, TYPE low, TYPE high>
bool is_in_range(TYPE c) {
   static_assert(low <= high);
   return ((low <= c) && (c <= high));
}

inline bool is_digit(char c) {
   return is_in_range<char, '0', '9'>(c);
}

inline bool is_onenine(char c) {
   return is_in_range<char, '1', '9'>(c);
}

inline bool is_hex(char c) {
   return is_digit(c)
       || is_in_range<char, 'A', 'F'>(c)
       || is_in_range<char, 'a', 'f'>(c);
}

inline bool is_whitespace(char c) {
   return (('\x09' == c) || ('\x0A' == c) || ('\x0D' == c) || ('\x20' == c));
}

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
//    * Must be valid token (i.e. string...) TODO(tblyons): Not sure about this
struct token {

   TokenType type() const { return calculate_type(m_value); }

   std::string_view value() const { return m_value; }

   token(std::string_view sv) : m_value(sv) { }

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
   static TokenType calculate_type(std::string_view in) {
      assert(!in.empty());
      TokenType result = TokenType::UNKNOWN;
      // TODO(tblyons): Can we guarantee this function will never be called with
      //                an empty input? If so, we can remove this redundant call
      //                to in.empty().
      if (!in.empty()) {
         switch (in.front()) {
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
   static size_t length(std::string_view in) {
      size_t result = 1;
      if (in.empty()) {
         return 0;
      } else {
         switch (calculate_type(in)) {
            case TokenType::NIL:
            case TokenType::TRUE:
               result = 4;
               break;
            case TokenType::FALSE:
               result = 5;
               break;
            case TokenType::STRING:
               // TODO(tblyons): Calculate string length
               result = static_cast<size_t>(std::cregex_iterator(in.begin(), in.end(), str_re)->length());
               break;
            case TokenType::NUMBER:
               // TODO(tblyons): Calculate number length
               result = static_cast<size_t>(std::cregex_iterator(in.begin(), in.end(), num_re)->length());
               break;
            case TokenType::OBJECT_OPEN:
            case TokenType::OBJECT_CLOSE:
            case TokenType::ARRAY_OPEN:
            case TokenType::ARRAY_CLOSE:
            case TokenType::SEPARATOR:
            case TokenType::DELIMITER:
            case TokenType::UNKNOWN:
            default: break; // default value of 1 is correct
         }
      }
      return result;
   }
private:
   std::string_view m_value;
};

struct token_iterator {

  token_iterator(std::string_view in) : m_value(in) {}

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
};

#if 0
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
};
#endif

static std::vector<token> lex(std::string_view in) {
   std::vector<token> result;
   while (!in.empty()) {
      switch (in.front()) {
         case '\x09':
         case '\x0A':
         case '\x0D':
         case '\x20':
            // Whitespace
            in.remove_prefix(1);
            break;
         case '"': {
            // String
            auto len = static_cast<size_t>(std::cregex_iterator(in.begin(), in.end(), str_re)->length());
            result.emplace_back(in.substr(0, len));
            in.remove_prefix(len);
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
            auto len = static_cast<size_t>(std::cregex_iterator(in.begin(), in.end(), num_re)->length());
            result.emplace_back(in.substr(0, len));
            in.remove_prefix(len);
            break;
         }
         case '[':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         case ']':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         case 'f':
            result.emplace_back(in.substr(0, 5));
            in.remove_prefix(5);
            break;
         case 'n':
            result.emplace_back(in.substr(0, 4));
            in.remove_prefix(4);
            break;
         case 't':
            result.emplace_back(in.substr(0, 4));
            in.remove_prefix(4);
            break;
         case '{':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         case '}':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         case ',':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         case ':':
            result.emplace_back(in.substr(0, 1));
            in.remove_prefix(1);
            break;
         default:
            printf("not sure what to do with: '%c'\n", in.front());
            throw std::runtime_error("Error: Encountered unexpected character while lexing JSON");
      }
   }
   return result;
}

vodka::json::value parse_element(std::string_view& in);
vodka::json::value parse_value(std::string_view& in);

static constexpr char FALSE[] = "false";
static constexpr char NIL[] = "null";
static constexpr char TRUE[] = "true";

template<char CHAR>
bool parse_character(std::string_view& in) {
   bool result = (!in.empty() && CHAR == in.front());
   in.remove_prefix(static_cast<std::string_view::size_type>(result));
   return result;
} // parse_character(std::string_view&)

static void parse_whitespace(std::string_view& in) {
   static constexpr std::string_view WHITESPACE_CHARS("\x09\x0A\x0D\x20");
   auto pos = in.find_first_not_of(WHITESPACE_CHARS);
   in.remove_prefix((in.npos != pos)? pos : 0); // consume whitespace
} // parse_whitespace(std::string_view&)

template <const char* LITERAL>
std::string_view parse_literal(std::string_view& in) {
   static constexpr std::string_view prefix = LITERAL;
   auto result = in.substr(0, prefix.length());
   if (prefix != result) {
      throw std::runtime_error("Error: Expected to find JSON literal '{}'");
   }
   in.remove_prefix(prefix.length());
   printf(LITERAL);
   return result;
} // parse_literal(std::string_view&)

static std::string_view parse_number(std::string_view& in) {
   static std::regex re("^[-]?(0|[1-9][0-9]*)(\\.[0-9]+)?([eE][+-]?[0-9]+)?");
   auto rei = std::cregex_iterator(in.begin(), in.end(), re);
   if (!rei->ready() || rei->empty() || rei->position() != 0) {
      throw std::runtime_error("Error: Expected JSON Number");
   }
   auto len = static_cast<size_t>(rei->length());
   std::string_view result(in.data(), len);
   in.remove_prefix(len);
   printf("#");
   return result;
} // parse_number(std::string_view&)

static std::string_view parse_string(std::string_view& in) {
   if (!parse_character<'"'>(in)) {
      throw std::runtime_error("Error: JSON String not found");
   }
   size_t i = 0;
   for (; (i < in.size()) && ('"' != in[i]); ++i) {
      if (is_in_range<char, 0x0, 0x19>(in[i])) {
         throw std::runtime_error("Error: String includes unescaped character in the range 0000 . 0019");
      }
      if ('\\' == in[i]) {
         if (i + 1 >= in.size()) {
            throw std::runtime_error("Error: Not enough hexadecimal characters after escape");
         }
         ++i;
         if (('"'  != in[i])
          && ('\\' != in[i])
          && ('/'  != in[i])
          && ('b'  != in[i])
          && ('f'  != in[i])
          && ('n'  != in[i])
          && ('r'  != in[i])
          && ('t'  != in[i])
          && ('u'  != in[i]))
         {
            throw std::runtime_error("Error: Unexpected escaped character");
         }
         if ('u' == in[i]) {
            if (i + 4 >= in.size()) {
               throw std::runtime_error("Error: Not enough hexadecimal characters in escaped 'u'");
            }
            if (!is_hex(in[i + 1])
             || !is_hex(in[i + 2])
             || !is_hex(in[i + 3])
             || !is_hex(in[i + 4]))
            {
               throw std::runtime_error("Error: Non-hexadecimal characters in escaped 'u'");
            }
            i += 4;
         }
      }
   }
   if (in.size() == i) {
      throw std::runtime_error("Error: JSON input ended before string was closed");
   }
   auto result = in.substr(0, i);
   in.remove_prefix(i + 1);
   printf("\"");
   return result;
} // parse_string(std::string_view&)

// Recursive
static std::vector<vodka::json::value> parse_array(std::string_view& in) {
   if (!parse_character<'['>(in)) {
      throw std::runtime_error("Error: JSON Array not found");
   }
   printf("[");
   std::vector<vodka::json::value> result;
   parse_whitespace(in);
   if (!in.empty() && ']' != in.front()) {
      result.push_back(parse_value(in));
      parse_whitespace(in);
      while (parse_character<','>(in)) {
         printf(",");
         result.push_back(parse_element(in));
      }
   }
   if (!parse_character<']'>(in)) {
      throw std::runtime_error("Error: Encountered unexpected character while parsing JSON Array");
   }
   printf("]");
   return result;
} // parse_array(std::string_view&)

// Recursive
static std::map<std::string_view, vodka::json::value> parse_object(std::string_view& in) {
   if (!parse_character<'{'>(in)) {
      throw std::runtime_error("Error: JSON Object not found");
   }
   printf("{");
   std::map<std::string_view, vodka::json::value> result;
   parse_whitespace(in);
   if (!in.empty() && '}' != in.front()) {
      std::string_view key = parse_string(in);
      parse_whitespace(in);
      if (!parse_character<':'>(in)) {
         throw std::runtime_error("Error: Missing ':' within JSON Object1");
      }
      printf(":");
      result[key] = parse_element(in);
      while (parse_character<','>(in)) {
         printf(",");
         parse_whitespace(in);
         key = parse_string(in);
         parse_whitespace(in);
         if (!parse_character<':'>(in)) {
            throw std::runtime_error("Error: Missing ':' within JSON Object2");
         }
         printf(":");
         result[key] = parse_element(in);
      }
   }
   if (!parse_character<'}'>(in)) {
      throw std::runtime_error("Error: Encountered unexpected character while parsing JSON Object");
   }
   printf("}");
   return result;
} // parse_object(std::string_view&)

// Recursive
vodka::json::value parse_value(std::string_view& in) {
   vodka::json::value result;
   if (in.empty()) {
      throw std::runtime_error("Error: Expected JSON value before end of input");
   }
   switch (in.front()) {
      case '"': result = parse_string(in); break;
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
      case '9': result = parse_number(in); break;
      case '[': result = parse_array(in); break;
      case 'f': result = parse_literal<FALSE>(in); break;
      case 'n': result = parse_literal<NIL>(in); break;
      case 't': result = parse_literal<TRUE>(in); break;
      case '{': result = parse_object(in); break;
      default:
         throw std::runtime_error("Error: Encountered unexpected character while parsing JSON value");
   }
   return result;
} // parse_value(std::string_view&)

// Recursive
vodka::json::value parse_element(std::string_view& in) {
   parse_whitespace(in);
   auto result = parse_value(in);
   parse_whitespace(in);
   return result;
} // parse_element(std::string_view&)

static vodka::json::value parse_json(std::string_view& in) {
   return parse_element(in);
} // parse_json(std::string_view&)

// I think an interesting way to parse json would be to programmatically
// make function calls defining the expected structure:
// doc[23] for arrays
// doc("key") for objects
// doc[23]("is healthy")...
// And the result is a json value, but the value has not been determined until it is evaluated.
// This might cause problems by requiring the document object to retain the entire input string.
// It could also retain the input stream... But then it cannot utilize string_views.

struct document {
  document operator()(std::string_view key) {
      static_cast<void>(key);
      return *this;
   }
   document operator[](size_t index) {
      static_cast<void>(index);
      return *this;
   }
   document operator/(std::string_view key) {
      static_cast<void>(key);
      return *this;
   }
   int as_int() const {
      return 5;
   }
};

struct expected_value {
};

struct expected_array {
};

struct expected_object {
};

int main() {
   std::string_view input(R"([ { "_id": "5e02311eb4f7fff26d6c8646", "index": 0, "guid": "0ea86154-c909-4220-97bc-21ae68a58474", "isActive": false, "balance": "$3,305.12", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "green", "name": { "first": "Toni", "last": "Griffin" }, "company": "WAZZU", "email": "toni.griffin@wazzu.info", "phone": "+1 (869) 462-3047", "address": "570 Lake Street, Brazos, Wisconsin, 2880", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, June 26, 2015 10:53 PM", "latitude": "-81.846796", "longitude": "-144.778871", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Colon Vargas" }, { "id": 1, "name": "Hahn Summers" }, { "id": 2, "name": "Battle Gilliam" } ], "greeting": "Hello, Toni! You have 9 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e2d3ae05377159db2", "index": 1, "guid": "ae96247d-dc1f-42f6-bc81-1cdd6b5c6829", "isActive": false, "balance": "$1,216.58", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "brown", "name": { "first": "Betsy", "last": "Jacobson" }, "company": "JETSILK", "email": "betsy.jacobson@jetsilk.io", "phone": "+1 (904) 459-3265", "address": "402 Little Street, Oasis, Kentucky, 6452", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, July 9, 2015 4:20 AM", "latitude": "-70.234084", "longitude": "152.163603", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Guzman Landry" }, { "id": 1, "name": "Schroeder Whitfield" }, { "id": 2, "name": "Guerrero Glass" } ], "greeting": "Hello, Betsy! You have 10 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311eaaec27bddb05708e", "index": 2, "guid": "cff1b9ac-f291-414f-97ca-101976eaeef6", "isActive": true, "balance": "$2,621.82", "picture": "http://placehold.it/32x32", "age": 24, "eyeColor": "green", "name": { "first": "Clark", "last": "Barnes" }, "company": "PYRAMAX", "email": "clark.barnes@pyramax.tv", "phone": "+1 (943) 500-2711", "address": "339 Polar Street, Bowmansville, Missouri, 1724", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, February 5, 2016 6:26 AM", "latitude": "-18.563984", "longitude": "46.697694", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Elba Huff" }, { "id": 1, "name": "Kathleen Conner" }, { "id": 2, "name": "Hannah Burns" } ], "greeting": "Hello, Clark! You have 6 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311ebd588df9ba3e0efe", "index": 3, "guid": "50f54d1c-aaeb-45c8-bcaa-3c7912acd29a", "isActive": true, "balance": "$3,393.94", "picture": "http://placehold.it/32x32", "age": 31, "eyeColor": "brown", "name": { "first": "Keller", "last": "Bates" }, "company": "OVIUM", "email": "keller.bates@ovium.co.uk", "phone": "+1 (873) 573-3712", "address": "809 Quay Street, Lorraine, Maryland, 8007", "about": "<TypeError: loremIpsum is not a function>", "registered": "Monday, April 18, 2016 11:35 AM", "latitude": "-38.828076", "longitude": "-11.594935", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Lorene Stephens" }, { "id": 1, "name": "Rosanna Pierce" }, { "id": 2, "name": "Ana Travis" } ], "greeting": "Hello, Keller! You have 10 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ec64656551ff176fd", "index": 4, "guid": "efa71fb6-e9a7-4126-9fdd-7e8c364bdbca", "isActive": true, "balance": "$2,071.33", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "blue", "name": { "first": "Ursula", "last": "Rosario" }, "company": "TWIIST", "email": "ursula.rosario@twiist.org", "phone": "+1 (961) 466-2258", "address": "142 Lawrence Avenue, Caspar, Pennsylvania, 7497", "about": "<TypeError: loremIpsum is not a function>", "registered": "Saturday, April 7, 2018 12:14 AM", "latitude": "8.87866", "longitude": "159.005552", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Espinoza Harding" }, { "id": 1, "name": "Cynthia Washington" }, { "id": 2, "name": "Felecia Mayo" } ], "greeting": "Hello, Ursula! You have 7 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311e0b2739a8ab4c2b73", "index": 5, "guid": "424b50e2-7426-4ad3-9895-1915674ac20c", "isActive": false, "balance": "$1,763.35", "picture": "http://placehold.it/32x32", "age": 27, "eyeColor": "green", "name": { "first": "Parsons", "last": "Reynolds" }, "company": "BIOTICA", "email": "parsons.reynolds@biotica.us", "phone": "+1 (954) 537-2763", "address": "758 Highland Avenue, Sims, Northern Mariana Islands, 5317", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, April 13, 2017 7:29 PM", "latitude": "51.800116", "longitude": "-166.912803", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Carmella Rasmussen" }, { "id": 1, "name": "Cox Pope" }, { "id": 2, "name": "Christian Mills" } ], "greeting": "Hello, Parsons! You have 5 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e9a939b787c8962f5", "index": 6, "guid": "c040191c-4d08-438a-8a18-bffb81725b29", "isActive": true, "balance": "$2,125.23", "picture": "http://placehold.it/32x32", "age": 20, "eyeColor": "brown", "name": { "first": "Sanford", "last": "Luna" }, "company": "REPETWIRE", "email": "sanford.luna@repetwire.ca", "phone": "+1 (986) 418-3119", "address": "206 Truxton Street, Tryon, South Carolina, 7676", "about": "<TypeError: loremIpsum is not a function>", "registered": "Sunday, January 17, 2016 3:58 AM", "latitude": "-5.489691", "longitude": "18.393453", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Katharine Leach" }, { "id": 1, "name": "Jackie Howard" }, { "id": 2, "name": "Ericka Kelley" } ], "greeting": "Hello, Sanford! You have 8 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ed0701d0ce968a58c", "index": 7, "guid": "6956ec95-c140-4a7d-bdbf-186d2788abe4", "isActive": true, "balance": "$2,766.13", "picture": "http://placehold.it/32x32", "age": 38, "eyeColor": "blue", "name": { "first": "Witt", "last": "Winters" }, "company": "VETRON", "email": "witt.winters@vetron.net", "phone": "+1 (836) 510-3138", "address": "132 Wogan Terrace, Maury, Ohio, 1113", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, November 2, 2018 7:53 PM", "latitude": "28.934741", "longitude": "149.678983", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Iva Garcia" }, { "id": 1, "name": "Meyers Gentry" }, { "id": 2, "name": "Kenya Carpenter" } ], "greeting": "Hello, Witt! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311e615133e998ffb689", "index": 8, "guid": "76f59cf9-a1f5-4289-8f04-97be29cbd557", "isActive": true, "balance": "$2,317.41", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "green", "name": { "first": "Reilly", "last": "Meadows" }, "company": "CENTICE", "email": "reilly.meadows@centice.name", "phone": "+1 (987) 457-3166", "address": "132 Llama Court, Elrama, American Samoa, 5050", "about": "<TypeError: loremIpsum is not a function>", "registered": "Wednesday, August 17, 2016 1:43 AM", "latitude": "87.182673", "longitude": "97.286414", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Louisa Oneil" }, { "id": 1, "name": "Hendricks Franco" }, { "id": 2, "name": "Sherrie Cote" } ], "greeting": "Hello, Reilly! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311ea3a55d6ed92a7718", "index": 9, "guid": "e7d3104c-18b7-4251-a0e3-eba8f26e5dc6", "isActive": true, "balance": "$3,915.23", "picture": "http://placehold.it/32x32", "age": 36, "eyeColor": "green", "name": { "first": "Buchanan", "last": "Dean" }, "company": "AMTAS", "email": "buchanan.dean@amtas.com", "phone": "+1 (986) 461-3487", "address": "950 Moffat Street, Century, New York, 8233", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, December 19, 2019 9:00 PM", "latitude": "-34.83994", "longitude": "-46.420874", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Woodard Stone" }, { "id": 1, "name": "Sharon Fulton" }, { "id": 2, "name": "Dejesus Reid" } ], "greeting": "Hello, Buchanan! You have 8 unread messages.", "favoriteFruit": "banana" } ])");
   auto result = parse_json(input);
   static_cast<void>(result);
   //document count = json/"root"/"home"/"user"/"doc"/"fin"/"budget"/"count";
   input = R"([ { "_id": "5e02311eb4f7fff26d6c8646", "index": 0, "guid": "0ea86154-c909-4220-97bc-21ae68a58474", "isActive": false, "balance": "$3,305.12", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "green", "name": { "first": "Toni", "last": "Griffin" }, "company": "WAZZU", "email": "toni.griffin@wazzu.info", "phone": "+1 (869) 462-3047", "address": "570 Lake Street, Brazos, Wisconsin, 2880", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, June 26, 2015 10:53 PM", "latitude": "-81.846796", "longitude": "-144.778871", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Colon Vargas" }, { "id": 1, "name": "Hahn Summers" }, { "id": 2, "name": "Battle Gilliam" } ], "greeting": "Hello, Toni! You have 9 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e2d3ae05377159db2", "index": 1, "guid": "ae96247d-dc1f-42f6-bc81-1cdd6b5c6829", "isActive": false, "balance": "$1,216.58", "picture": "http://placehold.it/32x32", "age": 23, "eyeColor": "brown", "name": { "first": "Betsy", "last": "Jacobson" }, "company": "JETSILK", "email": "betsy.jacobson@jetsilk.io", "phone": "+1 (904) 459-3265", "address": "402 Little Street, Oasis, Kentucky, 6452", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, July 9, 2015 4:20 AM", "latitude": "-70.234084", "longitude": "152.163603", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Guzman Landry" }, { "id": 1, "name": "Schroeder Whitfield" }, { "id": 2, "name": "Guerrero Glass" } ], "greeting": "Hello, Betsy! You have 10 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311eaaec27bddb05708e", "index": 2, "guid": "cff1b9ac-f291-414f-97ca-101976eaeef6", "isActive": true, "balance": "$2,621.82", "picture": "http://placehold.it/32x32", "age": 24, "eyeColor": "green", "name": { "first": "Clark", "last": "Barnes" }, "company": "PYRAMAX", "email": "clark.barnes@pyramax.tv", "phone": "+1 (943) 500-2711", "address": "339 Polar Street, Bowmansville, Missouri, 1724", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, February 5, 2016 6:26 AM", "latitude": "-18.563984", "longitude": "46.697694", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Elba Huff" }, { "id": 1, "name": "Kathleen Conner" }, { "id": 2, "name": "Hannah Burns" } ], "greeting": "Hello, Clark! You have 6 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311ebd588df9ba3e0efe", "index": 3, "guid": "50f54d1c-aaeb-45c8-bcaa-3c7912acd29a", "isActive": true, "balance": "$3,393.94", "picture": "http://placehold.it/32x32", "age": 31, "eyeColor": "brown", "name": { "first": "Keller", "last": "Bates" }, "company": "OVIUM", "email": "keller.bates@ovium.co.uk", "phone": "+1 (873) 573-3712", "address": "809 Quay Street, Lorraine, Maryland, 8007", "about": "<TypeError: loremIpsum is not a function>", "registered": "Monday, April 18, 2016 11:35 AM", "latitude": "-38.828076", "longitude": "-11.594935", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Lorene Stephens" }, { "id": 1, "name": "Rosanna Pierce" }, { "id": 2, "name": "Ana Travis" } ], "greeting": "Hello, Keller! You have 10 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ec64656551ff176fd", "index": 4, "guid": "efa71fb6-e9a7-4126-9fdd-7e8c364bdbca", "isActive": true, "balance": "$2,071.33", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "blue", "name": { "first": "Ursula", "last": "Rosario" }, "company": "TWIIST", "email": "ursula.rosario@twiist.org", "phone": "+1 (961) 466-2258", "address": "142 Lawrence Avenue, Caspar, Pennsylvania, 7497", "about": "<TypeError: loremIpsum is not a function>", "registered": "Saturday, April 7, 2018 12:14 AM", "latitude": "8.87866", "longitude": "159.005552", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Espinoza Harding" }, { "id": 1, "name": "Cynthia Washington" }, { "id": 2, "name": "Felecia Mayo" } ], "greeting": "Hello, Ursula! You have 7 unread messages.", "favoriteFruit": "banana" }, { "_id": "5e02311e0b2739a8ab4c2b73", "index": 5, "guid": "424b50e2-7426-4ad3-9895-1915674ac20c", "isActive": false, "balance": "$1,763.35", "picture": "http://placehold.it/32x32", "age": 27, "eyeColor": "green", "name": { "first": "Parsons", "last": "Reynolds" }, "company": "BIOTICA", "email": "parsons.reynolds@biotica.us", "phone": "+1 (954) 537-2763", "address": "758 Highland Avenue, Sims, Northern Mariana Islands, 5317", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, April 13, 2017 7:29 PM", "latitude": "51.800116", "longitude": "-166.912803", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Carmella Rasmussen" }, { "id": 1, "name": "Cox Pope" }, { "id": 2, "name": "Christian Mills" } ], "greeting": "Hello, Parsons! You have 5 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311e9a939b787c8962f5", "index": 6, "guid": "c040191c-4d08-438a-8a18-bffb81725b29", "isActive": true, "balance": "$2,125.23", "picture": "http://placehold.it/32x32", "age": 20, "eyeColor": "brown", "name": { "first": "Sanford", "last": "Luna" }, "company": "REPETWIRE", "email": "sanford.luna@repetwire.ca", "phone": "+1 (986) 418-3119", "address": "206 Truxton Street, Tryon, South Carolina, 7676", "about": "<TypeError: loremIpsum is not a function>", "registered": "Sunday, January 17, 2016 3:58 AM", "latitude": "-5.489691", "longitude": "18.393453", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Katharine Leach" }, { "id": 1, "name": "Jackie Howard" }, { "id": 2, "name": "Ericka Kelley" } ], "greeting": "Hello, Sanford! You have 8 unread messages.", "favoriteFruit": "apple" }, { "_id": "5e02311ed0701d0ce968a58c", "index": 7, "guid": "6956ec95-c140-4a7d-bdbf-186d2788abe4", "isActive": true, "balance": "$2,766.13", "picture": "http://placehold.it/32x32", "age": 38, "eyeColor": "blue", "name": { "first": "Witt", "last": "Winters" }, "company": "VETRON", "email": "witt.winters@vetron.net", "phone": "+1 (836) 510-3138", "address": "132 Wogan Terrace, Maury, Ohio, 1113", "about": "<TypeError: loremIpsum is not a function>", "registered": "Friday, November 2, 2018 7:53 PM", "latitude": "28.934741", "longitude": "149.678983", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Iva Garcia" }, { "id": 1, "name": "Meyers Gentry" }, { "id": 2, "name": "Kenya Carpenter" } ], "greeting": "Hello, Witt! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311e615133e998ffb689", "index": 8, "guid": "76f59cf9-a1f5-4289-8f04-97be29cbd557", "isActive": true, "balance": "$2,317.41", "picture": "http://placehold.it/32x32", "age": 26, "eyeColor": "green", "name": { "first": "Reilly", "last": "Meadows" }, "company": "CENTICE", "email": "reilly.meadows@centice.name", "phone": "+1 (987) 457-3166", "address": "132 Llama Court, Elrama, American Samoa, 5050", "about": "<TypeError: loremIpsum is not a function>", "registered": "Wednesday, August 17, 2016 1:43 AM", "latitude": "87.182673", "longitude": "97.286414", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Louisa Oneil" }, { "id": 1, "name": "Hendricks Franco" }, { "id": 2, "name": "Sherrie Cote" } ], "greeting": "Hello, Reilly! You have 6 unread messages.", "favoriteFruit": "strawberry" }, { "_id": "5e02311ea3a55d6ed92a7718", "index": 9, "guid": "e7d3104c-18b7-4251-a0e3-eba8f26e5dc6", "isActive": true, "balance": "$3,915.23", "picture": "http://placehold.it/32x32", "age": 36, "eyeColor": "green", "name": { "first": "Buchanan", "last": "Dean" }, "company": "AMTAS", "email": "buchanan.dean@amtas.com", "phone": "+1 (986) 461-3487", "address": "950 Moffat Street, Century, New York, 8233", "about": "<TypeError: loremIpsum is not a function>", "registered": "Thursday, December 19, 2019 9:00 PM", "latitude": "-34.83994", "longitude": "-46.420874", "tags": [ "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>", "<TypeError: loremIpsum is not a function>" ], "range": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], "friends": [ { "id": 0, "name": "Woodard Stone" }, { "id": 1, "name": "Sharon Fulton" }, { "id": 2, "name": "Dejesus Reid" } ], "greeting": "Hello, Buchanan! You have 8 unread messages.", "favoriteFruit": "banana" } ])";
   auto lexed_result = lex(input);
   for (auto lr : lexed_result) {
      std::cout << lr.value() << std::endl;
   }
   return 0;
}
