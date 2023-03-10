# Ceci est un fichier de configuration pour une application Qt
# Il faut peut-etre legerement l adapter pour votre ordinateur.

# nom de votre executable
TARGET  = viewer
# config de l executable
QMAKE_CXXFLAGS = --std=c++11
CONFIG *= qt opengl release c++11

# config de Qt
QT *= opengl xml
QT += widgets
QT += openglwidgets 

# Noms de vos fichiers entete
HEADERS = Viewer.h Utils.h
# Noms de vos fichiers source (vous pouvez en mettre d'autres)
SOURCES = Viewer.cpp main.cpp Utils.cpp

###########################################################
# Commentez/decommentez selon votre config/systeme
# (Une config windows est possible)
###########################################################

# Exemple de configuration Linux de Qt et libQGLViewer Qt5
# Ubuntu 16.04
# INCLUDEPATH *= /usr/include
# LIBS *= -L/usr/lib/x86_64-linux-gnu -lQGLViewer

# Exemple de configuration MacOSX avec macports
# INCLUDEPATH *= /opt/local/include
# LIBS *= -L/opt/local/lib -lQGLViewer 

# Exemple de configuration MacOSX avec frameworks
 INCLUDEPATH *= /Users/huseyinyurtseven/Downloads/libQGLViewer-2.9.1
 LIBS *= -F/Users/huseyinyurtseven/Downloads/libQGLViewer-2.9.1/QGLViewer -framework QGLViewer

# Exemple de configuration Windows :
# LIBS *= -lopengl32 -lglu32
# INCLUDEPATH *= D:\Cours\Info805\TP1\libQGLViewer-2.7.1
# LIBS *= -LD:\Cours\Info805\TP1\libQGLViewer-2.7.1\QGLViewer -lQGLViewer2
