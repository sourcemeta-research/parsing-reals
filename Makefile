PYTHON = python3
CMAKE = cmake

all: .always
	$(CMAKE) -S . -B ./build -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=OFF
	$(CMAKE) --build ./build --config Release --parallel 4
	$(PYTHON) benchmark_json.py 1e3.json 1>/dev/null
	./build/benchmark_jsontoolkit 1e3.json 1>/dev/null
	./build/benchmark_simdjson 1e3.json 1>/dev/null

.always:
