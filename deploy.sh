#!/bin/bash

# Define variables
APP_NAME="appMediaSphere"
ICON_NAME="iconMediaShere"
BUILD_DIR="build/Release"
DEPLOY_DIR="deployment"
QML_DIR="qml"
ASSETS_DIR="assets"
LINUXDEPLOYQT="./linuxdeployqt-continuous-x86_64.AppImage"
CMAKE_COMMAND="/usr/bin/cmake"
QT_PATH="/home/lucas/Qt/6.8.2/gcc_64"
QMAKE_PATH="$QT_PATH/bin/qmake"

# Build the application
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake ../../ -DCMAKE_BUILD_TYPE=Release
make
cd ../../

# Create deployment directory
echo "Creating deployment directory"
mkdir -p $DEPLOY_DIR

# Copy the application binary
echo "Copy application binary"
cp $BUILD_DIR/$APP_NAME $DEPLOY_DIR/

# Copy QML files
echo "copying qml files to ${DEPLOY_DIR}"
cp -r $QML_DIR $DEPLOY_DIR/

# Copy assets
echo "copying assets to ${DEPLOY_DIR}"
cp -r $ASSETS_DIR $DEPLOY_DIR/

echo "copying ${ICON_NAME} to ${DEPLOY_DIR}"
cp $ASSETS_DIR/$ICON_NAME.png $DEPLOY_DIR/

# Create a desktop file
cat <<EOL > $DEPLOY_DIR/$APP_NAME.desktop
[Desktop Entry]
Name=MediaSphere
Exec=appMediaSphere
Icon=$ICON_NAME
Type=Application
Categories=AudioVideo;
EOL

# Run linuxdeployqt
$LINUXDEPLOYQT $DEPLOY_DIR/$APP_NAME -qmake=$QMAKE_PATH -qmldir=$DEPLOY_DIR/$QML_DIR -appimage

echo "Deployment completed. AppImage is located in the deploy.sh directory."

