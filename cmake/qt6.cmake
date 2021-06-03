

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt6 COMPONENTS CoreTools Core Network REQUIRED
            PATHS "C:/Qt/6.1.0/msvc2019_64/lib/cmake/Qt6")

set(
    QT6_LIBRARIES

    Qt6::Core
    # Qt6::Widgets
    Qt6::Network
    # Qt6::Sql
    # Qt6::Multimedia

    ZLIB::ZLIB
    OpenSSL::SSL
    OpenSSL::Crypto
)
