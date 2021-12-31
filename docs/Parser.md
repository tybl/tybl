# NMEA Parser Design

I want to create a NMEA parser.
It occurs to me that there can be many different ways to design such a parser:

- Each NMEA sentence could be a subclass of the `Sentence` base class.
- Events could notify listeners about received/parsed NMEA sentences.

But, I'm not sure what those different features might accomplish.
In the case of a NMEA parser, I want to create an object that will receive bytes and update GPS station attributes.
