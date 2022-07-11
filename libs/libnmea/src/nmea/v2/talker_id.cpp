#include <nmea/v2/talker_id.hpp>

auto parse_talker_id(std::string_view& p_input) -> TalkerId {
  TalkerId result = TalkerId::Unknown;
  if ('G' == p_input.front()) {
    p_input.remove_prefix(1);
    switch (p_input.front()) {
      case 'A': result = TalkerId::GA; break;
      case 'B': result = TalkerId::GB; break;
      case 'I': result = TalkerId::GI; break;
      case 'L': result = TalkerId::GL; break;
      case 'N': result = TalkerId::GN; break;
      case 'P': result = TalkerId::GP; break;
      case 'Q': result = TalkerId::GQ; break;
    }
    p_input.remove_prefix(1);
  }
  return result;
}
