// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_TALKERID_HPP
#define TYBL_NMEA_TALKERID_HPP

#include <string_view>

enum class TalkerId {
  Unknown,
  GA,
  Galileo = GA,
  GB,
  BeiDou = GB,
  GI,
  NavIC = GI,
  GL,
  GLONASS = GL,
  GN,
  GNSS = GN,
  GP,
  GPS = GP,
  GQ,
  QZSS = GQ,
};

auto parse_talker_id(std::string_view& p_input) -> TalkerId;

#endif // TYBL_NMEA_TALKERID_HPP
