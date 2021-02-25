////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2006 - 2016, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <ColEntry.h>
#include <i18n.h>

////////////////////////////////////////////////////////////////////////////////
ColumnEntry::ColumnEntry ()
{
  _name  = "entry";
  _label = STRING_COLUMN_LABEL_ADDED;
}

////////////////////////////////////////////////////////////////////////////////
// Overriden so that style <----> label are linked.
// Note that you can not determine which gets called first.
void ColumnEntry::setStyle (const std::string& value)
{
  _style = value;

  if (_style == "age" && _label == STRING_COLUMN_LABEL_ADDED) {
    _label = STRING_COLUMN_LABEL_AGE;
  }
}

////////////////////////////////////////////////////////////////////////////////
