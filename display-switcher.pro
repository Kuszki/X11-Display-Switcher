#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T19:33:20
#
#-------------------------------------------------

TARGET		=	display-switcher
TEMPLATE		=	app

QT			+=	core gui widgets

SOURCES		+=	main.cpp \
				mainwindow.cpp

HEADERS		+=	mainwindow.hpp

FORMS		+=	mainwindow.ui

CONFIG		+=	c++11
QMAKE_CXXFLAGS	+=	-O3
