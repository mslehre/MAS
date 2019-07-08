CXXFLAGS := -std=c++11 -Wall -Wno-narrowing -O3 ${CXXFLAGS}
OBJ = linRegMain.o State.o Graph.o Node.o Edge.o Policy.o valueMLmodel.o Agent.o TrainingSet.o RLDataset.o
H1 = ../../../alignment/Graph.h
H2 = ../../../alignment/Edge.h
H3 = ../../../alignment/Node.h
H4 = ../../../alignment/State.h
H5 = ../../SimpleAgent/Episode.h
H6 = ../../SimpleAgent/Agent.h
H9 = ../valueMLmodel.h
H10 = ../Policy.h
H11 = ../LinearNet.h
H12 = ../RLDataset.h
H13 = ../TrainingSet.h
torchOpt1 = -l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -lcaffe2 -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch -lpthread
torchOpt2 = -D_GLIBCXX_USE_CXX11_ABI=0

all: linRegMain

linRegMain: $(OBJ)
	g++ $(OBJ) -o linRegMain -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \
	$(torchOpt1) $(torchOpt2)

linRegMain.o: linRegMain.cc $(H4) $(H10) $(H6) $(H9) $(H13)
	g++ $(CXXFLAGS) -c linRegMain.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \
	$(torchOpt1) $(torchOpt2)

State.o: ../../../alignment/State.cc $(H4) $(H2) $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../../alignment/State.cc

Policy.o: ../Policy.cc $(H9) $(H4)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../Policy.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \

valueMLmodel.o: ../valueMLmodel.cc $(H11) $(H12)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../valueMLmodel.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \

Agent.o: ../../SimpleAgent/Agent.cc $(H6)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../SimpleAgent/Agent.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \

RLDataset.o: ../RLDataset.cc $(H12)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../RLDataset.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \

TrainingSet.o: ../TrainingSet.cc $(H13)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../TrainingSet.cc -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \

Graph.o: ../../../alignment/Graph.cc $(H1) $(H2) $(H3) $(H4)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../../alignment/Graph.cc

Edge.o: ../../../alignment/Edge.cc $(H2) $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../../alignment/Edge.cc

Node.o: ../../../alignment/Node.cc $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../../alignment/Node.cc

clean:
	rm -f *.o linRegMain net.pt
