// License: The Unlicense (https://unlicense.org)
#include <nmea/v2/state.hpp>

state::~state() = default;

void state::apply_gga(gga_sentence const& p_sentence) {}
void state::apply_gsa(gsa_sentence const& p_sentence) {}
void state::apply_gsv(gsv_sentence const& p_sentence) {}
void state::apply_rmc(rmc_sentence const& p_sentence) {}
void state::apply_vtg(vtg_sentence const& p_sentence) {}
