# OMPL_DIR is the installation prefix for OMPL.
# YOU MUST CHANGE THIS VARIABLE depending on your installation!
# /usr for the virtual machine and deb packages
# /usr/local for install script
# /opt/local for OS X using MacPorts
OMPL_DIR=/usr
prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir_old=${prefix}/include/opencv
includedir_new=${prefix}/include


# Compilation flags
CXX_FLAGS=-std=c++11 -O2
# Change the -O2 flag to -g -O0 when debugging code, -O2 is for optimization.
# -g allows you to use tools like gdb to analyze your code.

# Include directories
INCLUDE_FLAGS=-I${OMPL_DIR}/include
# Linker options
LD_FLAGS=-L${OMPL_DIR}/lib -lompl -lboost_system -lompl_app -lompl_app_base -Wl,-rpath ${OMPL_DIR}/lib

Libs= -L${libdir} -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lopencv_videoio -lcurl -lrt
Cflags= -I${includedir_old} -I${includedir_new}

#CV_FLAGS= g++ -L${OMPL_DIR}/local/include/opencv2 -L${OMPL_DIR}/local/include/opencv -L${OMPL_DIR}/local/lib -g -o binary FaceDetection.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching

# The c++ compiler to invoke
CXX=c++

all:	FaceDetection

clean:
	rm -f *.o
	rm -f FaceDetection

FaceDetection: FaceDetection.o SendCommands.o Detect.o
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -o FaceDetection FaceDetection.o SendCommands.o Detect.o $(LD_FLAGS) $(Libs) $(Cflags)

#SendCommands: SendCommands.o
#	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -o SendCommands SendCommands.o $(LD_FLAGS) $(Libs) $(Cflags)

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_FLAGS) $< -o $@
