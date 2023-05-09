#!/bin/bash

# Prompt user for PID input
read -p "Enter PID: " pid

# Run `leaks` command every 1 second
while true; do
    leaks $pid
    sleep 0.1
done
