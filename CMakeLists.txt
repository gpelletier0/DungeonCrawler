cmake_minimum_required(VERSION 3.16)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 20)

add_executable(DungeonCrawler main.cpp Room.cpp Dungeon.cpp Dungeon.h GameCharacter.cpp GameCharacter.h Player.cpp Player.h Game.cpp Game.h Vector2Int.cpp Item.cpp)