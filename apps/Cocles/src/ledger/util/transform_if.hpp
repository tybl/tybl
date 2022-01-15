// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_COCLES_LEDGER_UTIL_TRANSFORMIF_HPP
#define TYBL_COCLES_LEDGER_UTIL_TRANSFORMIF_HPP

template<class InputIt, class OutputIt, class UnaryPredicate, class UnaryOperation>
OutputIt transform_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate pred, UnaryOperation unary_op) {
   while (first != last) {
      if (pred(*first)) {
         *d_first++ = unary_op(*first);
      }
      first++;
   }
   return d_first;
}

template<class Range, class OutputIt, class UnaryPredicate, class UnaryOperation>
OutputIt transform_if(Range source, OutputIt d_first, UnaryPredicate pred, UnaryOperation unary_op) {
   auto first = std::begin(source);
   const auto last = std::end(source);
   while (first != last) {
      if (pred(*first)) {
         *d_first++ = unary_op(*first);
      }
      first++;
   }
   return d_first;
}
#endif // TYBL_COCLES_LEDGER_UTIL_TRANSFORMIF_HPP
