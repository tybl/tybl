// License: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_NMEA_STATE_HPP
#define TYBL_NMEA_STATE_HPP

#include "gga_sentence.hpp"
#include "gsa_sentence.hpp"
#include "gsv_sentence.hpp"
#include "rmc_sentence.hpp"
#include "vtg_sentence.hpp"

struct state {
  virtual ~state() = 0;
  virtual void apply_gga(gga_sentence const& p_sentence);
  virtual void apply_gsa(gsa_sentence const& p_sentence);
  virtual void apply_gsv(gsv_sentence const& p_sentence);
  virtual void apply_rmc(rmc_sentence const& p_sentence);
  virtual void apply_vtg(vtg_sentence const& p_sentence);
}; // struct state

#endif // TYBL_NMEA_STATE_HPP