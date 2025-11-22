#!/bin/bash

# Output CSV file
CSV_FILE="benchmark_results.csv"
# echo "Scenario,Run,Time" > "$CSV_FILE"

# Function to run a benchmark scenario
run_scenario() {
    local scenario_name="$1"
    local cmake_opts="$2"
    local run_args="$3"
    local timeout_sec="$4"

    echo "----------------------------------------------------------------"
    echo "Starting Scenario: $scenario_name"
    echo "CMake Options: $cmake_opts"
    echo "Run Args: $run_args"
    
    # Configure and Build
    if [[ "$scenario_name" == "Debug" ]]; then
        cmake -B build -DCMAKE_BUILD_TYPE=Debug $cmake_opts > /dev/null
    else
        cmake -B build -DCMAKE_BUILD_TYPE=Release $cmake_opts > /dev/null
    fi
    cmake --build build --config Release > /dev/null # Config is ignored by Makefiles but good for multi-config gens

    # Run 3 times
    for i in {1..3}; do
        echo -n "  Run $i... "
        
        # Prepare command
        CMD="./build/rayborn $run_args"
        
        # Run with timeout if specified
        if [[ -n "$timeout_sec" ]]; then
            # Using perl for portable timeout on Mac/Linux
            START_TIME=$(date +%s.%N)
            OUTPUT=$(perl -e 'alarm shift; exec @ARGV' "$timeout_sec" $CMD 2>&1)
            EXIT_CODE=$?
            END_TIME=$(date +%s.%N)
            
            if [[ $EXIT_CODE -ne 0 ]]; then
                if [[ $EXIT_CODE -eq 142 ]]; then # 142 is typical SIGALRM exit
                     echo "TIMEOUT (> ${timeout_sec}s)"
                     echo "$scenario_name,$i,TIMEOUT" >> "$CSV_FILE"
                     echo "  Stopping repetitions for $scenario_name due to timeout."
                     break
                else
                     # Check if it was actually a timeout (perl alarm kills with SIGALRM)
                     # Sometimes perl returns different codes. 
                     # Let's rely on the output or time.
                     # But actually, if it timed out, we might not get the "Rendering finished" line.
                     echo "FAILED (Exit code $EXIT_CODE)"
                     echo "$scenario_name,$i,FAILED" >> "$CSV_FILE"
                     break
                fi
            fi
        else
            OUTPUT=$($CMD 2>&1)
        fi

        # Extract time
        # Expected output format: "Rendering finished : 53.371380 s"
        TIME_TAKEN=$(echo "$OUTPUT" | grep "Rendering finished" | awk '{print $4}')
        
        if [[ -z "$TIME_TAKEN" ]]; then
             # If we used timeout and it killed it, we won't have this line.
             # If we didn't use timeout, something went wrong.
             echo "ERROR: Could not parse time."
             echo "$scenario_name,$i,ERROR" >> "$CSV_FILE"
        else
             echo "${TIME_TAKEN}s"
             echo "$scenario_name,$i,$TIME_TAKEN" >> "$CSV_FILE"
        fi
    done
}

# 1. Multithreading Only
# run_scenario "Multithreading Only" "-DUSE_MATH_OPTIMIZATIONS=OFF" "--no-bvh" ""

# 2. BVH Only
run_scenario "BVH Only" "-DUSE_MATH_OPTIMIZATIONS=OFF" "--no-mt" ""

# 3. No Optimizations (Baseline)
run_scenario "Baseline" "-DUSE_MATH_OPTIMIZATIONS=OFF" "--no-bvh --no-mt" ""

# 4. Minor Optimizations
run_scenario "Minor Optimizations" "-DUSE_MATH_OPTIMIZATIONS=ON" "--no-bvh --no-mt" ""

# 5. All Optimizations
run_scenario "All Optimizations" "-DUSE_MATH_OPTIMIZATIONS=ON" "" ""

# 6. Debug Mode (Timeout 300s = 5m)
# Note: Debug build might be very slow.
run_scenario "Debug" "-DUSE_MATH_OPTIMIZATIONS=OFF" "--no-bvh --no-mt" "300"

echo "All benchmarks completed. Results saved to $CSV_FILE"
