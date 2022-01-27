// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "stats/distribution.hpp"

#include <Eigen/Dense>

#include <array>
#include <iomanip>
#include <iostream>
#include <random>

std::array<Eigen::Vector2d, 200> data = {
    {{65.78, 112.99}, {71.52, 136.49}, {69.40, 153.03}, {68.22, 142.34}, {67.79, 144.30}, {68.70, 123.30},
     {69.80, 141.49}, {70.01, 136.46}, {67.90, 112.37}, {66.78, 120.67}, {66.49, 127.45}, {67.62, 114.14},
     {68.30, 125.61}, {67.12, 122.46}, {68.28, 116.09}, {71.09, 140.00}, {66.46, 129.50}, {68.65, 142.97},
     {71.23, 137.90}, {67.13, 124.04}, {67.83, 141.28}, {68.88, 143.54}, {63.48, 97.90},  {68.42, 129.50},
     {67.63, 141.85}, {67.21, 129.72}, {70.84, 142.42}, {67.49, 131.55}, {66.53, 108.33}, {65.44, 113.89},
     {69.52, 103.30}, {65.81, 120.75}, {67.82, 125.79}, {70.60, 136.22}, {71.80, 140.10}, {69.21, 128.75},
     {66.80, 141.80}, {67.66, 121.23}, {67.81, 131.35}, {64.05, 106.71}, {68.57, 124.36}, {65.18, 124.86},
     {69.66, 139.67}, {67.97, 137.37}, {65.98, 106.45}, {68.67, 128.76}, {66.88, 145.68}, {67.70, 116.82},
     {69.82, 143.62}, {69.09, 134.93}, {69.91, 147.02}, {67.33, 126.33}, {70.27, 125.48}, {69.10, 115.71},
     {65.38, 123.49}, {70.18, 147.89}, {70.41, 155.90}, {66.54, 128.07}, {66.36, 119.37}, {67.54, 133.81},
     {66.50, 128.73}, {69.00, 137.55}, {68.30, 129.76}, {67.01, 128.82}, {70.81, 135.32}, {68.22, 109.61},
     {69.06, 142.47}, {67.73, 132.75}, {67.22, 103.53}, {67.37, 124.73}, {65.27, 129.31}, {70.84, 134.02},
     {69.92, 140.40}, {64.29, 102.84}, {68.25, 128.52}, {66.36, 120.30}, {68.36, 138.60}, {65.48, 132.96},
     {69.72, 115.62}, {67.73, 122.52}, {68.64, 134.63}, {66.78, 121.90}, {70.05, 155.38}, {66.28, 128.94},
     {69.20, 129.10}, {69.13, 139.47}, {67.36, 140.89}, {70.09, 131.59}, {70.18, 121.12}, {68.23, 131.51},
     {68.13, 136.55}, {70.24, 141.49}, {71.49, 140.61}, {69.20, 112.14}, {70.06, 133.46}, {70.56, 131.80},
     {66.29, 120.03}, {63.43, 123.10}, {66.77, 128.14}, {68.89, 115.48}, {64.87, 102.09}, {67.09, 130.35},
     {68.35, 134.18}, {65.61, 98.64},  {67.76, 114.56}, {68.02, 123.49}, {67.66, 123.05}, {66.31, 126.48},
     {69.44, 128.42}, {63.84, 127.19}, {67.72, 122.06}, {70.05, 127.61}, {70.19, 131.64}, {65.95, 111.90},
     {70.01, 122.04}, {68.61, 128.55}, {68.81, 132.68}, {69.76, 136.06}, {65.46, 115.94}, {68.83, 136.90},
     {65.80, 119.88}, {67.21, 109.01}, {69.42, 128.27}, {68.94, 135.29}, {67.94, 106.86}, {65.63, 123.29},
     {66.50, 109.51}, {67.93, 119.31}, {68.89, 140.24}, {70.24, 133.98}, {68.27, 132.58}, {71.23, 130.70},
     {69.10, 115.56}, {64.40, 123.79}, {71.10, 128.14}, {68.22, 135.96}, {65.92, 116.63}, {67.44, 126.82},
     {73.90, 151.39}, {69.98, 130.40}, {69.52, 136.21}, {65.18, 113.40}, {68.01, 125.33}, {68.34, 127.58},
     {65.18, 107.16}, {68.26, 116.46}, {68.57, 133.84}, {64.50, 112.89}, {68.71, 130.76}, {68.89, 137.76},
     {69.54, 125.40}, {67.40, 138.47}, {66.48, 120.82}, {66.01, 140.15}, {72.44, 136.74}, {64.13, 106.11},
     {70.98, 158.96}, {67.50, 108.79}, {72.02, 138.78}, {65.31, 115.91}, {67.08, 146.29}, {64.39, 109.88},
     {69.37, 139.05}, {68.38, 119.90}, {65.31, 128.31}, {67.14, 127.24}, {68.39, 115.23}, {66.29, 124.80},
     {67.19, 126.95}, {65.99, 111.27}, {69.43, 122.61}, {67.97, 124.21}, {67.76, 124.65}, {65.28, 119.52},
     {73.83, 139.30}, {66.81, 104.83}, {66.89, 123.04}, {65.74, 118.89}, {65.98, 121.49}, {66.58, 119.25},
     {67.11, 135.02}, {65.87, 116.23}, {66.78, 109.17}, {68.74, 124.22}, {66.23, 141.16}, {65.96, 129.15},
     {68.58, 127.87}, {66.59, 120.92}, {66.97, 127.65}, {68.08, 101.47}, {70.19, 144.99}, {65.52, 110.95},
     {67.46, 132.86}, {67.41, 146.34}, {69.66, 145.59}, {65.80, 120.84}, {66.11, 115.78}, {68.24, 128.30},
     {68.02, 127.47}, {71.39, 127.88}}};

template <size_t SIZE>
class distribution {
  // linalg::vec<double, SIZE> m_means;
public:
  // void update(linalg::vec<double, SIZE> const& xs) {
  // }
}; // class distribution

TEST_CASE("cent example") {
  tybl::stats::distribution<int> dist;
  auto input = {5, 5, 10, 10, 10};
  for (auto i : input) {
    dist += i;
  }
  CHECK(8 == dist.mean());
}

TEST_CASE("weight example") {
  tybl::stats::distribution<double> dist;
  auto input = {79.8, 80.0, 80.1, 79.8, 80.2};
  for (auto i : input) {
    dist += i;
  }
  CHECK(79.98 == dist.mean());
}

TEST_CASE("team height") {
  tybl::stats::distribution<double> team_a_dist;
  tybl::stats::distribution<double> team_b_dist;
  std::array<double, 5> team_a = {1.89, 2.1, 1.75, 1.98, 1.85};
  std::array<double, 5> team_b = {1.94, 1.9, 1.97, 1.89, 1.87};
  for (int i = 0; i < 5; ++i) {
    team_a_dist += team_a[i];
    team_b_dist += team_b[i];
  }
  CHECK(1.914 == team_a_dist.mean());
  CHECK(1.914 == team_b_dist.mean());
  CHECK(doctest::Approx(0.014104) == team_a_dist.pop_var());
  CHECK(doctest::Approx(0.001304) == team_b_dist.pop_var());
}

TEST_CASE("naive algorithm") {
  size_t n = data.size();
  double weight_total = 0.0;
  double height_total = 0.0;
  double cross_total = 0.0;
  for (auto& e : data) {
    weight_total += e(0);
    height_total += e(1);
    cross_total += e(0) * e(1);
  }
  std::cerr << "Naive algorithm: " << (cross_total - ((weight_total * height_total) / n)) / n << std::endl;
}

TEST_CASE("two pass") {
  size_t n = data.size();
  double weight_total = 0.0;
  double height_total = 0.0;
  for (auto& e : data) {
    weight_total += e(0);
    height_total += e(1);
  }
  double weight_mean = weight_total / n;
  double height_mean = height_total / n;
  double covariance = 0.0;
  for (auto& e : data) {
    double a = e(0) - weight_mean;
    double b = e(1) - height_mean;
    covariance += (a * b) / n;
  }
  std::cerr << "Two pass: " << covariance << std::endl;
}

TEST_CASE("online") {
  tybl::stats::distribution<double> xdist;
  tybl::stats::distribution<double> ydist;
  size_t n = 0;
  double c00 = 0.0;
  double c01 = 0.0;
  double c11 = 0.0;
  double mx = 0.0;
  double my = 0.0;

  for (auto& e : data) {
    n += 1;
    xdist += e(0);
    ydist += e(1);
    double dx1 = e(0) - mx;
    double dy1 = e(1) - my;
    mx += dx1 / n;
    my += dy1 / n;
    double dx2 = e(0) - mx;
    double dy2 = e(1) - my;
    c00 += dx1 * dx2;
    c01 += dx1 * dy2;
    c11 += dy1 * dy2;
  }
  std::cout << std::setw(10) << c00 / n << std::setw(10) << c01 / n << "\n"
            << std::setw(10) << c01 / n << std::setw(10) << c11 / n << "\n\n";
  double covariance = c01 / n;
  std::cerr << "Online: " << covariance << std::endl;
}

TEST_CASE("matrix") {
  tybl::stats::dist<2> d;
  size_t n = 0;
  Eigen::Vector2d mean = Eigen::Vector2d::Zero();
  Eigen::Matrix2d C = Eigen::Matrix2d::Zero();

  for (auto& x : data) {
    d.insert(x);
    n += 1;
    Eigen::Vector2d d = x - mean;
    mean += d / n;
    Eigen::Matrix2d dC = (x - mean) * d.transpose() - C;
    C += dC / n;
  }
  auto const& m = d.means();
  CHECK(m(0) == mean(0));
  CHECK(m(1) == mean(1));
  auto const& c = d.covariance();
  CHECK(c(0, 0) == C(0, 0));
  CHECK(c(0, 1) == C(0, 1));
  CHECK(c(1, 0) == C(1, 0));
  CHECK(c(1, 1) == C(1, 1));
  std::cout << std::setw(10) << C(0, 0) << std::setw(10) << C(0, 1) << "\n"
            << std::setw(10) << C(1, 0) << std::setw(10) << C(1, 1) << "\n\n";
}
