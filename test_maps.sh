#!/bin/bash

# Dynamically determine the script's directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Paths
CUB3D_EXEC="$SCRIPT_DIR/cub3D"
MAPS_DIR="$SCRIPT_DIR/maps"
GOOD_MAPS_DIR="$MAPS_DIR/good"
BAD_MAPS_DIR="$MAPS_DIR/bad"

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# Function to test maps
test_maps() {
    local dir=$1
    local expected=$2
    local result
    local map_name

    echo -e "${YELLOW}Testing maps in $dir (Expected: $expected)...${RESET}"

    for map in "$dir"/*.cub; do
        map_name=$(basename "$map")
        echo -n "Testing $map_name... "

        # Run the project with the map and capture output
        $CUB3D_EXEC "$map" > /dev/null 2>&1
        result=$?

        if [[ $expected == "success" && $result -eq 0 ]]; then
            echo -e "${GREEN}PASSED${RESET}"
        elif [[ $expected == "error" && $result -ne 0 ]]; then
            echo -e "${GREEN}PASSED${RESET}"
        else
            echo -e "${RED}FAILED${RESET}"
        fi

        # Check for memory leaks or segmentation faults
        echo -n "  Checking for memory leaks... "
        ASAN_OUTPUT=$($CUB3D_EXEC "$map" 2>&1)
        if echo "$ASAN_OUTPUT" | grep -q "ERROR"; then
            echo -e "${RED}Memory leaks or errors detected!${RESET}"
            echo "$ASAN_OUTPUT" | grep "ERROR" | sed 's/^/    /'
        else
            echo -e "${GREEN}No memory leaks detected.${RESET}"
        fi
    done
}

# Test good maps (should succeed)
if [[ -d $GOOD_MAPS_DIR ]]; then
    test_maps "$GOOD_MAPS_DIR" "success"
else
    echo -e "${RED}Good maps directory not found: $GOOD_MAPS_DIR${RESET}"
fi

# Test bad maps (should fail)
if [[ -d $BAD_MAPS_DIR ]]; then
    test_maps "$BAD_MAPS_DIR" "error"
else
    echo -e "${RED}Bad maps directory not found: $BAD_MAPS_DIR${RESET}"
fi
