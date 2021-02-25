It might be useful to store accounts in a trie. Each node holding a word. That seems like a good fit for the nested account structure used by ledger.
https://en.wikipedia.org/wiki/Trie
http://opendatastructures.org/ods-cpp.pdf
https://www.geeksforgeeks.org/trie-insert-and-search/
https://www.geeksforgeeks.org/trie-display-content/
https://www.geeksforgeeks.org/counting-number-words-trie/


https://abseil.io/ appears to be a high-quality library with useful abstractions. The webpage also offers tips on C++ usage.

https://github.com/LoopPerfect/valuable is a smart pointer that clones the object it points to when it is copied.
This is useful for classes using the pimpl idiom that need to be copyable.

Examples using JUCE:
* https://github.com/asit-dhal/CurrencyExchange
* https://github.com/asit-dhal/Juce-Qt-Menubar-Demo

Implementing a singly linked list using smart pointers: https://solarianprogrammer.com/2019/02/22/cpp-17-implementing-singly-linked-list-smart-pointers/

C++ hints and best practices:
* https://github.com/isocpp/CppCoreGuidelines
* https://github.com/lefticus/cppbestpractices
* https://www.fluentcpp.com/

This is an interesting backend where I wouldn't have to create my own:
* https://www.remi-coulom.fr/joedb/intro.html
* https://github.com/Remi-Coulom/joedb

Ways of documenting design:
* https://docs.readthedocs.io/en/latest/intro/getting-started-with-sphinx.html
* Doxygen
* draw.io

Tools
* https://blog.kitware.com/static-checks-with-cmake-cdash-iwyu-clang-tidy-lwyu-cpplint-and-cppcheck/
* https://rix0r.nl/blog/2015/08/13/cmake-guide/