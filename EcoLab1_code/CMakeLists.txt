cmake_minimum_required(VERSION 3.24.2)
project(EcoLab1 C)

set(CMAKE_C_STANDARD 89)

set(CMAKE_C_FLAGS "/TC /Gz")
set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE")
set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE")

add_definitions(-DECO_WINDOWS)
add_definitions(-D_DEBUG)
add_definitions(-DECO_DLL)
add_definitions(-DUGUID_UTILITY)
add_definitions(-DECO_WIN32)
add_definitions(-DWIN32)
add_definitions(-D_WINDOWS)
add_definitions(-D_CONSOLE)

include_directories(HeaderFiles)
include_directories(SharedFiles)
#include_directories(UnitTestFiles/HeaderFiles)

include_directories(
        $ENV{ECO_FRAMEWORK}/Eco.List1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.Core1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.System1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/SharedFiles
)


add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3A
        SHARED
        SourceFiles/CEcoLab1Gnome.c
        SourceFiles/CEcoLab1GnomeFactory.c
        SharedFiles/IdEcoLab1Gnome.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1Gnome.h
        HeaderFiles/CEcoLab1GnomeFactory.h
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3B
        SHARED
        SourceFiles/CEcoLab1Insertion.c
        SourceFiles/CEcoLab1InsertionFactory.c
        SharedFiles/IdEcoLab1Insertion.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1Insertion.h
        HeaderFiles/CEcoLab1InsertionFactory.h
)

add_executable(
        EcoLab1
        UnitTest/SourceFiles/EcoLab1.c
        SharedFiles/IdEcoLab1Gnome.h
        SharedFiles/IEcoLab1.h
        SharedFiles/IdEcoLab1Insertion.h
        HeaderFiles/CEcoLab1Gnome.h
        HeaderFiles/CEcoLab1GnomeFactory.h
        HeaderFiles/CEcoLab1Insertion.h
        HeaderFiles/CEcoLab1InsertionFactory.h

        #        UnitTestFiles/HeaderFiles/AppDelegate.h
        #        UnitTestFiles/HeaderFiles/EcoDemoDialog.h
        #        UnitTestFiles/HeaderFiles/GameViewController.h
        #        UnitTestFiles/SourceFiles/AppDelegate.m
        #        UnitTestFiles/SourceFiles/EcoDemoDialogIOS.m
        #        UnitTestFiles/SourceFiles/GameViewController.m
)

target_link_libraries(EcoLab1 1F5DF16EE1BF43B999A434ED38FE8F3A 1F5DF16EE1BF43B999A434ED38FE8F3B)
target_link_libraries(
        EcoLab1
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib
)
