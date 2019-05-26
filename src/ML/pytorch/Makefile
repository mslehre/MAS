include ../../common.mk
CC = -std=c++11
OBJ = TestDataset.o State.o Graph.o Node.o Edge.o
H1 = ../../alignment/Graph.h
H2 = ../../alignment/Edge.h
H3 = ../../alignment/Node.h
H4 = ../../alignment/State.h
H5 = ../../ReinforcementLearning/SimpleAgent/Episode.h
H6 = ../../ReinforcementLearning/SimpleAgent/Agent.h
H7 = ../../ReinforcementLearning/SimpleAgent/RandomPolicy.h
H8 = ../../ReinforcementLearning/SimpleAgent/Policy.h

all: TestDataset

TestDataset: $(OBJ) 
	g++ $(OBJ) -o TestDataset -I libtorch/include/torch/csrc/api/include -I libtorch/include/ -L libtorch/lib/ \
	-l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gloo_builder -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l THD -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l caffe2 -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch \
	-lpthread -D_GLIBCXX_USE_CXX11_ABI=0 

TestDataset.o: TestDataset.cc $(H1) $(H2) $(H3) $(H4) $(H5) $(H6) $(H7) $(H8)
	g++ $(CXXFLAGS) -c TestDataset.cc -I libtorch/include/torch/csrc/api/include -I libtorch/include/ -L libtorch/lib/ \
	-l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gloo_builder -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l THD -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l caffe2 -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch \
	-lpthread -D_GLIBCXX_USE_CXX11_ABI=0 

State.o: ../../alignment/State.cc $(H4) $(H2) $(H3)
	g++ $(CXXFLAGS) -D_GLIBCXX_USE_CXX11_ABI=0 -c -Wall ../../alignment/State.cc 

Graph.o: ../../alignment/Graph.cc $(H1) $(H2) $(H3) $(H4)
	g++ $(CXXFLAGS) -D_GLIBCXX_USE_CXX11_ABI=0 -c -Wall ../../alignment/Graph.cc

Edge.o: ../../alignment/Edge.cc $(H2) $(H3)
	g++ $(CXXFLAGS) -D_GLIBCXX_USE_CXX11_ABI=0 -c -Wall ../../alignment/Edge.cc

Node.o: ../../alignment/Node.cc $(H3)
	g++ $(CXXFLAGS) -D_GLIBCXX_USE_CXX11_ABI=0 -c -Wall ../../alignment/Node.cc

clean:
	rm -f *.o TestDataset net.pt
