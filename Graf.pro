TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += lib/Graflib.pro tst/test.pro
tst.depends = lib
