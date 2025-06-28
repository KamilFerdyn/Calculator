cmake_minimum_required(VERSION 3.28)
project(Kalkulator)

set(CMAKE_CXX_STANDARD 17)

# Ustaw ścieżki do SFML zainstalowanego przez Homebrew
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml")

# Znajdź bibliotekę SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Dodaj plik źródłowy
add_executable(Kalkulator main.cpp)

# Połącz projekt z bibliotekami SFML
target_link_libraries(Kalkulator sfml-system sfml-window sfml-graphics sfml-network sfml-audio)