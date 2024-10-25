#!/usr/bin/env python3
# Save this as json_timer.py
import json
import sys
import time
from json.decoder import JSONDecodeError

def measure_json_operations(filepath):
    """
    Reads a JSON file, measures parsing and stringifying operations in microseconds,
    and prints the stringified JSON to stdout.
    
    Args:
        filepath (str): Path to the JSON file
    """
    try:
        # Read the file content
        with open(filepath, 'r') as file:
            content = file.read()
        
        # Measure JSON parsing
        parse_start = time.perf_counter()
        parsed_json = json.loads(content)
        parse_end = time.perf_counter()
        parse_time = (parse_end - parse_start) * 1_000_000  # Convert to microseconds
        
        # Measure JSON stringifying
        stringify_start = time.perf_counter()
        json_string = json.dumps(parsed_json)
        stringify_end = time.perf_counter()
        stringify_time = (stringify_end - stringify_start) * 1_000_000  # Convert to microseconds
        
        # Print timing information to stderr
        print(f"Parse time: {parse_time:.2f}µs", file=sys.stderr)
        print(f"Stringify time: {stringify_time:.2f}µs", file=sys.stderr)
        
        # Print stringified JSON to stdout
        print(json_string)
        
    except FileNotFoundError:
        print(f"Error: File '{filepath}' not found", file=sys.stderr)
        sys.exit(1)
    except JSONDecodeError as e:
        print(f"Error: Invalid JSON in file: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python json_timer.py <json_file>", file=sys.stderr)
        sys.exit(1)
    
    measure_json_operations(sys.argv[1])
