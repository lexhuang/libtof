#ifndef TOFMANAGER_H
#define TOFMANAGER_H

#include "Device.h"

#include "voxelfw-linux.h"

//file open for devices
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <errno.h>

#include <linux/videodev2.h>


class TOFManager
{
private:
    VoxelDevice *device;
    int deviceNumber;
    int deviceCount;
    int deviceAddr[64];
    int majorVersion;
    int minorVersion;
    bool isDeviceOpen;
    TPS659122RegProgrammer *tpsDevice;
public:
    TOFManager();
    ~TOFManager();
    void populateDeviceList();
    void fwInit();
    void enumerateCameras();
    void voxelInit();
    VoxelDevice *getDevice() const;
    void setDevice(VoxelDevice *value);
    void reInit();
};

#endif // TOFMANAGER_H
