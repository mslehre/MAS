linreg: linreg.cpp
	g++ linreg.cpp -o linreg -I ../libtorch/include/torch/csrc/api/include -I ../libtorch/include/ -L ../libtorch/lib/ \
	-l benchmark -l benchmark_main -l c10d -l Caffe2_perfkernels_avx2 -l Caffe2_perfkernels_avx -l caffe2_protos -l clog -l cpuinfo -l cpuinfo_internals -l foxi_loader -l gloo -l gloo_builder -l gmock -l gmock_main -l gtest -l gtest_main -l mkldnn -l nnpack -l nnpack_reference_layers -l onnx -l onnxifi_loader -l onnx_proto -l protobuf -l protobuf-lite -l protoc -l pthreadpool -l qnnpack -l THD -l c10 -l caffe2_detectron_ops -l caffe2_module_test_dynamic -l caffe2 -l foxi_dummy -l foxi -l onnxifi_dummy -l onnxifi -l torch \
	-std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -lpthread

clean:
	rm -f *.o linreg net.pt
