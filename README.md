# Build Applications for TIYCam

## Intruduction
TIYCam is an open-source IPC system powered by a Quad-Core ARM Cortex-A7 processor and a 2.0Tops NPU. By default, we have installed the JES application on TIYCam, which provides basic surveillance camera functions. It also enables users to develop AI video surveillance and other applications on their own.

## Directory Structure
```bash 
├── board_libs     
│   └── rv1126
├── examples        # JES examples
│   └── hello_ipk
│   └── ...
├── ipkg_tool       # IPKG tool
│   ├── ipkg-build
│   └── pack_ipk.sh
├── lib             # JES libs
│   ├── jes_doc     # JES documentation
│   └── rv1126      # JES libs and include files
└── README.md
```

## Steps for building applications for TIYCam

### 1. Set up development environment on the Host PC
TIYCam is ARM based CPU, and the host development is X86. To develop arm based application on x86 based PC, we need cross compile, and use the cross-compilation toolchain. 
Install [gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf](https://linksprite.s3.amazonaws.com/TIYCam/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tgz) on Ubuntu20 as our development environment.

```bash
# Download toolchain
cd /opt
wget https://linksprite.s3.amazonaws.com/TIYCam/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tgz
tar xzf gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tgz 
```

```bash
# Set up environment variables
sudo vim /etc/profile 
```
```bash
# Append the following line to the end of the file
export PATH="/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin:$PATH"
```

Install NFS server for sharing file to TIYCam
```bash
sudo apt install -y nfs-kernel-server nfs-common -y
vim /etc/exports
# add the following line
/home/ubuntu *(rw,sync,no_root_squash,no_subtree_check)
```
```bash 
# restart nfs server
sudo systemctl restart nfs-server
```

### 2. Build Hello world application
To demonstrate how to develop applications on TIYCam, let's take the "Hello World" example and walk through the entire process from compilation, packaging, installation, to execution.
```bash
git clone https://github.com/deepcam-cn/tiycam-examples
cd tiycam-examples/examples/hello_ipk

mkdir build && cd build
cmake .. && make 
make install # install to /ipk/Hello_RV1126_Linux/usr/bin/./Hello_RV1126_Linux
```

```bash
cd ../ipk
./pack_ipk.sh ./Hello_RV1126_Linux # generate ipk package
```

### 3. Install and run application on TIYCam
```bash
# install ipk package with opkg command 
telnet <TIYCAM IP>  # username: root

mount -t nfs -o tcp -o nolock <HOST PC IP>:/home/ubuntu /mnt # mount the shared folder to TIYCam
cd /mnt/<tiycamexamples dir>/tiycam-examples/examples/hello_ipk/ipk

opkg install Hello_RV1126_Linux_1.0.0_arm.ipk  # install the ipk file

opkg status Hello_RV1126_Linux # check installation status

/etc/init.d/S100Hello_RV1126_Linux restart # manually restart the application
```

**basic opkg tips**:
1. `opkg remove Hello_RV1126_Linux` to remove the package
2. `opkg install Hello_RV1126_Linux_1.0.0_arm.ipk` to install the package
3. `opkg status Hello_RV1126_Linux` to check the installation status
4. `opkg install Hello_RV1126_Linux_1.0.0_arm.ipk --force-reinstall ` to reinstall the package 

## Todo List
- [x] Build hello IPK application
- [ ] Build Yolov5 Object Detection Application
- [ ] Build Face Detect Application