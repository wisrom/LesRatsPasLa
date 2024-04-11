TEMPLATE = vcapp
TARGET = Game
CONFIG += qt warn_on debug windows
HEADERS += \
UI/Qt/DisplayMenuQt.h \
UI/Qt/DisplayGameQt.h \
UI/Qt/GameView.h \
UI/Qt/ReelGauge.hpp \
UI/Console/DisplayColor.hpp \
UI/Console/DisplayConsole.hpp \
UI/Console/DisplayGame.hpp \
UI/Console/DisplayMenu.hpp \
UI/Console/MenuOption.hpp \
UI/Console/Menu.hpp \
Types/CaptureStep.hpp \
Types/InputGame.hpp \
Types/InputMenu.hpp \
Types/Movement.hpp \
Types/Position.hpp \
Types/RunSettings.hpp \
RNG/IRng.hpp \
RNG/RngClassic.hpp \
RNG/RngMuons.hpp \
Output/IOutput.hpp \
Output/OutputArduino.hpp \
Output/OutputConsole.hpp \
Input/IInput.hpp \
Input/InputArduino.hpp \
Input/InputConsole.hpp \
GameDomain/FishingRun.hpp \
GameDomain/FishingSession.hpp \
GameDomain/Watershed.hpp \
GameDomain/Entities/Entity.hpp \
GameDomain/Entities/Fish.hpp \
GameDomain/Entities/Player.hpp \
GameDomain/Map/Environment.hpp \
GameDomain/Map/Map.hpp \
Data/DataFile.hpp \
Data/DataMemory.hpp \
Data/FishDTO.hpp \
Data/IData.hpp \
Communication/ComSerialJSON.hpp \
Communication/include/json.hpp \
Communication/include/serial/SerialPort.hpp \

SOURCES += \
ProjetS2.cpp \
UI/Qt/DisplayMenuQt.cpp \
UI/Qt/DisplayGameQt.cpp \
UI/Qt/GameView.cpp \
UI/Qt/main.cpp \
UI/Qt/ReelGauge.cpp \
UI/Console/DisplayConsole.cpp \
UI/Console/DisplayGame.cpp \
UI/Console/DisplayMenu.cpp \
RNG/RngClassic.cpp \
RNG/RngMuons.cpp \
Output/OutputArduino.cpp \
Output/OutputConsole.cpp \
Input/InputArduino.cpp \
Input/InputConsole.cpp \
GameDomain/FishingRun.cpp \
GameDomain/FishingSession.cpp \
GameDomain/Watershed.cpp \
GameDomain/Entities/Entity.cpp \
GameDomain/Entities/Fish.cpp \
GameDomain/Entities/Player.cpp \
GameDomain/Map/Environment.cpp \
GameDomain/Map/Map.cpp \
Data/DataFile.cpp \
Data/DataMemory.cpp \
Communication/ComSerialJSON.cpp \
Communication/include/serial/SerialPort.cpp \



RESOURCES += \
UI/Qt/styles.css \
GameData/Fish/Fish.csv \
GameData/Fish/FishPool.csv \
GameData/Maps/Maps.csv \
GameData/Scores/Scores.csv \
Img/bulles.png \
Img/water.jpg \
Img/boat.png \
Img/poisson.png \
Img/nemo.jpg \

QT += widgets multimedia