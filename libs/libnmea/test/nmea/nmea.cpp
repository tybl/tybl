// License: The Unlicense (https://unlicense.org)

#include <date/date.h>
#include <doctest/doctest.h>

#include <charconv>
#include <chrono>
#include <thread>

namespace gps::nmea {

using milliseconds = std::chrono::duration<int32_t, std::milli>;

template <typename Float>
struct latitude_t {
  Float value;
};

template <typename Float>
struct longitude_t {
  Float value;
};

template <typename Float>
struct altitude_t {
  Float value;
};

template <typename Float>
struct lla_t {

  constexpr lla_t() noexcept = default;

  constexpr lla_t(Float p_latitude, Float p_longitude, Float p_altitude) noexcept : m_latitude(p_latitude), m_longitude(p_longitude), m_altitude(p_altitude) {}

  [[nodiscard,gnu::pure]] constexpr auto latitude() const noexcept { return m_latitude; }

  [[nodiscard,gnu::pure]] constexpr auto longitude() const noexcept { return m_longitude; }

  [[nodiscard,gnu::pure]] constexpr auto altitude() const noexcept { return m_altitude; }

private:
  latitude_t<Float> m_latitude;
  longitude_t<Float> m_longitude;
  altitude_t<Float> m_altitude;
}; // class lla_c

struct sentence {

  static auto parse(std::string_view) noexcept -> sentence { return {}; }

  [[nodiscard,gnu::pure]] auto timestamp() const noexcept { return m_timestamp; }

private:
  std::chrono::steady_clock::time_point m_timestamp{ std::chrono::steady_clock::now() };
};

struct gga_sentence : public sentence {

  static auto parse(std::string_view) noexcept -> gga_sentence { return {}; }

  [[nodiscard]] constexpr auto position() const noexcept { return m_position; }

  [[nodiscard]] constexpr auto time() const noexcept -> date::hh_mm_ss<milliseconds> { return m_time; }

private:
  date::hh_mm_ss<milliseconds> m_time;
  lla_t<float> m_position;
  float m_hdop;
  float m_geoidal_separation;
};

struct gsa_sentence : public sentence {

private:
  float m_position_dilution_of_precision;
  float m_horizontal_dilution_of_precision;
  float m_vertical_dilution_of_precision;
};

struct satellite
{
  uint8_t satellite_id;
  uint8_t elevation;
  uint8_t azimuth;
  uint8_t snr;
};

struct gsv_sentence : public sentence {

private:
  std::vector<satellite> m_satellites;
};

struct rmc_sentence : public sentence {

  [[nodiscard]] constexpr auto time() const noexcept { return m_time; }

  [[nodiscard]] constexpr auto date() const noexcept { return m_date; }

private:
  date::hh_mm_ss<milliseconds> m_time;
  date::year_month_day m_date;
  float m_latitude;
  float m_longitude;
  float m_speed;
  float m_course;
};

struct vtg_sentence
    : public sentence
{
private:
  date::hh_mm_ss<milliseconds> m_time;
};

} // namespace gps::nmea

struct gga_sentence {
  //date::hh_mm_ss<std::chrono::milliseconds> time_of_day;
  double time_of_day;
  gps::nmea::latitude_t<float> latitude;
  gps::nmea::longitude_t<float> longitude;
  int fix_quality;
  int num_satellites;
  double horizontal_dilution_of_precision;
  double height_above_ellipsoid;
  double time_since_last_dgps_update;
  int dgps_reference_station_id;
};

struct gsa_sentence {

};

struct gsv_sentence {

};

struct rmc_sentence {
  //date::hh_mm_ss<std::chrono::milliseconds> time;
  double time;
  //date::year_month_day date;
  int date;
  gps::nmea::latitude_t<float> latitude;
  gps::nmea::longitude_t<float> longitude;
  double speed;
  double course;
  double magnetic_variation;
  bool valid;
};

struct vtg_sentence {
  double track_made_good_t;
  double track_made_good_m;
  double speed_over_ground_kts;
  double speed_over_groubd_kmph;
};

struct State {
  virtual ~State() = 0;
  virtual void apply_gga(gga_sentence const& p_sentence) = 0;
  virtual void apply_gsa(gsa_sentence const& p_sentence) = 0;
  virtual void apply_gsv(gsv_sentence const& p_sentence) = 0;
  virtual void apply_rmc(rmc_sentence const& p_sentence) = 0;
  virtual void apply_vtg(vtg_sentence const& p_sentence) = 0;
};

State::~State() = default;

struct knots_t {};

struct LatestState : public State {

  ~LatestState() override = default;

  void apply_gga(gga_sentence const& p_sentence) override {
    m_time_of_day = p_sentence.time_of_day;
    m_latitude = p_sentence.latitude;
    m_longitude = p_sentence.longitude;
    m_fix_quality = p_sentence.fix_quality;
    m_num_satellites = p_sentence.num_satellites;
    m_horizontal_dilution_of_precision = p_sentence.horizontal_dilution_of_precision;
    m_height_above_ellipsoid = p_sentence.height_above_ellipsoid;
    m_time_since_last_dgps_update = p_sentence.time_since_last_dgps_update;
    m_dgps_reference_station_id = p_sentence.dgps_reference_station_id;
  }

  void apply_gsa(gsa_sentence const& p_sentence) override {
    // TODO
  }

  void apply_gsv(gsv_sentence const& p_sentence) override {
    // TODO
  }

  void apply_rmc(rmc_sentence const& p_sentence) override {
    m_time_of_day = p_sentence.time;
    m_latitude = p_sentence.latitude;
    m_longitude = p_sentence.longitude;
    m_speed_kts = p_sentence.speed;
    m_course = p_sentence.course;
    m_date = p_sentence.date;
    m_magnetic_variation = p_sentence.magnetic_variation;
  }

  void apply_vtg(vtg_sentence const& p_sentence) override {
    m_speed_kts = p_sentence.speed_over_ground_kts;
  }

  [[nodiscard]] auto latitude() const { return m_latitude; }
  [[nodiscard]] auto longitude() const { return m_longitude; }

private:
  //date::hh_mm_ss<std::chrono::milliseconds> m_time_of_day;
  double m_time_of_day;
  //date::year_month_day m_date;
  int m_date;
  gps::nmea::latitude_t<float> m_latitude;
  gps::nmea::longitude_t<float> m_longitude;
  int m_fix_quality;
  int m_num_satellites;
  double m_horizontal_dilution_of_precision;
  double m_height_above_ellipsoid;
  double m_time_since_last_dgps_update;
  double m_speed_kts;
  int m_dgps_reference_station_id;
  double m_course;
  double m_magnetic_variation;
}; // class LatestState

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

struct parser {

  explicit parser(State& p_state) : m_state(p_state) {}

  void parse(std::string_view p_input) {
    using namespace std::literals;
    p_input.remove_prefix(p_input.find('$') + 1); // +1 to remove `$` as well
    auto talker_id = parse_talker_id(p_input);
    if (p_input.starts_with("GGA"sv)) {
      p_input = parse_gga(p_input.substr(4));
    } else if (p_input.starts_with("GSA"sv)) {
      p_input = parse_gsa(p_input.substr(4));
    } else if (p_input.starts_with("GSV"sv)) {
      p_input = parse_gsv(p_input.substr(4));
    } else if (p_input.starts_with("RMC"sv)) {
      p_input = parse_rmc(p_input.substr(4));
    } else if (p_input.starts_with("VTG"sv)) {
      p_input = parse_vtg(p_input.substr(4));
    }
  }

  [[nodiscard]] auto state() const -> State& {
    return m_state;
  }

private:

  auto parse_gga(std::string_view p_input) -> std::string_view {
    gga_sentence result{};
    m_state.apply_gga(result);
    return p_input;
  }

  auto parse_gsa(std::string_view p_input) -> std::string_view {
    gsa_sentence result{};
    m_state.apply_gsa(result);
    return p_input;
  }

  auto parse_gsv(std::string_view p_input) -> std::string_view {
    gsv_sentence result{};
    m_state.apply_gsv(result);
    return p_input;
  }

  auto parse_rmc(std::string_view p_input) -> std::string_view {
    rmc_sentence result{};
    auto res = std::from_chars(p_input.begin(), p_input.end(), result.time);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    result.valid = ('A' == p_input.front());
    p_input.remove_prefix(2);
    res = std::from_chars(p_input.begin(), p_input.end(), result.latitude.value);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    result.latitude.value *= ('N' == p_input.front()) ? 1 : -1;
    p_input.remove_prefix(2);
    res = std::from_chars(p_input.begin(), p_input.end(), result.longitude.value);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    result.longitude.value *= ('E' == p_input.front()) ? 1 : -1;
    p_input.remove_prefix(2);
    res = std::from_chars(p_input.begin(), p_input.end(), result.speed);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    res = std::from_chars(p_input.begin(), p_input.end(), result.course);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    res = std::from_chars(p_input.begin(), p_input.end(), result.date);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));
    res = std::from_chars(p_input.begin(), p_input.end(), result.magnetic_variation);
    p_input.remove_prefix(static_cast<size_t>(res.ptr - p_input.begin() + 1));

    m_state.apply_rmc(result);
    return p_input;
  }

  auto parse_vtg(std::string_view p_input) -> std::string_view {
    vtg_sentence result{};
    m_state.apply_vtg(result);
    return p_input;
  }

//private:
  State& m_state;
}; // struct parser

TEST_CASE("New design") {
  gps::nmea::sentence first;
  std::this_thread::sleep_for(std::chrono::microseconds(1));
  gps::nmea::sentence second;
  CHECK(first.timestamp() < second.timestamp());
}

TEST_CASE("New code") {
  LatestState state;
  parser p(state);
  p.parse("$GNRMC,020219.000,A,3924.6965,N,07657.7015,W,0.65,189.45,140322,,,D*6B\r\n");
  CHECK(state.longitude().value == -7657.7015F);
  CHECK(state.latitude().value == 3924.6965F);
}