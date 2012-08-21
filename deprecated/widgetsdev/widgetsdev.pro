TEMPLATE =  subdirs

SUBDIRS += widgetsapi
CONFIG(release, debug|release):SUBDIRS += widgetsextension
