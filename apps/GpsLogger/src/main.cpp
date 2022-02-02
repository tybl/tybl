// License: The Unlicense (https://unlicense.org)
#include "nmea/nmea.hpp"

#include <vodka/parse_error.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
  if (1 < argc) {
    // Create a GPS service that will keep track of the fix data.
    nmea::Parser parser;
    nmea::GPSService gps(parser);
    // TODO(tybl): What's the default value for Parser::log
    parser.log = false;

    std::cout << "fix  Sats  Sig\t\tSpeed    Dir  Lat       , Lon           Accuracy" << std::endl;
    // Handle any changes to the GPS fix... This is called whenever it's updated.
    gps.on_update += [&gps]() {
      std::cout << (gps.fix.locked() ? "[*] " : "[ ] ") << std::setw(2) << std::setfill(' ')
                << gps.fix.tracking_satellites << "/" << std::setw(2) << std::setfill(' ') << gps.fix.visible_satellites
                << " ";
      std::cout << std::fixed << std::setprecision(2) << std::setw(5) << std::setfill(' ')
                << gps.fix.almanac.average_snr() << " dB   ";
      std::cout << std::fixed << std::setprecision(2) << std::setw(6) << std::setfill(' ') << gps.fix.speed << " km/h ["
                << gps::fix::ordinal_direction(gps.fix.travel_angle, true) << "]  ";
      std::cout << std::fixed << std::setprecision(6) << gps.fix.latitude
                << " "
                   "N, "
                << gps.fix.longitude
                << " "
                   "E"
                << "  ";
      std::cout << "+/- " << std::setprecision(1) << gps.fix.horizontal_accuracy() << "m  ";
      std::cout << std::endl;
    };

    std::string line;
    std::ifstream file(argv[1]);
    while (std::getline(file, line)) {
      try {
        parser.read_line(line);
      } catch (tybl::vodka::parse_error& e) { // TODO(tybl): Can/should this be const&?
        std::cout << e.what() << std::endl;
        // You can keep feeding data to the gps service...
        // The previous data is ignored and the parser is reset.
      }
    }

    // Show the final fix information
    std::cout << gps.fix.to_string() << std::endl;
  }
  std::cin.ignore();
}
