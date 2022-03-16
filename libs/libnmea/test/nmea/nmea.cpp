// License: The Unlicense (https://unlicense.org)

#include <date/date.h>
#include <doctest/doctest.h>

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

TEST_CASE("New design") {
  gps::nmea::sentence first;
  std::this_thread::sleep_for(std::chrono::microseconds(1));
  gps::nmea::sentence second;
  CHECK(first.timestamp() < second.timestamp());
}