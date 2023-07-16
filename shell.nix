{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.clang-tools_15
    pkgs.cmake
    pkgs.gcc
  ];
  nativeBuildInputs = [
    pkgs.doctest
    pkgs.fmt_9
    pkgs.howard-hinnant-date
    pkgs.sfml
    pkgs.spdlog
  ];
}
