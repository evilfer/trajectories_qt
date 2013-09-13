
DEFINES += _TRAJECTORIES_USE_OWN_WIN_STRPTIME

win32: LIBS += -L$$PWD/../../libs/mingw_cspice/lib/ -lming_cspice
INCLUDEPATH += $$PWD/../../libs/mingw_cspice/include
DEPENDPATH += $$PWD/../../libs/mingw_cspice/include
#win32: PRE_TARGETDEPS += $$PWD/../../libs/mingw_cspice/lib/ming_cspice.lib

win32: LIBS += -L$$PWD/../../libs/mingw_sqlite3/lib/ -lsqlite3
INCLUDEPATH += $$PWD/../../libs/mingw_sqlite3/include
DEPENDPATH += $$PWD/../../libs/minwg_sqlite3/include
#win32: PRE_TARGETDEPS += $$PWD/../../libs/minwg_sqlite3/lib/sqlite3.lib

