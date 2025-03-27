# MediaSphere

## About The Project

**MediaSphere** is a personal project for educational purposes and allows you to demonstrate some of what you can do as a desktop application with the Qt framework.

But more importantly, it is openly accessible for the pleasure of sharing knowledge.

Its current functional purpose is to provide a series of menus ranging from multimedia management (music, video), to weather, and finally video games.

It's nothing technically innovative, but it nevertheless provides a good understanding of how the Qt framework works.

Besides, this project is not finished at all, lots of things can be added. 

## Getting Started

MediaSphere is **multiplatform**, it can be built on **Linux** and **Windows**.

### Prerequisites

You will need to install Qt by following these links:
- [Qt5 Installation Guide](https://github.com/qt/qt5)
- [Qt6 Linux Installation Guide](https://doc.qt.io/qt-6/linux.html)

### Installation
The installation tutorial is only valid for Linux platform
To build the app in release mode, run the following command:

```bash
./build.sh
```
### Deployment
If you want to use this app without any external dependencies, you can deploy an AppImage using linuxdeployqt

You will need to install linuxdeployqt on a old OS (like Ubuntu 20.04):
- [linuxdeployqt](https://github.com/probonopd/linuxdeployqt)

Then you can run :
```bash
./deploy.sh
```
### License

This project is under MIT license

