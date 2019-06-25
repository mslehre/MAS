include ../../common.mk
CC = g++ -std=c++11
OBJ = RandomAgent_main.o State.o Graph.o Node.o Edge.o Agent.o
H1 = ../../alignment/Graph.h
H2 = ../../alignment/Edge.h
H3 = ../../alignment/Node.h
H4 = ../../alignment/State.h
H5 = ../pytorch/LearnedPolicy.h
H6 = Episode.h
torchOpt1 = -l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gloo_builder -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l THD -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l caffe2 -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch -lpthread
torchOpt2 = -D_GLIBCXX_USE_CXX11_ABI=0
all: RandomAgent_main

RandomAgent_main: $(OBJ)
	g++ $(CXXFLAGS) $(OBJ) -o RandomAgent_main -I ../pytorch/libtorch/include/torch/csrc/api/include -I ../pytorch/libtorch/include/ -L ../pytorch/libtorch/lib/ \
	$(torchOpt1) $(torchOpt2)

RandomAgent_main.o: RandomAgent_main.cc Agent.h Policy.h RandomPolicy.h $(H1) $(H2) $(H3) $(H4)
	g++ $(CXXFLAGS) -c RandomAgent_main.cc -I ../pytorch/libtorch/include/torch/csrc/api/include -I ../pytorch/libtorch/include/ -L ../pytorch/libtorch/lib/ \
	$(torchOpt1) $(torchOpt2)

Agent.o: Agent.cc Agent.h $(H5) $(H6)
	g++ $(CXXFLAGS) -c Agent.cc -I ../pytorch/libtorch/include/torch/csrc/api/include -I ../pytorch/libtorch/include/ -L ../pytorch/libtorch/lib/ \
	$(torchOpt1) $(torchOpt2)

State.o: ../../alignment/State.cc $(H4) $(H2) $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../alignment/State.cc 

Graph.o: ../../alignment/Graph.cc $(H1) $(H2) $(H3) $(H4)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../alignment/Graph.cc

Edge.o: ../../alignment/Edge.cc $(H2) $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../alignment/Edge.cc

Node.o: ../../alignment/Node.cc $(H3)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../../alignment/Node.cc

clean:
	rm -f *.o RandomAgent_main
