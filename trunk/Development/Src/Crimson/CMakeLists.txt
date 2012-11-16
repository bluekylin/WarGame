#include_directories(${WarGame_SOURCE_DIR}/Core)
#include_directories(${WarGame_SOURCE_DIR}/Engine)
#include_directories(${WarGame_SOURCE_DIR}/GameFramework)
include_directories(${WarGame_SOURCE_DIR}/../ThirdParty/Win/cocos2d-x/include)

#link_directories(${WarGame_BINARY_DIR}/Core)
#link_directories(${WarGame_BINARY_DIR}/Engine)
#link_directories(${WarGame_BINARY_DIR}/GameFramework)
link_directories(${WarGame_SOURCE_DIR}/../ThirdParty/Win/cocos2d-x/lib)

add_executable (WarGame_Crimson CrimsonGame.cpp AppDelegate.cpp)

#target_link_libraries (WarGame_Crimson Core)
#target_link_libraries (WarGame_Crimson Engine) 
#target_link_libraries (WarGame_Crimson GameFramework) 
target_link_libraries (WarGame_Crimson libcocos2d.lib) 