project (fusemount)

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(QT_MIN_VERSION "5.6.0")
set(KF5_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication 
)

# Find KDE modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons      # KAboutData
    I18n            # KLocalizedString
    WidgetsAddons   # KMessageBox
    Wallet
    XmlGui
    ConfigWidgets
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(fusemount_SRCS src/main.cpp src/mainwindow.cpp src/mounttreewidget.cpp)

add_executable(fusemount ${fusemount_SRCS})

target_link_libraries(fusemount
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::Wallet
    KF5::XmlGui
    KF5::ConfigWidgets
)

install(TARGETS fusemount  ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES src/fusemountui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/fusemount)
