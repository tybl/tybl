
I think an interesting way to parse json would be to programmatically
make function calls defining the expected structure:
`doc[23]` for arrays
`doc("key")` for objects
`doc[23]("is healthy")...`
And the result is a json value, but the value has not been determined until it is evaluated.
This might cause problems by requiring the document object to retain the entire input string.
It could also retain the input stream... But then it cannot utilize string_views.
```
struct document {
document operator()(std::string_view p_key) {
static_cast<void>(p_key);
return *this;
}
document operator[](size_t p_index) {
static_cast<void>(p_index);
return *this;
}
document operator/(std::string_view p_key) {
static_cast<void>(p_key);
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
```