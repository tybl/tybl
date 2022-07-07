The NMEA parser needs it's API thought out a little more. Right now, the parser provides several different interfaces:

* read byte,
* read buffer,
* read line, and
* read sentence

None of these functions have a return value because they use callbacks to notify registered handlers of success.
However, they all have the possibility of throwing exceptions and they will, in the event that a NMEA sentence is invalid.

As a tangent, I'm not sure how strong the need is for the `read_line` function.
It appears to be the same as `read_buffer`, but appends a carriage return and newline at the end.
I assume this is because using istream::getline will strip the such whitespace.

Given that `read_line` has dubious justification, that leaves `read_byte`, `read_buffer`, and `read_sentence`.
I don't think it makes sense to indicate success or failure parsing a single byte or a buffer that may contain multiple NMEA sentences.
Therefore, of the three, `read_sentence` is the only one where a return value seems to make sense.

### 2022-07-05

#### What is libnmea?
Libnmea is a library for parsing the output of NMEA 0183 compatible GPS receivers into a structure
usable by C++20 applications.

#### What are the use cases?
- Identify current location (parse latest GPS output)
- Identify series of locations from a start time to an end time
- Identify location at a specific time

From what I can tell, the nmea stream tries to work in transactions. Or, in other words, the one GPS receiver I have
interacted with dumps a few lines of NMEA sentences every second or so. Though, it doesn't appear that there is a
container for the sentences. This means, while the data may arrive together temporally, I don't think I can rely on it
to ensure that I have all the information required to report the current location. This makes me think that I want to
use a parser interface similar to JSON or other parser. For example, Nematode used push parsing using callbacks when
different NMEA sentences were parsed. However, to simplify things, I could just keep the current state and update it
after each processed sentence. Though, thinking about it, that's basically a push parser with the updates being pushed
to the state object. The state can either keep track of only the latest state or be a store of all the previous states.