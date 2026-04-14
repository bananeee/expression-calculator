#!/bin/bash
# Smoke test: send N sequential requests and verify each gets a response.
# For C10K (hold 10,000 connections open simultaneously), use:
#   python3 scripts/concurrent_connections_test.py --port <PORT>
HOST=${1:-127.0.0.1}
PORT=${2:-8080}
N=${3:-10000}

passed=0
failed=0

for i in $(seq 1 "$N"); do
    expr=$(./build/generator --count 1 --depth 2 --size 1)
    response=$(echo "$expr" | nc -q1 "$HOST" "$PORT" 2>/dev/null)
    if [ -n "$response" ]; then
        passed=$((passed + 1))
    else
        echo "FAIL [$i]: no response for: $expr" >&2
        failed=$((failed + 1))
    fi
done

echo "$passed/$N requests got a response, $failed failed"
