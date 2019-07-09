include ../common.mk

CC = g++
OBJ = gameMain.o Button.o Graph.o Node.o Edge.o Gamemaster.o sequence.o State.o generator.o colorlist.o colormap.o \
    GraphRenderer.o ArrowShape.o FuncArrowShape.o Slider.o Policy.o valueMLmodel.o Agent.o TrainingSet.o RLDataset.o

HEADER1 = ../alignment/Graph.h
HEADER2 = ../alignment/Node.h
HEADER3 = ../alignment/Edge.h
HEADER4 = ../alignment/State.h
HEADER5 = ../alignment/DrawNode.h
HEADER6 = ../SequenceSimulation/sequence.h
HEADER7 = ../SequenceSimulation/generator.h
HEADER8 = ../visualization/colormap.h
HEADER9 = ../visualization/colorlist.h
HEADER10 = ../visualization/GraphRenderer.h
HEADER11 = ../visualization/ArrowShape.h
HEADER12 = ../visualization/FuncArrowShape.h
HEADER13 = ../visualization/Button.h
HEADER14 = ../visualization/Slider.h
HEADER16 = ../visualization/scrollbar.h
HEADER15 = Gamemaster.h
H1 = ../alignment/Graph.h
H2 = ../alignment/Edge.h
H3 = ../alignment/Node.h
H4 = ../alignment/State.h
H5 = ../ML/SimpleAgent/Episode.h
H6 = ../ML/SimpleAgent/Agent.h
H9 = ../ML/pytorch/valueMLmodel.h
H10 = ../ML/pytorch/Policy.h
H11 = ../ML/pytorch/LinearNet.h
H12 = ../ML/pytorch/RLDataset.h
H13 = ../ML/pytorch/TrainingSet.h
torchOpt1 = -l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -lcaffe2 -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch -lpthread
torchOpt2 = -D_GLIBCXX_USE_CXX11_ABI=0

all: game_main

game_main: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ $(torchOpt1) $(torchOpt2)

gameMain.o: gameMain.cc $(HEADER10) $(HEADER13) $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@ -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/

Graph.o: ../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

Node.o: ../alignment/Node.cc $(HEADER2)
	$(CC) -c $(CXXFLAGS) $< -o $@

Edge.o: ../alignment/Edge.cc $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@

State.o: ../alignment/State.cc $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@

Button.o: ../visualization/Button.cc $(HEADER1) $(HEADER13)
	$(CC) -c $(CXXFLAGS) $< -o $@

sequence.o: ../SequenceSimulation/sequence.cc $(HEADER6)
	$(CC) -c $(CXXFLAGS) $< -o $@

generator.o: ../SequenceSimulation/generator.cc $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@

colormap.o: ../visualization/colormap.cc $(HEADER9)
	$(CC) -c $(CXXFLAGS) $< -o $@

Gamemaster.o: Gamemaster.cc $(HEADER1) $(HEADER4) $(HEADER5) $(HEADER6) $(HEADER8) $(HEADER9) $(HEADER15)
	$(CC) -c $(CXXFLAGS) $< -o $@ -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/

colorlist.o: ../visualization/colorlist.cc $(HEADER8)
	$(CC) -c $(CXXFLAGS) $< -o $@

GraphRenderer.o: ../visualization/GraphRenderer.cc $(HEADER1) $(HEADER10) $(HEADER11) $(HEADER13) $(HEADER15)
	$(CC) -c $(CXXFLAGS) $< -o $@ -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/

ArrowShape.o: ../visualization/ArrowShape.cc $(HEADER11)
	$(CC) -c $(CXXFLAGS) $< -o $@

FuncArrowShape.o: ../visualization/FuncArrowShape.cc $(HEADER11) $(HEADER12)
	$(CC) -c $(CXXFLAGS) $< -o $@

Slider.o: ../visualization/Slider.cc $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@

scrollbar.o: ../visualization/scrollbar.cc $(HEADER16)
	$(CC) -c $(CXXFLAGS) $< -o $@

Policy.o: ../ML/pytorch/Policy.cc $(H9) $(H4)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/Policy.cc -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ \

valueMLmodel.o: ../ML/pytorch/valueMLmodel.cc $(H11) $(H12)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/valueMLmodel.cc -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ \

Agent.o: ../ML/SimpleAgent/Agent.cc $(H6)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/SimpleAgent/Agent.cc -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ \

RLDataset.o: ../ML/pytorch/RLDataset.cc $(H12)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/RLDataset.cc -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ \

TrainingSet.o: ../ML/pytorch/TrainingSet.cc $(H13)
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/TrainingSet.cc -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/ \

clean:
	rm -f *.o game_main
