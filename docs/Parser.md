# NMEA Parser Design

I want to create a NMEA parser.
It occurs to me that there are many ways to design such a parser:

- Each NMEA sentence could be a subclass of the `sentence` base class.
- Events could notify listeners about received/parsed NMEA sentences.

But, I'm not sure what those different features might accomplish.
In the case of a NMEA parser, I want to create an object that will receive bytes and update GPS station attributes.
To me the object interface required to do that would include a `read()` method and an accessor to each of the GPS station attributes.
I'm not sure what the read function should accept as input; whether that's individual bytes, lines, or full buffers of text.
Even a stream or a file might make for useful input.
It's a bad idea to have the `read()` function contain all the parsing functionality.
The `read()` function should at least delegate to other functions for each of the different NMEA sentences.
The GPS module that I use appears to output the following strings:

- `$CDACK`
- `$GLGSA` - GLONASS receiver operating mode, active satellites used in the position solutions and DOP values.
- `$GLGSV` - GLONASS number of GLONASS satellites in view satellite ID numbers, elevation, azimuth, and SNR values.
- `$GNGGA` - Multi-system Time, position and fix type data
- `$GNRMC` - Multi-system Time, date, position, course and speed data. Recommended Minimum Navigation Information
- `$GNVTG` - Multi-system Course and speed information relative to the ground
- `$GPGSA` - GPS receiver operating mode, active satellites used in the position solutions and DOP values.
- `$GPGSV` - GPS number of GPS satellites in view satellite ID numbers, elevation, azimuth, and SNR values.
- `$PMTK010`
- `$PMTK011`
- `$TK011`

I'm not sure about the `$CDACK` or `TK01` messages, but the remainder seem to be defined by 5 sentences with three different systems between them.

|     | GPS   | GLONASS | GNSS  |
|-----|-------|---------|-------|
| GGA |       |         | GNGGA |
| GSA | GPGSA | GLGSA   |       |
| GSV | GPGSV | GLGSV   |       |
| RMC |       |         | GNRMC |
| VTG |       |         | GNVTG |

So, I should be able to only write 5 parsers and reuse the GSA and GSV versions for both versions.
