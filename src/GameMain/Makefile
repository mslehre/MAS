include ../common.mk

CC = g++
OBJ = gameMain.o Button.o Graph.o Node.o Edge.o Gamemaster.o sequence.o State.o generator.o colorlist.o colormap.o \
    GraphRenderer.o ArrowShape.o FuncArrowShape.o Slider.o TrainingSet.o RLDataset.o
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
HEADER15 = Gamemaster.h
HEADER16 = ../ML/pytorch/RLDataset.h
torchOpt1 = -l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gloo_builder -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l THD -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l caffe2 -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch -lpthread
torchOpt2 = -D_GLIBCXX_USE_CXX11_ABI=0
torchOpt3 = -I ../ML/pytorch/libtorch/include/torch/csrc/api/include -I ../ML/pytorch/libtorch/include/ -L ../ML/pytorch/libtorch/lib/


all: game_main

game_main: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) -o $@ -lsfml-graphics -lsfml-window -lsfml-system $(torchOpt1) $(torchOpt2) $(torchOpt3)

gameMain.o: gameMain.cc $(HEADER10) $(HEADER13) $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt1) $(torchOpt2) $(torchOpt3)

Graph.o: ../alignment/Graph.cc $(HEADER1) $(HEADER2) $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

Node.o: ../alignment/Node.cc $(HEADER2)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

Edge.o: ../alignment/Edge.cc $(HEADER3)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

State.o: ../alignment/State.cc $(HEADER4)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2) $(torchOpt3)

Agent.o: ../ML/SimpleAgent/Agent.cc ../ML/SimpleAgent/Agent.h
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/SimpleAgent/Agent.cc $(torchOpt1) $(torchOpt2) $(torchOpt3)

TrainingSet.o: ../ML/pytorch/TrainingSet.cc ../ML/pytorch/TrainingSet.h
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/TrainingSet.cc $(torchOpt1) $(torchOpt2) $(torchOpt3)

RLDataset.o: ../ML/pytorch/RLDataset.cc ../ML/pytorch/RLDataset.cc
	g++ $(CXXFLAGS) $(torchOpt2) -c ../ML/pytorch/RLDataset.cc $(torchOpt1) $(torchOpt2) $(torchOpt3)

Button.o: ../visualization/Button.cc $(HEADER1) $(HEADER13)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

sequence.o: ../SequenceSimulation/sequence.cc $(HEADER6)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

generator.o: ../SequenceSimulation/generator.cc $(HEADER7)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

colormap.o: ../visualization/colormap.cc $(HEADER9)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

Gamemaster.o: Gamemaster.cc $(HEADER1) $(HEADER4) $(HEADER5) $(HEADER6) $(HEADER8) $(HEADER9) $(HEADER15)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2) $(torchOpt3)

colorlist.o: ../visualization/colorlist.cc $(HEADER8)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

GraphRenderer.o: ../visualization/GraphRenderer.cc $(HEADER1) $(HEADER10) $(HEADER11) $(HEADER13) $(HEADER15) 
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt1) $(torchOpt2) $(torchOpt3)

ArrowShape.o: ../visualization/ArrowShape.cc $(HEADER11)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

FuncArrowShape.o: ../visualization/FuncArrowShape.cc $(HEADER11) $(HEADER12)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

Slider.o: ../visualization/Slider.cc $(HEADER14)
	$(CC) -c $(CXXFLAGS) $< -o $@ $(torchOpt2)

clean:
	rm -f *.o game_main
