#include "tofmanager.h"


VoxelDevice *TOFManager::getDevice() const
{
    return device;
}

void TOFManager::setDevice(VoxelDevice *value)
{
    device = value;
}

TOFManager::TOFManager()
{
    isDeviceOpen =false;
    this->device = new VoxelDevice();
    this->deviceNumber = 1;
    this->deviceCount = 0;

    tpsDevice = new TPS659122RegProgrammer();
    this->fwInit();
    this->voxelInit();

    this->populateDeviceList();
    VoxelI2CRegProgrammer *regProg = new VoxelI2CRegProgrammer(deviceAddr[this->deviceNumber], deviceCount);
    this->device->setProgrammer(regProg);
    VoxelCaptureDevice *capDev = new VoxelCaptureDevice(240, 320, deviceAddr[deviceNumber]);
    device->setCaptureDevice(capDev);

    device->regProgrammer->selectDevice(deviceAddr[deviceNumber], deviceCount);
    reInit();
}

TOFManager::~TOFManager(){
    if (isDeviceOpen) {
        device->release();
    }
}

void TOFManager::populateDeviceList() {
    int j, fd;
    int devCounter = 0;
    char devName[255];
    for (j = 0; j < 64; j++) {
        sprintf(devName, "/dev/video%d", j);
        fd = open(devName, O_RDWR);
        if (fd == -1) {
        }
        else {
            deviceAddr[devCounter] = j;
            devCounter += 1;
        }
    }
    deviceCount = devCounter;
}

void TOFManager::fwInit()
{
    std::string tempAddr;
    //tempAddr.append(QDir::currentPath().toLocal8Bit().data());
    tempAddr.append("/sdcard/OPT9220_0v27.tip");
    FW_DOWNLOADER::sendsp(strdup(tempAddr.c_str()));
    sleepFunction(2000);
    this->enumerateCameras();
}

static int xioctl(int fd, int request, void *arg) {
    int r;
    do {
        r = ioctl(fd, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}

struct v4l2_capability print_caps(int fd) {
    struct v4l2_capability caps = {};
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps)) {
        perror("Querying Capabilities");
        return caps;
    }
    return caps;
}

void TOFManager::enumerateCameras()
{
    //cameraSelect->combo->clear();
    int i, j;
    char tempStr[255];
    struct v4l2_capability retDevName;
    char devName[255];
    int temp = 1;
    int devCounter = 0;
    int fd;
    for (j = 0; j < 64; j++) {
        sprintf(devName, "/dev/video%d", j);
        fd = open(devName, O_RDWR);
        if (fd == -1) {
        }
        else {
            retDevName = print_caps(fd);
            sprintf(tempStr, "%d: %s", j, retDevName.card);
            //cameraSelect->combo->addItem(tempStr);
            deviceAddr[devCounter] = j;
            devCounter += 1;
        }
    }
}

void TOFManager::voxelInit()
{
    VoxelI2CRegProgrammer *tempProg = new VoxelI2CRegProgrammer(deviceAddr[deviceNumber], deviceCount);
    device->setProgrammer(tempProg);
    tpsDevice = new TPS659122RegProgrammer();

    /*
     * Make sure to start with a lower illum power
     * in case the range register is not properly set
     * and then increase it just after
     */
    tpsDevice->writeReg(0x0E, 0x14);
    tpsDevice->writeReg(0x0F, 0xFF);
    tpsDevice->writeReg(0x0D, 0x54);
    tpsDevice->writeReg(0x0E, 0x94);

    device->setRampPat(3);
    device->setBlkHeaderEn(1);
    device->setOpCsPolarity(1);
    device->setFbReadyEn(1);
    device->setAmplitudeScale(2);
    device->setFrequencyScale(25);
    device->setPixCntMax(120000);
    device->setEasyConfEn(1);
    // FIXME: This inverts the illum_en polarity
    // and should be done only on the rev 2p2 and newer boards
    device->setIllumPolarity(0);
    //confidenceThreshold->lineEdit->setText("1");
    int versionReg = device->regProgrammer->readReg(1);
    majorVersion = (versionReg & 0xFF00) >> 8;
    minorVersion = versionReg & 0xFF;
    if(majorVersion == 85 && minorVersion == 170) {
        majorVersion = 0;
        minorVersion = 0;
    }
    device->setTgEn(1);
    isDeviceOpen = true;
}

void TOFManager::reInit() {
    /*
     * If device is open release it
     * Also call voxelInit
    */
    if (isDeviceOpen) {
        device->release();
    }
    this->voxelInit();
}
