// License: The Unlicense (https://unlicense.org)
#include <nmea/nmea.hpp>

#include <vodka/parse_error.hpp>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <fstream>

auto main(int argc, char* argv[]) -> int {
  spdlog::set_level(spdlog::level::off);

  if (1 < argc) {
    // Create a GPS service that will keep track of the fix data.
    tybl::nmea::byte_parser parser;
    tybl::nmea::gps_service gps(parser);

    fmt::print("fix  Sats  Sig\t\tSpeed    Dir  Lat       , Lon           Accuracy\n");
    // Handle any changes to the GPS fix... This is called whenever it's updated.
    gps.on_update += [&gps]() {
      fmt::print("[{}] {: >2}/{: >2} {: >5.2f} dB   {: >6.2f} km/h [{}]  {:.6f} N, {:.6f} E  +/- {:.1f}m  \n",
                 gps.fix.locked() ? '*' : ' ', gps.fix.tracking_satellites, gps.fix.visible_satellites,
                 gps.fix.m_almanac.average_snr(), gps.fix.speed,
                 tybl::nmea::gps::fix::ordinal_direction(gps.fix.travel_angle, true),
                 gps.fix.latitude, gps.fix.longitude, gps.fix.horizontal_accuracy());
    };

    std::ifstream file(argv[1]);
    file.seekg(0, std::ios::end);
    auto file_size = file.tellg();
    std::string buffer(static_cast<size_t>(file_size), ' ');
    file.seekg(0);
    file.read(buffer.data(), file_size);

    parser.read_buffer(buffer);

    // Show the final fix information
    fmt::print("{}\n", gps.fix.to_string());
  }
}
