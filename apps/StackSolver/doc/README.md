# Design decisions

## Node structure

The naive node structure matches the problem definition. An array of stacks would be able to represent the state of the game at any step.
However, this representation includes significant overhead.
A layer of the stack can be represented by the smallest data type `char`.
A stack of `char`s could be represented by a `std::string` and provide a few other useful functions.
`std::string` also provides [small string optimization](https://tc-imba.github.io/posts/cpp-sso) (SSO).
SSO is useful because dynamically sized stacks would generally require an allocation.
