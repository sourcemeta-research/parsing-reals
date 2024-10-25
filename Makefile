PYTHON = python3

all: .always
	$(PYTHON) benchmark_json.py 1e3.json 1>/dev/null

.always:
