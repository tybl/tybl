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
